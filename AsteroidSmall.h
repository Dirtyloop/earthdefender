// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Public/AsteroidActor.h"
#include "AsteroidSmall.generated.h"

class URotatingMovementComponent;
class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AAsteroidSmall : public AAsteroidActor
{
	GENERATED_BODY()

public:
	AAsteroidSmall();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_AsteroidSmall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

public:
	virtual void Tick(float DeltaTime) override;

};