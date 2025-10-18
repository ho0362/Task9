#include "HealingActor.h"
#include "SpartaCharacter.h"

AHealingActor::AHealingActor()
{
	HealAmount = 20.0f;
	ItemType = "Healing";
}
void AHealingActor::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* PlayerCharacter =Cast<ASpartaCharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}
	
		DestroyItem();
	}
	
}