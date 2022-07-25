// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/BlockProjectile.h"
#include "../Items/BlockActor.h"
#include "../Characters/MonsterCharacter.h"

void ABlockProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	UWorld* World = GetWorld();
	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(OtherActor);

	if (World != nullptr && BlockActorClass != nullptr)
	{
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		World->SpawnActor<ABlockActor>(BlockActorClass, Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), ActorSpawnParams);
	}
}
