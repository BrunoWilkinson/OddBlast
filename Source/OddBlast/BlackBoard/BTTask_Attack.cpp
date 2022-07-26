// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "../Characters/MonsterCharacter.h"
#include "../Characters/PlayerCharacter.h"

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

	FHitResult HitResult;
	FVector Start = Monster->GetActorLocation();
	FVector End = Start + Monster->GetActorForwardVector() * MeleeRange;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(MeleeRadius);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit && HitResult.GetActor() != nullptr)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor());
		if (Player != nullptr)
		{
			Monster->Attack();
		}
	}

	return EBTNodeResult::Succeeded;
}
