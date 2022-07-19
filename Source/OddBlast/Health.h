// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ODDBLAST_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealth();

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void ApplyDamage(float Value);

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
