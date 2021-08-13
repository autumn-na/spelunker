#pragma execution_character_set("utf-8")
#include "ClothingStoreScene.h"
#include "MenuScene.h"
#include "ending.h"
#include "ClothesManagement.h"
#include "AudioManagement.h"

Scene* ClothingStoreScene::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ClothingStoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ClothingStoreScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	//Å°º¸µå È°¼ºÈ­
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(ClothingStoreScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(ClothingStoreScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	auto background = Sprite::create("clothes_shop.png");
	background->setScale(2);
	background->setPosition(visibleSize.width *0.5f, visibleSize.height * 0.5f);
	this->addChild(background, 0);
	 
	//º¸¼® ¼ýÀÚ
	auto gem = Sprite::create("main_gem.png");               
	gem->setPosition(Point(50, visibleSize.height - 50));
	gem->setScale(0.5f);
	this->addChild(gem, 1);

	gemLabel = Label::createWithSystemFont(StringUtils::format("%d", HeroMM::getInstance()->res_total), "res/arial.ttf", 60, Size(500, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	gemLabel->setAnchorPoint(Vec2(0.f, 0.5f));
	gemLabel->setPosition(100, visibleSize.height - 50);
	this->addChild(gemLabel, 1);

	auto homeButton = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(ClothingStoreScene::HomeButton, this));
	homeButton->setPosition(580, 1230);
	homeButton->setScale(0.5f);
	auto settingButton = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_0(ClothingStoreScene::SettingButton, this));
	settingButton->setPosition(670, 1230);
	settingButton->setScale(0.5f);
	mainButton = Menu::create(homeButton, settingButton, NULL);
	mainButton->setPosition(Vec2::ZERO);
	this->addChild(mainButton, 1);

	const char* clothesName_char[4] =
	{
		"»ç½½°©¹Ù",
		"Ã¶°©¹Ù",
		"±Ý°©¹Ù",
		"´ÙÀÌ¾Æ°©¹Ù",
	};

	ClothesMM::getInstance()->clothesCarry[0] = false;
	ClothesMM::getInstance()->clothesCarry[1] = false;
	ClothesMM::getInstance()->clothesCarry[2] = false;
	ClothesMM::getInstance()->clothesCarry[3] = false;
	ClothesMM::getInstance()->clothesEquip = 4;

	for (int i = 0; i < 4; i++)
	{
		auto clothes = Sprite::create(StringUtils::format("clothes0%d.png", i + 1));
		clothes->setPosition(210, 840 - (i * 212));
		clothes->setScale(0.4f);
		this->addChild(clothes, 1);

		auto clothesName = Label::createWithSystemFont(clothesName_char[i], "res/arial.ttf", 40, Size(300, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		clothesName->setAnchorPoint(Vec2(0.f, 0.5f));
		clothesName->setPosition(300, 880 - (i * 212));
		this->addChild(clothesName, 1);

		char* buyButton_type;
		char* buyButton_click;
		if (ClothesMM::getInstance()->clothesEquip == i)
		{
			buyButton_type = "unequip.png";
			buyButton_click = "unequip_click.png";
		}
		else
		{
			switch (ClothesMM::getInstance()->clothesCarry[i])
			{
			case true:
				buyButton_type = "use_button.png";
				buyButton_click = "use_button_click.png";
			case false:
				buyButton_type = "buy_button.png";
				buyButton_click = "buy_button_click.png";
			}
		}
		buyButton[i] = MenuItemImage::create(buyButton_type, buyButton_click, CC_CALLBACK_1(ClothingStoreScene::BuyButton, this));
		buyButton[i]->setPosition(410,800 - (i * 212));
		mainButton->addChild(buyButton[i]);

		searchButton[i] = MenuItemImage::create("search_button.png", "search_button", CC_CALLBACK_1(ClothingStoreScene::SearchButton, this));
		searchButton[i]->setPosition(570, 800 - (i * 212));
		mainButton->addChild(searchButton[i]);
	}
	InitClothesLayer();
	InitSettingLayer();
	return true;
}

void ClothingStoreScene::InitClothesLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	clothesShow_layer = Layer::create();
	clothesShow_layer->setPosition(100000, 100000);
	clothesShow_layer->setScale(1);	
	this->addChild(clothesShow_layer, 10);

	auto backgray = Sprite::create("gray.png");
	backgray->setPosition(visibleSize.height * 0.5f, visibleSize.height * 0.5f);
	backgray->setScale(3);
	backgray->setOpacity(100);
	clothesShow_layer->addChild(backgray);

	auto popWindow = Sprite::create("clothespopup.png");
	popWindow->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
	clothesShow_layer->addChild(popWindow);

	auto outButton = MenuItemImage::create("delete.png", "delete.png", CC_CALLBACK_0(ClothingStoreScene::SearchButtonOff, this));
	outButton->setPosition(550, 900);
	auto outButtonMenu = Menu::create(outButton, NULL);
	outButtonMenu->setPosition(Vec2::ZERO);
	clothesShow_layer->addChild(outButtonMenu, 2);

	charactor = Sprite::create("block01.png");
	charactor->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 15);
	clothesShow_layer->addChild(charactor, 1);
}

void ClothingStoreScene::InitSettingLayer()
{
	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 50);

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
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(ClothingStoreScene::SetBgmSound, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(ClothingStoreScene::SetEffectSound, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	setting_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_0(ClothingStoreScene::SettingButtonOff, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(ClothingStoreScene::HomeButton, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(ClothingStoreScene::EndingScene, this));
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

void ClothingStoreScene::SettingButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	setting_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
	mainButton->setEnabled(false);
}

void ClothingStoreScene::SettingButtonOff()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	setting_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	mainButton->setEnabled(true);
}

void ClothingStoreScene::SetBgmSound()
{
	AudioMM::getInstance()->changeBGMState();
	AudioMM::getInstance()->runEffect("BUTTON");
}

void ClothingStoreScene::SetEffectSound()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	AudioMM::getInstance()->changeEffectState();
}

void ClothingStoreScene::EndingScene()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void ClothingStoreScene::BuyButton(Ref* pSender)
{
	for (int i = 0; i < 4; i++)
	{
		if (buyButton[i]->_ID == pSender->_ID)
		{
			if (i == ClothesMM::getInstance()->clothesEquip)
			{
				buyButton[i]->setNormalImage(Sprite::create("use_button.png"));
				buyButton[i]->setSelectedImage(Sprite::create("use_button_click.png"));

				ClothesMM::getInstance()->clothesEquip = 4;
			}
			else if (ClothesMM::getInstance()->clothesCarry[i] == false)
			{
				if (HeroMM::getInstance()->res_total - 500 >= 0)
				{
					AudioMM::getInstance()->runEffect("BUY");
					HeroMM::getInstance()->res_total -= 500;
					gemLabel->setString(StringUtils::format("%d", HeroMM::getInstance()->res_total));
					buyButton[i]->setNormalImage(Sprite::create("use_button.png"));
					buyButton[i]->setSelectedImage(Sprite::create("use_button_click.png"));
					ClothesMM::getInstance()->clothesCarry[i] = true;
				}
			}
			else
			{
				if (ClothesMM::getInstance()->clothesEquip != 4)
				{
					buyButton[ClothesMM::getInstance()->clothesEquip]->setNormalImage(Sprite::create("use_button.png"));
					buyButton[ClothesMM::getInstance()->clothesEquip]->setSelectedImage(Sprite::create("use_button_click.png"));
					AudioMM::getInstance()->runEffect("WEAR");
				}
				buyButton[i]->setNormalImage(Sprite::create("unequip.png"));
				buyButton[i]->setSelectedImage(Sprite::create("unequip_click.png"));

				ClothesMM::getInstance()->clothesEquip = i;
			}
		}
	}
}

void ClothingStoreScene::SearchButton(Ref * pSender)
{
	for (int i = 0; i < 4; i++)
	{
		if (searchButton[i]->_ID == pSender->_ID)
		{
			AudioMM::getInstance()->runEffect("BUTTON");
			charactor->setTexture("clothes_show.png");
			//charactor->setTexture(StringUtils::format("clothes0%d.png", i + 1));
		}
	}

	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/clothes_poplayer_effect_0%d.png", i), Rect(0, 0, 444, 554)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	clothesShow_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
	openAni->setPosition(visibleSize * 0.5f);

	mainButton->setEnabled(false);
}

void ClothingStoreScene::SearchButtonOff()
{
	AudioMM::getInstance()->runEffect("BUTTON");

	clothesShow_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/clothes_poplayer_effect_0%d.png", i), Rect(0, 0, 444, 554)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
	mainButton->setEnabled(true);
}

void ClothingStoreScene::HomeButton()
{
	AudioMM::getInstance()->runEffect("CLOSE");
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void ClothingStoreScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	}
}
