#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

class URotatingMovementComponent;
class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AAsteroid : public AActor
{
	GENERATED_BODY()

public:
	AAsteroid();

	virtual void Move();

	FVector CurrentLocation;

	float speed;
	float shift;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Asteroid;

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

