// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "MMOAT/Err.h"


// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AIController = CreateDefaultSubobject<ADefault_AIController>(TEXT("AIController"));
	IS_NOT_NULL(AIController, "AIConrtoller Creation Failed");

	
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

