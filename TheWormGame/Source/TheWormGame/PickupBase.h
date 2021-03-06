// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class ASpermCharacterBase;
class UParticleSystem;

UCLASS()
class THEWORMGAME_API APickupBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickupBase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;

	// Effects
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticle;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASpermCharacterBase> SpermAIClass;

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
