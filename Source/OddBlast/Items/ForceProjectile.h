// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Items/Projectile.h"
#include "ForceProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ODDBLAST_API AForceProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	float Strength;
};
