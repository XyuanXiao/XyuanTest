// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Logging/LogMacros.h"
#include "AbilityHud.generated.h"

USTRUCT(BlueprintType)
struct FObjectiveInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlatformsAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveDescription;
};

class UVerticalBox;
/**
 * 
 */
UCLASS()
class XYUANTEST_API UAbilityHud : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Vertical Box to put the player's Air Platform charge slots */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* AirPlatformSlotsBox = nullptr;

	/** Widget class that will put as slot for the player's Air Platform charges */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> AirPlatformSlotClass = UUserWidget::StaticClass();

private:
	int AirPlatformSlots = 0;
	
protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void ChangePlatformSlots(bool AmountIncreased);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowNewObjective(int PlatformsOwned);

private:	
	// Show new charge slot at the left of the HUD
	void AddAirPlatformSlot();

	// Remove charge slot from the HUD
	void RemoveAirPlatformSlot();
};
