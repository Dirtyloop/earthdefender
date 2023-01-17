#pragma once

#include "CoreMinimal.h"
#include "Defender.h"
#include "GameFramework/Actor.h"
#include "AsteroidMedium.generated.h"

class URotatingMovementComponent;
class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AAsteroidMedium : public AActor
{
	GENERATED_BODY()

public:
	AAsteroidMedium();

	virtual void Move();

	FVector CurrentLocation;

	float speed;
	float shift;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_AsteroidMedium;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		float asteroidLifePoints = 100.0f;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	float defaultDamagePoints = 20.0f;

	void DestroyAsteroid();

public:
	virtual void Tick(float DeltaTime) override;

};

