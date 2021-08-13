#ifndef __SKILLICON_H__
#define __SKILLICON_H__

#include "cocos2d.h"

USING_NS_CC;

class Skill
{
public:
	int whole; //
	int prosent;
	int skill_time;
	bool skill_use;
	bool skill_on;

	Vec2 size;
	Sprite * icon;
	Sprite * effect;
	Sprite * effect_under;

	Skill(Layer * layer);
	void UpProsent(int add_prosent);
	void Upgrade(); 
	void play();
	void playoff();

};


#endif
