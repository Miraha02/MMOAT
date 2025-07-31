// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackAsDefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class MMOAT_API UAttackAsDefaultAIController : public UBTTaskNode
{
	GENERATED_BODY()

private:

protected:

public:

private:

	UAttackAsDefaultAIController();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	
	
};
