#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"
#include "equipment.h"

#define MAX_NAME_SIZE

typedef INT8 Attribute;

class Attributes
{
    typedef struct AttributeStruct
    {
        INT8 str;
        INT8 dex;
        INT8 con;
        INT8 int;
        INT8 wis;
        INT8 cha;
    }AttributeStruct;
    AttributeStruct attr;
    AttributeStruct attrBonus;
    AttributeStruct atrrMod;
    AttributeStruct raceBonus;
    AttributeStruct classBonus;

    int8 CalcMods(int8);

public:
    INT8 GetStr();
    INT8 GetDex();
    INT8 GetCon();
    INT8 GetInt();
    INT8 GetWis();
    INT8 GetCha();
    INT8 GetStrMod();
    INT8 GetDexMod();
    INT8 GetConMod();
    INT8 GetIntMod();
    INT8 GetWisMod();
    INT8 GetChaMod();

}


class Being
{

	typedef struct
	{
  		Attribute strength;
  		Attribute agility;
  		Attribute charisma;
 		Attribute constitution;
  		Attribute intelligence;
  		Attribute magic;
	}AttributeT;
	string name;
	UINT16 maxHealth;
	UINT16 currentHealth;
	AttributeT attributes;
	AttributeT	attributeModifiers;

	UINT8 defense;
	UINT8 meleeAttack;
	UINT8 rangedAttack;
	UINT8 speed;
	UINT8 armor;

 	void CalculateAttributeModifier(Attribute* sourceAttr);
	void CalculateMaxHealth();
 	void SetArmor(UINT8 setAmnt);
 	void SetSpeed(UINT8 setAmnt);
 	void SetRangedAttack(UINT8 setAmnt);
 	void SetMeleeAttack(UINT8 setAmnt);
 	void SetDefense(UINT8 setAmnt);

public:
	void RecalcCharacter();

	void SetName(string);
	string GetName();
	BOOL FullHeal();
	UINT16 Heal(UINT16 addedHealth);
	UINT16 Hurt(UINT16 removedHealth);
	BOOL	Kill();
	BOOL	Alive();
	UINT16 GetCurrentHealth();

	void SetStrength(Attribute setAttr);
	void SetAgility(Attribute setAttr);
	void SetCharisma(Attribute setAttr);
	void SetConstitution(Attribute setAttr);
	void SetIntelligence(Attribute setAttr);
	void SetMagic(Attribute setAttr);

 	Attribute GetStrength();
 	Attribute GetAgility();
 	Attribute GetCharisma();
 	Attribute GetConstitution();
 	Attribute GetIntelligence();
 	Attribute GetMagic();
	Attribute GetStrengthMod();
 	Attribute GetAgilityMod();
 	Attribute GetCharismaMod();
 	Attribute GetConstitutionMod();
 	Attribute GetIntelligenceMod();
 	Attribute GetMagicMod();

 	UINT8 GetDefense();
 	void IncreaseDefense(UINT8 incAmnt);
 	void DecreaseDefense(UINT8 decAmnt);
 	UINT8 GetMeleeAttack();
 	void IncreaseMeleeAttack(UINT8 incAmnt);
 	void DecreaseMeleeAttack(UINT8 decAmnt);
 	UINT8 GetRangedAttack();
 	void IncreaseRangedAttack(UINT8 incAmnt);
 	void DecreaseRangedAttack(UINT8 decAmnt);
 	UINT8 GetSpeed();
 	void IncreaseSpeed(UINT8 incAmnt);
 	void DecreaseSpeed(UINT8 decAmnt);
 	UINT8 GetArmor();
 	void IncreaseArmor(UINT8 incAmnt);
 	void DecreaseArmor(UINT8 decAmnt);
};

class Humanoid: public virtual Being
{
	typedef struct
	{
		ItemT head;
		ItemT torso;
		ItemT finger1;
		ItemT finger2;
		ItemT lefthand;
		ItemT righthand;
		ItemT feet;
	}EquipmentT;
	EquipmentT equipment;
	typedef enum RaceEnum
	{
		HUMAN,
		ELF,
		GNOME,
        DWARF,
        HALF-ELF,
        HALF-ORC,
        HALFLING
	}RaceEnum;
	RaceEnum race;
};

//Inherit from Humanoid
class PlayerCharacter: public Humanoid
{
	UINT8 level;
	UINT16 xp;
	UINT32 gold;


public:
	PlayerCharacter()
	{
		gold = 0;
		xp = 0;
		level = 0;
	}
	BOOL Buy(UINT32 cost);
	void RemoveGold(UINT32 amnt);
	void AddGold(UINT32 amnt);
	void Sell(UINT32 cost);
	UINT32 GetGold();
};

#endif
