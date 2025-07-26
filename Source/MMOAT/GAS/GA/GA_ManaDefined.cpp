// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ManaDefined.h"

#include "AbilitySystemComponent.h"
#include "MMOAT/GAS/GE/GE_ManaCost.h"

UGA_ManaDefined::UGA_ManaDefined()
{
	CostGameplayEffectClass = UGE_ManaCost::StaticClass();
}

void UGA_ManaDefined::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	
	if (ManaCost < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mana Cost can't be Negative !!!"));
		return;
	}

	FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(CostGameplayEffectClass, GetAbilityLevel());

	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Skill.Mana.Cost")), -ManaCost);

	ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*CostSpecHandle.Data.Get());

}
