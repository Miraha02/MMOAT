#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "QuestData.generated.h"

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 1;
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
    OT_Collect UMETA(DisplayName = "Collect"),
    OT_Kill UMETA(DisplayName = "Kill"),
    OT_Talk UMETA(DisplayName = "Talk"),
};

USTRUCT(BlueprintType)
struct FObjectiveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EObjectiveType ObjectiveType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TargetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TargetQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentQuantity = 0;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FObjectiveData> Objectives;

    // NOUVEAU : récompenses
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestReward> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCompleted = false;
};
