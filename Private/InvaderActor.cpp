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
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(FRotator(0.0f, (Angle + 90.0f), 0.0f)).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = FRotator(0.0f, (Angle + 90.0f), 0.0f);
		MuzzleRotation.Pitch += MuzzleRotationPitch;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			ABullet* Bullet = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Bullet)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection(LaunchDirection);
			}
		}
	}
}