// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleWeapon.h"
#include "TP_PickUpComponent.h"
#include "TP_WeaponComponent.h"

ARifleWeapon::ARifleWeapon()
{
	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUp Component"));
	PickUpComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(PickUpComponent);

	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("Weapon Component"));
}

UTP_PickUpComponent* ARifleWeapon::GetPickUpComponent() const
{
	return PickUpComponent;
}

UTP_WeaponComponent* ARifleWeapon::GetWeaponComponent() const
{
	return WeaponComponent;
}

USkeletalMeshComponent* ARifleWeapon::GetMeshComponent() const
{
	return MeshComponent;
}
