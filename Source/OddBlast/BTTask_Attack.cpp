// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "MonsterCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AMonsterCharacter* AIPawn = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AIPawn->Attack();

	return EBTNodeResult::Succeeded;
}
