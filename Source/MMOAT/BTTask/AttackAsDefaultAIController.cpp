// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAsDefaultAIController.h"

UAttackAsDefaultAIController::UAttackAsDefaultAIController()
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UAttackAsDefaultAIController::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
