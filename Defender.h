#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Defender.generated.h"

class UFloatingPawnMovement;
class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API ADefender : public APawn
{
	GENERATED_BODY()

public:
	ADefender();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveCircular(float AxisValue);
	virtual void Shoot();
	float CenterPointX = 50.0f;
	float CenterPointY = 230.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		APawn* Defender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RotateAround")
		float RotationSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RotateAround", meta = (ClampMin = "0.0", ClampMax = "6.28", UIMin = "0.0", UIMax = "6.28"))
		float InitialRotationAngle = 4.71f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	UFUNCTION(BlueprintCallable)
		void Reset();

	UFUNCTION(BlueprintCallable)
		void AddDefenderPoints();

	UFUNCTION(BlueprintCallable)
		void DamageDefender(int damagePoints);

	UFUNCTION(BlueprintCallable)
		int GetDefenderLifePoints();

protected:

	virtual void BeginPlay() override;

	float CurrentAngle = 0.0f;
	float Angle = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_Defender;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UFloatingPawnMovement* FloatingMovement;


	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		int DefenderLifePoints = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Points")
		int DefenderPoints = 0;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);
	
};
