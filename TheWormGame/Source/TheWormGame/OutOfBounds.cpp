// Copywrite TB 2020


#include "OutOfBounds.h"
#include "Components/BoxComponent.h"
#include "PickupBase.h"
#include "SpermCharacterBase.h"

// Sets default values
AOutOfBounds::AOutOfBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AOutOfBounds::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AOutOfBounds::ActorBeginOverlap);

}

void AOutOfBounds::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!SpermAIClass || !PickupClass) return;

	if (Cast<APickupBase>(OtherActor->GetClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("bounds hit"));
	}

	// if (OtherActor->GetClass() == SpermAIClass || OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	// {
	// 	// Destroy();
	// 	SetActorTickEnabled(false);
	// 	SetActorHiddenInGame(true);
	// 	SetActorEnableCollision(false);
	// }
}




