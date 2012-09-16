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

void Being::RecalcCharacter()
{
	CalculateMaxHealth();
}

void Being::CalculateMaxHealth()
{
	maxHealth = attributes.strength*3;
}

void Being::SetName(string passedName)
{
	name = passedName;
}

string Being::GetName()
{
	return name;
}


void Being::SetStrength(Attribute setAttr)
{
	attributes.strength = setAttr;
	CalculateAttributeModifier(&attributes.strength);
}

Attribute Being::GetStrength()
{
	return attributes.strength;
}

void Being::SetAgility(Attribute setAttr)
{
	attributes.agility = setAttr;
	CalculateAttributeModifier(&attributes.agility);
}

Attribute Being::GetAgility()
{
	return attributes.agility;
}

void Being::SetCharisma(Attribute setAttr)
{
	attributes.charisma = setAttr;
	CalculateAttributeModifier(&attributes.charisma);
}

Attribute Being::GetCharisma()
{
	return attributes.charisma;
}

void Being::SetConstitution(Attribute setAttr)
{
	attributes.constitution = setAttr;
	CalculateAttributeModifier(&attributes.constitution);
}

Attribute Being::GetConstitution()
{
	return attributes.constitution;
}

void Being::SetIntelligence(Attribute setAttr)
{
	attributes.intelligence = setAttr;
	CalculateAttributeModifier(&attributes.intelligence);
}

Attribute Being::GetIntelligence()
{
	return attributes.intelligence;
}

void Being::SetMagic(Attribute setAttr)
{
	attributes.magic = setAttr;
	CalculateAttributeModifier(&attributes.magic);
}

Attribute Being::GetMagic()
{
	return attributes.magic;
}

void Being::SetDefense(UINT8 setAmnt)
{
	defense = setAmnt;
}

UINT8 Being::GetDefense()
{
	return defense;
}

void Being::IncreaseDefense(UINT8 incAmnt)
{
	defense += incAmnt;
}

void Being::DecreaseDefense(UINT8 decAmnt)
{
	if (defense < decAmnt)
	{
		defense = 0;
	}
	else
	{
		defense -= decAmnt;
	}
}

void Being::SetMeleeAttack(UINT8 setAmnt)
{
	meleeAttack = setAmnt;
}

UINT8 Being::GetMeleeAttack()
{
	return meleeAttack;
}

void Being::IncreaseMeleeAttack(UINT8 incAmnt)
{
	meleeAttack += incAmnt;
}

void Being::DecreaseMeleeAttack(UINT8 decAmnt)
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

void Being::SetRangedAttack(UINT8 setAmnt)
{
	rangedAttack = setAmnt;
}

UINT8 Being::GetRangedAttack()
{
	return rangedAttack;
}

void Being::IncreaseRangedAttack(UINT8 incAmnt)
{
	rangedAttack += incAmnt;
}

void Being::DecreaseRangedAttack(UINT8 decAmnt)
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

void Being::SetSpeed(UINT8 setAmnt)
{
	speed = setAmnt;
}

UINT8 Being::GetSpeed()
{
	return speed;
}

void Being::IncreaseSpeed(UINT8 incAmnt)
{
	speed += incAmnt;
}

void Being::DecreaseSpeed(UINT8 decAmnt)
{
	if (speed < decAmnt)
	{
		speed = 0;
	}
	else
	{
		speed -= decAmnt;
	}
}

void Being::SetArmor(UINT8 setAmnt)
{
	armor = setAmnt;
}

UINT8 Being::GetArmor()
{
	return armor;
}

void Being::IncreaseArmor(UINT8 incAmnt)
{
	armor += incAmnt;
}

void Being::DecreaseArmor(UINT8 decAmnt)
{
	if (armor < decAmnt)
	{
		armor = 0;
	}
	else
	{
		armor -= decAmnt;
	}
}




Attribute Being::GetStrengthMod()
{
	return attributeModifiers.strength;
}

Attribute Being::GetAgilityMod()
{
	return attributeModifiers.agility;
}

Attribute Being::GetConstitutionMod()
{
	return attributeModifiers.constitution;
}

Attribute Being::GetCharismaMod()
{
	return attributeModifiers.charisma;
}

Attribute Being::GetIntelligenceMod()
{
	return attributeModifiers.intelligence;
}

Attribute Being::GetMagicMod()
{
	return attributeModifiers.magic;
}
	void Being::CalculateAttributeModifier(Attribute* sourceAttr)
{
	//attrOffset is the offset from the beginning of the attributeModifier
	//structure that the current attribute is located. Calculated from
	//the difference between the passed attribute and the start of the normal
	//attribute structure
	UINT8 attrOffset = sourceAttr - &attributes.strength;
	if(*sourceAttr==0)
	{
		*(&attributeModifiers.strength+attrOffset)=-3;
	}
	else if(*sourceAttr < 4)
	{
		*(&attributeModifiers.strength+attrOffset)= (*sourceAttr) - 4;
	}
	else if(*sourceAttr < 8)
	{
		*(&attributeModifiers.strength+attrOffset)= 0;
	}
	else
	{
		*(&attributeModifiers.strength+attrOffset)= ((((*sourceAttr)/2) - 3));
	}
	RecalcCharacter();

}
