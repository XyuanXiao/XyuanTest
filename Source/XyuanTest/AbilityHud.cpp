#include "AbilityHud.h"
#include "Components/VerticalBox.h"


void UAbilityHud::AddAirPlatformSlot()
{
	if (IsValid(AirPlatformSlotsBox) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertival Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	if (IsValid(AirPlatformSlotClass) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AirPlatformSlotClass is not valid. Please assign a valid class to this variable."), *GetNameSafe(this));
		return;
	}

	if (auto AbilitySlot = CreateWidget(this, AirPlatformSlotClass); IsValid(AbilitySlot))
	{
		AirPlatformSlotsBox->AddChildToVerticalBox(AbilitySlot);
	}
}

void UAbilityHud::RemoveAirPlatformSlot()
{
	if (nullptr == AirPlatformSlotsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertival Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	AirPlatformSlotsBox->RemoveChildAt(0);
}
