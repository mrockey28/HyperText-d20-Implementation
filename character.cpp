#include "character.h"
#include "stdio.h"

class Modifiers
{

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
#define MAX_GOLD 999999


BOOL PlayerCharacter::Buy(UINT32 cost)
{
	if (cost > gold)
	{
		return FALSE;
	}
	else
	{
		gold -= cost;
		return TRUE;
	}
}

void PlayerCharacter::RemoveGold(UINT32 amnt)
{
	if (Buy(amnt) == FALSE)
	{
		gold = 0;
	}
}

void PlayerCharacter::AddGold(UINT32 amnt)
{
	if ((amnt+gold) > MAX_GOLD)
	{
		gold = MAX_GOLD;
	}
	else
	{
		gold += amnt;
	}
}

void PlayerCharacter::Sell(UINT32 cost)
{
	AddGold(cost);
}

UINT32 PlayerCharacter::GetGold()
{
	return gold;
}
	
