#ifndef __TREASURESTORESCENE_H__
#define __TREASURESTORESCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "HeroManagement.h"

#pragma execution_character_set("UTF-8")

USING_NS_CC;
class TreasureStoreScene : public cocos2d::Layer
{
public:
	static Scene* createScene();


	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* gem_tex[10];
	Sprite* spr_background;
	Sprite* spr_treasure_layer_2;
	Sprite* spr_collection;
	Sprite* spr_open_text_case;
	Sprite* spr_open_text;
	Sprite* spr_treasure_box;
	Sprite* treasure_buttoncase;
	Sprite* treasure_buttoncase_02;
	Sprite* treasure_buttoncase_03;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Sprite* spr_treasure_layer_3;
	Sprite* spr_treasure_layer_4;
	Sprite* spr_button_case;
	Sprite* spr_button_case2;
	Sprite* spr_button_case3;
	Sprite* spr_button_case4;

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Sprite* spr_open_box;
	Sprite* spr_treasure_layer_5;
	Sprite* spr_get_treasure_text;

	MenuItemImage* inventory[5][5];

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Layer* buy_layer;
	Layer* left_layer;
	Layer* open_layer;
	Layer* ui_layer;
	Layer* right_layer;
	Layer* coll_layer;
	Layer* orepen_layer;
	Layer* operwher_layer;


	Label* treaName;
	Label* treaText;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool init();
	void InitBuyLayer();
	void InitOpenLayer();
	void InitUILayer();
	void InitUpdataLayer();
	void InitUpdaaLayer();
	void InitOpenLayere();
	void IpenLayer();
	
	void InitUPLayer();

	void TreasureOpenButton();
	void TreasureOpennButton();
	void TreasureOpenSceneButton();


	void HomeButton();
	void SettingButton();
	void ReButton();
	void Button();
	void T4yrButton();
	void jiButton();
	void EeButton();
	void FeButton();
	void TyrButton(Ref* pSender); 
	void change(float dt);
	void TrpennButton();
	void T4yrButtonn();
	void T4yreButtonn();
	void luck();

	bool update_layer_bool;
	bool up_layer_bool;


	typedef char chars[50];
	chars names[10] =
	{
		"a",
		"b",
	};
	chars texts[10] =
	{
		"asb",
		"asn",
	};
	CREATE_FUNC(TreasureStoreScene);
};

#endif