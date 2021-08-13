#include "SkillManagement.h"

SkillMM* SkillMM::inst = nullptr;

SkillMM::SkillMM()
{
	for (int i = 0; i < 8; i++)
	{
		skill_cost[i] = 500;

		lab_skill_cost[i] = "500";

		isSkillBought[i] = false;
	}

	for (int i = 0; i < 4; i++)
	{
		sprf_skill_icon[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		sprf_skill_icon[i]->retain();
	}

	sprf_skill_use_panel = Sprite::create("skill_use_panel.png");
	sprf_skill_use_panel->retain();
	

	place_skill_panel = Place::create(Vec2(-360, 720));
	
	place_use_skill_panel = Place::create(Vec2(360, 720));
	fadeout_use_skill_panel = FadeOut::create(0.5f);
	fadein_use_skill_panel = FadeIn::create(0.0f);

	seq_skill_use = Sequence::create(place_use_skill_panel, DelayTime::create(1.0f), fadeout_use_skill_panel, fadein_use_skill_panel, place_skill_panel, NULL);
	seq_skill_use->retain();

	seq_skill_icon = Sequence::create(DelayTime::create(1.0f), fadeout_use_skill_panel, fadein_use_skill_panel, NULL);
	seq_skill_icon->retain();
}

SkillMM::~SkillMM()
{

}

void SkillMM::Excavationskill1()
{

}

void SkillMM::Excavationskill2() 
{

}

void SkillMM::Excavationskill3()
{

}
void SkillMM::Excavationskill4()
{

}
void SkillMM::huntskill1()
{

}
void SkillMM::huntskill2() 
{

}
void SkillMM::huntskill3() 
{

}
void SkillMM::huntskill4()
{

}