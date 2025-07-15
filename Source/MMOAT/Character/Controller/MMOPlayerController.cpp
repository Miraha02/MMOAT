// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MMOAT/Err.h"

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