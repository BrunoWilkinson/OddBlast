// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "../BlackBoard/BTTask_RotateToPlayer.h"
#include "../Pawns/MonsterPawn.h"

UBTTask_RotateToPlayer::UBTTask_RotateToPlayer()
{
	NodeName = TEXT("Rotate to Player");
}

EBTNodeResult::Type UBTTask_RotateToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonsterPawn* AIPawn = Cast<AMonsterPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (Player == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FRotator CurrentRotation = AIPawn->GetActorRotation();
	FRotator PlayerRotation = Player->GetActorRotation();
	FRotator TargetRotation = CurrentRotation + PlayerRotation;
	float Speed = PlayerRotation.Euler().Length() / RotationDelay;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotation, TargetRotation, DeltaTime, Speed);

	AIPawn->SetActorRotation(NewRotation);

	return EBTNodeResult::Succeeded;
}
