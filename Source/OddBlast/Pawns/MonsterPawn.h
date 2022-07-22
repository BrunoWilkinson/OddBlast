// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MonsterPawn.generated.h"

class UHealthComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class UArrowComponent;

UCLASS()
class ODDBLAST_API AMonsterPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent;

public:
	AMonsterPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Attack();

	void ResetCanAttack();

	void ApplyDamage(float Value);

	void ApplySlow(float Value, float Duration);

	void ApplyForce(float Value, FVector Velocity);

	void ApplyStun(float Duration);

	void ApplyPoison(float Value, float Duration);

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

	float DefaultWalkSpeed;

	bool IsAttacking;
};
