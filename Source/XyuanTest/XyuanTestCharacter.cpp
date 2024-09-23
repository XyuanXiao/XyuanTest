// Copyright Epic Games, Inc. All Rights Reserved.

#include "XyuanTestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilityHud.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AXyuanTestCharacter

AXyuanTestCharacter::AXyuanTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AXyuanTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Abilities
		EnhancedInputComponent->BindAction(AirPlatformAction, ETriggerEvent::Started, this, &AXyuanTestCharacter::AirPlatform);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXyuanTestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AXyuanTestCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AXyuanTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilityHudClass) == false)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' AbilityHidClass is not valid. Please assign a valid class to this variable."), *GetNameSafe(this));
		return;
	}
	
	AbilityHud = CreateWidget<UAbilityHud>(GetWorld()->GetGameInstance(), AbilityHudClass);
	AbilityHud->AddToViewport();
}

void AXyuanTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AXyuanTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AXyuanTestCharacter::AirPlatform()
{
	if (GetCharacterMovement()->IsFalling() && bAirAbilityUsed == false && AirPlatformsCount > 0)
	{
		bAirAbilityUsed = true;
		UseAirPlatform();
		PerformAirAbility();
	}
}

void AXyuanTestCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bAirAbilityUsed = false;
}

void AXyuanTestCharacter::PerformAirAbility()
{
	if (IsValid(AirPlatformClass) == false)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' AirPlatformClass is not valid. Please assign a valid class to this variable."), *GetNameSafe(this));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		return;
	}

	FVector PlatformLocation = GetActorLocation() - FVector(0, 0, 90.0f); // Location under the player
	FTransform PlatformTransform (GetActorRotation(), PlatformLocation, FVector(1.0f, 1.0f, 1.0f));

	// Spawn Air Platform at desired transform
	AAirPlatform* AirPlatform = GetWorld()->SpawnActor<AAirPlatform>(AirPlatformClass, PlatformTransform);
}

void AXyuanTestCharacter::CollectAirPlatform()
{
	AirPlatformsCount++;

	if (IsValid(AbilityHud))
	{
		AbilityHud->AddAirPlatformSlot();
	}
}

void AXyuanTestCharacter::UseAirPlatform()
{
	AirPlatformsCount--;
	
	if (IsValid(AbilityHud))
	{
		AbilityHud->RemoveAirPlatformSlot();
	}
}
