#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "types.h"

typedef struct
{
	UINT16 stdPrice;
	UINT8 weight;
}ItemT;


///////////
//ARMORS
///////////
typedef struct
{
	UINT8 armor;
	UINT8 durability;
	UINT8 sizeClass;
	ItemT itemProperties;
}ArmorT;

#endif


