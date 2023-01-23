// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvaderActor.generated.h"

UCLASS()
class EARTHDEFENDERCPP_API AInvaderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInvaderActor();

	UPROPERTY(VisibleAnywhere)
		int EarthXLocation = 50;

	UPROPERTY(VisibleAnywhere)
		int EarthYLocation = 230;

	UPROPERTY(VisibleAnywhere)
	int RandomShootHigherBoundry = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString InvaderName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifePoints")
		int InvaderLifePoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		int DefaultDamagePoints;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void DestroyInvader();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void RandomizeShootTime();

	UFUNCTION()
	virtual void Shoot();
};
