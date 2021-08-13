#pragma execution_character_set("utf-8")
#include "SkillshopScene.h"
#include "AudioManagement.h"
#include "ending.h"

Scene* SkillshopScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SkillshopScene::create();

	scene->addChild(layer);

	return scene;
}

bool SkillshopScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	AudioMM::getInstance()->runBGM("SKILL");

	initLayer();
	initSprite();
	initUILayer();
	initHuntingLayer();
	initMiningLayer();
	initPopUpLayer();
	Pause();

	miningToHuntingCallback();

	initData();

	AudioMM::getInstance()->runBGM("SKILL");

	return true;
}

void SkillshopScene::initData()
{
	gem_total = HeroMM::getInstance()->res_total;

	for (int i = 0; i < 8; i++)
	{
		if (SkillMM::getInstance()->isSkillBought[i] == true)
		{
			if (i < 4)
			{
				spr_gem_cost[i]->setVisible(false);
			}
			else if (i >= 4)
			{
				spr_gem_cost2[i - 4]->setVisible(false);
			}
		}
	}
}

void SkillshopScene::initLayer()
{
	layer_hunting = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_hunting);

	layer_mining = LayerColor::create(Color4B(0, 0, 0, 0));
	layer_mining->setVisible(false);
	this->addChild(layer_mining);

	layer_ui = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer_ui, 99);

	layer_popup = Layer::create();
	layer_popup->setPosition(100000, 100000);
	layer_popup->runAction(FadeOut::create(0));
	this->addChild(layer_popup, 101);

	pause_layer = LayerColor::create(Color4B(0, 0, 0, 122));
	pause_layer->setVisible(false);
	this->addChild(pause_layer,102);
}

void SkillshopScene::initSprite()
{
	background = Sprite::create("back.png");
	background->setPosition(Vec2(360, 640));
	this->addChild(background, -2);

	backframe2 = Sprite::create("frame2.png");
	backframe2->setPosition(Vec2(360, 570));
	backframe2->setScaleY(1.2);
	this->addChild(backframe2, -1);

	skill_text = Sprite::create("skill_text.png");
	skill_text->setPosition(Vec2(360, 1000));
	skill_text->setScale(1.5);
	this->addChild(skill_text, 0);

	for (int i = 0; i < 4; i++)
	{
		frame[i] = Sprite::create("frame.png");
		frame[i]->setPosition(vec2_frame[i]);
		frame[i]->setScaleY(1.2);

		item_image[i] = Sprite::create("itemimage.png");
		item_image[i]->setPosition(vec2_item_image[i]);
		item_image[i]->setScale(1.2);

		yourname[i] = Sprite::create("yourname.png");
		yourname[i]->setPosition(vec2_yourname[i]);
		yourname[i]->setScaleY(1.2);

		layer_hunting->addChild(frame[i], -1);
		layer_hunting->addChild(item_image[i], 0);
		layer_hunting->addChild(yourname[i], 0);

		frame2[i] = Sprite::create("frame.png");
		frame2[i]->setPosition(vec2_frame[i]);
		frame2[i]->setScaleY(1.2);

		item_image2[i] = Sprite::create("itemimage.png");
		item_image2[i]->setPosition(vec2_item_image[i]);
		item_image2[i]->setScale(1.2);

		yourname2[i] = Sprite::create("yourname.png");
		yourname2[i]->setPosition(vec2_yourname[i]);
		yourname2[i]->setScaleY(1.2);
		
		layer_mining->addChild(frame2[i], -1);
		layer_mining->addChild(item_image2[i], 0);
		layer_mining->addChild(yourname2[i], 0);
	}
}

void SkillshopScene::initUILayer()
{
	menui_hunting = MenuItemImage::create("battle.png", "battle_off.png",
		CC_CALLBACK_0(SkillshopScene::miningToHuntingCallback, this));
	menui_hunting->setPosition(170, 1000);
	menui_hunting->setScale(1.3);

	menui_hunting_off = MenuItemImage::create("battle_off.png", "battle.png",
		CC_CALLBACK_0(SkillshopScene::miningToHuntingCallback, this));
	menui_hunting_off->setPosition(170, 1000);
	menui_hunting_off->setScale(1.3);

	menui_mining = MenuItemImage::create("mining.png", "mining_off.png",
		CC_CALLBACK_0(SkillshopScene::huntingToMiningCallback, this));
	menui_mining->setPosition(550, 1000);
	menui_mining->setScale(1.3);

	menui_mining_off = MenuItemImage::create("mining_off.png", "mining.png",
		CC_CALLBACK_0(SkillshopScene::huntingToMiningCallback, this));
	menui_mining_off->setPosition(550, 1000);
	menui_mining_off->setScale(1.3);
	
	menu_change_type = Menu::create(menui_hunting, menui_mining, menui_mining_off, menui_hunting_off, NULL);
	menu_change_type->setPosition(Vec2::ZERO);
	layer_ui->addChild(menu_change_type, 0);

	menui_setting = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_1(SkillshopScene::delet2, this));
	menui_setting->setPosition(670, 1230);
	menui_setting->setScale(0.5);

	menui_home = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(SkillshopScene::goToMainCallback, this));
	menui_home->setPosition(580, 1230);
	menui_home->setScale(0.5);

	menu_ui = Menu::create(menui_setting, menui_home, NULL);
	menu_ui->setPosition(Vec2::ZERO);
	layer_ui->addChild(menu_ui, 1);
	
	//auto home_button = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(SkillshopScene::goToMainCallback, this)); //홈버튼tg
	//home_button->setPosition(visible.width - 150, visible.height - 60);
	//home_button->setScale(0.5f);

	//auto setting_button = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_0(TreasureStoreScene::SettingButton, this)); //홈버튼
	//setting_button->setPosition(visible.width - 75, visible.height - 60);
	//setting_button->setScale(0.5f);

	//////////////////////////////////////////////////////////////////////////////////////////////

	gem = Sprite::create("main_gem.png");
	gem->setPosition(50, Director::getInstance()->getVisibleSize().height - 50);
	gem->setScale(0.5);
	layer_ui->addChild(gem, 1);

	label_gem = Label::createWithSystemFont(StringUtils::format("%d", HeroMM::getInstance()->res_total), "res/arial.ttf", 60, Size(500, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_gem->setAnchorPoint(Vec2(0.0f, 0.5f));
	label_gem->setPosition(100, Director::getInstance()->getVisibleSize().height - 50);
	layer_ui->addChild(label_gem, 1);

	//gem_tex[i]->setPosition(90 + (digit - i) * 30, visible.height - 60);
	//gem_tex[i]->setScale(0.5f);
}

void SkillshopScene::initHuntingLayer()
{
	for (int i = 0; i < 4; i++)
	{
		spr_gem_cost[i] = MenuItemImage::create(StringUtils::format("buy.png"), StringUtils::format("buy.png"), CC_CALLBACK_1(SkillshopScene::skillBuyCallback, this));
		spr_gem_cost[i]->setPosition(gem_cost[i]);
		spr_gem_cost[i]->setTag(i);
		//layer_hunting->addChild(spr_gem_cost[i], 1);

		hunting[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		hunting[i]->setPosition(vec2_hunting[i]);
		hunting[i]->setScale(0.95);
		layer_hunting->addChild(hunting[i], 1);

		//menui_buy = MenuItemImage::create("equip.png", "equip.png", CC_CALLBACK_0(SkillshopScene::skillBuyCallback, this));
		//menui_buy->setPosition(vec2_menui_buy[i]);
		//menu_hunting_skill = Menu::create(menui_buy, NULL);

		hunting_skill[i] = MenuItemImage::create(StringUtils::format("info2.png"), StringUtils::format("info2.png"), CC_CALLBACK_1(SkillshopScene::skillDetailCallback, this));
		hunting_skill[i]->setPosition(vec2_hunting_skill[i]);
		hunting_skill[i]->setTag(i);

		lab_hunting[i] = Label::createWithSystemFont((huntName_char[i]), "fonts/arial.ttf", 48, Size(48 * strlen(huntName_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_hunting[i]->setPosition(vec2_lab_hunting[i]);
		layer_hunting->addChild(lab_hunting[i], 2);

		//lab_cost[i] = Label::createWithTTF(StringUtils::format(""), "fonts/arial.ttf", 64);
		//lab_cost[i]->setPosition(vec2_lab_cost[i]);

		//layer_hunting->addChild(lab_cost[i], 1);
	}

	menu_hunting_skill = Menu::create(spr_gem_cost[0], spr_gem_cost[1], spr_gem_cost[2], spr_gem_cost[3], hunting_skill[0], hunting_skill[1], hunting_skill[2], hunting_skill[3], NULL);
	menu_hunting_skill->setPosition(0, 0);
	layer_hunting->addChild(menu_hunting_skill);
}

void SkillshopScene::initMiningLayer()
{
	for (int i = 0; i < 4; i++)
	{
		spr_gem_cost2[i] = MenuItemImage::create(StringUtils::format("buy.png"), StringUtils::format("buy.png"), CC_CALLBACK_1(SkillshopScene::skillBuyCallback, this));
		spr_gem_cost2[i]->setPosition(gem_cost[i]);
		spr_gem_cost2[i]->setTag(i + 4);

		hunting2[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		hunting2[i]->setPosition(vec2_hunting[i]);
		hunting2[i]->setScale(0.95);
		layer_mining->addChild(hunting2[i], 1);

		mining_skill[i] = MenuItemImage::create(StringUtils::format("info2.png"), StringUtils::format("info2.png"), CC_CALLBACK_1(SkillshopScene::skillDetailCallback, this));
		mining_skill[i]->setPosition(vec2_hunting_skill[i]);
		mining_skill[i]->setTag(i + 4);

		lab_mining[i] = Label::createWithSystemFont((miningName_char[i]), "fonts/arial.ttf", 48, Size(48 * strlen(miningName_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_mining[i]->setPosition(vec2_lab_hunting[i]);
		layer_mining->addChild(lab_mining[i]);
	}

	menu_mining_skill = Menu::create(spr_gem_cost2[0], spr_gem_cost2[1], spr_gem_cost2[2], spr_gem_cost2[3], mining_skill[0], mining_skill[1], mining_skill[2], mining_skill[3], NULL);
	menu_mining_skill->setPosition(0, 0);
	layer_mining->addChild(menu_mining_skill);
}

void SkillshopScene::initPopUpLayer()
{
	auto frame3 = Sprite::create("frame.png");
	frame3->setPosition(420, 875);
	layer_popup->addChild(frame3);

	auto gray = Sprite::create("gray.png");
	gray->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	gray->setScale(2);
	gray->setOpacity(200);
	layer_popup->addChild(gray);
	
	skill_popup = Sprite::create("skillpopup.png");
	skill_popup->setPosition(360, 640);
	skill_popup->setScale(2.0);
	layer_popup->addChild(skill_popup);

	menui_close_detail = MenuItemImage::create("delete.png", "delete.png", CC_CALLBACK_0(SkillshopScene::closeSkillDetailCallback, this));
	menui_close_detail->setPosition(615, 938);
	menui_close_detail->setScale(2.0);

	menu_buy = Menu::create(menui_close_detail, NULL);
	menu_buy->setPosition(0, 0);
	layer_popup->addChild(menu_buy);

	popup_item_image = Sprite::create("itemimage.png");
	popup_item_image->setPosition(165, 875);
	layer_popup->addChild(popup_item_image);

	for (int i = 0; i < 4; i++)
	{
		skillimage[i] = Sprite::create(StringUtils::format("skill_image%d.png", i + 1));
		skillimage[i]->setPosition(360, 550);
		skillimage[i]->setScaleX(1.5);
		layer_popup->addChild(skillimage[i]);

		popup_skill[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		popup_skill[i]->setPosition(165,875);
		popup_skill[i]->setScale(0.75);
		layer_popup->addChild(popup_skill[i]);

		//spr_hunting_skill[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		//spr_hunting_skill[i]->setPosition(200, 800);
		//spr_hunting_skill[i]->setVisible(false);
		//layer_popup->addChild(spr_hunting_skill[i]);

		lab_hunting_name[i] = Label::createWithSystemFont(huntName_char[i],"fonts/arial.ttf", 32, Size(32 * strlen(huntName_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_hunting_name[i]->setPosition(420, 925);
		lab_hunting_name[i]->setScale(1.5);
		lab_hunting_name[i]->setVisible(false);
		layer_popup->addChild(lab_hunting_name[i]);

		lab_hunting_explain[i] = Label::createWithSystemFont(hunt_char[i], "fonts/arial.ttf", 32, Size(32 * strlen(hunt_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_hunting_explain[i]->setPosition(420, 825);
		lab_hunting_explain[i]->setVisible(false);
		layer_popup->addChild(lab_hunting_explain[i]);

		//spr_mining_skill[i] = Sprite::create(StringUtils::format("skill%d.png", i + 1));
		//spr_mining_skill[i]->setPosition(200, 1000);
		//spr_mining_skill[i]->setVisible(false);
		//layer_popup->addChild(spr_mining_skill[i]);

		lab_mining_name[i] = Label::createWithSystemFont((miningName_char[i]), "fonts/arial.ttf", 32, Size(32 * strlen(miningName_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_mining_name[i]->setPosition(420, 875);
		lab_mining_name[i]->setScale(1.5);
		lab_mining_name[i]->setVisible(false);
		layer_popup->addChild(lab_mining_name[i]);

		lab_mining_explain[i] = Label::createWithSystemFont((mining_char[i]), "fonts/arial.ttf", 32, Size(32 * strlen(mining_char[i]), 70), TextHAlignment::CENTER, TextVAlignment::CENTER);
		lab_mining_explain[i]->setPosition(350, 700);
		lab_mining_explain[i]->setVisible(false);
		layer_popup->addChild(lab_mining_explain[i]);
	}
}

void SkillshopScene::goToMainCallback()
{
	AudioMM::getInstance()->runEffect("CLOSE");

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void SkillshopScene::goToEndingCallback()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void SkillshopScene::huntingToMiningCallback()
{
	layer_hunting->setVisible(false);
	layer_mining->setVisible(true);
	menui_mining_off->setVisible(false);
	menui_hunting_off->setVisible(true);
}

void SkillshopScene::miningToHuntingCallback()
{
	layer_hunting->setVisible(true);
	layer_mining->setVisible(false);
	menui_mining_off->setVisible(true);
	menui_hunting_off->setVisible(false);
}

void SkillshopScene::skillDetailCallback(Ref* pSender)
{
	AudioMM::getInstance()->runEffect("POPUP");

	selected_skill_num = ((Node*)pSender)->getTag();
	log("%d", selected_skill_num);
	
	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);

	for (int i = 1; i < 5; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/skill_pop_0%d.png", i), Rect(0, 0, 334, 352)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
	openAni->setScale(2.f);
	layer_popup->runAction(Sequence::create(DelayTime::create(0.20f), MoveTo::create(0, Vec2::ZERO), nullptr));


	menui_hunting->setEnabled(false);
	menui_mining->setEnabled(false);
	
	menui_hunting_off->setEnabled(false);
	menui_mining_off->setEnabled(false);

	if (selected_skill_num < 4)
	{
		lab_hunting_explain[selected_skill_num]->setVisible(true);
		lab_hunting_name[selected_skill_num]->setVisible(true);

		for (int i = 0; i < 4; i++)
		{
			if (i == selected_skill_num)
			{
				continue;
			}
			lab_hunting_explain[i]->setVisible(false);
			lab_hunting_name[i]->setVisible(false);

			hunting_skill[i]->setEnabled(false);
		}
	}
	else if (selected_skill_num < 8)
	{
		lab_mining_name[selected_skill_num - 4]->setVisible(true);
		lab_mining_explain[selected_skill_num - 4]->setVisible(true);

		for (int i = 0; i < 4; i++)
		{
			if (i + 4 == selected_skill_num)
			{
				continue;
			}

			lab_mining_name[i]->setVisible(false);
			lab_mining_explain[i]->setVisible(false);

			mining_skill[i]->setEnabled(false);
		}
	}

	menui_hunting->setEnabled(false);
	menui_mining->setEnabled(false);

	menui_home->setEnabled(false);
}

void SkillshopScene::skillBuyCallback(Ref* pSender)
{
	AudioMM::getInstance()->runEffect("BUY");

	selected_skill_num = ((Node*)pSender)->getTag();

	SkillMM::getInstance()->isSkillBought[selected_skill_num] = true;
	
	HeroMM::getInstance()->res_total -= SkillMM::getInstance()->skill_cost[selected_skill_num];
	label_gem->setString(StringUtils::format("%d", HeroMM::getInstance()->res_total));
	
	for (int i = 0; i < 4; i++)
	{
		if (SkillMM::getInstance()->isSkillBought[selected_skill_num] == true)
		{
			if (selected_skill_num < 4)
			{
				spr_gem_cost[selected_skill_num]->setVisible(false);
			}
			else if (selected_skill_num >= 4)
			{
				spr_gem_cost2[selected_skill_num - 4]->setVisible(false);
			}
		}
	}
}

void SkillshopScene::closeSkillDetailCallback()
{
	layer_popup->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 5; i >= 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/skill_pop_0%d.png", i), Rect(0, 0, 334, 352)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
	openAni->setScale(1.5f);
	menui_hunting->setEnabled(true);
	menui_mining->setEnabled(true);

	menui_hunting_off->setEnabled(true);
	menui_mining_off->setEnabled(true);

	for (int i = 0; i < 4; i++)
	{
		hunting_skill[i]->setEnabled(true);
		mining_skill[i]->setEnabled(true);
	}

	menui_hunting->setEnabled(true);
	menui_mining->setEnabled(true);

	menui_home->setEnabled(true);

	lab_hunting_explain[selected_skill_num]->setVisible(false);
	lab_hunting_name[selected_skill_num]->setVisible(false);

	lab_mining_name[selected_skill_num - 4]->setVisible(false);
	lab_mining_explain[selected_skill_num - 4]->setVisible(false);
}

void SkillshopScene::endingScene()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void SkillshopScene::Pause()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 100);

	pause_layer = Layer::create();
	pause_layer->setPosition(100000, 10000);
	this->addChild(pause_layer, 100);

	char* spriteName[4];

	spriteName[0] = AudioMM::getInstance()->getBGMEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[1] = AudioMM::getInstance()->getBGMEnabled() ? "sound_off.png" : "sound_on.png";
	spriteName[2] = AudioMM::getInstance()->getEffectEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[3] = AudioMM::getInstance()->getEffectEnabled() ? "sound_off.png" : "sound_on.png";

	auto sound_bgm_on = MenuItemSprite::create(Sprite::create(spriteName[0]), Sprite::create(spriteName[1]));
	auto sound_bgm_off = MenuItemSprite::create(Sprite::create(spriteName[1]), Sprite::create(spriteName[0]));
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(SkillshopScene::SettingBgmButton, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(SkillshopScene::SettingsoundButton, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	pause_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_1(SkillshopScene::delet, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(SkillshopScene::goToMainCallback, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(SkillshopScene::endingScene, this));
	ending_scene->setPosition(visibleSize.width * 0.5f, 350);

	auto ending_gradation = Sprite::create("credit_button_gradation.png");
	ending_gradation->setPosition(visibleSize.width * 0.5f, 350);
	pause_layer->addChild(ending_gradation, 2);

	auto menu1 = Menu::create(paused_done, ending_scene, menuScene_button, NULL);
	menu1->setPosition(0, 0);
	pause_layer->addChild(menu1, 3);

	auto setting_menu = Menu::create(setting_bgm_button, setting_effect_button, NULL);
	setting_menu->setPosition(Vec2::ZERO);
	pause_layer->addChild(setting_menu, 2);

	auto backgray = Sprite::create("gray.png");
	backgray->setPosition(visibleSize.height * 0.5f, visibleSize.height * 0.5f);
	backgray->setScale(3);
	backgray->setOpacity(200);
	pause_layer->addChild(backgray);
}

void SkillshopScene::SettingBgmButton() //BGM끄기
{	
	AudioMM::getInstance()->changeBGMState();
}

void SkillshopScene::SettingsoundButton() //사운드끄기
{
	AudioMM::getInstance()->changeEffectState();
}

void SkillshopScene::delet2(Ref* pSender)
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
	openAni->setScale(1);
	pause_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
}

void SkillshopScene::delet(Ref* pSender)
{
	pause_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
	openAni->setScale(1);
}