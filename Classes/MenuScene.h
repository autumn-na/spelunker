#pragma once

#include "cocos2d.h"
#include "HeroManagement.h"
#include "BlockSlideGameScene.h"

class MenuScene: public cocos2d::Layer
{
public:
	CCProgressTimer* _progressTimeBar;

	Layer* setting_layer;

	Menu* menu;
	Sprite* openAni;

	Sprite * gem_tex[10]; // 보석 숫자

    static cocos2d::Scene* createScene();

	int bgm = 1;
	int sound = 1;

	virtual bool init();
	
	void HomeButton();
	void SettingButton();
	void SettingCloseButton();
	void SettingBgmButton();

	void SettingsoundButton();

	void EndingSceneCallBack();

	void ChangeScene();
	void UpgradeCallback();
	void SkillShopCallback();
	void ClothesCallback();
	void TreasureCallback();
	
	
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};
