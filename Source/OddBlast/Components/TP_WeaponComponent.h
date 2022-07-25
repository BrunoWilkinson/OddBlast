// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TP_WeaponComponent.generated.h"

class APlayerCharacter;
class AProjectile;

UENUM()
enum EProjectileType
{
	Normal UMETA(DisplayName = "Normal"),
	Slow UMETA(DisplayName = "Slow"),
	Stun UMETA(DisplayName = "Stun"),
	Poison UMETA(DisplayName = "Poison"),
	Force UMETA(DisplayName = "Force"),
	Block UMETA(DisplayName = "Block"),
};

USTRUCT(BlueprintType)
struct FProjectileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AProjectile> Class;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TEnumAsByte<EProjectileType> Type;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODDBLAST_API UTP_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties */
	UTP_WeaponComponent();

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TArray<FProjectileInfo> ProjectileList;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	float FireRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ProjectileTypeInterval = 5.f;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(APlayerCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintPure)
	TEnumAsByte<EProjectileType> GetCurrentProjectileType() const { return CurrentProjectileType; }

	TEnumAsByte<EProjectileType> SetCurrentProjectileType(TEnumAsByte<EProjectileType> Type);

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = Projectile)
	bool DebugMode = false;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TEnumAsByte<EProjectileType> DebugType;

	void UpdateProjectileType();

	/** The Character holding this weapon*/
	APlayerCharacter* Character;

	TEnumAsByte<EProjectileType> CurrentProjectileType;

	bool CanFire = true;

	void ResetCanFire();
};
