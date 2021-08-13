#pragma once

#pragma execution_character_set("UTF-8")



#include "cocos2d.h"
#include "MenuScene.h"
#include "HeroManagement.h"

USING_NS_CC;
class StrartScene : public cocos2d::Layer
{
public:
	static Scene* createScene();

	int whole;
	bool abcdef;

	virtual bool init();
	void change();
	Layer* eve_layer;

	Sprite* spr_title;
	Sprite* spr_hat;

	bool onTouchBegan(Touch * touch, Event * unused_event);

	CREATE_FUNC(StrartScene);
};