// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Projectile.h"

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
		return;
	}
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No projectile Settled!"), __FUNCTION__);
		return;
	}

	
}
