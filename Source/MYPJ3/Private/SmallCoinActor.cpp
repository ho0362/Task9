#include "SmallCoinActor.h"

ASmallCoinActor::ASmallCoinActor()
{
	PointValue = 10;
	ItemType = "SmallCoin";
}
void ASmallCoinActor::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
}