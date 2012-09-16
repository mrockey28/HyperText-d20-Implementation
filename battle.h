#ifndef BATTLE_H
#define BATTLE_H

#include "types.h"
#include "Beings\enemy.h"
#include "Beings\character.h"

#define NUM_OF_MAIN_MENU_OPTIONS 8
#define MAX_DISTANCE 250

class Battle
{
	
	uint8 distanceToEnemy;
	uint16 totalRounds;
	uint8 playerMoves;
	uint8 playerMaxMoves;
	bool battleFled;

	EnemyHumanoid enemy;
	PlayerCharacter player;

public:
	Battle(uint8 startingDistance, PlayerCharacter passedPlayer, EnemyHumanoid passedEnemy)
	{
		distanceToEnemy = startingDistance;
		player = passedPlayer;
		enemy = passedEnemy;
		totalRounds = 0;
		battleFled = FALSE;
		playerMaxMoves = player.GetAgilityMod()+2;
		playerMoves = playerMaxMoves;
	}
	void GetFurther(uint8 distance)
	{
		if (distance+distanceToEnemy > MAX_DISTANCE)
			distanceToEnemy = MAX_DISTANCE;
		else
			distanceToEnemy += distance;
	}
	void GetCloser(uint8 distance)
	{
		if (distanceToEnemy - distance < 0)
			distanceToEnemy = 0;
		else
			distanceToEnemy -= distance;
	}
	void SpendMoves(uint8 numberOfMoves)
	{
		if (numberOfMoves >= playerMoves)
			playerMoves = 0;
		else
			playerMoves -= numberOfMoves;
	}
	void MainLoop();
	void MainBattleMenu();
	char GetMainMenuSelection();
	bool IsValidMainMenuOption(char);
	bool MainMenuSwitcher(char);
	bool RunForward();
	bool GoBackwards();
	bool BackpackMenu();
	bool DrawWeapon();
	bool UseMeleeWeapon();
	bool UseRangedWeapon();
	bool MagicMenu();
	bool RunAway();
	

};

#endif
