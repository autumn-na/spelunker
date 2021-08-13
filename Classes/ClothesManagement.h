#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class ClothesMM
{
public:
	ClothesMM() 
	{
		for (int i = 0; i < 4; i++)
			clothesCarry[i] = false;
		clothesEquip = 4;	
	}
	~ClothesMM() {}

	static ClothesMM* inst;
	static ClothesMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new ClothesMM();
		}
		return inst;
	}
	bool clothesCarry[4];
	int clothesEquip;
};

ClothesMM* ClothesMM::inst = nullptr;