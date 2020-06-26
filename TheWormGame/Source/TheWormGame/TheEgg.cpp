// Copywrite TB 2020


#include "TheEgg.h"
#include "SpermCharacterBase.h"
#include "WormGameModeBase.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATheEgg::ATheEgg()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	EggMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EggMesh"));
	EggMesh->SetupAttachment(Root);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BoxComponent"));
	SphereComponent->SetupAttachment(Root);


}

// Called when the game starts or when spawned
void ATheEgg::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AWormGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	// Hard Code
	if (GameModeRef) GameModeRef->SetEggLocation(SphereComponent->GetComponentLocation());
	OnActorBeginOverlap.AddDynamic(this, &ATheEgg::ActorBeginOverlap);
}


void ATheEgg::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!SpermAIClass || !GameModeRef) return;

	if (OtherActor->GetClass() == SpermAIClass || OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		GameModeRef->ActorWon(OtherActor);
	}
}
