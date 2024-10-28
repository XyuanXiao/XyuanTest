#include "AbilityHud.h"
#include "Components/VerticalBox.h"


void UAbilityHud::AddAirPlatformSlot()
{
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

void UAbilityHud::RemoveAirPlatformSlot() const
{
	if (nullptr == AirPlatformSlotsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertical Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	AirPlatformSlotsBox->RemoveChildAt(0);
}
