// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOPlayerController.h"

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
