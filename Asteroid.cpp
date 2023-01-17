#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

	SM_Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid"));
	SM_Asteroid->SetEnableGravity(false);
	SM_Asteroid->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_Asteroid;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_Asteroid);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	speed = 0.05f;
	shift = 0.0f;
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroid::OnOverlapBegin);
	AAsteroid::Tags.Add(FName("Asteroid"));
}

void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AAsteroid::Move()
{
	CurrentLocation = this->GetActorLocation();
	shift = speed * GetWorld()->GetDeltaSeconds();
	//speed += 0.01f;
	
	CurrentLocation.X += shift * (50 - CurrentLocation.X);
	CurrentLocation.Y += shift * (230 - CurrentLocation.Y);
	
	SetActorLocation(CurrentLocation);
}


void AAsteroid::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("Asteroid hitten!"));
		//asteroidLifePoints -= defaultDamagePoints;
		asteroidLifePoints = 0;
		UE_LOG(LogTemp, Warning, TEXT("Asteroid Life Points: %g"), asteroidLifePoints);
		if (asteroidLifePoints <= 0) {
			DestroyAsteroid();
		}
		OtherActor->Destroy();
	}
}

void AAsteroid::DestroyAsteroid()
{
	UE_LOG(LogTemp, Warning, TEXT("Asteroid destroyed!"));
	this->Destroy();
}