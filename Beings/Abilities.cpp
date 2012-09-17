/*
 * Abilities.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: mrockey
 */

#include "Abilities.h"
#include "string.h"

Abilities::Abilities() {
	memset(abilities, 0x00, TOTAL_ABILITIES);
}

Abilities::~Abilities() {
	// TODO Auto-generated destructor stub
}

int8 Abilities::GetAbility(AbilityEnum ability)
{
	return abilities[ability];
}

void Abilities::SetAbility(AbilityEnum ability, int8 value)
{
	abilities[ability] = value;
}

int8 Abilities::GetAbilityMod(AbilityEnum ability)
{
	return (int8)((GetAbility(ability)) / 2) - 5;
}

