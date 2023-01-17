#include "Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	SM_Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	RootComponent = SM_Bullet;

	SM_Bullet->SetEnableGravity(false);
	SM_Bullet->SetConstraintMode(EDOFMode::XZPlane);
	SM_Bullet->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Bullet->SetCollisionProfileName(TEXT("PhysicsActor"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->SetUpdatedComponent(SM_Bullet);
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	InitialLifeSpan = 0.3f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	ABullet::Tags.Add(FName("Bullet"));
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}

