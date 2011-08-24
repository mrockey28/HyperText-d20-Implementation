typedef enum SizeEnum
{
    SMALL = 0x00,
    MEDIUM = 0x01,
    LARGE = 0x02,
    INVALID = 0x03
} SizeEnum;

typedef enum RaceEnum
{
    ELF,
    TOTAL_RACES
}RaceEnum;


typedef enum ClassEnum
{
    WIZARD,
    TOTAL_CLASSES
}ClassEnum;


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
}AbilityStruct;


class Feat;


class Being
{
    string name;
    AbilityStruct abilities;
    SizeEnum size;
    uint8 speed;
    uint8 initiative;
    uint8 acBase;
    uint8 acTouch;
    uint8 acFlatfoot;

    uint8 fort;
    uint8 ref;
    uint8 will;

    uint8 bab;
    SkillStruct skills;
    Feat* featHead;

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
    return abilities.base[ability] + abilities.raceBonus[ability]+ abilities.classBonus[ability] + abilities.miscBonus[ability];
}

int8 Being::GetAbilityMod(AbilityEnum ability)
{
	return (int8)((GetAbility(ability)) / 2) - 5;	
}



class Humanoid: public Being
{
    RaceEnum race;
    ClassEnum clas;
    uint8 level;
       
};
