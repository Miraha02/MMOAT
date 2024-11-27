// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeSet.h"
#include "Net/UnrealNetwork.h" //Pour le online plus tard

UCharacterAttributeSet::UCharacterAttributeSet() {
	// Initinal values for Health, MaxHealth and HealthRegen
	Health = 100;
	MaxHealth = 100;
	HealthRegen = 3;

	// Initinal values for Mana, MaxMana andManahRegen
	Mana = 100;
	MaxMana = 100;
	ManaRegen = 3;
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
