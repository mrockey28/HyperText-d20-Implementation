#include "character.h"
#include "stdio.h"

class Modifiers
{

};

#define MAX_GOLD 999999


bool PlayerCharacter::Buy(uint32 cost)
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

void PlayerCharacter::RemoveGold(uint32 amnt)
{
	if (Buy(amnt) == FALSE)
	{
		gold = 0;
	}
}

void PlayerCharacter::AddGold(uint32 amnt)
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

void PlayerCharacter::Sell(uint32 cost)
{
	AddGold(cost);
}

uint32 PlayerCharacter::GetGold()
{
	return gold;
}
	
