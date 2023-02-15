// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Public/InvaderActor.h"
#include "Invader.generated.h"


class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AInvader : public AInvaderActor
{
	GENERATED_BODY()
	
public:	
	AInvader();
	
	virtual void MoveCircular();

	virtual void Tick(float DeltaTime) override;

	FVector CurrentLocation;

	float Speed;

	FTimerHandle MemberTimerHandle;

protected:
	virtual void BeginPlay() override;

	float CurrentAngle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Invader;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float StartAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float Distance = 350.0f;

};
