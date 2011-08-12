#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"
#include "character.h"

	
//Inherit from Being
class Enemy: public virtual Being
{
	UINT16 xpBonusGranted;
	BOOL bossFlag;

public:
	Enemy()
	{
		bossFlag = 0;
	}
	BOOL GetBossFlag()
	{
		return bossFlag;
	}
	UINT16 GetXpBonus();
};

//Inherit from Enemy & Humanoid
class EnemyHumanoid: public Humanoid, public Enemy
{
	
};



#endif
