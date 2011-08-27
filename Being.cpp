#include "types.h"
#include "Being.h"


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
    return abilities.base[ability] + abilities.raceBonus[ability]+ abilities.classBonus[ability] + abilities.ageBonus[ability] + abilities.miscBonus[ability];
}

int8 Being::GetAbilityMod(AbilityEnum ability)
{
	return (int8)((GetAbility(ability)) / 2) - 5;
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

void Being::SetBaseSaveBonus(uint8 bonusNum, int8 bonusAmount)
{
    if (bonusAmount < 0)
    {
        baseSaveBonus[bonusNum] = 0;
    }
    else
    {
        baseSaveBonus[bonusNum] = bonusAmount;
    }
}

uint8 Being::GetBaseSaveBonus(uint8 bonusNum)
{
    return baseSaveBonus[bonusNum];
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
