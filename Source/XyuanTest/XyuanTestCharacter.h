// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AirPlatform.h"
#include "AbilityHud.h"
#include "PauseMenu.h"
#include "XyuanTestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AXyuanTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Air Platform Ability Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AirPlatformAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

protected:
	// Air Platform Class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TSubclassOf<AAirPlatform> AirPlatformClass = AAirPlatform::StaticClass();

	// Air Platform spawn distance from root
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	float AirPlatformZ = 150;

	// Ability HUD class
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TSubclassOf<UAbilityHud> AbilityHudClass = UAbilityHud::StaticClass();

	UPROPERTY()
	UAbilityHud* AbilityHud = nullptr;

	// Pause Menu class
	UPROPERTY(EditDefaultsOnly, Category = Pause)
	TSubclassOf<UPauseMenu> PauseMenuClass = UPauseMenu::StaticClass();

private:
	/** Air Ability can only be used once per jump/fall */
	bool bAirAbilityUsed = false;

	/** Number of Air Platforms collected by the player */
	int AirPlatformCharges = 0;

public:
	AXyuanTestCharacter();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {
		return CameraBoom;
	}
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const {
		return FollowCamera;
	}

	/** Increases Air Platforms inventory for the player */
	void CollectAirPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for air platform ability input*/
	void AirPlatform();

	/** Called for pause input */
	void Pause();

	/** Called for jump finish */
	virtual void Landed(const FHitResult& Hit) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/** Triggers Air Ability */
	void PerformAirAbility() const;

	/** Decreases the Air Platform inventory for the player */
	void UseAirPlatform();

};

