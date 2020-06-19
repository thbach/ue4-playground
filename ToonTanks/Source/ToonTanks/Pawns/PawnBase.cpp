// Copyright TB 2020


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// update turrent mesh to look at LookAtTarget
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurrentRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z));
	TurretMesh->SetWorldRotation(TurrentRotation);
}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
	if (!ProjectileClass) return;
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}

	// Get ProjectileSpawnPoint Location && Rotation -> spawn projectile class
}

void APawnBase::HandleDestruction()
{
	// universal function
	// play death effects/ soujnd and camera

	// ... then do unique child ovverrides.

	// -- pawnTurrent - inform GameMode Turret died - then Destroy()

	// -- pawnTank - inform GameMode player died -> then Hide() all components && styop movement input.
}

