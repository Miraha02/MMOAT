// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCostCalculation.h"
#include "ManaCostGameplayAbility.h"
#include "AbilitySystemComponent.h"

float UBaseCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
    // V�rifier si le contexte contient une Ability

    UE_LOG(LogTemp, Warning, TEXT("Utilisation de CalculateBaseMAgnitude"));
    
    const FGameplayEffectContextHandle& Context = Spec.GetContext();

    if (!Context.IsValid()) {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Context"));
        return 10.f; // Retourne une valeur par d�faut si le contexte est invalide
    }

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Context.ToString());

    // R�cup�rer l'Ability � partir du contexte
    const UGameplayAbility* Ability = Context.GetAbility();

    if (!Ability) {
        UE_LOG(LogTemp, Warning, TEXT("No Ability found in Context"));
        return 10.f; // Retourne une valeur par d�faut si aucune Ability n'est associ�e
    }

    // Faire le cast vers ton type sp�cifique (UManaCostGameplayAbility)
    const UManaCostGameplayAbility* ManaAbility = Cast<UManaCostGameplayAbility>(Ability);

    if (!ManaAbility) {
        UE_LOG(LogTemp, Warning, TEXT("Ability is not of type UManaCostGameplayAbility"));
        return 10.f; // Retourne une valeur par d�faut si l'Ability n'est pas du bon type
    }

    UE_LOG(LogTemp, Warning, TEXT("%f"),ManaAbility->Cost);
    return ManaAbility->Cost; // Retourne le co�t de mana si tout est valide
}
