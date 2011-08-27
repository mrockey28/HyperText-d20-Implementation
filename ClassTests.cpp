#include "types.h"
#include "Being.h"
#include "Humanoid.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main()
{
	string playerEnterString;
	Humanoid player(ELF, 34, WIZARD);

	printf("Will: %d, Ref: %d, Str: %d", player.GetWillBonus(), player.GetRefBonus(), player.GetAbilityMod(STR));
	
	
}
