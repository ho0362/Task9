#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "HealingActor.generated.h"

UCLASS()
class MYPJ3_API AHealingActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AHealingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
