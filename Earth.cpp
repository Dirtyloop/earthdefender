#include "Earth.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Bullet.h"

AEarth::AEarth()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereEarth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Earth"));
	SphereEarth->SetEnableGravity(false);

	RootComponent = SphereEarth;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SphereEarth);
	RotatingMovement->RotationRate = FRotator(0.0f, 90.0f, 0.0f);

	Sphere_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	Sphere_Collision->InitSphereRadius(50.0f);
}

void AEarth::BeginPlay()
{
	Super::BeginPlay();

	Sphere_Collision->OnComponentBeginOverlap.AddDynamic(this, &AEarth::OnOverlapBegin);
}

void AEarth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEarth::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("Earth hitten!"));
		DamageEarth(defaultDamagePoints);
		OtherActor->Destroy();
	}
	if (OtherActor->ActorHasTag("Invader") || OtherActor->ActorHasTag("Invader2") || OtherActor->ActorHasTag("Asteroid")) {
		UE_LOG(LogTemp, Warning, TEXT("Earth fatally hitten!"));
		DamageEarth(100);
		OtherActor->Destroy();
	}
}

void AEarth::DamageEarth(int damagePoints)
{
	EarthLifePoints -= damagePoints;
	if (EarthLifePoints <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("You lose! Earth is destroyed!"));
		UE_LOG(LogTemp, Warning, TEXT("Earth Life Points: %d"), EarthLifePoints);
		//DestroyEarth();
	}
	else {
	
		UE_LOG(LogTemp, Warning, TEXT("Earth Life Points: %d"), EarthLifePoints);
	}
}

void AEarth::DestroyEarth()
{
	UE_LOG(LogTemp, Warning, TEXT("Earth destroyed!"));
	this->Destroy();
}