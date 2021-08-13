#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class EquipmentMM
{
private:
	EquipmentMM();
	~EquipmentMM();
	static EquipmentMM* inst;

public:
	static EquipmentMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new EquipmentMM();
		}
		return inst;
	}

public:

	enum equipmentName
	{
		one,
		two,
		three,
		four,
		five,
	};

	int equipment_level[5];

	float equipmentOne();
	float equipmentTwo();
	float equipmentThree();
	float equipmentFour();
	float equipmentFive();

	int equipmentUpgradeMoney(int);

	int weapon_level = 0;
	int pickaxe_level = 0;

	int weapon_upgrade_probability = 50;
	int pickaxe_upgrade_probability = 50;

	int weapon_upgrade_cost[30];
	int pickaxe_upgrade_cost[30];

	int weapon_damage[30];
	int pickaxe_res_up[30];
};

