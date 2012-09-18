#include "types.h"
#include "Beings/Being.h"
#include "Beings/Humanoid.h"
#include "stdio.h"
#include "stdlib.h"
#include <iostream>

int main()
{
	string playerEnterString;
	Humanoid player("myname", Race::GNOME, Clas::WIZARD, 34, 1);
	printf("Will: %d, Ref: %d, Str: %d\n", player.GetWillBonus(), player.GetRefBonus(), player.GetAbilityMod(STR));
	printf("speed: %d, sizeMod: %d", player.GetSpeed(), player.GetSizeModifier());
}
