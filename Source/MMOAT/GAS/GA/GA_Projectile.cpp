// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Projectile.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "MMOAT/Character/MMOATCharacter.h"

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
		UE_LOG(LogTemp, Error, TEXT("No Montage was set!"));
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No projectile Settled!"));
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
		EventTask->EventReceived.AddDynamic(this, &UGA_Projectile::SpawnProjectileOnHand);
		EventTask->ReadyForActivation();
	}
	
}

void UGA_Projectile::SpawnProjectileOnHand(FGameplayEventData Payload)
{
	if (!HasAuthority(&CurrentActivationInfo))
	{
		return;
	}
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return;
	
	AMMOATCharacter* MMOATCharacter = Cast<AMMOATCharacter>(AvatarActor);
	if (!MMOATCharacter) return;

	USkeletalMeshComponent* MeshComp = MMOATCharacter->GetMesh();
	if (!MeshComp) return;
	
	FVector SpawnLocation = MeshComp->GetSocketLocation(BoneName != NAME_None ? BoneName : FName("hand_r"));
	FRotator SpawnRotation = AvatarActor->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwningActorFromActorInfo();
	SpawnParams.Instigator = MMOATCharacter;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (ProjectileClass)
	{
		GetWorld()->SpawnActor<AActor>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);
	}

	// Commit l'ability après le spawn
	CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo());

	EndAbility(
	GetCurrentAbilitySpecHandle(),
	GetCurrentActorInfo(),
	GetCurrentActivationInfo(),
	true, // bReplicateEndAbilityToRemote
	false // bWasCancelled
);

}