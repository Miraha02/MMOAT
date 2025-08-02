// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "MMOAT/ActorComponent/DeathComponent.h"
#include "Net/UnrealNetwork.h"

UEnnemyAttributeSet::UEnnemyAttributeSet()
{
	Health = 1000;
	Damage = 22.5;
}

void UEnnemyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnnemyAttributeSet, Health, OldHealth);
}

void UEnnemyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnnemyAttributeSet, MaxHealth, OldMaxHealth);
}

void UEnnemyAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEnnemyAttributeSet, Damage, OldDamage);
}

void UEnnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Empeche la vie d'être superieur a la vie max pour n'importe quel raison
		if (GetHealth() >= GetMaxHealth())
		{
			Health = GetMaxHealth();
		}

		// Empeche la vie d'être inférieur à 0
		if (GetHealth() <= 0)
		{
			Health = 0;

			// Call the Die Function On the Character Only if it is not Already Dead
			FGameplayTag DeadTag = FGameplayTag::RequestGameplayTag(FName("AI.IsDead"));
			if (!GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(DeadTag))
			{
				// Call Die Function if Character Has a UDeathComponent
				UDeathComponent* DeathComponent = GetOwningActor()->FindComponentByClass<UDeathComponent>();
				if (DeathComponent)
				{
					DeathComponent->Die();
				}
			}
		}
	}
}

void UEnnemyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEnnemyAttributeSet, Health);
	DOREPLIFETIME(UEnnemyAttributeSet, MaxHealth);
	DOREPLIFETIME(UEnnemyAttributeSet, Damage);
}
