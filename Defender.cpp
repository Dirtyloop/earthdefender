#include "Defender.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Bullet.h"
#include "math.h"

ADefender::ADefender()
{
	PrimaryActorTick.bCanEverTick = false;

	SM_Defender = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM Defender"));

	RootComponent = SM_Defender;

	SM_Defender->SetEnableGravity(false);
	SM_Defender->SetConstraintMode(EDOFMode::XZPlane);
	SM_Defender->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Defender->SetCollisionProfileName(TEXT("PhysicsActor"));

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	Box_Collision->SetBoxExtent(FVector(15.0f, 15.0f, 15.0f));

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
}

void ADefender::BeginPlay()
{
	Super::BeginPlay();
	Reset();
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ADefender::OnOverlapBegin);
}

void ADefender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADefender::MoveCircular(float AxisValue)
{
	CurrentAngle += RotationSpeed * AxisValue * GetWorld()->GetDeltaSeconds();;
	Angle = CurrentAngle * RadToDeg - 90.0f;

	if ((CurrentAngle > 2 * M_PI) || (CurrentAngle < -2 * M_PI)) {
		CurrentAngle = 0.0f;
		Angle = 180.0f;
	}
	
	float xPosition = CenterPointX + cos(CurrentAngle) * 90.0;
	float yPosition = CenterPointY + sin(CurrentAngle) * 90.0;

	if (AxisValue != 0) {
		SetActorLocationAndRotation(FVector(xPosition, yPosition, -110.0f), FRotator(0.0f, Angle, 0.0f));
	}
}

void ADefender::Shoot()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		MuzzleOffset.Set(420.0f, 0.0f, -140.0f);
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


void ADefender::Reset()
{
	CurrentAngle = InitialRotationAngle;
	DefenderPoints = 0;
	Angle = 180.0f;
	SetActorLocationAndRotation(FVector(50.0f, 140.0f, -110.0f), FRotator(0.0f, Angle, 0.0f));
}

void ADefender::AddDefenderPoints()
{
	DefenderPoints++;
	UE_LOG(LogTemp, Warning, TEXT("Defender Points: %d"), DefenderPoints);
}

void ADefender::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Bullet")) {
		UE_LOG(LogTemp, Warning, TEXT("Defender hitten!"));
		DamageDefender(25);
		OtherActor->Destroy();
	}
	if (OtherActor->ActorHasTag("Invader") || OtherActor->ActorHasTag("Invader2") || OtherActor->ActorHasTag("Asteroid")) {
		UE_LOG(LogTemp, Warning, TEXT("Defender crushed!"));
		DamageDefender(100);
		OtherActor->Destroy();
	}
}

void ADefender::DamageDefender(int damagePoints)
{
	DefenderLifePoints -= damagePoints;
	if (DefenderLifePoints <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("You lose! Your Points: %d"), DefenderPoints);
	}
	else {
		
		UE_LOG(LogTemp, Warning, TEXT("Defender Life Points: %d"), DefenderLifePoints);
	}
}

int ADefender::GetDefenderLifePoints()
{
	return DefenderLifePoints;
}

