// Fill out your copyright notice in the Description page of Project Settings.


#include "../Items/PoisonProjectile.h"
#include "../Characters/MonsterCharacter.h"

void APoisonProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	AMonsterCharacter* Monster = Cast<AMonsterCharacter>(OtherActor);
	if (Monster != nullptr)
	{
		Monster->ApplyPoison(Damage, Duration, DamageInterval);
	}
}
