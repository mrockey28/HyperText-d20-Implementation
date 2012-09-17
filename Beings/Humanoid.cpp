#include "../types.h"
#include "stdio.h"
#include "string.h"
#include "Humanoid.h"

Humanoid::Humanoid(){}
Humanoid::Humanoid(string nameP, RaceEnum passedRace, uint16 passedAge, ClassEnum passedClass)
	: level(1), Being(nameP, GetRaceSize(passedRace), GetRaceSpeed(passedRace), GetBaseSaveBonus(REF, passedClass),
			GetBaseSaveBonus(WILL, passedClass), GetBaseSaveBonus(FORT, passedClass))
{
	level = 1;
	race = passedRace;
	age = passedAge;
	clas = passedClass;
	SetAgeBonuses();
	SetRaceBonuses();
	CalculateBaseAttackBonus();
}

SizeEnum Humanoid::GetRaceSize()
{
	return GetRaceSize(race);
}

SizeEnum Humanoid::GetRaceSize(RaceEnum raceP)
{
	switch(raceP)
	{
		case HUMAN:
		case ELF:
		case DWARF:
		case HALF_ELF:
		case HALF_ORC:
			return MEDIUM;
		case GNOME:
		case HALFLING:
			return SMALL;
	}
	return MEDIUM;
}

uint8 Humanoid::GetRaceSpeed()
{
	return GetRaceSpeed(race);
}

uint8 Humanoid::GetRaceSpeed(RaceEnum raceP)
{
	switch(raceP)
	{
		case HUMAN:
		case ELF:
		case HALF_ELF:
		case HALF_ORC:
			return 30;
		case GNOME:
		case DWARF:
		case HALFLING:
			return 20;
	}
	return 30;
}

void Humanoid::SetRaceBonuses()
{
    switch(race)
    {
        case DWARF:
            abilities.raceBonus.SetAbility(CON, 2);
            abilities.raceBonus.SetAbility(CHA, -2);
            break;
        case ELF:
            abilities.raceBonus.SetAbility(DEX, 2);
            abilities.raceBonus.SetAbility(CON, -2);
            break;
        case GNOME:
            abilities.raceBonus.SetAbility(STR, 2);
            abilities.raceBonus.SetAbility(CON, -2);
            break;
        case HALF_ORC:
            abilities.raceBonus.SetAbility(STR, 2);
            abilities.raceBonus.SetAbility(INT, -2);
            abilities.raceBonus.SetAbility(CHA, -2);
            break;
        case HALFLING:
            abilities.raceBonus.SetAbility(DEX, 2);
            abilities.raceBonus.SetAbility(STR, -2);
            break;
        case HUMAN:
        case HALF_ELF:
        default:
            break;
    }
}

void Humanoid::SetAgeBonuses()
{
    switch(race)
    {
        case HUMAN:
            if (age < 35) {}
            else if (age < 53) SetMiddleAge();
            else if (age <70) SetOldAge();
            else SetVenerableAge();
            break;
        case DWARF:
            if (age < 125) {}
            else if (age < 188) SetMiddleAge();
            else if (age < 250) SetOldAge();
            else SetVenerableAge();
            break;
        case ELF:
            if (age < 175) {}
            else if (age < 263) SetMiddleAge();
            else if (age < 350) SetOldAge();
            else SetVenerableAge();
            break;
        case GNOME:
            if (age < 100) {}
            else if (age < 150) SetMiddleAge();
            else if (age < 200) SetOldAge();
            else SetVenerableAge();
            break;
        case HALF_ELF:
            if (age < 62) {}
            else if (age < 93) SetMiddleAge();
            else if (age < 125) SetOldAge();
            else SetVenerableAge();
            break;
        case HALF_ORC:
            if (age < 30) {}
            else if (age < 45) SetMiddleAge();
            else if (age < 60) SetOldAge();
            else SetVenerableAge();
            break;
        case HALFLING:
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
        case BARBARIAN:
            hitDie = 12;
            break;
        case BARD:
        case ROGUE:
            hitDie = 6;
            break;
        case CLERIC:
        case DRUID:
        case MONK:
        case RANGER:
            hitDie = 8;
            break;
        case FIGHTER:
        case PALADIN:
            hitDie = 10;
            break;
        case SORCERER:
        case WIZARD:
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
        case BARBARIAN:
        case FIGHTER:
        case PALADIN:
        case RANGER:
            SetBaseAttackBonus(0, level);
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, (GetBaseAttackBonus(1) - 10));
            SetBaseAttackBonus(3, (GetBaseAttackBonus(2) - 15));
            break;
        case BARD:
        case CLERIC:
        case DRUID:
        case MONK:
        case ROGUE:
            SetBaseAttackBonus(0, (level - 1) - ((level-1)/4));
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, (GetBaseAttackBonus(1) - 10));
            SetBaseAttackBonus(3, 0);
            break;
        case SORCERER:
        case WIZARD:
            SetBaseAttackBonus(0, level/2);
            SetBaseAttackBonus(1, (GetBaseAttackBonus(0) - 5));
            SetBaseAttackBonus(2, 0);
            SetBaseAttackBonus(3, 0);
            break;
        default:
            break;
    }
}

int8 Humanoid::GetBaseSaveBonus(SaveThrowEnum saveType, ClassEnum clasP)
{
    switch (clasP)
    {
        case BARBARIAN:
        case FIGHTER:
        case PALADIN:
        	if (saveType == FORT) return level/2 + 2;
        	if (saveType == REF) return level/3;
        	if (saveType == WILL) return level/3;
            break;
        case BARD:
        	if (saveType == FORT) return level/3;
        	if (saveType == REF) return level/2 + 2;
        	if (saveType == WILL) return level/2 + 2;
            break;
        case CLERIC:
        case DRUID:
        	if (saveType == FORT) return level/2 + 2;
        	if (saveType == REF) return level/3;
        	if (saveType == WILL) return level/2 + 2;
            break;
        case MONK:
        	if (saveType == FORT) return level/2 + 2;
        	if (saveType == REF) return level/2 + 2;
        	if (saveType == WILL) return level/2 + 2;
            break;
        case RANGER:
        	if (saveType == FORT) return level/2 + 2;
        	if (saveType == REF) return level/2 + 2;
        	if (saveType == WILL) return level/3;
            break;
        case ROGUE:
        	if (saveType == FORT) return level/3;
        	if (saveType == REF) return level/2 + 2;
        	if (saveType == WILL) return level/3;
            break;
        case SORCERER:
        case WIZARD:
        	if (saveType == FORT) return level/3;
        	if (saveType == REF) return level/3;
        	if (saveType == WILL) return level/2 + 2;
            break;
    }
    return 0;
}
