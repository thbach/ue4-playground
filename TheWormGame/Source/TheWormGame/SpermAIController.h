// Copywrite TB 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpermAIController.generated.h"

class AWormGameModeBase;
class UBehaviorTree;

UCLASS()
class THEWORMGAME_API ASpermAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


private:
	// Config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* AIBehavior;
	UPROPERTY(VisibleAnywhere)
	AWormGameModeBase* GameModeRef;

	void GetEggLocation();


};

