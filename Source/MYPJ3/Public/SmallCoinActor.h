#pragma once

#include "CoreMinimal.h"
#include "CoinActor.h"
#include "SmallCoinActor.generated.h"

/**
 * 
 */
UCLASS()
class MYPJ3_API ASmallCoinActor : public ACoinActor
{
	GENERATED_BODY()
	
public:
	ASmallCoinActor();

	virtual void ActivateItem(AActor* Activator) override;
};
