#ifndef __TREASURESCENE_H__
#define __TREASURESCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class TreasureScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	//���۽� �ʱ�ȭ ����
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
		"���� ���Ʈ",
		"���� PK",
		"�Ͻ�����",
	};

	char* treaExplan[30] =
	{
		"��ų ��Ÿ�� ���� 5%",
		"��ų ������ ���� 5%",
		"���ݷ� ���� 10%",
	};
	CREATE_FUNC(TreasureScene);
};

#endif