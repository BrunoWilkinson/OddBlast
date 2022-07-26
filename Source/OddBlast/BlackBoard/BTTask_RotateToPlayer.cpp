// Fill out your copyright notice in the Description page of Project Settings.

#include "../BlackBoard/BTTask_RotateToPlayer.h"
#include "../Characters/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

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

	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (Player == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector ToTarget = Player->GetActorLocation() - Monster->GetActorLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	float Speed = Player->GetActorRotation().Euler().Length() / RotationDelay;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	FRotator NewRotation = FMath::RInterpConstantTo(Monster->GetActorRotation(), LookAtRotation, DeltaTime, Speed);

	Monster->GetMeshComponent()->SetWorldRotation(NewRotation);

	return EBTNodeResult::Succeeded;
}
