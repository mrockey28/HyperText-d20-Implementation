#include "stdlib.h"
#include "types.h"
#include "rpgUtils.h"

static UINT16 XdX(UINT8 numOfDice, UINT8 numOfSides)
{
	UINT8 loop;
	UINT16 diceSum = 0;

	srand(time(NULL));	//Seeding the randomizer

	for (loop=0;loop < numOfDice;loop++)
	{
		diceSum += (rand()%numOfSides)+1;
	}
	return diceSum;
}

UINT16 Xd20(UINT8 numOfDice)
{
	return XdX(numOfDice, 20);
}

UINT16 Xd6(UINT8 numOfDice) 
{
	return XdX(numOfDice, 6);
}


