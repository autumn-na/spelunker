#include <stdio.h>

#include "EquipmentManagement.h"

EquipmentMM* EquipmentMM::inst = nullptr;

EquipmentMM::EquipmentMM()
{
	for (int i = 0; i < 30; i++)
	{
		weapon_upgrade_cost[i] = 100 * (i + 1);
		pickaxe_upgrade_cost[i] = 100 * (i + 1);

		weapon_damage[i] = 25 * (i + 1);
		pickaxe_res_up[i] = 1 * (i + 1);
	};
}

EquipmentMM::~EquipmentMM()
{

}

float EquipmentMM::equipmentOne()
{
	return 0;
}

float EquipmentMM::equipmentTwo()
{
	return 0;
}

float EquipmentMM::equipmentThree()
{
	return 0;
}

float EquipmentMM::equipmentFour()
{
	return 0;
}

float EquipmentMM::equipmentFive()
{
	return 0;
}

int EquipmentMM::equipmentUpgradeMoney(int idx)
{
	return 0;
}