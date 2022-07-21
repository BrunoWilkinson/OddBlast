// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/StunProjectile.h"
#include "../Pawns/MonsterPawn.h"

void AStunProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	AMonsterPawn* MonsterPawn = Cast<AMonsterPawn>(OtherActor);
	if (MonsterPawn != nullptr)
	{
		MonsterPawn->ApplyStun(Duration);
	}
}
