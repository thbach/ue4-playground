// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedPatchBase.generated.h"

class ASpermCharacterBase;
class USceneComponent;
class UBoxComponent;

UCLASS()
class THEWORMGAME_API ASpeedPatchBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedPatchBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Config
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*  SpeedPatchMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent*  BoxComponent;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed", meta = (AllowPrivateAccess = "true"))
	float SpeedModifier = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASpermCharacterBase> SpermAIClass;


	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


};
