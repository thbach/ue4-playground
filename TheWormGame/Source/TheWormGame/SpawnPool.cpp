// Copywrite TB 2020


#include "SpawnPool.h"
#include "Components/BoxComponent.h"
#include "Containers/Map.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
ASpawnPool::ASpawnPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

}

// Called when the game starts or when spawned
void ASpawnPool::BeginPlay()
{
	Super::BeginPlay();

	if (ActorsToSpawnMap.Num() > 0)
	{
		SpawnActors();
		if (bRespawn)
		{
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASpawnPool::RespawnActors, RespawnTimer);
		}
	}
}

void ASpawnPool::SpawnActors()
{
	for (auto Elem : ActorsToSpawnMap)
	{
		for (int32 i = 0; i < Elem.Value; i++)
		{
			TotalSpawnableActors ++;
			SpawnActor(Elem.Key);
		}
	}
}

void ASpawnPool::SpawnActor(TSubclassOf<AActor> ActorClass)
{
	AActor* TempActor = GetWorld()->SpawnActor<AActor>(ActorClass, GetSpawnLocation(), GetSpawnRotation());
	if (TempActor)
	{
		TempActor->SetOwner(this);
		SpawnedActors.Add(TempActor);
	}
}

void ASpawnPool::RespawnActors()
{
	// Add Dead Actors, then chose one randomly, then reset them
	TArray<AActor* > DeadActors;
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor->IsHidden())
		{
			DeadActors.Add(Actor);
		}
	}

	if (DeadActors.Num() > 0)
	{
		int32 ActorToSpawn = FMath::RandRange(0, DeadActors.Num()-1);
		AActor* DeadActor = DeadActors[ActorToSpawn];
		DeadActor->SetActorLocation(GetSpawnLocation());
		DeadActor->SetActorRotation(GetSpawnRotation());
		DeadActor->SetActorHiddenInGame(false);
		DeadActor->SetActorTickEnabled(true);
		DeadActor->SetActorEnableCollision(true);
		DeadActors.Remove(DeadActor);
	}

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASpawnPool::RespawnActors, RespawnTimer);
}

FVector ASpawnPool::GetSpawnLocation()
{
	FVector ActorOrigin;
	FVector BoxExtent;
	GetActorBounds(false, ActorOrigin, BoxExtent);
	return UKismetMathLibrary::RandomPointInBoundingBox(ActorOrigin, BoxExtent);

}

FRotator ASpawnPool::GetSpawnRotation()
{
	FRotator Rotation = FRotator(0);
	if (bRandomYaw) Rotation.Yaw = FMath::RandRange(0, 360);
	if (bRandomPitch) Rotation.Pitch = FMath::RandRange(0, 360);
	if (bRandomRoll) Rotation.Roll = FMath::RandRange(0, 360);

	return Rotation;
}

