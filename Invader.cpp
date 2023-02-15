// Copyright Dirtyloop. All Rights Reserved.

#include "Invader.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"


AInvader::AInvader()
{
	PrimaryActorTick.bCanEverTick = true;

	InvaderName = "Invader";

	SM_Invader = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	SM_Invader->SetEnableGravity(false);
	SM_Invader->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootComponent = SM_Invader;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 40.0f, 15.0f));

	Speed = 10.0f;
	RotationSpeed = 0.5;
	DefaultDamagePoints = 100;
}

void AInvader::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AInvader::OnOverlapBegin);
	CurrentAngle = StartAngle * DegToRad;
	AInvader::Tags.Add(FName("Invader"));
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AInvader::RandomizeShootTime, 0.1f, true);
	MuzzleOffset.Set(370.0f, 0.0f, -60.0f);
	MuzzleRotationPitch = 0.0f;
}

void AInvader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCircular();

}


void AInvader::MoveCircular()
{
	CurrentAngle += RotationSpeed * GetWorld()->GetDeltaSeconds();

	Angle = 57.3f * CurrentAngle;

	if ((CurrentAngle > 2 * PI + StartAngle * DegToRad) || (CurrentAngle < -2 * PI + StartAngle * DegToRad)) {
		CurrentAngle = StartAngle * DegToRad;
		Angle = StartAngle;
		Distance -= 25.0;
		RotationSpeed += 0.1;
	}

	float xPosition = EarthXLocation + cos(CurrentAngle - 1.57f) * Distance;
	float yPosition = EarthYLocation + sin(CurrentAngle - 1.57f) * Distance;

	SetActorLocationAndRotation(FVector(xPosition, yPosition, -110.0f), FRotator(0.0f, Angle, 0.0f));
	
}