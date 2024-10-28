// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Logging/LogMacros.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class XYUANTEST_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	/** Remove Pause Menu and resume the game */
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	/** Reset the level */
	UFUNCTION(BlueprintCallable)
	void ResetGame() const;

private:
	void UnpauseGame() const;
	
};
