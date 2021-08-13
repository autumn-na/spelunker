#ifndef __CLOTHINGSTORESCENE_H__
#define __CLOTHINGSTORESCENE_H__

#include "cocos2d.h"
#include "HeroManagement.h"
//#include "MenuScene.h"
class ClothingStoreScene : public cocos2d::Layer
{
public:
	Size visibleSize;

	Layer* clothesShow_layer;
	Layer* setting_layer;
	MenuItemImage* setting_button[2];
	Sprite* charactor;
	Sprite* openAni;
	Menu* mainButton;
	Label* gemLabel;

	MenuItemImage* buyButton[4];
	MenuItemImage* searchButton[4];
	
	static cocos2d::Scene* createScene();

	virtual bool init();

	void InitClothesLayer();
	void InitSettingLayer();

	void SettingButton();
	void SettingButtonOff();

	void SetBgmSound();
	void SetEffectSound();

	void EndingScene();

	void BuyButton(Ref* pSender);
	void SearchButton(Ref* pSender);
	void SearchButtonOff();
	void HomeButton();
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event);
	// implement the "static create()" method manually
	CREATE_FUNC(ClothingStoreScene);
};

#endif // __HELLOWORLD_SCENE_H__
