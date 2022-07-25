// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "../Characters/MonsterCharacter.h"

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

	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Monster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Monster->Attack();

	return EBTNodeResult::Succeeded;
}
