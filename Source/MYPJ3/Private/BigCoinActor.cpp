#include "BigCoinActor.h"

ABigCoinActor::ABigCoinActor()
{
	PointValue = 50;
	ItemType = "BigCoin";
}

void ABigCoinActor::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}
