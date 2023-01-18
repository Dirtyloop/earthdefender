// Copyright Dirtyloop. All Rights Reserved.

#include "AsteroidMedium.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroidMedium::AAsteroidMedium()
{
	PrimaryActorTick.bCanEverTick = true;

	AsteroidName = "AsteroidMedium";

	SM_Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMedium"));
	SM_Asteroid->SetEnableGravity(false);
	SM_Asteroid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Asteroid;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_Asteroid);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	Speed = 0.1f;
	Shift = 0.0f;
	DefaultDamagePoints = 50;
}

void AAsteroidMedium::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidMedium::OnOverlapBegin);
}

void AAsteroidMedium::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}