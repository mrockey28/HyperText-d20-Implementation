#ifndef HUMANOID_H
#define HUMANOID_H

typedef enum RaceEnum
{
    HUMAN,
    ELF,
    GNOME,
    DWARF,
    HALF_ELF,
    HALF_ORC,
    HALFLING
}RaceEnum;


typedef enum ClassEnum
{
    BARBARIAN,
    BARD,
    CLERIC,
    DRUID,
    FIGHTER,
    MONK,
    PALADIN,
    RANGER,
    ROGUE,
    SORCERER,
    WIZARD,
    TOTAL_CLASSES
}ClassEnum;


class Humanoid: public Being
{
    RaceEnum race;
    ClassEnum clas;
    uint16 age;
    uint16 xp;
    uint8 level;


    void SetAgeBonuses();
    void SetRaceBonuses();
    void SetHitDie();
    void CalculateBaseAttackBonus();
    void CalculateBaseSaveBonus();
    void SetMiddleAge();
    void SetOldAge();
    void SetVenerableAge();

public:
    Humanoid(){}
    Humanoid(RaceEnum passedRace, uint16 passedAge, ClassEnum passedClass)
    {
        level = 1;
        race = passedRace;
        age = passedAge;
        clas = passedClass;
        SetAgeBonuses();
        SetRaceBonuses();
        CalculateBaseAttackBonus();
        CalculateBaseSaveBonus();
    }
};



#endif //HUMANOID_H
