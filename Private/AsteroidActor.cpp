// Copyright Dirtyloop. All Rights Reserved.

#include "AsteroidActor.h"

AAsteroidActor::AAsteroidActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAsteroidActor::BeginPlay()
{
	Super::BeginPlay();

	AAsteroidActor::Tags.Add(FName("Asteroid"));
}

void AAsteroidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAsteroidActor::Move()
{
	CurrentLocation = this->GetActorLocation();
	Shift = Speed * GetWorld()->GetDeltaSeconds();

	CurrentLocation.X += Shift * (EarthXLocation - CurrentLocation.X);
	CurrentLocation.Y += Shift * (EarthYLocation - CurrentLocation.Y);

	SetActorLocation(CurrentLocation);
}

void AAsteroidActor::DestroyAsteroid()
{
	UE_LOG(LogTemp, Warning, TEXT("%s destroyed!"), *AsteroidName);
	this->Destroy();
}

void AAsteroidActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("%s hitten!"), *AsteroidName);
		AsteroidLifePoints -= DefaultDamagePoints;
		UE_LOG(LogTemp, Warning, TEXT("%s Life Points: %d"), *AsteroidName, AsteroidLifePoints);
		if (AsteroidLifePoints <= 0) {
			DestroyAsteroid();
		}
		OtherActor->Destroy();
	}
}