#ifndef ENEMY_H
#define ENEMY_H

#include "..\types.h"
#include "character.h"

	
//Inherit from Being
class Enemy: public virtual Being
{
	uint16 xpBonusGranted;
	bool bossFlag;

public:
	Enemy()
	{
		bossFlag = 0;
	}
	bool GetBossFlag()
	{
		return bossFlag;
	}
	uint16 GetXpBonus();
};

//Inherit from Enemy & Humanoid
class EnemyHumanoid: public Humanoid, public Enemy
{
	
};



#endif
