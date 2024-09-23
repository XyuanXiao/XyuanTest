// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Logging/LogMacros.h"
#include "AbilityHud.generated.h"

class UVerticalBox;
/**
 * 
 */
UCLASS()
class XYUANTEST_API UAbilityHud : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Vertical Box to put the player's Air Platform slots */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* AirPlatformSlotsBox = nullptr;

	/** WIdget class that will put as slot for the player's Air Platform inventory */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> AirPlatformSlotClass = UUserWidget::StaticClass();

public:
	void AddAirPlatformSlot();

	void RemoveAirPlatformSlot();
};
