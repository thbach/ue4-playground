// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPool.generated.h"


class UBoxComponent;
class APickupBase;

UCLASS()
class THEWORMGAME_API ASpawnPool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent*  BoxComponent;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	TMap<TSubclassOf<AActor>, int32> ActorsToSpawnMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	bool bRandomYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	bool bRandomPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	bool bRandomRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	bool bRespawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", meta = (AllowPrivateAccess = "true"));
	float RespawnTimer = 10;
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(VisibleAnywhere)
	int32 TotalSpawnableActors = 0;
	UPROPERTY(VisibleAnywhere)
	TArray<AActor* > SpawnedActors;

	void SpawnActors();
	void SpawnActor(TSubclassOf<AActor> ActorClass);
	void RespawnActors();
	FVector GetSpawnLocation();
	FRotator GetSpawnRotation();


};
