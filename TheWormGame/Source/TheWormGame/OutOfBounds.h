// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OutOfBounds.generated.h"

class UBoxComponent;
class ASpermCharacterBase;
class APickupBase;

UCLASS()
class THEWORMGAME_API AOutOfBounds : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOutOfBounds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	// Varriables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASpermCharacterBase> SpermAIClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APickupBase> PickupClass;

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
