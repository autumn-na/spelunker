#pragma once

#include "cocos2d.h"

USING_NS_CC;

class UpgradeScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	LayerColor* layer_background;
	LayerColor* layer_sword;
	LayerColor* layer_pickaxe;
	LayerColor* layer_ui;
	LayerColor* layer_panel;
	Layer* setting_layer;

	Sprite* openAni;
	Sprite* spr_background;
	Sprite* spr_character;
	Sprite* spr_panel;
	Sprite* spr_panel_inside;
	Sprite* spr_panel_up;
	Sprite* spr_gem;
	Sprite* light;

	Sprite* spr_pickaxe;
	Sprite* spr_sword;

	Sprite* spr_upgrade[2];

	Sprite* spr_back_button[2];
	Sprite* spr_setting_button;
	Sprite* spr_sword_to_pickaxe_button[2];
	Sprite* spr_ok_button;

	Sprite* spr_upgrade_success;
	Sprite* spr_upgrade_fail;

	Sprite* spr_upgrade_hatch_left;
	Sprite* spr_upgrade_hatch_right;

	Sprite* spr_weapon_grad;
	Sprite* spr_pickaxe_grad;
	Sprite* spr_button_grad;

	Sprite* spr_upgrade_success_back;
	Sprite* spr_upgrade_success_light;

	MenuItemSprite* menui_upgrade;
	MenuItemSprite* menui_back_to_menu;
	MenuItemSprite* menui_setting;
	MenuItemSprite* menui_sword_to_pickaxe;
	MenuItemSprite* menui_ok_button;

	Menu* menu_sword;
	Menu* menu_pickaxe;
	Menu* menu_ui;

	Label* label_current_res;

	Label* lab_weapon_level;
	Label* lab_pickaxe_level;

	Label* lab_weapon_probability;
	Label* lab_pickaxe_probability;

	Label* label_weapon_upgrade_cost;
	Label* label_pickaxe_upgrade_cost;

	Label* lab_change;

	//Actions
	MoveBy* moveby_right;
	MoveBy* moveby_left;
	Spawn* move_hatch;

	Sequence* seq_move_hatch;
	Sequence* seq_upgrade;

	enum
	{
		WEAPON,
		PICKAXE
	};

	///////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////

	void initLayer();
	void initSprite();
	void initMenu();
	void initLabel();
	void initSetting();

	void backToMenu();
	void changeTarget();

	void SettingLayerOn();
	void SettingLayerOff();
	void SetBgmSound();
	void SetEffectSound();
	void EnddingScene();
	

	bool upgradeGamble(int percentage);
	void upgradeAnimationWithEffect(int target);
	void upgradeTarget(int target);
	void upgradeSuccess(int target);
	void upgradeFail(int target);

	void buttonCallBack(Ref* sender);

	CREATE_FUNC(UpgradeScene);
};
