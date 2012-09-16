#ifndef CHARACTER_H
#define CHARACTER_H

#include "..\types.h"
#include "..\equipment.h"
#include "Being.h"
#include "Humanoid.h"

#define MAX_NAME_SIZE

//Inherit from Humanoid
class PlayerCharacter: public Humanoid
{
	uint16 xp;
	uint32 gold;


public:
	PlayerCharacter()
	{
		gold = 0;
		xp = 0;
	}
	bool Buy(uint32 cost);
	void RemoveGold(uint32 amnt);
	void AddGold(uint32 amnt);
	void Sell(uint32 cost);
	uint32 GetGold();
};

#endif
