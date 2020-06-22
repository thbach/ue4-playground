// Copywrite TB 2020


#include "SpeedPatchBase.h"
#include "SpermCharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpeedPatchBase::ASpeedPatchBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SpeedPatchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpeedPatchMesh"));
	SpeedPatchMesh->SetupAttachment(Root);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASpeedPatchBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ASpeedPatchBase::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ASpeedPatchBase::ActorEndOverlap);
}

void ASpeedPatchBase::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!SpermAIClass) return;

	if (OtherActor->GetClass() == SpermAIClass || OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Cast<ASpermCharacterBase>(OtherActor)->HandleSpeedHit(SpeedModifier);
	}
}

void ASpeedPatchBase::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!SpermAIClass) return;

	if (OtherActor->GetClass() == SpermAIClass || OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		Cast<ASpermCharacterBase>(OtherActor)->HandleSpeedHit(1.0f);
	}
}

