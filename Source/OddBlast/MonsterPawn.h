// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MonsterPawn.generated.h"

class UHealthComponent;

UCLASS()
class ODDBLAST_API AMonsterPawn : public APawn
{
	GENERATED_BODY()

public:
	AMonsterPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Attack();

	void ResetCanAttack();

	void ApplySlow(float Value, float Duration);

	void ApplyBoop(float Value, float Duration);

	void ResetWalkSpeed();

	UFUNCTION(BlueprintPure)
	UHealthComponent* GetHealthComponent() const;

	UFUNCTION(BlueprintPure)
	bool CanAttack() const;

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USkeletalMeshComponent * MeshComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UArrowComponent* ArrowComponent;
	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	UPROPERTY(EditAnywhere)
	float MeleeRange = 200.f;

	UPROPERTY(EditAnywhere)
	float MeleeRadius = 50.f;

	float DefaultWalkSpeed = 300.f;

	bool IsAttacking;
};
