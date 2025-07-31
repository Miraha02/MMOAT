#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// Wrapper pour UHT
UINTERFACE(Blueprintable)
class MMOAT_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

// Interface réelle à implémenter
class MMOAT_API IInteractable
{
	GENERATED_BODY()

public:

	// Fonction appelée pour interagir avec l’objet
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool Interact(AActor* Interactor);
};
