// Copywrite TB 2020


#include "SpermAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WormGameModeBase.h"
#include "TimerManager.h"


void ASpermAIController::BeginPlay()
{
    Super::BeginPlay();

	GameModeRef = Cast<AWormGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

    if (AIBehavior != nullptr && GameModeRef != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        FTimerHandle TimerHandle;
        float SearchTimer = 1;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpermAIController::GetEggLocation, SearchTimer);
    }

}

void ASpermAIController::GetEggLocation()
{
    FVector EggLocation = GameModeRef->GetEggLocation();
    GetBlackboardComponent()->SetValueAsVector(TEXT("EggLocation"), EggLocation);
}
