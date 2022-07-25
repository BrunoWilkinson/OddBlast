// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Characters/MonsterCharacter.h"
#include "../Components/HealthComponent.h"

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr && PlayerPawn != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
	}
}

void AMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn != nullptr && GetBlackboardComponent() != nullptr)
	{
		GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
	}
}

bool AMonsterAIController::IsDead() const
{
	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(GetPawn());
	if (Monster != nullptr)
	{
		UHealthComponent* MonsterHealth = Monster->GetHealthComponent();
		if (MonsterHealth != nullptr)
		{
			return MonsterHealth->IsDead();
		}
	}
	return true;
}
