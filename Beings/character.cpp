#include "character.h"
#include "stdio.h"

class Modifiers
{

}

#define MAX_GOLD 999999


BOOL PlayerCharacter::Buy(UINT32 cost)
{
	if (cost > gold)
	{
		return FALSE;
	}
	else
	{
		gold -= cost;
		return TRUE;
	}
}

void PlayerCharacter::RemoveGold(UINT32 amnt)
{
	if (Buy(amnt) == FALSE)
	{
		gold = 0;
	}
}

void PlayerCharacter::AddGold(UINT32 amnt)
{
	if ((amnt+gold) > MAX_GOLD)
	{
		gold = MAX_GOLD;
	}
	else
	{
		gold += amnt;
	}
}

void PlayerCharacter::Sell(UINT32 cost)
{
	AddGold(cost);
}

UINT32 PlayerCharacter::GetGold()
{
	return gold;
}
	
