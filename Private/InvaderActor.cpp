// Copyright Dirtyloop. All Rights Reserved.


#include "InvaderActor.h"

AInvaderActor::AInvaderActor()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AInvaderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInvaderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInvaderActor::DestroyInvader()
{
	UE_LOG(LogTemp, Warning, TEXT("%s destroyed!"), *InvaderName);
	this->Destroy();
}

void AInvaderActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("%s hitten!"), *InvaderName);
		InvaderLifePoints -= DefaultDamagePoints;
		UE_LOG(LogTemp, Warning, TEXT("%s Life Points: %d"), *InvaderName, InvaderLifePoints);
		if (InvaderLifePoints <= 0) {
			DestroyInvader();
		}
		OtherActor->Destroy();
	}
}

void AInvaderActor::RandomizeShootTime()
{
	if (FMath::RandRange(0, RandomShootHigherBoundry) == 0) {
		Shoot();
	}
}

void AInvaderActor::Shoot()
{

}

