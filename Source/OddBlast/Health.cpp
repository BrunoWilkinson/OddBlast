// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

UHealth::UHealth()
{
	Health = MaxHealth;
}

bool UHealth::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

void UHealth::ApplyDamage(float Value)
{
	Health -= FMath::Min(Health, Value);
}

