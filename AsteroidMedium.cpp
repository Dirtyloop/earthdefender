#include "AsteroidMedium.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroidMedium::AAsteroidMedium()
{
	PrimaryActorTick.bCanEverTick = true;

	SM_AsteroidMedium = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMedium"));
	SM_AsteroidMedium->SetEnableGravity(false);
	SM_AsteroidMedium->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_AsteroidMedium;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_AsteroidMedium);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	speed = 0.1f;
	shift = 0.0f;
}

void AAsteroidMedium::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidMedium::OnOverlapBegin);
	AAsteroidMedium::Tags.Add(FName("Asteroid"));
}

void AAsteroidMedium::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AAsteroidMedium::Move()
{
	CurrentLocation = this->GetActorLocation();
	shift = speed * GetWorld()->GetDeltaSeconds();
	//speed += 0.01f;

	CurrentLocation.X += shift * (50 - CurrentLocation.X);
	CurrentLocation.Y += shift * (230 - CurrentLocation.Y);

	SetActorLocation(CurrentLocation);
}


void AAsteroidMedium::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("AsteroidMedium hitten!"));
		//asteroidLifePoints -= defaultDamagePoints;
		asteroidLifePoints = 0;
		UE_LOG(LogTemp, Warning, TEXT("AsteroidMedium Life Points: %g"), asteroidLifePoints);
		if (asteroidLifePoints <= 0) {
			DestroyAsteroid();
		}
		OtherActor->Destroy();
	}
}

void AAsteroidMedium::DestroyAsteroid()
{
	UE_LOG(LogTemp, Warning, TEXT("AsteroidMedium destroyed!"));
	this->Destroy();
}