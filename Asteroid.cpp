// Copyright Dirtyloop. All Rights Reserved.

#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

	AsteroidName = "Asteroid";

	SM_Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid"));
	SM_Asteroid->SetEnableGravity(false);
	SM_Asteroid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Asteroid;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_Asteroid);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	Speed = 0.05f;
	Shift = 0.0f;
	DefaultDamagePoints = 25;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Move();
}