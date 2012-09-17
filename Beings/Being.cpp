#include "../types.h"
#include "Being.h"


Being::Being()
{
	skills.reqToBeTrained = 0x118810A0;
	CalculateMaxHealth();

}

Being::Being(string nameP, SizeEnum sizeP, uint8 speedP, int8 refSaveP, int8 willSaveP, int8 fortSaveP)
{
	name = nameP;
	size = sizeP;
	speed = speedP;
	baseSaveBonus[REF] = refSaveP;
	baseSaveBonus[WILL] = willSaveP;
	baseSaveBonus[FORT] = fortSaveP;
}

int8 Being::GetArmorClass()
{
	return GetArmorClass(0, true);
}

int8 Being::GetArmorClass(int8 armorPenalty)
{
	return GetArmorClass(armorPenalty, true);
}

int8 Being::GetArmorClass(int8 armorPenalty, bool canUseDexBonus)
{
	return 10 + (canUseDexBonus * (GetAbilityMod(DEX) - armorPenalty)) + GetSizeModifier();
}

int8 Being::GetSizeModifier()
{
	switch(size)
	{
		case FINE:
			return 8;
		case DIMINUTIVE:
			return 4;
		case TINY:
			return 2;
		case SMALL:
			return 1;
		case MEDIUM:
			return 0;
		case LARGE:
			return -1;
		case HUGE:
			return -2;
		case GARGANTUAN:
			return -4;
		case COLOSSAL:
			return -8;
	}
	return 0;
}

int8 Being::GetInitiativeBonus()
{
	return GetAbilityMod(DEX);
}

uint8 Being::GetSkillMod(SkillEnum skill)
{
    return skills.ranks[skill] + GetSkillAbilityMod(skill) + skills.miscMod[skill];
}


void Being::AddSkillRanks(SkillEnum skill, uint8 ranksToAdd)
{
    skills.ranks[skill] += ranksToAdd;
}


void Being::ChangeSkillMiscMod(SkillEnum skill, int8 delta)
{
    if (delta < 0)
    {
        if ((int8)skills.miscMod[skill] - delta < 0)
        {
            skills.miscMod[skill] = 0;
        }
        else
        {
            skills.miscMod[skill] -= uint8(delta*(-1));
        }
    }
    else
    {
        skills.miscMod[skill] += (uint8)delta;
    }
}


uint8 Being::GetSkillAbilityMod(SkillEnum skill)
{
    switch(skill)
    {
        case CLIMB:
        case JUMP:
        case SWIM:
            return GetAbilityMod(STR);
        case BALANCE:
        case ESCAPE_ARTIST:
        case HIDE:
        case MOVE_SILENTLY:
        case OPEN_LOCK:
        case RIDE:
        case SLEIGHT_OF_HAND:
        case TUMBLE:
        case USE_ROPE:
            return GetAbilityMod(DEX);
        case CONCENTRATION:
            return GetAbilityMod(CON);
        case APPRAISE:
        case DECIPHER_SCRIPT:
        case DISABLE_DEVICE:
        case FORGERY:
        case SEARCH:
        case SPELLCRAFT:
            return GetAbilityMod(INT);
        case HEAL:
        case LISTEN:
        case SENSE_MOTIVE:
        case SPOT:
        case SURVIVAL:
            return GetAbilityMod(WIS);
        case BLUFF:
        case DIPLOMACY:
        case DISGUISE:
        case GATHER_INFO:
        case HANDLE_ANIMAL:
        case INTIMIDATE:
        case USE_MAGIC_DEVICE:
            return GetAbilityMod(CHA);
        default:
            return 0xFF;
    }
}


int8 Being::GetAbility(AbilityEnum ability)
{
    return abilities.base.GetAbility(ability) + abilities.raceBonus.GetAbility(ability)
    		+ abilities.classBonus.GetAbility(ability) + abilities.ageBonus.GetAbility(ability) +
    		abilities.miscBonus.GetAbility(ability);
}

int8 Being::GetAbilityMod(AbilityEnum ability)
{
	int8 abilityValue = GetAbility(ability);

	if(abilityValue == 0)
	{
		return -3;
	}
	else if(abilityValue < 4)
	{
		return abilityValue - 4;
	}
	else if(abilityValue < 8)
	{
		return 0;
	}
	else
	{
		return (((abilityValue)/2) - 3);
	}
}

bool Being::FullHeal()
{
    currentHealth = maxHealth;
    return TRUE;
}

uint16 Being::Heal(uint16 addedHealth)
{
    if ((currentHealth += addedHealth) > maxHealth)
    {
        currentHealth = maxHealth;
    }
    return currentHealth;
}

uint16 Being::Hurt(uint16 removedHealth)
{
    if (currentHealth < removedHealth)
    {
        currentHealth = 0;
    }
    else
    {
        currentHealth -= removedHealth;
    }
    return currentHealth;
}

bool Being::Kill()
{
    currentHealth = 0;
    return TRUE;
}

bool Being::IsAlive()
{
    if (currentHealth > 0)
    {
        return TRUE;
    }
    return FALSE;
}

void Being::SetBaseAttackBonus(uint8 bonusNum, int8 bonusAmount)
{
    if (bonusAmount < 0)
    {
        baseAttackBonus[bonusNum] = 0;
    }
    else
    {
        baseAttackBonus[bonusNum] = bonusAmount;
    }
}

uint8 Being::GetBaseAttackBonus(uint8 bonusNum)
{
    return baseAttackBonus[bonusNum];
}

uint8 Being::GetRefBonus()
{
    return baseSaveBonus[REF];
}
uint8 Being::GetFortBonus()
{
    return baseSaveBonus[FORT];
}
uint8 Being::GetWillBonus()
{
    return baseSaveBonus[WILL];
}


uint16 Being::GetCurrentHealth()
{
    return currentHealth;
}

void Being::RecalcCharacter()
{
	CalculateMaxHealth();
}

void Being::CalculateMaxHealth()
{
	maxHealth = Being::GetAbility(STR)*3;
}

void Being::SetName(string passedName)
{
	name = passedName;
}

string Being::GetName()
{
	return name;
}

void Being::SetMeleeAttack(uint8 setAmnt)
{
	meleeAttack = setAmnt;
}

uint8 Being::GetMeleeAttack()
{
	return meleeAttack;
}

void Being::IncreaseMeleeAttack(uint8 incAmnt)
{
	meleeAttack += incAmnt;
}

void Being::DecreaseMeleeAttack(uint8 decAmnt)
{
	if (meleeAttack < decAmnt)
	{
		meleeAttack = 0;
	}
	else
	{
		meleeAttack -= decAmnt;
	}
}

void Being::SetRangedAttack(uint8 setAmnt)
{
	rangedAttack = setAmnt;
}

uint8 Being::GetRangedAttack()
{
	return rangedAttack;
}

void Being::IncreaseRangedAttack(uint8 incAmnt)
{
	rangedAttack += incAmnt;
}

void Being::DecreaseRangedAttack(uint8 decAmnt)
{
	if (rangedAttack < decAmnt)
	{
		rangedAttack = 0;
	}
	else
	{
		rangedAttack -= decAmnt;
	}
}

uint8 Being::GetSpeed()
{
	return speed;
}
