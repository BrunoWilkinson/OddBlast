// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void AMonsterCharacter::ApplySlow(float SlowValue, float Duration)
{
	FTimerHandle SlowDelayHandle;
	if (MovementComponent != nullptr && MovementComponent->MaxWalkSpeed > 100)
	{
		MovementComponent->MaxWalkSpeed -= SlowValue;
		GetWorld()->GetTimerManager().SetTimer(SlowDelayHandle, this, &AMonsterCharacter::ResetWalkSpeed, Duration, false);
	}
}

void AMonsterCharacter::ApplyBoop(float BoopValue, float Duration)
{
	MovementComponent->JumpZVelocity = BoopValue;
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

