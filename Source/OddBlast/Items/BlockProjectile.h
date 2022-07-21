// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Items/Projectile.h"
#include "BlockProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ODDBLAST_API ABlockProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	UPROPERTY(EditAnywhere, Category = "Projectile Properties")
	float Duration;
	
};
