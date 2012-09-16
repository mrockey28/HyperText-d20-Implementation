#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "types.h"

typedef struct
{
	uint16 stdPrice;
	uint8 weight;
}ItemT;


///////////
//ARMORS
///////////
typedef struct
{
	uint8 armor;
	uint8 durability;
	uint8 sizeClass;
	ItemT itemProperties;
}ArmorT;

#endif


