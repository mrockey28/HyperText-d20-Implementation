#include "character.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main()
{
	string playerEnterString;
	PlayerCharacter player;
	
	player.SetStrength(17);
	player.RecalcCharacter();
	player.FullHeal();
	printf("The strength is: %d\n", player.GetStrength());
	printf("The modifier is: %d\n", player.GetStrengthMod());
	printf("Current Health is: %d\n", player.GetCurrentHealth());
	printf("KILLING...\n");
	player.Kill();
	system("clear");
	printf("Current Health is: %d\n", player.GetCurrentHealth());
	player.Heal(6);
	printf("Current Health is: %d\n", player.GetCurrentHealth());
	player.Heal(6);
	printf("Current Health is: %d\n", player.GetCurrentHealth());
	player.Hurt(13);
	printf("Current Health is: %d\n", player.GetCurrentHealth());
	printf("Current gold is: %lu\n", player.GetGold());
	player.AddGold(1200);
	printf("Current gold is: %lu\n", player.GetGold());
	player.Sell(200);
	printf("Current gold is: %lu\n", player.GetGold());
	player.Buy(900);
	printf("Current gold is: %lu\n", player.GetGold());
	std::cin >> playerEnterString;
	player.SetName(playerEnterString);
	playerEnterString = player.GetName();
	printf("\nMy name is %s\n", playerEnterString.c_str());
}
