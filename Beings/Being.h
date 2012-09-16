#ifndef BEING_H
#define BEING_H

typedef int8 Attribute;

typedef enum SizeEnum
{
    SMALL = 0x00,
    MEDIUM = 0x01,
    LARGE = 0x02,
    INVALID = 0x03
} SizeEnum;


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
    int8 base[TOTAL_ABILITIES];
    int8 raceBonus[TOTAL_ABILITIES];
    int8 miscBonus[TOTAL_ABILITIES];
    int8 classBonus[TOTAL_ABILITIES];
    int8 ageBonus[TOTAL_ABILITIES];
}AbilityStruct;


class Feat;

class Being
{
    string name;

    uint16 maxHealth;
    uint16 currentHealth;

    SizeEnum size;
    uint8 speed;
    uint8 initiative;
    uint8 acBase;
    uint8 acTouch;
    uint8 acFlatfoot;



    uint8 baseSaveBonus[3];

    uint8 baseAttackBonus[4];
    SkillStruct skills;
    Feat* featHead;

	typedef struct
	{
  		Attribute strength;
  		Attribute agility;
  		Attribute charisma;
 		Attribute constitution;
  		Attribute intelligence;
  		Attribute magic;
	}AttributeT;


 	void CalculateAttributeModifier(Attribute* sourceAttr);
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
    void SetBaseSaveBonus(uint8 saveType, int8 bonusAmount);

public:
    Being()
    {
        skills.reqToBeTrained = 0x118810A0;
    }
    int8 GetAbilityMod(AbilityEnum ability);
    int8 GetAbility(AbilityEnum ability);
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

 	uint8 GetDefense();
 	void IncreaseDefense(uint8 incAmnt);
 	void DecreaseDefense(uint8 decAmnt);
 	uint8 GetMeleeAttack();
 	void IncreaseMeleeAttack(uint8 incAmnt);
 	void DecreaseMeleeAttack(uint8 decAmnt);
 	uint8 GetRangedAttack();
 	void IncreaseRangedAttack(uint8 incAmnt);
 	void DecreaseRangedAttack(uint8 decAmnt);
 	uint8 GetSpeed();
 	void IncreaseSpeed(uint8 incAmnt);
 	void DecreaseSpeed(uint8 decAmnt);
 	uint8 GetArmor();
 	void IncreaseArmor(uint8 incAmnt);
 	void DecreaseArmor(uint8 decAmnt);

	void RecalcCharacter();

	void SetName(string);
	string GetName();

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

#define FORT 0
#define REF 1
#define WILL 2


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