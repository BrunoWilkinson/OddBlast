// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "../Components/TP_PickUpComponent.h"
#include "../Components/TP_WeaponComponent.h"

AWeapon::AWeapon()
{
	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("PickUp Component"));
	PickUpComponent->SetupAttachment(RootComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(PickUpComponent);

	WeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>(TEXT("Weapon Component"));
}

UTP_PickUpComponent* AWeapon::GetPickUpComponent() const
{
	return PickUpComponent;
}

UTP_WeaponComponent* AWeapon::GetWeaponComponent() const
{
	return WeaponComponent;
}

USkeletalMeshComponent* AWeapon::GetMeshComponent() const
{
	return MeshComponent;
}
