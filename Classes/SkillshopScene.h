#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "HeroManagement.h"
#include "MonsterManagement.h"
#include "SkillManagement.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "ending.h"
#include <time.h>

using namespace cocos2d;
using namespace CocosDenshion;

class SkillshopScene : public Layer
{
public:
	LayerColor* layer_hunting;
	LayerColor* layer_mining;
	LayerColor* layer_ui;
	Layer* layer_popup;
	Layer* pause_layer;

	MenuItemImage* pause_button[2];
	MenuItemImage* menui_hunting;
	MenuItemImage* menui_hunting_off;
	MenuItemImage* menui_mining;
	MenuItemImage* menui_mining_off;
	MenuItemImage* menui_setting;
	Menu* menu_change_type;

	MenuItemSprite* sound_bgm_off;
	MenuItemSprite* sound_bgm_on;
	MenuItemSprite* sound_effect_off;
	MenuItemSprite* sound_effect_on;

	MenuItemToggle* setting_bgm_button;
	MenuItemToggle* setting_effect_button;

	MenuItemImage* menui_home;
	MenuItemImage* menui_ok2;
	MenuItemImage* spr_gem_cost2[4];
	MenuItemImage* spr_gem_cost[4];
	Menu* menu_ui;

	MenuItemImage* hunting_skill[4];
	Vec2 vec2_hunting_skill[4] = { Vec2(570, 750), Vec2(570, 540), Vec2(570, 330), Vec2(570, 120) };

	Menu* menu_hunting_skill;

	MenuItemImage* mining_skill[4];
	Vec2 vec2_mining_skill[4] = { Vec2(145, 900), Vec2(145, 680), Vec2(145, 460), Vec2(145, 240) };

	Menu* menu_mining_skill;

	Label* lab_hunting[4];
	
	Vec2 vec22[4] = { Vec2(450,850),Vec2(450,630),Vec2(450,410),Vec2(450,190) };

	Label* lab_mining[4];
	Vec2 vec2_lab_mining[4] = { Vec2(450, 900), Vec2(450, 680), Vec2(450, 460), Vec2(450, 240) };

	
	Vec2 vec2_menui_buy[4] = { Vec2(150,740), Vec2(150,560), Vec2(150,360), Vec2(150,170) };
	
	Vec2 vec2_lab_cost[4] = { Vec2(450,885), Vec2(450, 665), Vec2(450, 450), Vec2(450, 315) };

	///////////////////////////////////////////////////////////////////////////////////////////////

	Vec2 vec2_frame[4] = { Vec2(360,150) ,Vec2(360,360) ,Vec2(360,570) ,Vec2(360,780) };

	Vec2 gem_cost[4] = { Vec2(395,750), Vec2(395, 540), Vec2(395,330), Vec2(395,120) };

	Vec2 vec2_item_image[4] = { Vec2(180,150) ,Vec2(180,360) ,Vec2(180,570) ,Vec2(180,775) };
	Vec2 vec2_hunting[4] = { Vec2(180,775), Vec2(180,570), Vec2(180,360), Vec2(180,150) };

	Vec2 vec2_yourname[4] = { Vec2(445,200) ,Vec2(445,410) ,Vec2(445,620) ,Vec2(445,830) };
	Vec2 vec2_lab_hunting[4] = { Vec2(445, 830), Vec2(445, 620), Vec2(445, 410), Vec2(445, 200) };

	///////////////////////////////////////////////////////////////////////////////////////////////

	Sprite* spr_hunting_skill[4];
	Sprite* spr_mining_skill[4];
	Sprite* openAni;

	Label* lab_hunting_name[4];
	Label* lab_mining_name[4];
	
	Label* lab_hunting_explain[4];
	Label* lab_mining_explain[4];

	Label* label_gem;
	Label* lab_cost[4];

	Sprite* paused_paused;
	Sprite* paused_case;
	MenuItemImage* paused_done;
	
	Menu* setting_menu;
	Menu* menu1;

	Sprite* spr_skill_character;

	Sprite* skillimage[4];

	Sprite* battle;
	Sprite* skill_popup;
	Sprite* battle_off;
	Sprite* mining_off;
	Sprite* skill_text;
	Sprite* background;
	Sprite* frame[4];
	Sprite* frame2[4];
	Sprite* item_image[4];
	Sprite* item_image2[4];
	Sprite* yourname[4];
	Sprite* yourname2[4];

	Sprite* backframe;
	Sprite* backframe2;

	Sprite* hunting[4];
	Sprite* hunting2[4];
	Sprite* panel_hunting;
	Sprite* panel_mining;
	Sprite* panel_detail;

	Sprite* hunting_skill1;
	Sprite* hunting_skill2;
	Sprite* hunting_skill3;
	Sprite* hunting_skill4;

	MenuItemImage* menui_buy;
	MenuItemImage* menui_close_detail;
	Menu* menu_buy;

	MenuItemImage* unequip[4];
	Menu* skillbuy;

	Sprite* gem;
	Sprite* info;
	
	Sprite* popup_item_image;
	Sprite* popup_skill[4];

	DelayTime* delay_revibe = DelayTime::create(30.0f); //30초후에실행

	int gem_total;
	int bgm = 1;
	int sound = 1;

	int selected_skill_num;

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	static cocos2d::Scene* createScene();

	virtual bool init();

	//초기화들
	void initData();
	void initTouch();
	void initLayer();
	void initSprite();
	void initUILayer();
	void initHuntingLayer();
	void initMiningLayer();
	void initPopUpLayer();

	//콜백들
	void goToMainCallback();
	void goToEndingCallback();
	void huntingToMiningCallback();
	void miningToHuntingCallback();
	void skillDetailCallback(Ref* pSender);
	void skillBuyCallback(Ref* pSender);
	void closeSkillDetailCallback();
	void endingScene();

	//옵션
	void Pause();
	void SettingBgmButton();
	void SettingsoundButton();
	void delet2(Ref* pSender);
	void delet(Ref* pSender);

	const char* huntName_char[4] =
	{
		"파멸의 불덩이",
		"파멸의 눈",
		"울부짖는 돌풍",
		"불사",
	};

	const char* miningName_char[4] =
	{
		"쇼타임",
		"레스트",
		"빈칸",
		"스피드 업",
	};

	const char* hunt_char[4] =
	{
		"2.4배의 데미지가 \n한번에 들어갑니다.",
		"0.8배의 데미지가 \n3번에 걸쳐 들어갑니다.",
		"1.2배의 데미지가 \n2번 들어갑니다.",
		"3초간 몬스터에게 \n데미지를 받지않습니다.",
	};

	const char* mining_char[4] =
	{
		"1초간 모든블럭이 \n자원블럭으로 변합니다.",
		"1분동안 자동으로 \n블럭을 캡니다.",
		"1분동안 자원획득량이 \n2배로 증가합니다.",
		"1분동안 진행률속도가 \n2배로 증가합니다.",
	};

	CREATE_FUNC(SkillshopScene);
};


