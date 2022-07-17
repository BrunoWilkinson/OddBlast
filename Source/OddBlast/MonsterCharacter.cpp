// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	MovementComponent = this->GetCharacterMovement();
	if (MovementComponent != nullptr)
	{
		DefaultWalkSpeed = MovementComponent->MaxWalkSpeed;
	}
}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	if (IsDead())
	{
		Destroy();
	}

	return DamageToApply;
}

void AMonsterCharacter::ApplySlow(float Value, float Duration)
{
	FTimerHandle SlowDelayHandle;
	if (MovementComponent != nullptr && MovementComponent->MaxWalkSpeed > 100)
	{
		MovementComponent->MaxWalkSpeed -= Value;
		GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
	}
}

void AMonsterCharacter::ApplyBoop(float Value, float Duration)
{
	MovementComponent->JumpZVelocity = Value;
	Jump();
	MovementComponent->MaxWalkSpeed = 0;
	FTimerHandle SlowDelayHandle;
	GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
}

void AMonsterCharacter::ResetWalkSpeed()
{
	if (MovementComponent != nullptr)
	{
		MovementComponent->MaxWalkSpeed = DefaultWalkSpeed;
	}
}

bool AMonsterCharacter::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

