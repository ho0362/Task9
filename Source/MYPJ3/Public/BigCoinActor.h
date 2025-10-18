#pragma once

#include "CoreMinimal.h"
#include "CoinActor.h"
#include "BigCoinActor.generated.h"

UCLASS()
class MYPJ3_API ABigCoinActor : public ACoinActor
{
	GENERATED_BODY()
	
public:
	ABigCoinActor();

	virtual void ActivateItem(AActor* Activator) override;
};
