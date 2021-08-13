#ifndef __ending_H__
#define __ending_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "HeroManagement.h"

USING_NS_CC;

class EndingtScene : public cocos2d::Layer
{
public:
	static Scene* createScene();

	int whole;

	virtual bool init();
	void change(float dt);
	void HomeButton();
	void SettingButton();
	Layer* ending_layer;
	Layer* home_go_layer;


	Size visibleSize = Director::getInstance()->getVisibleSize();


	Sprite* spr_Chung_layer;
	Sprite* spr_chang_layer;
	Sprite* spr_taho_layer;
	Sprite* spr_yun_layer;
	Sprite* spr_pak_layer;
	Sprite* spr_min_layer;
	Sprite* spr_backgruond_layer;

	CREATE_FUNC(EndingtScene);
};

#endif