#include "PauseMenu.h"

#include "Kismet/GameplayStatics.h"


void UPauseMenu::ResumeGame()
{
	UnpauseGame();
	RemoveFromParent();
}

void UPauseMenu::ResetGame() const
{
	UnpauseGame();
	
	// Open the same level again to reset
	const FString LevelNameString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	const FName LevelName = FName(*LevelNameString);
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UPauseMenu::UnpauseGame() const
{
	if (IsValid(GetWorld()) == false || IsValid(GetOwningPlayer()) == false)
	{
		return;
	}
		
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	GetOwningPlayer()->bShowMouseCursor = false;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
