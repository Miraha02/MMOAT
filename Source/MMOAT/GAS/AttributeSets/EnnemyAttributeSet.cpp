// Fill out your copyright notice in the Description page of Project Settings.


#include "EnnemyAttributeSet.h"

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

void UEnnemyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEnnemyAttributeSet, Health);
	DOREPLIFETIME(UEnnemyAttributeSet, MaxHealth);
	DOREPLIFETIME(UEnnemyAttributeSet, Damage);
}