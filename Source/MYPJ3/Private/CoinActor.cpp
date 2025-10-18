#include "CoinActor.h"
#include "Engine/World.h"
#include "SpartaGameState.h"
ACoinActor::ACoinActor()
{
	PointValue = 0;
	ItemType = "DefaultCoin";
}

void ACoinActor::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if(Activator && Activator->ActorHasTag("Player"))
	{
		if(UWorld* World  = GetWorld())
		{
			if(ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		DestroyItem();
	}
}