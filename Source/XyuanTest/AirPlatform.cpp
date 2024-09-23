#include "AirPlatform.h"
#include "XyuanTestCharacter.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AAirPlatform::AAirPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	// Mesh of the air platform that will appear under the player character
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAirPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	// Platform starts to fall after the set DelayToFall
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAirPlatform::StartFall, DelayToFall, false);
}

void AAirPlatform::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	PlatformMesh->OnComponentHit.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void AAirPlatform::StartFall()
{
	PlatformMesh->SetSimulatePhysics(true);
	PlatformMesh->OnComponentHit.AddDynamic(this, &AAirPlatform::PlatformHit);
}

void AAirPlatform::PlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AXyuanTestCharacter* PlayerCharacter = Cast<AXyuanTestCharacter>(OtherActor); IsValid(PlayerCharacter))
	{
		PlayerCharacter->CollectAirPlatform();
		Destroy();
	}
}

