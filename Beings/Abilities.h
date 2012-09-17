/*
 * Abilities.h
 *
 *  Created on: Sep 16, 2012
 *      Author: mrockey
 */

#ifndef ABILITIES_H_
#define ABILITIES_H_

#include "../types.h"

typedef enum AbilityEnum
{
    STR,
    DEX,
    CON,
    INT,
    WIS,
    CHA,
    TOTAL_ABILITIES
}AbilityEnum;

class Abilities {

protected:
	int8 abilities[TOTAL_ABILITIES];

public:
	Abilities();
	virtual ~Abilities();
    int8 GetAbilityMod(AbilityEnum ability);
    int8 GetAbility(AbilityEnum ability);
    void SetAbility(AbilityEnum ability, int8 value);
};

#endif /* ABILITIES_H_ */
