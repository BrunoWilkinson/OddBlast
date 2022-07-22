// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/BlockProjectile.h"
#include "../Items/BlockActor.h"
#include "../Pawns//MonsterPawn.h"

void ABlockProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	UWorld* World = GetWorld();
	AMonsterPawn* Monster = Cast<AMonsterPawn>(OtherActor);

	if (World != nullptr && BlockActorClass != nullptr && Monster != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		World->SpawnActor<ABlockActor>(BlockActorClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), ActorSpawnParams);
	}
}
