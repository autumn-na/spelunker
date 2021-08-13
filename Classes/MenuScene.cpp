#include "MenuScene.h"
#include "UpgradeScene.h"
#include "ClothingStoreScene.h"
#include "SkillshopScene.h"
#include "TreasureScene.h"
#include "UpgradeScene.h"
#include "SimpleAudioEngine.h"
#include "AudioManagement.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MenuScene::createScene()
{

    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visible = Director::getInstance()->getVisibleSize();

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	AudioMM::getInstance()->runBGM("MAIN");

	auto background = Sprite::create("main_background.png");
	//background->setScale(1.5f);
	background->setPosition(visible.width *0.5f, visible.height * 0.5f);
	this->addChild(background, 0);

	auto gem = Sprite::create("main_gem.png");                //보석이미햨E
	gem->setPosition(Point(50, visible.height - 50));
	gem->setScale(0.5f);
	this->addChild(gem, 1);

	auto label_current_res = Label::createWithSystemFont(StringUtils::format("%d", HeroMM::getInstance()->res_total), "res/arial.ttf", 60, Size(500, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	label_current_res->setAnchorPoint(Vec2(0, 0.5f));
	label_current_res->setPosition(100, Director::getInstance()->getVisibleSize().height - 50);
	this->addChild(label_current_res, 1);

	auto character = Sprite::create("character.png");  //주인공캐릭터
	character->setPosition(Vec2(380, 500));
	character->setScale(0.4);
	this->addChild(character, 1);

	//auto home_button = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(MenuScene::HomeButton, this)); //홈버튼
	//home_button->setPosition(visible.width - 150, visible.height - 60);
	//home_button->setScale(0.5f);

	auto setting_button = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_0(MenuScene::SettingButton, this)); //설정 버튼
	setting_button->setPosition(670, 1230);
	setting_button->setScale(0.5f);

	auto close_normal = MenuItemImage::create("cave_start.png", "cave_start.png", CC_CALLBACK_0(MenuScene::ChangeScene, this)); //탐험시작 버튼 
	close_normal->setPosition(100, 100);

	auto enhance_house = MenuItemImage::create("upgrade_house.png", "upgrade_house.png", CC_CALLBACK_0(MenuScene::UpgradeCallback, this)); //강화상점
	enhance_house->setPosition(630, 909);

	auto upgradeicon = Sprite::create("upgrade_icon.png");
	upgradeicon->setPosition(676, 600);

	auto special_skill_house = MenuItemImage::create("skill_house.png", "skill_house.png", CC_CALLBACK_0(MenuScene::SkillShopCallback, this)); //특수스킬상점
	special_skill_house->setPosition(92, 410);
	
	auto skillicon = Sprite::create("skill_icon.png");
	skillicon->setPosition(50, 1000);

	auto clothes_house = MenuItemImage::create("shop_house.png", "shop_house.png", CC_CALLBACK_0(MenuScene::ClothesCallback, this)); //의상가게
	clothes_house->setPosition(100, 838);

	auto shopicon = Sprite::create("shop_icon.png");
	shopicon->setPosition(92, 560);

	auto main_npc = MenuItemImage::create("treasure_house.png", "treasure_house.png", CC_CALLBACK_0(MenuScene::TreasureCallback, this)); //보물상자주는 npc
	main_npc->setPosition(600, 469);

	auto treasureicon = Sprite::create("treasure_icon.png");
	treasureicon->setPosition(560, 1050);

	this->addChild(treasureicon,2);
	this->addChild(upgradeicon,2);
	this->addChild(skillicon,2);
	this->addChild(shopicon,2);

	menu = Menu::create(/*home_button,*/ setting_button, close_normal, clothes_house, enhance_house, special_skill_house, main_npc, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	setting_layer = Layer::create();
	setting_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));
	this->addChild(setting_layer, 10);

	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 99);

	setting_layer = Layer::create();
	setting_layer->setPosition(100000, 10000);
	this->addChild(setting_layer, 100);

	char* spriteName[4];
	auto visibleSize = Director::getInstance()->getVisibleSize();

	spriteName[0] = AudioMM::getInstance()->getBGMEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[1] = AudioMM::getInstance()->getBGMEnabled() ? "sound_off.png" : "sound_on.png";
	spriteName[2] = AudioMM::getInstance()->getEffectEnabled() ? "sound_on.png" : "sound_off.png";
	spriteName[3] = AudioMM::getInstance()->getEffectEnabled() ? "sound_off.png" : "sound_on.png";

	auto sound_bgm_on = MenuItemSprite::create(Sprite::create(spriteName[0]), Sprite::create(spriteName[1]));
	auto sound_bgm_off = MenuItemSprite::create(Sprite::create(spriteName[1]), Sprite::create(spriteName[0]));
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MenuScene::SettingBgmButton, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MenuScene::SettingsoundButton, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	setting_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_0(MenuScene::SettingCloseButton, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(MenuScene::HomeButton, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(MenuScene::EndingSceneCallBack, this));
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

	return true;
}

void MenuScene::HomeButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::SettingButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");

	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	setting_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
	openAni->setPosition(Director::getInstance()->getVisibleSize() * 0.5f);

	menu->setEnabled(false);
}

void MenuScene::SettingCloseButton()
{
	//AudioMM::getInstance()->runEffect("YELLOWKEY");
	SimpleAudioEngine::getInstance()->playEffect("sound / effect / EF_yellowkey.wav");
	//AudioMM::getInstance()->runEffect("BUTTON");

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

	menu->setEnabled(true);
}

void MenuScene::SettingBgmButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	AudioMM::getInstance()->changeBGMState();
}

void MenuScene::SettingsoundButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");

	AudioMM::getInstance()->changeEffectState();
}

void MenuScene::EndingSceneCallBack()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::ChangeScene()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, BlockSlideGameScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::UpgradeCallback()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, UpgradeScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::SkillShopCallback()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, SkillshopScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::ClothesCallback()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, ClothingStoreScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::TreasureCallback()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, TreasureScene::createScene());
	Director::getInstance()->replaceScene(scene);
}