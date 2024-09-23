#include "AbilityHud.h"
#include "Components/VerticalBox.h"


void UAbilityHud::AddAirPlatformSlot()
{
	if (nullptr == AirPlatformSlotsBox)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' AbilityHud needs to contain a Vertival Box called AirPlatformSlotsBox."), *GetNameSafe(this));
		return;
	}

	auto AbilitySlot = CreateWidget(this, AirPlatformSlotClass);
	AirPlatformSlotsBox->AddChildToVerticalBox(AbilitySlot);
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
