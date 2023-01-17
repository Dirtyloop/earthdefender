#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Earth.generated.h"

class URotatingMovementComponent;
class USphereComponent;

UCLASS()
class EARTHDEFENDERCPP_API AEarth : public AActor
{
	GENERATED_BODY()
	
public:	
	AEarth();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SphereEarth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		URotatingMovementComponent* RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* Sphere_Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		int EarthLifePoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamagePoints")
		int defaultDamagePoints = 10;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	void DestroyEarth();

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void DamageEarth(int damagePoints);
};
