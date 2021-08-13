#pragma execution_character_set("utf-8")

#include "UpgradeScene.h"
#include "MenuScene.h"
#include "EquipmentManagement.h"
#include "AudioManagement.h"
#include "ending.h"

Scene* UpgradeScene::createScene()
{
	auto scene = Scene::create();

	auto layer = UpgradeScene::create();

	scene->addChild(layer);

	return scene;
}

bool UpgradeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initLayer();
	initSprite();
	initMenu();
	initLabel();
	initSetting();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm/BGM_equipment.wav");

	light = Sprite::create("upgrade_light.png");
	light->runAction(FadeOut::create(0));
	light->setAnchorPoint(Vec2(0.5f, 0));
	light->setPosition(Director::getInstance()->getVisibleSize().width * 0.5f, 50);
	this->addChild(light);

	//AudioMM::getInstance()->runBGM("EQUIPMENT");

	return true;
}

void UpgradeScene::initLayer()
{
	layer_background = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_background);

	layer_sword = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_sword);

	layer_pickaxe = LayerColor::create(Color4B(0, 0, 0, 0));
	layer_pickaxe->setVisible(false);
	this->addChild(layer_pickaxe);

	layer_ui = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_ui);

	layer_panel = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_panel);


}

void UpgradeScene::initSprite()
{
	spr_background = Sprite::create("upgrade_background.png");
	spr_background->setAnchorPoint(Vec2(0, 0));
	layer_background->addChild(spr_background);

	spr_character = Sprite::create("upgrade_character.png");
	spr_character->setPosition(360, 900);
	spr_character->setScale(2.0f);
	layer_background->addChild(spr_character);

	spr_panel_inside = Sprite::create("upgrade_inside.png");
	spr_panel_inside->setPosition(360, 450);
	spr_panel_inside->setScale(1.0f);
	layer_background->addChild(spr_panel_inside, 1);

	spr_panel = Sprite::create("upgrade_panel.png");
	spr_panel->setPosition(360, 450);
	spr_panel->setScale(1.0f);
	layer_panel->addChild(spr_panel, 1);

	spr_panel_up = Sprite::create("upgrade_panel_up.png");
	spr_panel_up->setPosition(360, 850);
	spr_panel_up->setScale(1.0f);
	layer_panel->addChild(spr_panel_up, 1);

	spr_gem = Sprite::create("main_gem.png");
	spr_gem->setPosition(50, Director::getInstance()->getVisibleSize().height - 50);
	spr_gem->setScale(0.5f);
	layer_background->addChild(spr_gem, 1);

	spr_sword = Sprite::create("weapon_0.png");
	spr_sword->setPosition(360, 560);
	spr_sword->setAnchorPoint(ccp(0.5f, 0.5f));
	layer_sword->addChild(spr_sword);

	spr_weapon_grad = Sprite::create("upgrade_weapon_grad.png");
	spr_weapon_grad->setPosition(360, 560);
	layer_sword->addChild(spr_weapon_grad, -1);

	spr_pickaxe = Sprite::create("pickaxe_0.png");
	spr_pickaxe->setPosition(360, 560);
	spr_pickaxe->setScale(2.0f);
	layer_pickaxe->addChild(spr_pickaxe);

	spr_pickaxe_grad = Sprite::create("upgrade_weapon_grad.png");
	spr_pickaxe_grad->setPosition(360, 560);
	layer_pickaxe->addChild(spr_pickaxe_grad, -1);
	
	for (int i = 0; i < 2; i++)
	{
		spr_upgrade[i] = Sprite::create(StringUtils::format("upgrade_button_%d.png", i));

		spr_back_button[i] = Sprite::create(StringUtils::format("back_button_%d.png", i));

		spr_sword_to_pickaxe_button[i] = Sprite::create(StringUtils::format("sword_to_pickaxe_button_%d.png", i));
	}

	spr_setting_button = Sprite::create("setting_button.png");

	spr_upgrade_success = Sprite::create("upgrade_success.png");
	spr_upgrade_success->setPosition(360, 1000);
	spr_upgrade_success->setVisible(false);
	layer_background->addChild(spr_upgrade_success, 2);

	spr_upgrade_success_back = Sprite::create("upgrade_success_back.png");
	spr_upgrade_success_back->setPosition(spr_upgrade_success->getPosition());
	spr_upgrade_success_back->setVisible(false);
	spr_upgrade_success_back->runAction(RepeatForever::create(RotateBy::create(3.0f, 360)));
	layer_background->addChild(spr_upgrade_success_back);

	spr_upgrade_success_light = Sprite::create("upgrade_success_light.png");
	spr_upgrade_success_light->setPosition(spr_upgrade_success->getPosition());
	spr_upgrade_success_light->setVisible(false);
	spr_upgrade_success_light->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.8f, 0.8f), ScaleTo::create(0.8f, 1.0f), NULL)));
	layer_background->addChild(spr_upgrade_success_light);

	spr_upgrade_fail = Sprite::create("upgrade_fail.png");
	spr_upgrade_fail->setPosition(360, 1000);
	spr_upgrade_fail->setVisible(false);
	layer_background->addChild(spr_upgrade_fail);

	spr_ok_button = Sprite::create("upgrade_ok_button.png");

	spr_upgrade_hatch_left = Sprite::create("upgrade_hatch_left.png");
	spr_upgrade_hatch_left->setPosition(-150, 400);
	layer_panel->addChild(spr_upgrade_hatch_left, -1);

	spr_upgrade_hatch_right = Sprite::create("upgrade_hatch_right.png");
	spr_upgrade_hatch_right->setPosition(870, 400);
	layer_panel->addChild(spr_upgrade_hatch_right, -1);
}

void UpgradeScene::initMenu()
{
	menui_upgrade = MenuItemSprite::create(spr_upgrade[0], spr_upgrade[1], CC_CALLBACK_1(UpgradeScene::buttonCallBack, this));
	menui_upgrade->setName("UPGRADE");
	menui_upgrade->setPosition(360, 210);

	menui_back_to_menu = MenuItemSprite::create(spr_back_button[0], spr_back_button[1], CC_CALLBACK_1(UpgradeScene::buttonCallBack, this));
	menui_back_to_menu->setName("BACK");
	menui_back_to_menu->setScale(0.5f);
	menui_back_to_menu->setPosition(580, 1230);

	menui_setting = MenuItemSprite::create(spr_setting_button, spr_setting_button, CC_CALLBACK_0(UpgradeScene::SettingLayerOn, this));
	menui_setting->setName("SETTING");
	menui_setting->setScale(0.5f);
	menui_setting->setPosition(670, 1230);

	menui_sword_to_pickaxe = MenuItemSprite::create(spr_sword_to_pickaxe_button[0], spr_sword_to_pickaxe_button[1], CC_CALLBACK_1(UpgradeScene::buttonCallBack, this));
	menui_sword_to_pickaxe->setName("CHANGE");
	menui_sword_to_pickaxe->setScale(2.0f);
//	menui_sword_to_pickaxe->setPosition(360, 110);
	menui_sword_to_pickaxe->setPosition(10000, 10000);

	menui_ok_button = MenuItemSprite::create(spr_ok_button, spr_ok_button, CC_CALLBACK_1(UpgradeScene::buttonCallBack, this));
	menui_ok_button->setName("OK");
	menui_ok_button->setVisible(false);
	menui_ok_button->setPosition(360, 210);

	spr_button_grad = Sprite::create("upgrade_button_grad.png");
	spr_button_grad->setPosition(360, 210);
	layer_ui->addChild(spr_button_grad, -1);

	menu_ui = Menu::create(menui_upgrade, menui_back_to_menu, menui_setting, menui_sword_to_pickaxe, menui_ok_button, NULL);
	menu_ui->setPosition(0, 0);
	layer_ui->addChild(menu_ui);
}

void UpgradeScene::initLabel()
{
	label_current_res = Label::createWithSystemFont(StringUtils::format("%d", HeroMM::getInstance()->res_total), "res/arial.ttf", 60, Size(500, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_current_res->setAnchorPoint(Vec2(0, 0.5f));
	label_current_res->setPosition(100, Director::getInstance()->getVisibleSize().height - 50);
	layer_ui->addChild(label_current_res);

	lab_weapon_level = Label::create("", "", 48);
	lab_weapon_level->setString(StringUtils::format("강화 +%d", EquipmentMM::getInstance()->weapon_level));
	lab_weapon_level->setPosition(360, 380);
	layer_sword->addChild(lab_weapon_level);

	lab_pickaxe_level = Label::create("", "", 48);
	lab_pickaxe_level->setString(StringUtils::format("강화 +%d", EquipmentMM::getInstance()->pickaxe_level));
	lab_pickaxe_level->setPosition(360, 380);
	layer_pickaxe->addChild(lab_pickaxe_level);

	lab_weapon_probability = Label::create("", "", 48);
	lab_weapon_probability->setString(StringUtils::format("성공률 %d%%", EquipmentMM::getInstance()->weapon_upgrade_probability));
	lab_weapon_probability->setPosition(360, 310);
	layer_sword->addChild(lab_weapon_probability);

	lab_pickaxe_probability = Label::create("", "", 48);
	lab_pickaxe_probability->setString(StringUtils::format("성공률 %d%%", EquipmentMM::getInstance()->pickaxe_upgrade_probability));
	lab_pickaxe_probability->setPosition(360, 310);
	layer_pickaxe->addChild(lab_pickaxe_probability);

	label_weapon_upgrade_cost = Label::create("", "", 40);
	label_weapon_upgrade_cost->setString(StringUtils::format("%d", EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level]));
	label_weapon_upgrade_cost->setPosition(10000, 10000);
	//label_weapon_upgrade_cost->setPosition(480, 210);
	layer_sword->addChild(label_weapon_upgrade_cost);

	label_pickaxe_upgrade_cost = Label::create("", "", 40);
	label_pickaxe_upgrade_cost->setString(StringUtils::format("%d", EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level]));
	label_pickaxe_upgrade_cost->setPosition(10000, 10000);
	//label_pickaxe_upgrade_cost->setPosition(480, 210);
	layer_pickaxe->addChild(label_pickaxe_upgrade_cost, 5);

	lab_change = Label::create("변경", "", 40);
	lab_change->setPosition(10000, 10000);
	//lab_change->setPosition(360, 110);
	layer_ui->addChild(lab_change);
}

void UpgradeScene::initSetting()
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 99);

	setting_layer = Layer::create();
	setting_layer->setPosition(100000, 10000);
	this->addChild(setting_layer, 100);

	char* spriteName[4];

	spriteName[0] = AudioMM::getInstance()->getBGMEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[1] = AudioMM::getInstance()->getBGMEnabled() ? "sound_off.png" : "sound_on.png";
	spriteName[2] = AudioMM::getInstance()->getEffectEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[3] = AudioMM::getInstance()->getEffectEnabled() ? "sound_off.png" : "sound_on.png";

	auto sound_bgm_on = MenuItemSprite::create(Sprite::create(spriteName[0]), Sprite::create(spriteName[1]));
	auto sound_bgm_off = MenuItemSprite::create(Sprite::create(spriteName[1]), Sprite::create(spriteName[0]));
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(UpgradeScene::SetBgmSound, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(UpgradeScene::SetEffectSound, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	setting_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_0(UpgradeScene::SettingLayerOff, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(UpgradeScene::backToMenu, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(UpgradeScene::EnddingScene, this));
	ending_scene->setPosition(visibleSize.width * 0.5f, 400);

	auto ending_gradation = Sprite::create("credit_button_gradation.png");
	ending_gradation->setPosition(visibleSize.width * 0.5f, 400);
	setting_layer->addChild(ending_gradation, 2);


	auto menu1 = Menu::create(paused_done, ending_scene, menuScene_button, NULL);
	menu1->setPosition(0, 0);
	setting_layer->addChild(menu1, 3);

	auto setting_menu = Menu::create(setting_bgm_button, setting_effect_button, NULL);
	setting_menu->setPosition(Vec2::ZERO);
	setting_layer->addChild(setting_menu, 2);

	auto backgray = Sprite::create("gray.png");
	backgray->setPosition(visibleSize.height * 0.5f, visibleSize.height * 0.5f);
	backgray->setScale(3);
	backgray->setOpacity(200);
	setting_layer->addChild(backgray);
}

bool UpgradeScene::upgradeGamble(int percentage)
{
	srand((unsigned)time(NULL));

	int tmp_rand;

	tmp_rand = rand() % 101;
	
	if (tmp_rand <= percentage)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UpgradeScene::upgradeAnimationWithEffect(int target)
{
	AudioMM::getInstance()->runEffect("EQUIPMENTUPGRADE");

	if (target == WEAPON)
	{
		HeroMM::getInstance()->res_total -= EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level];
		label_current_res->setString(StringUtils::format("%d", HeroMM::getInstance()->res_total));
	}
	else if (target == PICKAXE)
	{
		HeroMM::getInstance()->res_total -= EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level];
		label_current_res->setString(StringUtils::format("%d", HeroMM::getInstance()->res_total));
	}

	spr_button_grad->setVisible(false);

	menui_upgrade->setVisible(false);
	menui_sword_to_pickaxe->setVisible(false);
	menui_back_to_menu->setVisible(false);
	menui_setting->setVisible(false);

	lab_weapon_level->setVisible(false);
	lab_pickaxe_level->setVisible(false);
	lab_weapon_probability->setVisible(false);
	lab_pickaxe_probability->setVisible(false);
	label_weapon_upgrade_cost->setVisible(false);
	label_pickaxe_upgrade_cost->setVisible(false);
	lab_change->setVisible(false);

	moveby_right = MoveBy::create(0.5f, Vec2(430, 0));
	moveby_left = MoveBy::create(0.5f, Vec2(-430, 0));

	auto moveby_up = MoveBy::create(0.02f, Vec2(0, 10));
	auto moveby_down = MoveBy::create(0.02f, Vec2(0, -10));

	spr_upgrade_hatch_left->runAction(Sequence::create(DelayTime::create(1), 
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, nullptr));
	spr_upgrade_hatch_right->runAction(Sequence::create(DelayTime::create(1),
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down, moveby_down, moveby_up, moveby_up, moveby_down,
		moveby_up, moveby_down, nullptr));
	
	spr_upgrade_hatch_left->runAction(TintTo::create(0.5f, 255, 255, 255));
	spr_upgrade_hatch_right->runAction(TintTo::create(0.5f, 255, 255, 255));

	seq_upgrade = Sequence::create(CallFunc::create([&]() { spr_upgrade_hatch_left->runAction(Sequence::create(moveby_right->clone(), TintTo::create(0.5f, 255, 180, 180), DelayTime::create(1.0f), moveby_left->clone(), nullptr)); spr_upgrade_hatch_right->runAction(Sequence::create(moveby_left->clone(), TintTo::create(0.5f, 255, 180, 180), DelayTime::create(1.0f), moveby_right->clone(), nullptr)); }),
								   DelayTime::create(2.1f),
								   CallFunc::create(CC_CALLBACK_0(UpgradeScene::upgradeTarget, this, target)),
								   CallFunc::create([&] { lab_weapon_level->setVisible(true); lab_pickaxe_level->setVisible(true); spr_button_grad->setVisible(true); }),
								   NULL);

	light->runAction(Sequence::create(DelayTime::create(1.f), FadeIn::create(1.f), FadeOut::create(0),nullptr));

	spr_background->runAction(seq_upgrade);
}

void UpgradeScene::upgradeTarget(int target)
{
	if (target == WEAPON)
	{
		if (EquipmentMM::getInstance()->weapon_level <= 30 && HeroMM::getInstance()->res_total + EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level] >= EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level])
		{
			menui_ok_button->setVisible(true);

			if (upgradeGamble(EquipmentMM::getInstance()->weapon_upgrade_probability))
			{
				upgradeSuccess(target);
				log("upgrade success");
			}
			else
			{
				upgradeFail(target);
				log("upgrade fail");
			}
		}
		else
		{
			log("you can't upgrade");
		}
	}
	else if (target == PICKAXE)
	{
		if (EquipmentMM::getInstance()->pickaxe_level <= 30 && HeroMM::getInstance()->res_total + EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level] >= EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level])
		{
			menui_ok_button->setVisible(true);

			if (upgradeGamble(EquipmentMM::getInstance()->pickaxe_upgrade_probability))
			{
				upgradeSuccess(target);
				log("upgrade success");
			}
			else
			{
				upgradeFail(target);
				log("upgrade fail");
			}
		}
		else
		{
			log("you can't upgrade");
		}
	}

	log("weapon%d pickaxe%d", EquipmentMM::getInstance()->weapon_level, EquipmentMM::getInstance()->pickaxe_level);
}

void UpgradeScene::backToMenu()
{
	AudioMM::getInstance()->runEffect("CLOSE");
	Scene* scene_menu = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene_menu);
}

void UpgradeScene::changeTarget()
{
	AudioMM::getInstance()->runEffect("EQUIPMENTCHANGE");

	if (layer_sword->isVisible())
	{
		layer_sword->setVisible(false);
		layer_pickaxe->setVisible(true);
	}
	else if (layer_pickaxe->isVisible())
	{
		layer_sword->setVisible(true);
		layer_pickaxe->setVisible(false);
	}
}

void UpgradeScene::SettingLayerOn()
{
	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	setting_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
}

void UpgradeScene::SettingLayerOff()
{
	setting_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
}

void UpgradeScene::SetBgmSound()
{
	AudioMM::getInstance()->changeBGMState();
}

void UpgradeScene::SetEffectSound()
{
	AudioMM::getInstance()->changeEffectState();
}

void UpgradeScene::EnddingScene()
{
	Scene* scene_menu = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene_menu);
}

void UpgradeScene::upgradeSuccess(int target)
{
	spr_upgrade_success->setVisible(true);
	
	spr_upgrade_success_back->setVisible(true);

	AudioMM::getInstance()->runEffect("UPGRADESUCCESS");



	if (target == WEAPON)
	{
		EquipmentMM::getInstance()->weapon_level++;
		lab_weapon_level->setString(StringUtils::format("강화 +%d", EquipmentMM::getInstance()->weapon_level));

		EquipmentMM::getInstance()->weapon_upgrade_probability--;

		if (EquipmentMM::getInstance()->weapon_upgrade_probability <= 0)
		{
			EquipmentMM::getInstance()->weapon_upgrade_probability = 1;
		}

		lab_weapon_probability->setString(StringUtils::format("성공률 %d%%", EquipmentMM::getInstance()->weapon_upgrade_probability));

		label_weapon_upgrade_cost->setString(StringUtils::format("%d", EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level]));
	}
	else if (target == PICKAXE)
	{
		EquipmentMM::getInstance()->pickaxe_level++;
		lab_pickaxe_level->setString(StringUtils::format("강화 +%d", EquipmentMM::getInstance()->pickaxe_level));

		EquipmentMM::getInstance()->pickaxe_upgrade_probability--;

		if (EquipmentMM::getInstance()->pickaxe_upgrade_probability <= 0)
		{
			EquipmentMM::getInstance()->pickaxe_upgrade_probability = 1;
		}

		lab_pickaxe_probability->setString(StringUtils::format("성공률 %d%%", EquipmentMM::getInstance()->pickaxe_upgrade_probability));

		label_pickaxe_upgrade_cost->setString(StringUtils::format("%d", EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level]));
	}
}

void UpgradeScene::upgradeFail(int target)
{
	AudioMM::getInstance()->runEffect("UPGRADEFAIL");
	spr_upgrade_fail->setVisible(true);
}

void UpgradeScene::buttonCallBack(Ref* sender)
{
	if (((Node*)sender)->getName() == "UPGRADE")
	{
		if (layer_sword->isVisible() && EquipmentMM::getInstance()->weapon_level <= 30 && HeroMM::getInstance()->res_total >= EquipmentMM::getInstance()->weapon_upgrade_cost[EquipmentMM::getInstance()->weapon_level])
		{
			upgradeAnimationWithEffect(WEAPON);
		}
		else if (layer_pickaxe->isVisible() && EquipmentMM::getInstance()->pickaxe_level <= 30 && HeroMM::getInstance()->res_total >= EquipmentMM::getInstance()->pickaxe_upgrade_cost[EquipmentMM::getInstance()->pickaxe_level])
		{
			upgradeAnimationWithEffect(PICKAXE);
		}
	}

	if (((Node*)sender)->getName() == "BACK")
	{
		backToMenu();
	}

	if (((Node*)sender)->getName() == "CHANGE")
	{
		changeTarget();
	}

	if (((Node*)sender)->getName() == "OK")
	{
		spr_upgrade_success->setVisible(false);
		spr_upgrade_fail->setVisible(false);

		spr_upgrade_success_back->setVisible(false);
		spr_upgrade_success_light->setVisible(false);

		menui_ok_button->setVisible(false);
		menui_upgrade->setVisible(true);
		menui_sword_to_pickaxe->setVisible(true);
		menui_back_to_menu->setVisible(true);
		menui_setting->setVisible(true);

		lab_weapon_probability->setVisible(true);
		lab_pickaxe_probability->setVisible(true);
		label_weapon_upgrade_cost->setVisible(true);
		label_pickaxe_upgrade_cost->setVisible(true);
		lab_change->setVisible(true);
	}
}
