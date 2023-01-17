// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Defender.h"
#include "Public/Enemy.h"
#include "GameFramework/Actor.h"
#include "Invader.generated.h"


class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AInvader : public AEnemy
{
	GENERATED_BODY()
	
public:	
	AInvader();

	virtual void MoveCircular();
	virtual void Shoot();

	virtual void Tick(float DeltaTime) override;

	FVector CurrentLocation;

	float speed;

	FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ADefender* Defender;

protected:
	virtual void BeginPlay() override;

	float CurrentAngle = 0.0f;
	float Angle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Invader;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		float InvaderLifePoints = 100.0f;

	UFUNCTION()
		void RandomizeShootTime();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, 
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float StartAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float Distance = 350.0f;

	int randomShootHigherBoundry = 100;

	void DestroyInvader();


};
