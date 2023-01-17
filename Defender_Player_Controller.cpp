#include "Defender_Player_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Defender.h"

ADefender_Player_Controller::ADefender_Player_Controller()
{
}

void ADefender_Player_Controller::BeginPlay()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);
}

void ADefender_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	EnableInput(this);

	InputComponent->BindAxis("MoveCircular", this, &ADefender_Player_Controller::MoveCircular);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ADefender_Player_Controller::Shoot);
}

void ADefender_Player_Controller::MoveCircular(float AxisValue)
{

	auto MyPawn = Cast<ADefender>(GetPawn());

	if (MyPawn) {
		MyPawn->MoveCircular(AxisValue);
	}

}

void ADefender_Player_Controller::Shoot()
{
	auto MyPawn = Cast<ADefender>(GetPawn());

	if (MyPawn) {
		MyPawn->Shoot();
	}
}
