#include "../types.h"
#include "stdio.h"
#include "string.h"
#include "Humanoid.h"

/**
 * Will create a non-meaningful object. Should not be used.
 */
Humanoid::Humanoid() : race(Race::HUMAN), clas(Clas::BARBARIAN){}

/**
 *
 * @param name Name of the humanoid
 * @param race Race of the humanoid
 * @param age Age of the humanoid
 * @param clas Class of the humanoid
 * @param level Current level of the humanoid
 */
Humanoid::Humanoid(string name, Race race, Clas clas, uint16 age, uint8 level)
	: 	Being(name, GetRaceSize(race), GetRaceSpeed(race), GetBaseRefBonus(clas, level),
			GetBaseWillBonus(clas, level), GetBaseFortBonus(clas, level)),
		race(race),
		clas(clas),
		age(age),
		level(level)
{
	SetAgeBonuses();
	SetRaceBonuses();
	CalculateBaseAttackBonus();
	GetRaceSize();
}

/**
 * Get the size of this humanoid.
 *
 * @return The size of the humanoid, as defined by SizeEnum
 */
Size Humanoid::GetRaceSize()
{
	return GetRaceSize(race);
}

/**
 * Get the size of a humanoid of a given race.
 *
 * @param race The race used to find the size.
 * @return The size of the humanoid, as defined by SizeEnum
 */
Size Humanoid::GetRaceSize(Race race)
{
	switch(race)
	{
		case Race::HUMAN:
		case Race::ELF:
		case Race::DWARF:
		case Race::HALF_ELF:
		case Race::HALF_ORC:
			return Size::MEDIUM;
		case Race::GNOME:
		case Race::HALFLING:
			return Size::SMALL;
	}
	return Size::MEDIUM;
}

uint8 Humanoid::GetRaceSpeed()
{
	return GetRaceSpeed(race);
}

uint8 Humanoid::GetRaceSpeed(Race race)
{
	switch(race)
	{
		case Race::HUMAN:
		case Race::ELF:
		case Race::HALF_ELF:
		case Race::HALF_ORC:
			return 30;
		case Race::GNOME:
		case Race::DWARF:
		case Race::HALFLING:
			return 20;
	}
	return 30;
}

void Humanoid::SetRaceBonuses()
{
    switch(race)
    {
        case Race::DWARF:
            abilities.raceBonus.SetAbility(CON, 2);
            abilities.raceBonus.SetAbility(CHA, -2);
            break;
        case Race::ELF:
            abilities.raceBonus.SetAbility(DEX, 2);
            abilities.raceBonus.SetAbility(CON, -2);
            break;
        case Race::GNOME:
            abilities.raceBonus.SetAbility(STR, 2);
            abilities.raceBonus.SetAbility(CON, -2);
            break;
        case Race::HALF_ORC:
            abilities.raceBonus.SetAbility(STR, 2);
            abilities.raceBonus.SetAbility(INT, -2);
            abilities.raceBonus.SetAbility(CHA, -2);
            break;
        case Race::HALFLING:
            abilities.raceBonus.SetAbility(DEX, 2);
            abilities.raceBonus.SetAbility(STR, -2);
            break;
        case Race::HUMAN:
        case Race::HALF_ELF:
        default:
            break;
    }
}

void Humanoid::SetAgeBonuses()
{
    switch(race)
    {
        case Race::HUMAN:
            if (age < 35) {}
            else if (age < 53) SetMiddleAge();
            else if (age <70) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::DWARF:
            if (age < 125) {}
            else if (age < 188) SetMiddleAge();
            else if (age < 250) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::ELF:
            if (age < 175) {}
            else if (age < 263) SetMiddleAge();
            else if (age < 350) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::GNOME:
            if (age < 100) {}
            else if (age < 150) SetMiddleAge();
            else if (age < 200) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::HALF_ELF:
            if (age < 62) {}
            else if (age < 93) SetMiddleAge();
            else if (age < 125) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::HALF_ORC:
            if (age < 30) {}
            else if (age < 45) SetMiddleAge();
            else if (age < 60) SetOldAge();
            else SetVenerableAge();
            break;
        case Race::HALFLING:
            if (age < 50) {}
            else if (age < 75) SetMiddleAge();
            else if (age < 100) SetOldAge();
            else SetVenerableAge();
            break;
    }
}


void Humanoid::SetMiddleAge()
{
    abilities.ageBonus.SetAbility(STR, -1);
    abilities.ageBonus.SetAbility(DEX, -1);
    abilities.ageBonus.SetAbility(CON, -1);
    abilities.ageBonus.SetAbility(INT, 1);
    abilities.ageBonus.SetAbility(WIS, 1);
    abilities.ageBonus.SetAbility(CHA, 1);
}

void Humanoid::SetOldAge()
{
    abilities.ageBonus.SetAbility(STR, -2);
    abilities.ageBonus.SetAbility(DEX, -2);
    abilities.ageBonus.SetAbility(CON, -2);
    abilities.ageBonus.SetAbility(INT, 1);
    abilities.ageBonus.SetAbility(WIS, 1);
    abilities.ageBonus.SetAbility(CHA, 1);
}

void Humanoid::SetVenerableAge()
{
    abilities.ageBonus.SetAbility(STR, -3);
    abilities.ageBonus.SetAbility(DEX, -3);
    abilities.ageBonus.SetAbility(CON, -3);
    abilities.ageBonus.SetAbility(INT, 1);
    abilities.ageBonus.SetAbility(WIS, 1);
    abilities.ageBonus.SetAbility(CHA, 1);
}

void Humanoid::SetHitDie()
{
    switch (clas)
    {
        case Clas::BARBARIAN:
            hitDie = 12;
            break;
        case Clas::BARD:
        case Clas::ROGUE:
            hitDie = 6;
            break;
        case Clas::CLERIC:
        case Clas::DRUID:
        case Clas::MONK:
        case Clas::RANGER:
            hitDie = 8;
            break;
        case Clas::FIGHTER:
        case Clas::PALADIN:
            hitDie = 10;
            break;
        case Clas::SORCERER:
        case Clas::WIZARD:
            hitDie = 4;
            break;
        default:
            break;
    }

}

void Humanoid::CalculateBaseAttackBonus()
{
    switch (clas)
    {
        case Clas::BARBARIAN:
        case Clas::FIGHTER:
        case Clas::PALADIN:
        case Clas::RANGER:
            SetBaseAttackBonus(0, level);
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, (GetBaseAttackBonus(1) - 10));
            SetBaseAttackBonus(3, (GetBaseAttackBonus(2) - 15));
            break;
        case Clas::BARD:
        case Clas::CLERIC:
        case Clas::DRUID:
        case Clas::MONK:
        case Clas::ROGUE:
            SetBaseAttackBonus(0, (level - 1) - ((level-1)/4));
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, (GetBaseAttackBonus(1) - 10));
            SetBaseAttackBonus(3, 0);
            break;
        case Clas::SORCERER:
        case Clas::WIZARD:
            SetBaseAttackBonus(0, level/2);
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, 0);
            SetBaseAttackBonus(3, 0);
            break;
        default:
            break;
    }
}

int8 Humanoid::GetBaseWillBonus()
{
	return GetBaseWillBonus(clas, level);
}

int8 Humanoid::GetBaseRefBonus()
{
	return GetBaseRefBonus(clas, level);
}

int8 Humanoid::GetBaseFortBonus()
{
	return GetBaseFortBonus(clas, level);
}

int8 Humanoid::GetBaseWillBonus(Clas clas, uint8 level)
{
    switch (clas)
    {
		case Clas::SORCERER:
		case Clas::WIZARD:
        case Clas::BARD:
        case Clas::CLERIC:
        case Clas::DRUID:
        case Clas::MONK:
        	return level/2 + 2;
        case Clas::BARBARIAN:
        case Clas::FIGHTER:
        case Clas::PALADIN:
        case Clas::RANGER:
        case Clas::ROGUE:
        	return level/3;
    }
    return 0;
}

int8 Humanoid::GetBaseRefBonus(Clas clas, uint8 level)
{
    switch (clas)
    {
        case Clas::BARD:
        case Clas::MONK:
        case Clas::RANGER:
        case Clas::ROGUE:
        	return level/2 + 2;
        case Clas::BARBARIAN:
        case Clas::FIGHTER:
        case Clas::PALADIN:
        case Clas::CLERIC:
        case Clas::DRUID:
        case Clas::SORCERER:
        case Clas::WIZARD:
        	return level/3;
    }
    return 0;
}

int8 Humanoid::GetBaseFortBonus(Clas clas, uint8 level)
{
    switch (clas)
    {
        case Clas::BARBARIAN:
        case Clas::FIGHTER:
        case Clas::PALADIN:
        case Clas::CLERIC:
        case Clas::DRUID:
        case Clas::MONK:
        case Clas::RANGER:
        	return level/2 + 2;
        case Clas::BARD:
        case Clas::ROGUE:
        case Clas::SORCERER:
        case Clas::WIZARD:
        	return level/3;
    }
    return 0;
}
