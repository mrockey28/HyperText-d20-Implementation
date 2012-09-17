#include "stdlib.h"
#include "types.h"
#include "rpgUtils.h"

static uint16 XdX(uint8 numOfDice, uint8 numOfSides)
{
	uint8 loop;
	uint16 diceSum = 0;

	srand(time(NULL));	//Seeding the randomizer

	for (loop=0;loop < numOfDice;loop++)
	{
		diceSum += (rand()%numOfSides)+1;
	}
	return diceSum;
}

uint16 Xd20(uint8 numOfDice)
{
	return XdX(numOfDice, 20);
}
uint16 Xd6(uint8 numOfDice)
{
	return XdX(numOfDice, 6);
}


