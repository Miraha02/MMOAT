#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UQuestComponent::BeginPlay()
{
    Super::BeginPlay();
    // Cherche le InventoryComponent sur le même Actor
    InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();

    if (!InventoryComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on %s"), *GetOwner()->GetName());
    }
}

void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!InventoryComponent)
    {
        InventoryComponent = GetOwner()->FindComponentByClass<UInventoryComponent>();
        if (InventoryComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("InventoryComponent récupéré dans Tick: %s"), *InventoryComponent->GetName());
        }
    }

}

void UQuestComponent::AddQuest(const FName& QuestName)
{
    FQuestData NewQuest;
    NewQuest.QuestName = QuestName;
    NewQuest.bIsCompleted = false;
    Quests.Add(NewQuest);
    UE_LOG(LogTemp, Warning, TEXT("New Quest Add %s"), *QuestName.ToString());

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
        UE_LOG(LogTemp, Warning, TEXT("Quest added: %s"), *NewQuest.QuestName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No quest found for ID: %s"), *QuestRowID.ToString());
    }
}

void UQuestComponent::AddQuestFromRow(const FQuestData& QuestRow)
{
    Quests.Add(QuestRow);
    UE_LOG(LogTemp, Warning, TEXT("Quest %s added from row!"), *QuestRow.QuestName.ToString());
}

void UQuestComponent::UpdateObjective(EObjectiveType ObjectiveType, const FName& TargetID, int64 Quantity)
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
            UE_LOG(LogTemp, Warning, TEXT("Quest %s completed!"), *Quest.QuestName.ToString());
        }
    }
}

void UQuestComponent::UpdateQuestOnItemPickup(const FName& ItemID, int64 Quantity)
{
    UE_LOG(LogTemp, Warning, TEXT("%s x%d"),*ItemID.ToString(),Quantity);
    for (FQuestData& Quest : Quests)
    {
        if (Quest.bIsCompleted)
            continue;

        bool bQuestCompleted = true;

        for (FObjectiveData& Obj : Quest.Objectives)
        {
            if (Obj.ObjectiveType == EObjectiveType::OT_Collect && Obj.TargetID == ItemID)
            {
                if (Quantity == -1) {
                    Obj.CurrentQuantity++;
                }
                else {
                    Obj.CurrentQuantity += Quantity;
                }
                Obj.CurrentQuantity = FMath::Clamp(Obj.CurrentQuantity, 0, Obj.TargetQuantity);

                if (Obj.CurrentQuantity >= Obj.TargetQuantity)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Objective %s for quest %s completed!"),
                        *ItemID.ToString(), *Quest.QuestName.ToString());
                }
            }

            if (Obj.CurrentQuantity < Obj.TargetQuantity)
            {
                bQuestCompleted = false;
            }
        }

        if (bQuestCompleted)
        {
            Quest.bIsCompleted = true;
            GiveRewardsForQuest(Quest);
            UE_LOG(LogTemp, Warning, TEXT("Quest %s is completed!"), *Quest.QuestName.ToString());
        }
    }
}

bool UQuestComponent::IsQuestCompleted(const FName& QuestName)
{
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
        UE_LOG(LogTemp, Warning, TEXT("Reward: %s x%d"), *Reward.ItemID.ToString(), Reward.Quantity);

        if (InventoryComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("Reward: %s x%d"), *Reward.ItemID.ToString(), Reward.Quantity);
            InventoryComponent->GiveItem(Reward.ItemID, Reward.Quantity);
        }
    }
}
