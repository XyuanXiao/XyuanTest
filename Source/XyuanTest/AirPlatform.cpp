#include "AirPlatform.h"
#include "XyuanTestCharacter.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AAirPlatform::AAirPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	// Mesh of the air platform that will appear under the player character
	if (PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh")); IsValid(PlatformMesh))
	{
		PlatformMesh->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AAirPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetWorld()) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' World is not valid."), *GetNameSafe(this));
		return;
	}
	
	// Platform starts to fall after the set DelayToFall
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAirPlatform::StartFall, DelayToFall, false);
}

void AAirPlatform::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(PlatformMesh))
	{
		PlatformMesh->OnComponentHit.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

void AAirPlatform::StartFall()
{
	if (IsValid(PlatformMesh))
	{
		PlatformMesh->SetSimulatePhysics(true);
		PlatformMesh->OnComponentHit.AddDynamic(this, &AAirPlatform::PlatformHit);
	}
}

void AAirPlatform::PlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AXyuanTestCharacter* PlayerCharacter = Cast<AXyuanTestCharacter>(OtherActor); IsValid(PlayerCharacter))
	{
		PlayerCharacter->CollectAirPlatform();
		Destroy();
	}
}

