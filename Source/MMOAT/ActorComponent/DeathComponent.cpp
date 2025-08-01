// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathComponent.h"

// Sets default values for this component's properties
UDeathComponent::UDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UDeathComponent::Die()
{
	//Call HandleDef Function to use Specific Death Logic
	HandleDeath();

	// Call every function bound to OnDeath
	OnDeath.Broadcast();

	// Destroy The Actor if bDestroyOnDeath is True after DelayBeforeDestroy Seconds
	if (bDestroyOnDeath)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			if (AActor* Owner = GetOwner())
			{
				Owner->Destroy();
			}
		}, DelayBeforeDestroy, false);
	}
}

void UDeathComponent::HandleDeath_Implementation()
{
	
}


// Called when the game starts
void UDeathComponent::BeginPlay()
{
	Super::BeginPlay();

}
