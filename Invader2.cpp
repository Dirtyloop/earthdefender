// Copyright Dirtyloop. All Rights Reserved.

#include "Invader2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

AInvader2::AInvader2()
{
	PrimaryActorTick.bCanEverTick = true;

	InvaderName = "Invader2";

	SM_Invader = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	SM_Invader->SetEnableGravity(false);
	SM_Invader->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Invader;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	Speed = 10.0f;
	Shift = 0.0f;
	DeltaMove = 0.0f;
	RotationSpeed = 0.8;
	DefaultDamagePoints = 20;
}

void AInvader2::BeginPlay()
{
	Super::BeginPlay();
	
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AInvader2::OnOverlapBegin);
	CurrentAngle = StartAngle * DegToRad;
	AInvader2::Tags.Add(FName("Invader2"));
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AInvader2::RandomizeShootTime, 0.1f, true);

	MuzzleOffset.Set(400.0f, 0.0f, -50.0f);
	MuzzleRotationPitch = -10.0f;
}

void AInvader2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveSpiral();

}

void AInvader2::MoveHorizontal()
{
	CurrentLocation = this->GetActorLocation();
	Shift = Speed * GetWorld()->GetDeltaSeconds() * FMath::RandRange(0, 1);
	DeltaMove += Shift;
	if (DeltaMove > 800) DeltaMove = 0;
	if (DeltaMove < 200 || DeltaMove > 600) {
		CurrentLocation.X += Shift;
	}
	else {
		CurrentLocation.X -= Shift;
	}
	SetActorLocation(CurrentLocation);
}

void AInvader2::MoveSpiral()
{
	CurrentAngle += RotationSpeed * GetWorld()->GetDeltaSeconds();
	Angle = 57.3f * CurrentAngle;

	if ((CurrentAngle > 6.28f + StartAngle * DegToRad) || (CurrentAngle < -6.28f + StartAngle * DegToRad)) {
		CurrentAngle = StartAngle * DegToRad;
		Angle = StartAngle;
		
		RotationSpeed += 0.1;
	}
	Distance -= 0.2;

	float xPosition = EarthXLocation + cos(CurrentAngle - 1.57f) * Distance;
	float yPosition = EarthYLocation + sin(CurrentAngle - 1.57f) * Distance;

	SetActorLocationAndRotation(FVector(xPosition, yPosition, -110.0f), FRotator(0.0f, Angle, 0.0f));
}