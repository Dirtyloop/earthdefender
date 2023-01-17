#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Bullet.h"
#include "Defender_Player_Controller.generated.h"

UCLASS()
class EARTHDEFENDERCPP_API ADefender_Player_Controller : public APlayerController
{
	GENERATED_BODY()

		ADefender_Player_Controller();
	
	UFUNCTION()
		virtual void SetupInputComponent() override;

protected:

	virtual void BeginPlay() override;
	void MoveCircular(float AxisValue);

	UFUNCTION()
	void Shoot();
};
