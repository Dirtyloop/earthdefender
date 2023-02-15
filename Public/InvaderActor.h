// Copyright Dirtyloop. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Bullet.h"
#include "Math/UnrealMathUtility.h"
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

	UPROPERTY(VisibleAnywhere)
	float Angle = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float MuzzleRotationPitch = 0.0f;

	float M_PI = PI;

	float DegToRad = PI / 180.0f;

	float RadToDeg = 180.0f / PI;

	float NinetyDegreeInRadians = PI / 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString InvaderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifePoints")
		int InvaderLifePoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		int DefaultDamagePoints;



protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void DestroyInvader();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void RandomizeShootTime();

	UFUNCTION()
	void Shoot();
};
