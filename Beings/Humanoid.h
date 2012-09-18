#ifndef HUMANOID_H
#define HUMANOID_H

#include "../equipment.h"
#include "Being.h"

DEFINE_SIMPLE_ENUM(Race,
		((HUMAN, 1))
		((ELF, 2))
		((GNOME, 3))
		((DWARF, 4))
		((HALF_ELF, 5))
		((HALF_ORC, 6))
		((HALFLING, 7))
		)

DEFINE_SIMPLE_ENUM(Clas,
		((BARBARIAN, 1))
		((BARD, 2))
		((CLERIC, 3))
		((DRUID, 4))
		((FIGHTER, 5))
		((MONK, 6))
		((PALADIN, 7))
		((RANGER, 8))
		((ROGUE, 9))
		((SORCERER, 10))
		((WIZARD, 11))
		)

class Humanoid: public Being
{
    Race race;
    Clas clas;
    uint16 age;
    uint8 level;

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

	Size GetRaceSize();
	Size GetRaceSize(Race race);
	uint8 GetRaceSpeed();
	uint8 GetRaceSpeed(Race race);

    void SetAgeBonuses();
    void SetRaceBonuses();
    void SetHitDie();
    void CalculateBaseAttackBonus();
    int8 GetBaseWillBonus();
    int8 GetBaseRefBonus();
    int8 GetBaseFortBonus();
    int8 GetBaseWillBonus(Clas clas, uint8 level);
    int8 GetBaseRefBonus(Clas clas, uint8 level);
    int8 GetBaseFortBonus(Clas clas, uint8 level);
    void SetMiddleAge();
    void SetOldAge();
    void SetVenerableAge();

public:
    Humanoid();
    Humanoid(string name, Race race, Clas clas, uint16 age, uint8 level);
};



#endif //HUMANOID_H
