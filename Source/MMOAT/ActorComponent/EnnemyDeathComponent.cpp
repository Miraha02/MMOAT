// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyDeathComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BrainComponent.h"


// Sets default values for this component's properties
UEnnemyDeathComponent::UEnnemyDeathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bDestroyOnDeath = true;
	DelayBeforeDestroy = 3.0f;
}


// Called when the game starts
void UEnnemyDeathComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnnemyDeathComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnnemyDeathComponent::HandleDeath_Implementation()
{
	Super::HandleDeath_Implementation();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEnnemyDeathComponent: No owner found"));
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!ASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEnnemyDeathComponent: No AbilitySystemComponent found on %s"), *Owner->GetName());
		return;
	}

	// Remove AI.IsAlive
	ASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("AI.IsAlive")));

	// Add AI.IsDead
	ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("AI.IsDead")));

	UE_LOG(LogTemp, Display, TEXT("GameplayTags updated on %s: +AI.IsDead, -AI.IsAlive"), *Owner->GetName());

	// Stop Behavior Tree
	APawn* PawnOwner = Cast<APawn>(Owner);
	if (!PawnOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UEnnemyDeathComponent: Owner is not a Pawn"));
		return;
	}

	AAIController* AIController = Cast<AAIController>(PawnOwner->GetController());
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->StopLogic(TEXT("Death"));
		UE_LOG(LogTemp, Display, TEXT("Behavior Tree stopped due to death"));
	}

}

