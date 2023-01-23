// Copyright Dirtyloop. All Rights Reserved.

#include "AsteroidSmall.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroidSmall::AAsteroidSmall()
{
	PrimaryActorTick.bCanEverTick = true;

	AsteroidName = "AsteroidSmall";

	SM_Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidSmall"));
	SM_Asteroid->SetEnableGravity(false);
	SM_Asteroid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Asteroid;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_Asteroid);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	Speed = 0.2f;
	Shift = 0.0f;
	DefaultDamagePoints = 100;
}

void AAsteroidSmall::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidSmall::OnOverlapBegin);
}

void AAsteroidSmall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Move();
}