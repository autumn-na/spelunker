#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HeroManagement.h"

using namespace cocos2d;
using namespace CocosDenshion;

class SkillMM
{
private:
	SkillMM();
	SkillMM(const SkillMM&);
	SkillMM* operator=(const SkillMM&) {}
	~SkillMM();
	static SkillMM* inst;

public:
	static SkillMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new SkillMM();
		}
		return inst;
	}

	int isEquiped;
	
	Sprite* sprf_skill_icon[4];
	
	Sprite* sprf_skill_use_panel;

	EaseExponentialOut* ease_skill_panel;
	EaseExponentialOut* ease_fast_skill_panel;
	MoveBy* move_skill_panel;
	MoveBy* move_fast_skill_panel;
	Place* place_skill_panel;
	CallFunc* callf_setvisible;
	Sequence* seq_skill_use;
	Sequence* seq_skill_icon;

	Place* place_use_skill_panel;
	FadeOut* fadeout_use_skill_panel;
	FadeIn* fadein_use_skill_panel;

	enum
	{
		EXCAVATIONSKILL1,
		EXCAVATIONSKILL2,
		EXCAVATIONSKILL3,
		EXCAVATIONSKILL4,
		HUNTSKILL1,
		HUNTSKILL2,
		HUNTSKILL3,
		HUNTSKILL4,
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Excavationskill1();
	void Excavationskill2();
	void Excavationskill3();
	void Excavationskill4();

	void huntskill1();
	void huntskill2();
	void huntskill3();
	void huntskill4();

	bool isSkillBought[8];
	
	int skill_cost[8];
	char* lab_skill_cost[8];

	enum SkillType
	{
		HUNT,
		MINING
	};
};