#include "Invader.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"
#include "Defender.h"
#include "Components/SphereComponent.h"

AInvader::AInvader()
{
	PrimaryActorTick.bCanEverTick = true;

	SM_Invader = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	SM_Invader->SetEnableGravity(false);
	SM_Invader->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootComponent = SM_Invader;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 40.0f, 15.0f));

	speed = 10.0f;
	RotationSpeed = 0.5;
}

void AInvader::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AInvader::OnOverlapBegin);
	CurrentAngle = StartAngle / 57.3f;
	AInvader::Tags.Add(FName("Invader"));
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AInvader::RandomizeShootTime, 0.1f, true);
	//MoveCircular();
}

void AInvader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCircular();

}

void AInvader::RandomizeShootTime()
{
	if (FMath::RandRange(0, randomShootHigherBoundry) == 0) {
		Shoot();
	}
}


void AInvader::MoveCircular()
{
	CurrentAngle += RotationSpeed * GetWorld()->GetDeltaSeconds();

	Angle = 57.3f * CurrentAngle;

	if ((CurrentAngle > 6.28f + StartAngle / 57.3f) || (CurrentAngle < -6.28f + StartAngle / 57.3f)) {
		CurrentAngle = StartAngle / 57.3f;
		Angle = StartAngle;
		Distance -= 25.0;
		RotationSpeed += 0.1;
	}

	float xPosition = 50.0 + cos(CurrentAngle - 1.57f) * Distance;
	float yPosition = 230.0 + sin(CurrentAngle - 1.57f) * Distance;

	SetActorLocationAndRotation(FVector(xPosition, yPosition, -110.0f), FRotator(0.0f, Angle, 0.0f));
	
}

void AInvader::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("Invader hitten!"));
		InvaderLifePoints = 0.0f;
		UE_LOG(LogTemp, Warning, TEXT("Invader Life Points: %g"), InvaderLifePoints);
		DestroyInvader();
		OtherActor->Destroy();
	}
}

void AInvader::DestroyInvader()
{
	UE_LOG(LogTemp, Warning, TEXT("Invader destroyed!"));
	this->Destroy();
}

void AInvader::Shoot()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		MuzzleOffset.Set(370.0f, 0.0f, -60.0f);
		FVector MuzzleLocation = CameraLocation + FTransform(FRotator(0.0f, (Angle + 90.0f), 0.0f)).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = FRotator(0.0f, (Angle + 90.0f), 0.0f);

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			ABullet* Bullet = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Bullet)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection(LaunchDirection);
			}
		}
	}
}