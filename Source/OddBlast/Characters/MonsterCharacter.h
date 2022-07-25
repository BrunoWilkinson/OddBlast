// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MonsterCharacter.generated.h"

class UHealthComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class UArrowComponent;

UCLASS()
class ODDBLAST_API AMonsterCharacter : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovementComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent;

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

	void ResetCanAttack();

	void ApplyDamage(float Value);

	void ApplySlow(float Value, float Duration);

	void ApplyForce(float Value, FVector Velocity);

	void ApplyStun(float Duration);

	void ApplyPoison(float Value, float Duration, float DamageInterval);

	void ResetWalkSpeed();

	UFUNCTION(BlueprintPure)
	UHealthComponent* GetHealthComponent() const { return HealthComponent; };

	UFUNCTION(BlueprintPure)
	bool CanAttack() const;

private:
	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	UPROPERTY(EditAnywhere)
	float MeleeRange = 200.f;

	UPROPERTY(EditAnywhere)
	float MeleeRadius = 50.f;

	UPROPERTY(EditAnywhere)
	float MinWalkSpeed = 50.f;

	float DefaultSpeed;

	bool IsAttacking;
};
