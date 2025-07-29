// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "MMOAT/Err.h"
#include "MMOAT/Character/MMOATCharacter.h"

#define CAST_TO_MMOATCHARACTER\
auto* MMOATCharacter = Cast<AMMOATCharacter>(GetCharacter());\
	if (!MMOATCharacter)\
	{\
		UE_LOG(LogTemp, Error, TEXT("Controlled Character is not a MMOATCharacter"));\
		return;\
	}

AMMOPlayerController::AMMOPlayerController()
{
	
}

void AMMOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Check que l'IMC et les IA ont été selectionnés
	IS_NOT_NULL(DefaultMappingContext,"Mapping Context is Null");
	IS_NOT_NULL(MoveAction,"Move Action is Null");
	IS_NOT_NULL(LookAction,"Look Action is Null");
	IS_NOT_NULL(JumpAction,"Jump Action is Null");

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AMMOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMMOPlayerController::Move);
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMMOPlayerController::Look);
		}
		if (JumpAction)
		{
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AMMOPlayerController::Jump);
		}
	}
}

void AMMOPlayerController::Move(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector2D MovementVector = Value.Get<FVector2D>();
		const FRotator ControlRot = GetControlRotation();
		const FRotator YawRot(0, ControlRot.Yaw, 0);

		const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(Forward, MovementVector.Y);
		ControlledPawn->AddMovementInput(Right, MovementVector.X);
	}
}

void AMMOPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();
	AddYawInput(LookAxis.X);
	AddPitchInput(LookAxis.Y);
}

void AMMOPlayerController::Jump(const FInputActionValue& Value)
{
	GetCharacter()->Jump();
}

void AMMOPlayerController::Spell1(const FInputActionValue& Value)
{
	CAST_TO_MMOATCHARACTER
	MMOATCharacter->LaunchSpell1();
}

void AMMOPlayerController::Spell2(const FInputActionValue& Value)
{
	CAST_TO_MMOATCHARACTER
	MMOATCharacter->LaunchSpell2();
}

void AMMOPlayerController::Spell3(const FInputActionValue& Value)
{
	CAST_TO_MMOATCHARACTER
	MMOATCharacter->LaunchSpell3();
}
