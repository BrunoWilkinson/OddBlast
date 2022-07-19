// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterPawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "OddBlastCharacter.h"
#include "HealthComponent.h"

AMonsterPawn::AMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Compomemt"));
	MeshComponent->SetupAttachment(RootComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	ArrowComponent->SetupAttachment(RootComponent);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterPawn::Attack()
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
		AOddBlastCharacter* PlayerCharacter = Cast<AOddBlastCharacter>(HitResult.GetActor());
		if (PlayerCharacter != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, GetActorForwardVector(), nullptr);
			PlayerCharacter->TakeDamage(Damage, DamageEvent, GetController(), this);

			IsAttacking = true;
			FTimerHandle ResetAttackDelayHandle;
			GetWorld()->GetTimerManager().SetTimer(ResetAttackDelayHandle, this, &AMonsterPawn::ResetCanAttack, 2.0f, false);
		}
	}
}

void AMonsterPawn::ResetCanAttack()
{
	IsAttacking = false;
}

void AMonsterPawn::ApplySlow(float Value, float Duration)
{
	FTimerHandle SlowDelayHandle;
	// MovementComponent->MaxWalkSpeed -= Value;
	GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterPawn::ResetWalkSpeed, Duration, false);
}

void AMonsterPawn::ApplyBoop(float Value, float Duration)
{
	//MovementComponent->JumpZVelocity = Value;
	//Jump();
	// MovementComponent->MaxWalkSpeed = 0;
	FTimerHandle BoopDelayHandle;
	GetWorld()->GetTimerManager().SetTimer(BoopDelayHandle, this, &AMonsterPawn::ResetWalkSpeed, Duration, false);
}

void AMonsterPawn::ResetWalkSpeed()
{
}

UHealthComponent* AMonsterPawn::GetHealthComponent()
{
	return HealthComponent;
}

bool AMonsterPawn::CanAttack() const
{
	return false;
}
