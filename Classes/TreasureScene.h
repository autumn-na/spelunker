#ifndef __TREASURESCENE_H__
#define __TREASURESCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class TreasureScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	//시작시 초기화 관련
	virtual bool init();
	void InitOpenLayer();
	void InitCollectionLayer();
	void InitExplainLayer();
	void InitGetLayer();
	void InitSettingLayer();

	void BoxOpen();
	void BoxOpenEnd();

	void ChangeOpenLayer();
	void ChangeCollectionLayer();

	void OpenExplanLayer(Ref* pSender);
	void EndExplanLayer();

	void SettingButton();
	void SettingButtonOff();
	void HomeButton();

	void EndingScene();
	void SetBgmSound();
	void SetEffectSound();

	bool onTouchBegan(Touch * touch, Event * unused_event);

public:
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Layer* openLayer;
	Layer* collectionLayer;
	Layer* explanLayer;
	Layer* setting_layer;
	Layer* getLayer;

	Sprite* openAni;

	bool openLayerChange;
	Sprite* openSprite;
	MenuItemImage* button[5][5];
	Sprite* buttonSprite[5][5];

	Label* explanName;
	Label* explanText;
	Sprite* explanSprite;
	Sprite* getTreasureSprite;

	Sprite* box;
	Label* treasureName;
	Label* treasureExplan;

	Label* moneyLabel;

	Menu* settingUI;
	Menu* openMenu;
	Menu* treaMenu;
	

public:
	char* treaName[30] =
	{
		"낡은 펜던트",
		"발터 PK",
		"하스스톤",
	};

	char* treaExplan[30] =
	{
		"스킬 쿨타임 감소 5%",
		"스킬 데미지 증가 5%",
		"공격력 증가 10%",
	};
	CREATE_FUNC(TreasureScene);
};

#endif