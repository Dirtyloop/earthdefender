// Copyright Dirtyloop. All Rights Reserved.

#include "Invader2.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"

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

	speed = 10.0f;
	shift = 0.0f;
	deltaMove = 0.0f;
	RotationSpeed = 0.8;
	DefaultDamagePoints = 20;
}

void AInvader2::BeginPlay()
{
	Super::BeginPlay();
	
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AInvader2::OnOverlapBegin);
	CurrentAngle = StartAngle / 57.3f;
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
	shift = speed * GetWorld()->GetDeltaSeconds() * FMath::RandRange(0, 1);
	deltaMove += shift;
	if (deltaMove > 800) deltaMove = 0;
	if (deltaMove < 200 || deltaMove > 600) {
		CurrentLocation.X += shift;
	}
	else {
		CurrentLocation.X -= shift;
	}
	SetActorLocation(CurrentLocation);
}

void AInvader2::MoveSpiral()
{
	CurrentAngle += RotationSpeed * GetWorld()->GetDeltaSeconds();
	Angle = 57.3f * CurrentAngle;

	if ((CurrentAngle > 6.28f + StartAngle / 57.3f) || (CurrentAngle < -6.28f + StartAngle / 57.3f)) {
		CurrentAngle = StartAngle / 57.3f;
		Angle = StartAngle;
		
		RotationSpeed += 0.1;
	}
	Distance -= 0.2;

	float xPosition = EarthXLocation + cos(CurrentAngle - 1.57f) * Distance;
	float yPosition = EarthYLocation + sin(CurrentAngle - 1.57f) * Distance;

	SetActorLocationAndRotation(FVector(xPosition, yPosition, -110.0f), FRotator(0.0f, Angle, 0.0f));
}