// Fill out your copyright notice in the Description page of Project Settings.

#include "../Characters/MonsterCharacter.h"
#include "../Characters/PlayerCharacter.h"
#include "../Components/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetCharacterMovement() != nullptr)
	{
		DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
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
		Destroy();
	}
}

void AMonsterCharacter::ApplySlow(float Value, float Duration)
{
	if (GetCharacterMovement() != nullptr && GetCharacterMovement()->MaxWalkSpeed > MinWalkSpeed)
	{
		GetCharacterMovement()->MaxWalkSpeed -= FMath::Min(GetCharacterMovement()->MaxWalkSpeed, Value);
		FTimerHandle SlowDelayHandle;
		GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
	}
}

void AMonsterCharacter::ApplyForce(float Value, FVector Velocity)
{
	if (GetCapsuleComponent() != nullptr)
	{
		GetCapsuleComponent()->AddImpulseAtLocation(Velocity * Value, GetActorLocation());
	}
}

void AMonsterCharacter::ApplyStun(float Duration)
{
	if (GetCharacterMovement() != nullptr)
	{
		GetCharacterMovement()->StopMovementImmediately();
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
	if (GetCharacterMovement() != nullptr)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

bool AMonsterCharacter::CanAttack() const
{
	return false;
}
