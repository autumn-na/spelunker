#pragma execution_character_set("utf-8")
#include "TreasureScene.h"
#include "TreasureManager.h"
#include "MenuScene.h"
#include "ending.h"
#include "AudioManagement.h"

Scene* TreasureScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TreasureScene::create();

	scene->addChild(layer);

	return scene;
}

bool TreasureScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	                                                                                                 
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	AudioMM::getInstance()->runBGM("TREASURE");
	const unsigned nSprite = 7;
	char* sprite_name[nSprite] =
	{
		"treasure_store_background.png",
		"treasure_layer_01.png",
		"treasure_layer_02.png",
		"treasure_buttoncase.png",
		"treasure_buttoncase_02.png",
		"treasure_buttoncase_03.png",
		"main_gem.png",
	};

	Vec2 sprite_pos[nSprite] =
	{
		Vec2(visibleSize * 0.5f),
		Vec2(visibleSize * 0.5f + Size(0, -30)),
		Vec2(visibleSize * 0.5f + Size(0, -50)),
		Vec2(visibleSize * 0.5f + Size(0, 370)),
		Vec2(visibleSize * 0.5f + Size(0, 370)),
		Vec2(visibleSize * 0.5f + Size(0, 320)),
		Vec2(50, visibleSize.height - 50),

	};
	Sprite* sprites[nSprite];
	for (unsigned int n = 0; n < nSprite; n++)
	{
		sprites[n]= Sprite::create(sprite_name[n]);
		sprites[n]->setPosition(sprite_pos[n]);
		this->addChild(sprites[n]);
	}
	sprites[2]->setScaleY(1.1f);
	sprites[6]->setScale(0.5f);

	auto homeButton = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(TreasureScene::HomeButton, this));
	homeButton->setPosition(580, 1230);
	homeButton->setScale(0.5f);

	auto settingButton = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_0(TreasureScene::SettingButton, this));
	settingButton->setPosition(670, 1230);
	settingButton->setScale(0.5f);
	settingUI = Menu::create(homeButton, settingButton, nullptr);
	settingUI->setPosition(Vec2::ZERO);
	this->addChild(settingUI, 1);

	moneyLabel = Label::createWithSystemFont(StringUtils::format("%d", HeroMM::getInstance()->res_total), "res/arial.ttf", 60, Size(500, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
	moneyLabel->setAnchorPoint(Vec2(0, 0.5f));
	moneyLabel->setPosition(100, visibleSize.height - 50);
	this->addChild(moneyLabel, 11);

	InitOpenLayer();
	InitCollectionLayer();
	InitExplainLayer();
	InitGetLayer();
	InitSettingLayer();
	return true;
}

void TreasureScene::InitOpenLayer()
{
	openLayer = Layer::create();
	openLayer->setPosition(Vec2::ZERO);
	this->addChild(openLayer, 10);

	openLayerChange = false;

	auto treasureOpen_text = Sprite::create("treasure_text_treasure.png");
	treasureOpen_text->setPosition(visibleSize * 0.5f + Size(-130, 370));
	openLayer->addChild(treasureOpen_text);

	auto collection_text = MenuItemImage::create("treasure_text_collection_02_off.png", "treasure_text_collection_02.png", CC_CALLBACK_0(TreasureScene::ChangeCollectionLayer, this));
	collection_text->setPosition(visibleSize * 0.5f + Size(130, 370));

	box = Sprite::create("pit_01.png");
	box->setPosition(visibleSize * 0.5f + Size(0, -100));
	openLayer->addChild(box);

	auto buyButton = MenuItemImage::create("buy_button.png", "buy_button_click.png", CC_CALLBACK_0(TreasureScene::BoxOpen, this));
	buyButton->setPosition(visibleSize * 0.5f + Size(0, -400));
	buyButton->setScale(1.6f);

	openMenu = Menu::create(buyButton, collection_text, nullptr);
	openMenu->setPosition(Vec2::ZERO);
	openLayer->addChild(openMenu);
}

void TreasureScene::InitCollectionLayer()
{
	collectionLayer = Layer::create();
	collectionLayer->setPosition(Vec2::ZERO);
	collectionLayer->setVisible(false);
	this->addChild(collectionLayer, 10);

	auto treasureOpen_text = MenuItemImage::create("treasure_text_treasure_off.png", "treasure_text_treasure.png", CC_CALLBACK_0(TreasureScene::ChangeOpenLayer,this));
	treasureOpen_text->setPosition(visibleSize * 0.5f + Size(-130, 370));

	auto collection_text = Sprite::create("treasure_text_collection.png");
	collection_text->setPosition(visibleSize * 0.5f + Size(130, 370));
	collectionLayer->addChild(collection_text);

	treaMenu = Menu::create(treasureOpen_text, nullptr);
	treaMenu->setPosition(Vec2::ZERO);
	collectionLayer->addChild(treaMenu);

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			button[y][x] = MenuItemImage::create("treasure_itemcase_02.png", "treasure_itemcase_02.png", CC_CALLBACK_1(TreasureScene::OpenExplanLayer, this));
			button[y][x]->setPosition(140 + (x * 108), 850 - (y * 140));
			treaMenu->addChild(button[y][x]);

			buttonSprite[y][x] = Sprite::create("pit_10.png");
			buttonSprite[y][x]->setPosition(140 + (x * 108), 850 - (y * 140));
			buttonSprite[y][x]->setScale(0.1f);
			buttonSprite[y][x]->setVisible(false);
			collectionLayer->addChild(buttonSprite[y][x]);
		}
	}
}

void TreasureScene::InitExplainLayer()
{
	explanLayer = Layer::create();
	explanLayer->setPosition(10000, 10000);
	this->addChild(explanLayer, 15);

	auto gray = Sprite::create("gray.png");
	gray->setPosition(visibleSize * 0.5f);
	gray->setScale(2);
	gray->setOpacity(200);
	explanLayer->addChild(gray, 0);

	auto base = Sprite::create("skillpopup.png");
	base->setPosition(visibleSize * 0.5f);
	base->setScale(2.f);
	explanLayer->addChild(base, 0);

	explanName = Label::createWithSystemFont("±úÁø ÆÒ´øÆ®", "fonts/arial.ttf", 50);
	explanName->setPosition(440, 860);
	explanLayer->addChild(explanName, 1);

	explanText = Label::createWithSystemFont("Äð°¨ 50ÆÛ", "fonts/arial.ttf", 50);
	explanText->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 40 - 120);
	explanLayer->addChild(explanText, 1);

	explanSprite = Sprite::create("pit_10.png");
	explanSprite->setPosition(visibleSize * 0.5f + Size(-190, 210));
	explanLayer->addChild(explanSprite, 1);

	auto exitButton = MenuItemImage::create("paused_X.png", "paused_X.png", CC_CALLBACK_0(TreasureScene::EndExplanLayer, this));
	exitButton->setPosition(620, 940);
	auto menu = Menu::create(exitButton, nullptr);
	menu->setPosition(Vec2::ZERO);
	explanLayer->addChild(menu, 2);
}

void TreasureScene::InitGetLayer()
{
	getLayer = Layer::create();
	getLayer->setPosition(Vec2::ZERO);
	getLayer->setVisible(false);
	this->addChild(getLayer, 10);

	openSprite = Sprite::create("pit_01.png");
	openSprite->setPosition(visibleSize * 0.5f + Size(0, -100));
	getLayer->addChild(openSprite, 2);

	treasureName = Label::createWithSystemFont("", "fonts/arial.ttf", 64);
	treasureName->setPosition(visibleSize * 0.5f + Size(0, 250));
	getLayer->addChild(treasureName);

	treasureExplan = Label::createWithSystemFont("", "fonts/arial.ttf", 50);
	treasureExplan->setPosition(visibleSize * 0.5f + Size(0, -400));
	getLayer->addChild(treasureExplan);

	getTreasureSprite = Sprite::create("pit_01.png");
	getTreasureSprite->setPosition(visibleSize * 0.5f + Size(0, -100));
	getTreasureSprite->runAction(FadeOut::create(0));
	getLayer->addChild(getTreasureSprite, 5);

	treasureName->runAction(FadeOut::create(0));
	treasureExplan->runAction(FadeOut::create(0));
}

void TreasureScene::InitSettingLayer()
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
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(TreasureScene::SetBgmSound, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(TreasureScene::SetEffectSound, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	setting_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_0(TreasureScene::SettingButtonOff, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(TreasureScene::HomeButton, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(TreasureScene::EndingScene, this));
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

void TreasureScene::BoxOpen()
{
	if (HeroMM::getInstance()->res_total - 500 < 0)
		return;

	HeroMM::getInstance()->res_total -= 500;

	moneyLabel->setString(StringUtils::format("%d", HeroMM::getInstance()->res_total));

	openLayer->setVisible(false);
	getLayer->setVisible(true);

	AudioMM::getInstance()->runEffect("TREASUREOPEN");

	static int itemID = 0;	
	if (itemID < 3)
		itemID++;

	TreasureMM::getInstance()->id[TreasureMM::getInstance()->haveNum] = itemID;
	TreasureMM::getInstance()->haveNum++;
	
	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 1; i < 10; i++)
	{
		animation->addSpriteFrame(SpriteFrame::create(StringUtils::format("pit_0%d.png", i), Rect(0, 0, 740, 740)));
	}
	animation->addSpriteFrame(SpriteFrame::create("pit_07.png", Rect(0, 0, 740, 740)));
	getTreasureSprite->runAction(Sequence::create(DelayTime::create(0.9f), FadeIn::create(0), nullptr));
	getTreasureSprite->setTexture(StringUtils::format("treasure_0%d.png", itemID));
	//animation->addSpriteFrame(SpriteFrame::create(StringUtils::format("treasure_0%d.png", itemID), Rect(0, 0, 740, 740)));
	openSprite->runAction(Sequence::create(Animate::create(animation), CallFunc::create(CC_CALLBACK_0(TreasureScene::BoxOpenEnd, this)), nullptr));
	openSprite->setScale(0.8f);


	auto delay = DelayTime::create(0.9f);
	auto fadein = FadeIn::create(0);
	auto sequence = Sequence::create(delay, fadein, nullptr);

	treasureName->runAction(sequence->clone());
	treasureExplan->runAction(sequence->clone());

	treasureName->setString(treaName[itemID - 1]);
	treasureExplan->setString(treaExplan[itemID - 1]);
}

void TreasureScene::BoxOpenEnd()
{
	openLayerChange = true;
	AudioMM::getInstance()->runEffect("TREASUREGET");
}

void TreasureScene::ChangeOpenLayer()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	openLayer->setVisible(true);
	collectionLayer->setVisible(false);

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			buttonSprite[y][x]->setVisible(false);
		}
	}
}

void TreasureScene::ChangeCollectionLayer()
{
	openLayer->setVisible(false);
	collectionLayer->setVisible(true);

	MoveBy* move = MoveBy::create(0.2f, Vec2(0, 50));
	ScaleTo* scale = ScaleTo::create(0.05f, 1, 1);

	ScaleTo* spriteScale = ScaleTo::create(0.2f, 0.1f, 0.1f);
	
	for (unsigned int y = 0; y < 5; y++)
	{
		for (unsigned int x = 0; x < 5; x++)
		{
			if (TreasureMM::getInstance()->haveNum > x + (y * 5))
			{
				AudioMM::getInstance()->runEffect("BUTTON");
				buttonSprite[y][x]->setVisible(true);
				buttonSprite[y][x]->setTexture(StringUtils::format("treasure_0%d.png", TreasureMM::getInstance()->id[x + (y * 5)]));

				buttonSprite[y][x]->setPosition(140 + (x * 108), 800 - (y * 140));
				buttonSprite[y][x]->runAction(move->clone());

				buttonSprite[y][x]->setScaleY(0);
				buttonSprite[y][x]->runAction(spriteScale->clone());

			}
			DelayTime* delay = DelayTime::create(y * 0.2f);

			button[y][x]->setPosition(140 + (x * 108), 800 - (y * 140));
			button[y][x]->runAction(Sequence::create(delay, move->clone(), nullptr));

			button[y][x]->setScaleY(0);
			button[y][x]->runAction(Sequence::create(delay, scale->clone(), nullptr));
		}
	}
}

void TreasureScene::OpenExplanLayer(Ref* pSender)
{
	AudioMM::getInstance()->runEffect("BUTTON");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (button[i][j]->_ID == pSender->_ID  &&  TreasureMM::getInstance()->haveNum > j + i * 5)
			{
				settingUI->setEnabled(false);
				openMenu->setEnabled(false);
				treaMenu->setEnabled(false);

				//explanLayer->setVisible(true);
				openAni->setPosition(visibleSize * 0.5f);
				openAni->stopAllActions();
				openAni->setScale(2.f);
				Animation * openAnimation = Animation::create();
				openAnimation->setDelayPerUnit(0.05f);
				for (int i = 1; i < 5; i++)
				{
					openAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/skill_pop_0%d.png", i), Rect(0, 0, 334, 352)));
				}
				openAni->runAction(Sequence::create(Animate::create(openAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
				explanLayer->runAction(Sequence::create(DelayTime::create(0.20f), MoveTo::create(0, Vec2::ZERO), nullptr));


				explanSprite->setTexture(StringUtils::format("treasure_0%d.png", TreasureMM::getInstance()->id[j + (i * 5)]));
				explanSprite->setScale(0.3f);

				explanName->setString(treaName[TreasureMM::getInstance()->id[j + (i * 5)] - 1]);


				explanText->setString(treaExplan[TreasureMM::getInstance()->id[j + (i * 5)] - 1]);
			}
		}
	}
}

void TreasureScene::EndExplanLayer()
{
	AudioMM::getInstance()->runEffect("BUTTON");

	settingUI->setEnabled(true);
	openMenu->setEnabled(true);
	treaMenu->setEnabled(true);

	explanLayer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(visibleSize * 0.5f);
	openAni->setScale(2.f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 5; i >= 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/skill_pop_0%d.png", i), Rect(0, 0, 334, 352)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
}

void TreasureScene::SettingButton()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	openAni->setScale(1);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	setting_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
}

void TreasureScene::SettingButtonOff()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	setting_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	openAni->setScale(1);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));
}

void TreasureScene::HomeButton()
{
	AudioMM::getInstance()->runEffect("CLOSE");
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void TreasureScene::EndingScene()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void TreasureScene::SetBgmSound()
{
	AudioMM::getInstance()->runEffect("BUTTON");
	AudioMM::getInstance()->changeBGMState();
}

void TreasureScene::SetEffectSound()
{
	AudioMM::getInstance()->changeEffectState();
}

bool TreasureScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	if (openLayerChange)
	{
		getLayer->setVisible(false);
		openLayer->setVisible(true);
		openLayerChange = false;

		getTreasureSprite->runAction(FadeOut::create(0));
		treasureName->runAction(FadeOut::create(0));
		treasureExplan->runAction(FadeOut::create(0));
	}

	return true;
}
