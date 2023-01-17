#pragma once

#include "CoreMinimal.h"
#include "Defender.h"
#include "Public/Enemy.h"
#include "GameFramework/Actor.h"
#include "Invader2.generated.h"


class UBoxComponent;

UCLASS()
class EARTHDEFENDERCPP_API AInvader2 : public AActor
{
	GENERATED_BODY()

public:
	AInvader2();

	virtual void MoveHorizontal();
	virtual void MoveSpiral();
	virtual void Shoot();

	virtual void Tick(float DeltaTime) override;

	FVector CurrentLocation;

	float speed;
	float shift;
	float deltaMove;

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

	UFUNCTION()
		void RandomizeShootTime();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifePoints")
		float invaderLifePoints = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiralMovement")
		float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiralMovement")
		float StartAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpiralMovement")
		float Distance = 400.0f;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	int randomShootHigherBoundry = 100;
	float defaultDamagePoints = 20.0f;

	void DestroyInvader();


};
