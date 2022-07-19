// Copyright Epic Games, Inc. All Rights Reserved.

#include "OddBlastProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MonsterPawn.h"

AOddBlastProjectile::AOddBlastProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AOddBlastProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = LifeSpan;
}

void AOddBlastProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AMonsterPawn* MonsterPawn = Cast<AMonsterPawn>(OtherActor);
		if (MonsterPawn != nullptr)
		{
			if (DamageProjectile)
			{
				AController* OwnerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (OwnerController != nullptr)
				{
					FVector ShotDirection;
					FVector PlayerViewPointLocation;
					FRotator PlayerViewPointRotation;
					OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
					ShotDirection = -PlayerViewPointRotation.Vector();

					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
					MonsterPawn->TakeDamage(Damage, DamageEvent, OwnerController, this);
				}
			}

			if (SlowProjectile)
			{
				MonsterPawn->ApplySlow(SlowSpeed, SlowDuration);
			}

			if (BoopProjectile)
			{
				MonsterPawn->ApplyBoop(BoopDistance, BoopDuration);
			}
		}

		Destroy();
	}
}