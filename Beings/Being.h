#ifndef BEING_H
#define BEING_H

#include "Abilities.h"

typedef enum SaveThrowEnum
{
	REF,
	WILL,
	FORT
} SaveThrowEnum;

typedef enum SizeEnum
{
	FINE,
	DIMINUTIVE,
	TINY,
    SMALL,
    MEDIUM,
    LARGE,
    HUGE,
    GARGANTUAN,
    COLOSSAL
} SizeEnum;

typedef enum SkillEnum
{
    APPRAISE,
    BALANCE,
    BLUFF,
    CLIMB,
    CONCENTRATION,
    //CRAFT,
    DECIPHER_SCRIPT,
    DIPLOMACY,
    DISABLE_DEVICE,
    DISGUISE,
    ESCAPE_ARTIST,
    FORGERY,
    GATHER_INFO,
    HANDLE_ANIMAL,
    HEAL,
    HIDE,
    INTIMIDATE,
    JUMP,
    //KNOWLEDGE,
    LISTEN,
    MOVE_SILENTLY,
    OPEN_LOCK,
    //PERFORM,
    //PROFESSION,
    RIDE,
    SEARCH,
    SENSE_MOTIVE,
    SLEIGHT_OF_HAND,
    SPELLCRAFT,
    SPOT,
    SURVIVAL,
    SWIM,
    TUMBLE,
    USE_MAGIC_DEVICE,
    USE_ROPE,
    TOTAL_SKILLS
}SkillEnum;

typedef struct SkillStruct
{
    uint32 reqToBeTrained; //Bitfield; USE_ROPE is highest order bit
    uint8 ranks[TOTAL_SKILLS];
    uint8 miscMod[TOTAL_SKILLS]; 
}SkillStruct;


typedef struct AbilityStruct
{    
	Abilities base;
    Abilities raceBonus;
    Abilities miscBonus;
    Abilities classBonus;
    Abilities ageBonus;
}AbilityStruct;


class Feat;

class Being
{
    string name;
    SizeEnum size;
    uint8 speed;

    uint16 maxHealth;
    uint16 currentHealth;

    uint8 baseSaveBonus[3];

    uint8 baseAttackBonus[4];
    SkillStruct skills;
    Feat* featHead;


	uint8 meleeAttack;
	uint8 rangedAttack;

 	void RecalculateAttributeModifiers();
	void CalculateMaxHealth();
 	void SetArmor(uint8 setAmnt);
 	void SetSpeed(uint8 setAmnt);
 	void SetRangedAttack(uint8 setAmnt);
 	void SetMeleeAttack(uint8 setAmnt);
 	void SetDefense(uint8 setAmnt);

protected:

 	AbilityStruct abilities;
    uint8 hitDie;
    uint8 GetBaseAttackBonus(uint8 bonusNum);
    void SetBaseAttackBonus(uint8 bonusNum, int8 bonusAmount);
    uint8 GetBaseSaveBonus(uint8 saveType);

public:
    Being();
    Being(string nameP, SizeEnum sizeP, uint8 speedP, int8 refSaveP, int8 willSaveP, int8 fortSaveP);

    int8 GetArmorClass();
    int8 GetArmorClass(int8 armorPenalty);
    int8 GetArmorClass(int8 armorPenalty, bool canUseDexBonus);

    int8 GetSizeModifier();
    int8 GetInitiativeBonus();

    uint8 GetSpeed();

    int8 GetAbility(AbilityEnum ability);
    int8 GetAbilityMod(AbilityEnum ability);

    uint8 GetSkillMod(SkillEnum skill);
    void ChangeSkillMiscMod(SkillEnum skill, int8 delta);
    uint8 GetSkillAbilityMod(SkillEnum skill);
    void AddSkillRanks(SkillEnum skill, uint8 ranksToAdd);

    bool FullHeal();
    uint16 Heal(uint16 addedHealth);
    uint16 Hurt(uint16 removedHealth);
    bool Kill();
    bool IsAlive();
    uint16 GetCurrentHealth();

    uint8 GetRefBonus();
    uint8 GetFortBonus();
    uint8 GetWillBonus();

 	uint8 GetMeleeAttack();
 	void IncreaseMeleeAttack(uint8 incAmnt);
 	void DecreaseMeleeAttack(uint8 decAmnt);
 	uint8 GetRangedAttack();
 	void IncreaseRangedAttack(uint8 incAmnt);
 	void DecreaseRangedAttack(uint8 decAmnt);

	void RecalcCharacter();

	void SetName(string);
	string GetName();
};


typedef enum FeatEnum
{
    FEAT1,
    TOTAL_FEATS
}FeatEnum;


class Feat
{
    Feat* next;
    FeatEnum feat;
public:
    Feat(FeatEnum featToAdd)
    {
        next = NULL;
        feat = featToAdd;
    }
    bool IncorporateFeatBonus(Being being)
    {
        return TRUE;
    }
};


#endif //BEING_H
