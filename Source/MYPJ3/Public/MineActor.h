// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "MineActor.generated.h"

UCLASS()
class MYPJ3_API AMineActor : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AMineActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay;

	bool bHasExploded;
	FTimerHandle ExplosionTimerHandle;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();

};
