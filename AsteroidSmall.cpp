#include "AsteroidSmall.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"

AAsteroidSmall::AAsteroidSmall()
{
	PrimaryActorTick.bCanEverTick = true;

	SM_AsteroidSmall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidSmall"));
	SM_AsteroidSmall->SetEnableGravity(false);
	SM_AsteroidSmall->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = SM_AsteroidSmall;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
	RotatingMovement->SetUpdatedComponent(SM_AsteroidSmall);
	RotatingMovement->RotationRate = FRotator(90.0f, 0.0f, 0.0f);

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 20.0f, 15.0f));

	speed = 0.2f;
	shift = 0.0f;
}

void AAsteroidSmall::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAsteroidSmall::OnOverlapBegin);
	AAsteroidSmall::Tags.Add(FName("Asteroid"));
}

void AAsteroidSmall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AAsteroidSmall::Move()
{
	CurrentLocation = this->GetActorLocation();
	shift = speed * GetWorld()->GetDeltaSeconds();
	//speed += 0.01f;

	CurrentLocation.X += shift * (50 - CurrentLocation.X);
	CurrentLocation.Y += shift * (230 - CurrentLocation.Y);

	SetActorLocation(CurrentLocation);
}


void AAsteroidSmall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("AsteroidSmall hitten!"));
		//asteroidLifePoints -= defaultDamagePoints;
		asteroidLifePoints = 0;
		UE_LOG(LogTemp, Warning, TEXT("AsteroidSmall Life Points: %g"), asteroidLifePoints);
		if (asteroidLifePoints <= 0) {
			DestroyAsteroid();
		}
		OtherActor->Destroy();
	}
}

void AAsteroidSmall::DestroyAsteroid()
{
	UE_LOG(LogTemp, Warning, TEXT("AsteroidSmall destroyed!"));
	this->Destroy();
}