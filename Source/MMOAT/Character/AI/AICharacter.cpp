// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "MMOAT/Err.h"
#include "MMOAT/GAS/AttributeSets/EnnemyAttributeSet.h"


// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	AIController = CreateDefaultSubobject<ADefault_AIController>(TEXT("AIController"));
	IS_NOT_NULL(AIController, "AIController Creation Failed");

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	IS_NOT_NULL(ASC, "Ability System Component Creation Failed");
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);

	InitAttributes();
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

bool AAICharacter::Default_Attack_Implementation(AActor* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Target Found"));
		return false;
	}

	
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag("Event.AI.Attack");
	EventData.Instigator = this;
	EventData.Target = Target;
	EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Target);

	UE_LOG(LogTemp, Display, TEXT("Launching IA's ATTACK"));
	ASC->HandleGameplayEvent(EventData.EventTag, &EventData);

	return true;
}

void AAICharacter::InitAttributes()
{
	NewObject<UEnnemyAttributeSet>(this, UEnnemyAttributeSet::StaticClass());
	ASC->AddAttributeSetSubobject(IA_Attributes);
}
