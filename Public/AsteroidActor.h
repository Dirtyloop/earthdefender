// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidActor.generated.h"

UCLASS()
class EARTHDEFENDERCPP_API AAsteroidActor : public AActor
{
	GENERATED_BODY()

public:
	AAsteroidActor();

	UPROPERTY(VisibleAnywhere)
	int EarthXLocation = 50;

	UPROPERTY(VisibleAnywhere)
	int EarthYLocation = 230;

	UPROPERTY()
	FVector CurrentLocation;

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float Shift;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString AsteroidName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifePoints")
	int AsteroidLifePoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
	int DefaultDamagePoints;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Move();

	UFUNCTION()
	void DestroyAsteroid();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
		const FHitResult& SweepResult);
};
