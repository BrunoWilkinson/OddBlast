// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UTP_PickUpComponent;
class UTP_WeaponComponent;

UCLASS()
class ODDBLAST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

public:
	UFUNCTION(BlueprintPure)
	UTP_PickUpComponent* GetPickUpComponent() const;

	UFUNCTION(BlueprintPure)
	UTP_WeaponComponent* GetWeaponComponent() const;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMeshComponent() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTP_PickUpComponent* PickUpComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTP_WeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USkeletalMeshComponent* MeshComponent;
};
