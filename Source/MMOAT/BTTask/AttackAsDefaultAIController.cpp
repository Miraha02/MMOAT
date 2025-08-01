// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAsDefaultAIController.h"

#include "MMOAT/Character/AI/AIController/Default_AIController.h"

UAttackAsDefaultAIController::UAttackAsDefaultAIController()
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UAttackAsDefaultAIController::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	ADefault_AIController* Default_AIController = Cast<ADefault_AIController>(AIController);

	if (Default_AIController)
	{
		if (Default_AIController->Default_Attack())
		{
			return EBTNodeResult::Succeeded;
		}
		UE_LOG(LogTemp, Warning, TEXT("Attack Failed !"));
		return EBTNodeResult::Failed;
	}

	UE_LOG(LogTemp, Warning, TEXT("AI is not Controller by Default_AI_Controller"))
	return EBTNodeResult::Failed;
}
