#include "AbilityHud.h"

#include "XyuanTestCharacter.h"
#include "Components/VerticalBox.h"


void UAbilityHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AXyuanTestCharacter* Player = Cast<AXyuanTestCharacter>(GetOwningPlayerPawn()); IsValid(Player))
	{
		Player->OnPlatformsAmountChanged.AddDynamic(this, &UAbilityHud::ChangePlatformSlots);
	}

	ShowNewObjective(0);
}

void UAbilityHud::NativeDestruct()
{
	if (AXyuanTestCharacter* Player = Cast<AXyuanTestCharacter>(GetOwningPlayerPawn()); IsValid(Player))
	{
		Player->OnPlatformsAmountChanged.RemoveAll(this);
	}
	
	Super::NativeDestruct();
}

void UAbilityHud::ChangePlatformSlots(const bool AmountIncreased)
{
	if (AmountIncreased)
	{
		AddAirPlatformSlot();
	}
	else
	{
		RemoveAirPlatformSlot();
	}
	
	ShowNewObjective(AirPlatformSlots);
}

void UAbilityHud::AddAirPlatformSlot()
{
	AirPlatformSlots++;
	
	if (IsValid(AirPlatformSlotsBox) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertical Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	if (IsValid(AirPlatformSlotClass) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AirPlatformSlotClass is not valid. Please assign a valid class to this variable."), *GetNameSafe(this));
		return;
	}

	if (const auto AbilitySlot = CreateWidget(this, AirPlatformSlotClass); IsValid(AbilitySlot))
	{
		AirPlatformSlotsBox->AddChildToVerticalBox(AbilitySlot);
	}
}

void UAbilityHud::RemoveAirPlatformSlot()
{
	AirPlatformSlots--;
	
	if (nullptr == AirPlatformSlotsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertical Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	AirPlatformSlotsBox->RemoveChildAt(0);
}
