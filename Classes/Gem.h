#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"
#include "HeroManagement.h"

USING_NS_CC;
class Gem
{
public:
	Sprite * gem_tex[10];
	Vec2 pos;

	Gem(Layer * layer);
	void AddGem(int addRes);
};

#endif