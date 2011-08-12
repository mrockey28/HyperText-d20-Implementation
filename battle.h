#ifndef BATTLE_H
#define BATTLE_H

#include "types.h"
#include "enemy.h"
#include "character.h"

#define NUM_OF_MAIN_MENU_OPTIONS 8
#define MAX_DISTANCE 250

class Battle
{
	
	UINT8 distanceToEnemy;
	UINT16 totalRounds;	
	UINT8 playerMoves;
	UINT8 playerMaxMoves;
	BOOL battleFled;

	EnemyHumanoid enemy;
	PlayerCharacter player;

public:
	Battle(UINT8 startingDistance, PlayerCharacter passedPlayer, EnemyHumanoid passedEnemy)
	{
		distanceToEnemy = startingDistance;
		player = passedPlayer;
		enemy = passedEnemy;
		totalRounds = 0;
		battleFled = FALSE;
		playerMaxMoves = player.GetAgilityMod()+2;
		playerMoves = playerMaxMoves;
	}
	void GetFurther(UINT8 distance)
	{
		if (distance+distanceToEnemy > MAX_DISTANCE)
			distanceToEnemy = MAX_DISTANCE;
		else
			distanceToEnemy += distance;
	}
	void GetCloser(UINT8 distance)
	{
		if (distanceToEnemy - distance < 0)
			distanceToEnemy = 0;
		else
			distanceToEnemy -= distance;
	}
	void SpendMoves(UINT8 numberOfMoves)
	{
		if (numberOfMoves >= playerMoves)
			playerMoves = 0;
		else
			playerMoves -= numberOfMoves;
	}
	void MainLoop();
	void MainBattleMenu();
	char GetMainMenuSelection();
	BOOL IsValidMainMenuOption(char);
	BOOL MainMenuSwitcher(char);
	BOOL RunForward();
	BOOL GoBackwards();
	BOOL BackpackMenu();
	BOOL DrawWeapon();
	BOOL UseMeleeWeapon();
	BOOL UseRangedWeapon();
	BOOL MagicMenu();
	BOOL RunAway();
	

};

#endif
