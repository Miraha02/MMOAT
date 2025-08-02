// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

// Sets default values for this component's properties
UQuestComponent::UQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
    //InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();

}


// Called every frame
void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestComponent::AddQuest(const FString& QuestName)
{
    // Crée une nouvelle quête
    FQuestData NewQuest;
    NewQuest.QuestName = QuestName;
    NewQuest.bIsCompleted = false;
    Quests.Add(NewQuest);
}

void UQuestComponent::AddQuestFromID(FName QuestRowID)
{
    if (!QuestDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("QuestDataTable is null"));
        return;
    }

    static const FString ContextString(TEXT("Quest Lookup"));
    FQuestData* QuestFromRow = QuestDataTable->FindRow<FQuestData>(QuestRowID, ContextString);

    if (QuestFromRow)
    {
        FQuestData NewQuest = *QuestFromRow;
        Quests.Add(NewQuest);

        UE_LOG(LogTemp, Warning, TEXT("Quest added: %s"), *NewQuest.QuestName);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No quest found for ID: %s"), *QuestRowID.ToString());
    }
}


void UQuestComponent::AddQuestFromRow(const FQuestData& QuestRow)
{
    Quests.Add(QuestRow);
    UE_LOG(LogTemp, Warning, TEXT("Quest %s added from row!"), *QuestRow.QuestName);
}


void UQuestComponent::UpdateObjective(EObjectiveType ObjectiveType, const FString& TargetID, int32 Quantity)
{
    for (FQuestData& Quest : Quests)
    {
        if (Quest.bIsCompleted)
            continue;

        for (FObjectiveData& Obj : Quest.Objectives)
        {
            if (Obj.ObjectiveType == ObjectiveType && Obj.TargetID == TargetID)
            {
                Obj.CurrentQuantity += Quantity;
                Obj.CurrentQuantity = FMath::Clamp(Obj.CurrentQuantity, 0, Obj.TargetQuantity);
            }
        }

        // Vérifie si tous les objectifs sont remplis
        bool bAllDone = true;
        for (const FObjectiveData& Obj : Quest.Objectives)
        {
            if (Obj.CurrentQuantity < Obj.TargetQuantity)
            {
                bAllDone = false;
                break;
            }
        }

        if (bAllDone)
        {
            Quest.bIsCompleted = true;
            UE_LOG(LogTemp, Warning, TEXT("Quest %s completed!"), *Quest.QuestName);
        }
    }
}
void UQuestComponent::UpdateQuestOnItemPickup(const FString& ItemID, int32 Quantity)
{
    // Parcours toutes les quêtes
    for (FQuestData& Quest : Quests)
    {
        if (Quest.bIsCompleted)
            continue; // Si la quête est déjà terminée, on passe à la suivante

        bool bQuestCompleted = true; // Flag pour vérifier si tous les objectifs de la quête sont complétés

        // Parcours tous les objectifs de la quête
        for (FObjectiveData& Obj : Quest.Objectives)
        {
            // Si l'objectif est de type Collect et que l'ID cible correspond à l'objet ramassé
            if (Obj.ObjectiveType == EObjectiveType::OT_Collect && Obj.TargetID == ItemID)
            {
                // Mise à jour de la quantité collectée
                Obj.CurrentQuantity += Quantity;
                Obj.CurrentQuantity = FMath::Clamp(Obj.CurrentQuantity, 0, Obj.TargetQuantity);

                // Vérifie si l'objectif est complété
                if (Obj.CurrentQuantity >= Obj.TargetQuantity)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Objectif %s de la quête %s complété!"), *ItemID, *Quest.QuestName);
                }
            }

            // Vérifie si cet objectif est toujours incomplet
            if (Obj.CurrentQuantity < Obj.TargetQuantity)
            {
                bQuestCompleted = false; // Si un objectif n'est pas terminé, la quête n'est pas terminée
            }
        }

        // Si tous les objectifs de la quête sont remplis
        if (bQuestCompleted)
        {
            Quest.bIsCompleted = true;
            GiveRewardsForQuest(Quest);
            UE_LOG(LogTemp, Warning, TEXT("La quête %s est terminée!"), *Quest.QuestName);
        }
    }
}



bool UQuestComponent::IsQuestCompleted(const FString& QuestName)
{
    // Vérifie si la quête est terminée
    for (const FQuestData& Quest : Quests)
    {
        if (Quest.QuestName == QuestName)
        {
            return Quest.bIsCompleted;
        }
    }
    return false;
}


void UQuestComponent::GiveRewardsForQuest(const FQuestData& Quest)
{
    for (const FQuestReward& Reward : Quest.Rewards)
    {
        UE_LOG(LogTemp, Warning, TEXT("Reward: %s x%d"), *Reward.ItemID, Reward.Quantity);

        // EXEMPLE : ajout à l'inventaire
       /* if (InventoryComponent)
        {
            InventoryComponent->AddItem(Reward.ItemID, Reward.Quantity);
        }*/
    }
}