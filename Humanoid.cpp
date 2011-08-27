#include "types.h"
#include "stdio.h"
#include "string.h"
#include "Being.h"
#include "Humanoid.h"

void Humanoid::SetRaceBonuses()
{
    memset(abilities.raceBonus, 0x00, TOTAL_ABILITIES);
    switch(race)
    {
        case DWARF:
            abilities.raceBonus[CON] = 2;
            abilities.raceBonus[CHA] = -2;
            break;
        case ELF:
            abilities.raceBonus[DEX] = 2;
            abilities.raceBonus[CON] = -2;
            break;
        case GNOME:
            abilities.raceBonus[STR] = 2;
            abilities.raceBonus[CON] = -2;
            break;
        case HALF_ORC:
            abilities.raceBonus[STR] = 2;
            abilities.raceBonus[INT] = -2;
            abilities.raceBonus[CHA] = -2;
            break;
        case HALFLING:
            abilities.raceBonus[DEX] = 2;
            abilities.raceBonus[STR] = -2;
            break;
        case HUMAN:
        case HALF_ELF:
        default:
            break;
    }
}

void Humanoid::SetAgeBonuses()
{
    memset(abilities.ageBonus, 0x00, TOTAL_ABILITIES);
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
    abilities.ageBonus[STR] = -1;
    abilities.ageBonus[DEX] = -1;
    abilities.ageBonus[CON] = -1;
    abilities.ageBonus[INT] = 1;
    abilities.ageBonus[WIS] = 1;
    abilities.ageBonus[CHA] = 1;

}

void Humanoid::SetOldAge()
{
    abilities.ageBonus[STR] = -2;
    abilities.ageBonus[DEX] = -2;
    abilities.ageBonus[CON] = -2;
    abilities.ageBonus[INT] = 1;
    abilities.ageBonus[WIS] = 1;
    abilities.ageBonus[CHA] = 1;
}

void Humanoid::SetVenerableAge()
{
    abilities.ageBonus[STR] = -3;
    abilities.ageBonus[DEX] = -3;
    abilities.ageBonus[CON] = -3;
    abilities.ageBonus[INT] = 1;
    abilities.ageBonus[WIS] = 1;
    abilities.ageBonus[CHA] = 1;
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

void Humanoid::CalculateBaseSaveBonus()
{
    switch (clas)
    {
        case BARBARIAN:
        case FIGHTER:
        case PALADIN:
            SetBaseSaveBonus(FORT, level/2 + 2);
            SetBaseSaveBonus(REF, level/3);
            SetBaseSaveBonus(WILL, level/3);
            break;
        case BARD:
            SetBaseSaveBonus(FORT, level/3);
            SetBaseSaveBonus(REF, level/2 + 2);
            SetBaseSaveBonus(WILL, level/2 + 2);
            break;
        case CLERIC:
        case DRUID:
            SetBaseSaveBonus(FORT, level/2 + 2);
            SetBaseSaveBonus(REF, level/3);
            SetBaseSaveBonus(WILL, level/2 + 2);
            break;
        case MONK:
            SetBaseSaveBonus(FORT, level/2 + 2);
            SetBaseSaveBonus(REF, level/2 + 2);
            SetBaseSaveBonus(WILL, level/2 + 2);
            break;
        case RANGER:
            SetBaseSaveBonus(FORT, level/2 + 2);
            SetBaseSaveBonus(REF, level/2 + 2);
            SetBaseSaveBonus(WILL, level/3);
            break;
        case ROGUE:
            SetBaseSaveBonus(FORT, level/3);
            SetBaseSaveBonus(REF, level/2 + 2);
            SetBaseSaveBonus(WILL, level/3);
            break;
        case SORCERER:
        case WIZARD:
            SetBaseSaveBonus(FORT, level/3);
            SetBaseSaveBonus(REF, level/3);
            SetBaseSaveBonus(WILL, level/2 + 2);
            break;
    }
}
