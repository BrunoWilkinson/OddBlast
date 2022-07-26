// Fill out your copyright notice in the Description page of Project Settings.

#include "../Characters/MonsterCharacter.h"
#include "../Characters/PlayerCharacter.h"
#include "../Components/HealthComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ArrowComponent->SetupAttachment(RootComponent);

	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Movement Component");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (FloatingPawnMovementComponent != nullptr)
	{
		DefaultSpeed = FloatingPawnMovementComponent->GetMaxSpeed();
	}
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterCharacter::Attack()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * MeleeRange;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(MeleeRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit && HitResult.GetActor() != nullptr)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(HitResult.GetActor());
		if (PlayerCharacter != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, GetActorForwardVector(), nullptr);
			PlayerCharacter->TakeDamage(Damage, DamageEvent, GetController(), this);

			IsAttacking = true;
			FTimerHandle ResetAttackDelayHandle;
			GetWorld()->GetTimerManager().SetTimer(ResetAttackDelayHandle, this, &AMonsterCharacter::ResetCanAttack, 2.0f, false);
		}
	}
}

void AMonsterCharacter::ResetCanAttack()
{
	IsAttacking = false;
}

void AMonsterCharacter::ApplyDamage(float Value)
{
	HealthComponent->ApplyDamage(Value);
	if (HealthComponent->IsDead())
	{
		DetachFromControllerPendingDestroy();
		FTimerHandle DestroyDelayHandle;
		GetWorld()->GetTimerManager().SetTimer(DestroyDelayHandle, this, &AMonsterCharacter::HandleDestroy, 3.0f, false);
	}
}

void AMonsterCharacter::ApplySlow(float Value, float Duration)
{
	if (FloatingPawnMovementComponent != nullptr && FloatingPawnMovementComponent->GetMaxSpeed() > MinWalkSpeed)
	{
		FloatingPawnMovementComponent->MaxSpeed -= FMath::Min(FloatingPawnMovementComponent->GetMaxSpeed(), Value);
		FTimerHandle SlowDelayHandle;
		GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
	}
}

void AMonsterCharacter::ApplyForce(float Value, FVector Velocity)
{
	if (CapsuleComponent != nullptr)
	{
		CapsuleComponent->AddImpulseAtLocation(Velocity * Value, GetActorLocation());
	}
}

void AMonsterCharacter::ApplyStun(float Duration)
{
	if (FloatingPawnMovementComponent != nullptr)
	{
		FloatingPawnMovementComponent->MaxSpeed = 0.f;
		FTimerHandle StunDelayHandle;
		GetWorld()->GetTimerManager().SetTimer(StunDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
	}
}

void AMonsterCharacter::ApplyPoison(float Value, float Duration, float DamageInterval)
{
	int32 Counter = 0;
	while (Duration > Counter)
	{
		FTimerHandle PoisonDelayHandle;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AMonsterCharacter::ApplyDamage, Value);
		GetWorld()->GetTimerManager().SetTimer(PoisonDelayHandle, TimerDelegate, DamageInterval + Counter, false);
		Counter++;
	}
}

void AMonsterCharacter::ResetWalkSpeed()
{
	if (FloatingPawnMovementComponent != nullptr)
	{
		FloatingPawnMovementComponent->MaxSpeed = DefaultSpeed;
	}
}

bool AMonsterCharacter::CanAttack() const
{
	return false;
}

void AMonsterCharacter::HandleDestroy()
{
	Destroy();
}
