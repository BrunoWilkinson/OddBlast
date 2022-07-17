// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class ODDBLAST_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();

	void ResetCanAttack();

	void ApplySlow(float Value, float Duration);

	void ApplyBoop(float Value, float Duration);

	void ResetWalkSpeed();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	bool CanAttack() const;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	float DefaultWalkSpeed = 300.f;

	bool IsAttacking;

	class UCharacterMovementComponent* MovementComponent;
};
