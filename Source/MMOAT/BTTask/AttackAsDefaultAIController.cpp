// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAsDefaultAIController.h"

#include "MMOAT/Character/AI/AIController/Default_AIController.h"

UAttackAsDefaultAIController::UAttackAsDefaultAIController()
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UAttackAsDefaultAIController::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ADefault_AIController* Default_AIController = Cast<ADefault_AIController>(AIController->GetPawn());

	if (Default_AIController)
	{
		Default_AIController->Default_Attack();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
