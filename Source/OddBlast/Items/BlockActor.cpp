// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/BlockActor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlockActor::ABlockActor()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(BoxComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABlockActor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle DestroyDelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyDelayHandle, this, &ABlockActor::HandleDestroy, Duration, false);
}

void ABlockActor::HandleDestroy()
{
	Destroy();
}


