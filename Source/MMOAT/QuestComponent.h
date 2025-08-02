// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestData.h"
#include "QuestComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MMOAT_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Fonction pour ajouter une quête
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuest(const FString& QuestName);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuestFromID(FName QuestRowID);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateQuestOnItemPickup(const FString& ItemID, int32 Quantity);

	// Fonction pour mettre à jour un objectif
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateObjective(EObjectiveType ObjectiveType, const FString& TargetID, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuestFromRow(const FQuestData& QuestRow);

	// Fonction pour vérifier si la quête est terminée
	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool IsQuestCompleted(const FString& QuestName);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<FQuestData>& GetQuests() const { return Quests; }

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void GiveRewardsForQuest(const FQuestData& Quest);

	//UPROPERTY()
	//UInventoryComponent* InventoryComponent;
	// Liste des quêtes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	TArray<FQuestData> Quests;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	UDataTable* QuestDataTable;
};
