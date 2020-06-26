// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WormGameModeBase.generated.h"

class ASpermCharacterBase;

UCLASS()
class THEWORMGAME_API AWormGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	void ActorDied(AActor* DeadActor);
	void ActorWon(AActor* WinningActor);

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon, bool bIsTimeout);

	FVector GetEggLocation() { return EggLocation; }
	void SetEggLocation(FVector Location) { EggLocation = Location; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	ASpermCharacterBase* PlayerSperm;

	void HandleGameOver(bool PlayerWon, bool bIsTimeout=false);

	bool bGameHasEnded = false;

	FVector EggLocation;


};
