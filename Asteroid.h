// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Public/AsteroidActor.h"
#include "Asteroid.generated.h"

class URotatingMovementComponent;
class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AAsteroid : public AAsteroidActor
{
	GENERATED_BODY()

public:
	AAsteroid();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Asteroid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

public:
	virtual void Tick(float DeltaTime) override;

};