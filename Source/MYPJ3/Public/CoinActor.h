// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "CoinActor.generated.h"

UCLASS()
class MYPJ3_API ACoinActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	ACoinActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

	virtual void ActivateItem(AActor* Activator) override;
};
