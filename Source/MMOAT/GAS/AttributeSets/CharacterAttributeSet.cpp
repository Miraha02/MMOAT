// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeSet.h"

#include "MMOAT/Character/MMOATCharacter.h"
#include "Net/UnrealNetwork.h" //Pour le online plus tard

UCharacterAttributeSet::UCharacterAttributeSet() {
	// Initial values for Health, MaxHealth and HealthRegen
	Health = 1;
	MaxHealth = 1;
	HealthRegen = 0.01;

	// Initial values for Mana, MaxMana andManahRegen
	Mana = 1;
	MaxMana = 1;
	ManaRegen = 0.01;
}

void UCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, OldHealth);
}

void UCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void UCharacterAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, HealthRegen, OldHealthRegen);
}

void UCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Mana, OldMana);
}

void UCharacterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxMana, OldMaxMana);
}

void UCharacterAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, ManaRegen, OldManaRegen);
}

// Replication logic pour les attributs

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate attributes
	DOREPLIFETIME(UCharacterAttributeSet, Health);
	DOREPLIFETIME(UCharacterAttributeSet, MaxHealth);
	DOREPLIFETIME(UCharacterAttributeSet, HealthRegen);
	DOREPLIFETIME(UCharacterAttributeSet, Mana);
	DOREPLIFETIME(UCharacterAttributeSet, MaxMana);
	DOREPLIFETIME(UCharacterAttributeSet, ManaRegen);
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Give Mana Activation Tag if Character is not Full Mana
		if (GetMana() < GetMaxMana())
		{
			ActivateManaRegen();
		}

		// Empêche la mana d'être supérieure au mana max pour n'importe quelle raison
		if (GetMana() >= GetMaxMana())
		{
			Mana = GetMaxMana();
			ActivateManaRegen(false);
		}

		// Empeche le mana d'être inférieur à 0
		if (GetMana() < 0)
		{
			Mana = 0;
		}

		// Update Mana UI If Owning Actor is A AMMOATCharacter
		AMMOATCharacter* Character = Cast<AMMOATCharacter>(GetOwningActor());
		if (Character)
		{
			Character->OnManaUpdateEvent();
		}
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Give Health Activation Tag if Chracter is not Full Life
		if (GetHealth() < GetMaxHealth())
		{
			ActivateHealthRegen();
		}
		
		// Empeche la vie d'être superieur a la vie max pour n'importe quel raison
		if (GetHealth() >= GetMaxHealth())
		{
			Health = GetMaxHealth();
			ActivateHealthRegen(false);
		}

		// Empeche la vie d'être inférieur à 0
		if (GetHealth() <= 0)
		{
			Health = 0;

			// Call On Death Event Function If Owning Actor Is a AMMOATCharacter
			AMMOATCharacter* Character = Cast<AMMOATCharacter>(GetOwningActor());
			if (Character)
			{
				Character->OnDeathEvent();
			}
		}

		// Update Health UI If Owning Actor is A AMMOATCharacter
		AMMOATCharacter* Character = Cast<AMMOATCharacter>(GetOwningActor());
		if (Character)
		{
			Character->OnHealthUpdateEvent();
		}
	}
}


bool UCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	Super::PreGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Modification pour que le mana n'excede jamais la valeur du mana max
		if (GetMana() + GetManaRegen() > GetMaxMana() && Data.EvaluatedData.Magnitude > 0)
		{
			Data.EvaluatedData.Magnitude = GetMaxMana() - GetMana();
		}
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Modification pour que la vie n'excede jamais la valeur du mana max
		if (GetHealth() + GetHealthRegen() > GetMaxHealth() && Data.EvaluatedData.Magnitude > 0)
		{
			Data.EvaluatedData.Magnitude = GetMaxHealth() - GetHealth();
		}
	}
	return true;
}

void UCharacterAttributeSet::ActivateHealthRegen(bool Activate)
{
		if (auto Character = Cast<AMMOATCharacter>(GetOwningActor()))
		{
			Character->ActivateHealthRegen(Activate);
		}
}

void UCharacterAttributeSet::ActivateManaRegen(bool Activate)
{
	if (auto Character = Cast<AMMOATCharacter>(GetOwningActor()))
	{
		Character->ActivateManaRegen(Activate);
	}
}