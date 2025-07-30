// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Projectile.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

UGA_Projectile::UGA_Projectile()
{
	
}

void UGA_Projectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!Montage)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Montage was set!"), __FUNCTION__);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No projectile Settled!"), __FUNCTION__);
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		Montage,
		1.0f,                          // Rate
		NAME_None,                    // StartSection
		true,                         // Stop when ability ends
		1.0f,                          // RootMotionTranslationScale
		0.0f                          // StartTime
	);

	if (MontageTask)
	{
		// These functions should be implemented to execute logic related to the Montage states
		// (to prevent from spamming skill button while the event tag has not been received)
		/*
		MontageTask->OnCompleted.AddDynamic(this, &UMyGameplayAbility::OnMontageCompleted);
		MontageTask->OnInterrupted.AddDynamic(this, &UMyGameplayAbility::OnMontageInterrupted);
		MontageTask->OnCancelled.AddDynamic(this, &UMyGameplayAbility::OnMontageCancelled);
		MontageTask->OnBlendOut.AddDynamic(this, &UMyGameplayAbility::OnMontageBlendOut);
		*/
		MontageTask->ReadyForActivation();
	}
	
	FGameplayTag EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Montage.Projectile"));

	UAbilityTask_WaitGameplayEvent* EventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		EventTag,
		nullptr,      // Optional External Target
		true,         // Only Trigger Once
		true          // Only Match Exact
	);

	if (EventTask)
	{
		EventTask->EventReceived.AddDynamic(this, &UMyGameplayAbility::OnProjectileEventReceived);
		EventTask->ReadyForActivation();
	}
	
}
