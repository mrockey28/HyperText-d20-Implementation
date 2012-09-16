#include "types.h"
#include "Beings\Being.h"
#include "Beings\Humanoid.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main()
{
	string playerEnterString;
	Humanoid player(ELF, 34, WIZARD);

	printf("Will: %d, Ref: %d, Str: %d", player.GetWillBonus(), player.GetRefBonus(), player.GetAbilityMod(STR));
	
	
}
