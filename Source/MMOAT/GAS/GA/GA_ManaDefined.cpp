// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ManaDefined.h"

#include "AbilitySystemComponent.h"
#include "MMOAT/GAS/AttributeSets/CharacterAttributeSet.h"
#include "MMOAT/GAS/GE/GE_Cooldown.h"
#include "MMOAT/GAS/GE/GE_ManaCost.h"

UGA_ManaDefined::UGA_ManaDefined()
{
	CooldownGameplayEffectClass = UGE_Cooldown::StaticClass();
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

	FGameplayEffectSpecHandle CostSpecHandle = MakeOutgoingGameplayEffectSpec(UGE_ManaCost::StaticClass(), GetAbilityLevel());

	CostSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Skill.Mana.Cost")), -ManaCost);

	ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*CostSpecHandle.Data.Get());

}

bool UGA_ManaDefined::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	auto AttributeSet = ActorInfo->AbilitySystemComponent->GetSet<UCharacterAttributeSet>();
	if (AttributeSet)
	{
		if (AttributeSet->GetMana() >= ManaCost)
		{
			return true;
		}
		UE_LOG(LogTemp, Display, TEXT("Not Enough Mana To Cast %s"), *GetName());
	}
	return false;
}

const FGameplayTagContainer* UGA_ManaDefined::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset(); // MutableTags writes to the TempCooldownTags on the CDO so clear it in case the ability cooldown tags change (moved to a different slot)
	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}
	MutableTags->AppendTags(CooldownTags);
	return MutableTags;
}

void UGA_ManaDefined::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Skill.Cooldown")), CooldownDuration.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
