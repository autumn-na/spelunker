#include "BlockSlideGameScene.H"
#include "SimpleAudioEngine.h"
#include "ClickerScene.h"
#include "ending.h"
#include "MenuScene.h"
#include "AudioManagement.h"

#pragma execution_character_set("utf-8")

using namespace CocosDenshion;
Scene* BlockSlideGameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BlockSlideGameScene::create();

	scene->addChild(layer);

	return scene;
}

bool BlockSlideGameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	AudioMM::getInstance()->runBGM("INGAME1");

	GameSetting();
	InitUI();
	InitProgressBar();
	InitPause();

	//static bool out = true;
	//if (out)
	//	InittutorialLayer1();

	//out = false;
/*;
	InittutorialLayer2();
	InittutorialLayer3();
	InittutorialLayer4();
	InittutorialLayer5();
	InittutorialLayer6();*/

	for (int y = 0; y < 11; y++)
	{
		CreateBlock(Vec2(BLOCK_RIGHT_XPOS, BLOCK_LEFT_XPOS), y);
	}
	CreateBlock(Vec2(280, 440), 11);

	for (int i = 0; i < 100; i++)
	{
		backEffect_heart[i] = Sprite::create("b.png");
		backEffect_heart[i]->setPosition(-500, -500);
		backEffect_heart[i]->setScale(0.25f);
		this->addChild(backEffect_heart[i], 1);
	}	
	backEffect_image = Sprite::create("amy.png");
	backEffect_image->setPosition(-1000, -1000);
	backEffect_image->setScale(0.5f);
	this->addChild(backEffect_image, 1);

	auto clock = Sprite::create("timer.png");
	clock->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 170);
	this->addChild(clock, 17);

	hpProgress = ProgressTimer::create(Sprite::create("timer_gauge.png"));
	hpProgress->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 150);
	hpProgress->setType(ProgressTimer::Type::RADIAL);
	hpProgress->setPercentage(hpInt);
	hpProgress->setRotationSkewY(180);
	this->addChild(hpProgress, 18); 

	needle = Sprite::create("timer_needle.png");
	needle->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 150);
	this->addChild(needle, 19);
	this->schedule(schedule_selector(BlockSlideGameScene::AutoTouch), 0.1f);
	this->scheduleUpdate();
	return true;
}

void BlockSlideGameScene::GameSetting()
{
	//화면 크기 설정
	visibleSize = Director::getInstance()->getVisibleSize();
	autoKey_state = false;
	whole = 1000;//진행도 전체 크
	poisonCheck = false; //독병 
	hpInt = 100; //현제 HP
	gametime = clock() - 1000;
	unbeatable = false;
	start = false;
	skullTouch = clock();
	srand(time(NULL));
	//터치 활성화
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//키보드 활성화
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(BlockSlideGameScene::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(BlockSlideGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	//effect 사용할수 있게 만들기
	poisonGrid = NodeGrid::create();
	this->addChild(poisonGrid, 2);


}

const std::string Unit(const unsigned long n)
{
	int ascll = 96;
	int m = n;
	int p = n;
	while (1)
	{
		if (m < 100)
		{
			std::string text;
			char a[30];
			if(ascll == 96){ sprintf(a, "%d", m, ascll); }
			else { sprintf(a, "%d.%d%c", m, p, ascll); }
			text = a;
			return text;
		}
		else
		{
			ascll++;
			p = m % 100 * 0.1f;
			m *=  0.01;
		}
	}
	return "FAILED";
}



void BlockSlideGameScene::InittutorialLayer1()
{ 
	torial1_layer = Layer::create();
	auto visible = Director::getInstance()->getVisibleSize();
	torial1_layer->setVisible(true); //적용 시엔 true

	torial1_layer->setPosition(Vec2::ZERO);
	this->addChild(torial1_layer, 20);

	auto spr_torialback_layer = Sprite::create("gray.png");
	spr_torialback_layer->setPosition(visible.width * 0.5f, visible.height * 0.5f);
	spr_torialback_layer->setOpacity(200);
	spr_torialback_layer->setScale(2);
	torial1_layer->addChild(spr_torialback_layer, 1);

	 spr_torialnpc_layer = Sprite::create("amy_01.png");
	spr_torialnpc_layer->setPosition(visible.width * 0.5f - 200, visible.height * 0.5f +20 );
	spr_torialnpc_layer->setScale(0.9);
	torial1_layer->addChild(spr_torialnpc_layer, 1);

	tutorialBlock = Sprite::create("block01.png");
	tutorialBlock->setPosition(visible.width * 0.5f + 240, visible.height * 0.5f + 180);
	tutorialBlock->setVisible(false);
	torial1_layer->addChild(tutorialBlock, 10);
	tutorialBlock->setScale(1.6f);

	auto spr_torialtextcase_layer = MenuItemImage::create("npcdeck.png", "npcdeck.png", CC_CALLBACK_0(BlockSlideGameScene::tutorialScene, this));
	spr_torialtextcase_layer->setPosition(visible.width * 0.5f, visible.height * 0.5f - 460);
	auto meernuw = Menu::create(spr_torialtextcase_layer, NULL);
	meernuw->setPosition(Vec2::ZERO);
	torial1_layer->addChild(meernuw, 1);
	spr_torialtextcase_layer->setScale(1.6);
	tutorialLabel = Label::createWithSystemFont("에이미\n\n\n지금 보시는 화면은 블록 퍼즐 화면이에요.\n 무슨 퍼즐들이 있는 한번 살펴볼까요?", "", 40, Size(1000, 500), TextHAlignment::LEFT, TextVAlignment::CENTER);
	tutorialLabel->setAnchorPoint(Vec2(0, 1));
	tutorialLabel->setPosition(100, 500);
	tutorialLabel->setColor(Color3B::WHITE);
	torial1_layer->addChild(tutorialLabel, 10);
}

void BlockSlideGameScene::tutorialScene()
{
	char* tutorialString[10] =
	{
		"에이미\n\n\n첫번째는 호박 블록이에요. \n호박 블록은 방향키를 한번 터치하면 파괴하실 수 있어요. ",
		"에이미\n\n\n두번째는 루비 블록인데요. \n루비 블록은 방향키를 동시에 터치해야 파괴하실 수 있답니다. ",
		"에이미\n\n\n세번째는 에메랄드 블록이에요. \n에메랄드 블록은 방향키를 연속 두번 터치해야만 파괴가 가능하답니다.",
		"다음은 모험가님을 방해하는 블록들이에요.",
		"에이미\n\n\n해골 블록은 터치하게 되면 방향키가 잠시동안 터치 불가 상태가 되고\n블록들을 모두 재배치 시켜버리니 조심하셔야 해요.",
		"에이미\n\n\n독 블록은 블록들의 색깔을 랜덤으로 바꾸어 모험가님의 시야를 방해해요.",
		"이제 블록들의 설명이 모두 끝났으니, 바로 게임을 시작해볼까요?",
	};
	int tutorialBlocka[10] =
	{
		1, 2, 3, 3, 0 ,4, 4
	};

	int tutorialSprite[10] =
	{
		1, 2, 1, 2, 1, 2, 2
	};


	static int tutorialCount = 0;
	tutorialCount++;
	if (tutorialCount == 6)
	{
		torial1_layer->setVisible(false);
		return;
	}
	tutorialLabel->setString(tutorialString[tutorialCount - 1]);
	tutorialBlock->setTexture(StringUtils::format("block0%d.png", tutorialBlocka[tutorialCount -1]));
	tutorialBlock->setVisible(true);

	spr_torialnpc_layer->setTexture(StringUtils::format("amy_0%d.png", tutorialSprite[tutorialCount]));
}




















void BlockSlideGameScene::InitUI()
{
	//상단 매뉴바 돈
	moneyLabel = Label::createWithSystemFont(Unit(HeroMM::getInstance()->res_get), "res/arial.ttf", 60, Size(300, 100), TextHAlignment::CENTER, TextVAlignment::CENTER);
	moneyLabel->setPosition(visibleSize.width * 0.5f, 600);
	this->addChild(moneyLabel, 11);

	combo_sprite = Sprite::create("combo.png");
	combo_sprite->setPosition(visibleSize.width * 0.5f, 1120);
	combo_sprite->runAction(FadeOut::create(0));
	this->addChild(combo_sprite, 11);

	for (int i = 0; i < 10; i++)
	{
		combo_num[i] = Sprite::create("BlockCombo/combo_0.png");
		combo_num[i]->setVisible(false);
		this->addChild(combo_num[i], 11);
	}

	//background
	auto background = Sprite::create("block_background.png");
	background->setPosition(Vec2(visibleSize.width * 0.5f , visibleSize.height * 0.5f ));
	background->setScale(1);
	this->addChild(background, 0);
	
	//sprite
	const unsigned int nSprite = 3;
	const char* spriteTex[nSprite] =
	{
		 "bos_ui.png" ,
		 "progress_under.png",
		 "skill_button.png",

	};
	const Vec2 spritePos[nSprite] =
	{
		 Vec2( visibleSize.width * 0.5f + 165, visibleSize.height - 50 ),
		 Vec2( visibleSize.width * 0.5f, visibleSize.height - 50 ),
		 Vec2 (visibleSize.width * 0.5f, 150)
	};
	const unsigned int axisZ[nSprite] = { 15, 13, 2 };
	for (unsigned int i = 0; i < 2; i++)
	{
		auto sprite = Sprite::create(spriteTex[i]);
		sprite->setPosition(spritePos[i]);
		this->addChild(sprite, axisZ[i]);
	}
	//오른쪽 버튼 
	button_right = Sprite::create("arrow.png");
	button_right->setRotation(180);
	button_right->setPosition(visibleSize.width * 0.5f + 200, 150);
	this->addChild(button_right, 2);
	//왼쪽버튼
	button_left = Sprite::create("arrow.png");
	button_left->setPosition(visibleSize.width * 0.5f - 200, 150);
	this->addChild(button_left, 2);
	//일시 정지 버튼
	pause_state = false; //정지버튼 보이는 상태
	auto pauseButton = MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_0(BlockSlideGameScene::PauseLayerOn, this));
	pauseButton->setPosition(visibleSize.width - 50, visibleSize.height - 50);
	auto pauseMenu = Menu::create(pauseButton, nullptr);
	pauseMenu->setPosition(Vec2::ZERO);
	this->addChild(pauseMenu, 11);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    

	skill_progress = ProgressTimer::create(Sprite::create("skill_gauge_on.png"));
	skill_progress->setPosition(1000, 1000);
	//skill_progress->setPosition(visibleSize.width * 0.5f, 150);
	skill_progress->setType(kCCProgressTimerTypeBar);
	skill_progress->setPercentage(0);
	skill_progress->setMidpoint(ccp(0.5f, 0.0f));
	skill_progress->setBarChangeRate(ccp(0.0f, 1.0f));
	skill_progress->runAction(TintTo::create(0.f, Color3B(50, 50, 50)));
	this->addChild(skill_progress, 18);
}

void BlockSlideGameScene::InitProgressBar()
{
	//진행도
	auto bar_tex = Sprite::create("progressbar.png");
	progressBar = ProgressTimer::create(bar_tex);
	progressBar->setMidpoint(Vec2(0.0f, 0.5f));
	progressBar->setBarChangeRate(Vec2(1.f, 0.f));
	progressBar->setType(kCCProgressTimerTypeBar);//kCCProgressTimerTypeHorizontalBarLR);
	progressBar->setPosition(visibleSize.width * 0.5f, visibleSize.height - 50);
	this->addChild(progressBar, 14);
	hpBar = Sprite::create("progressbar.png");
	hpBar->setPosition(visibleSize.width * 0.5f - hpBar->getContentSize().width * 0.5f - 5,- visibleSize.height * 0.5f - 150);
	hpBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	hpBar->setScaleX(hpInt / 100);
	this->addChild(hpBar, 14);
	//플레이어 상단 애니메이션
	progress_player = Sprite::create("character_animation_01.png");
	progress_player->setPosition(visibleSize.width * 0.5f + (((static_cast<float>(HeroMM::getInstance()->progress_percent) / static_cast<float>(whole)) - 0.5f) * 320) + 5, visibleSize.height - 50);
	this->addChild(progress_player, 16);
	Animation * player_animation = Animation::create();
	player_animation->setDelayPerUnit(0.2f);
	for (int i = 1; i < 7; i++)
	{
		player_animation->addSpriteFrame(SpriteFrame::create(StringUtils::format("character_animation_0%d.png", i), Rect(0, 0, 80, 80)));
	}
	progress_player->runAction(RepeatForever::create(Animate::create(player_animation)));
	SetProgress(0);
}

void BlockSlideGameScene::InitPause()
{
	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 50);

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
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(BlockSlideGameScene::SetBgmSound, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f);
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_0(BlockSlideGameScene::SetEffectSound, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	pause_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_1(BlockSlideGameScene::PauseLayerOff, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(BlockSlideGameScene::MenuScene, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(BlockSlideGameScene::EndingScene, this));
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

void BlockSlideGameScene::comboEffect()
{
	int type = rand() % 3;
	FadeIn* fadein = FadeIn::create(0);
	Vec2 imagePos[3] = { Vec2(visibleSize.width * 0.5f, -backEffect_image->getContentSize().height * 0.5f),
							Vec2(-backEffect_image->getContentSize().width * 0.5f, visibleSize.height * 0.5f),
							Vec2(visibleSize.width + backEffect_image->getContentSize().width * 0.5f, visibleSize.height * 0.5f) };

	MoveTo* moveSenter = MoveTo::create(0.2f, Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));

	Vec2 imagePos2[3] = { Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 50),
						 Vec2(visibleSize.width * 0.5f + 50, visibleSize.height * 0.5f),
						 Vec2(visibleSize.width * 0.5f - 50, visibleSize.height * 0.5f), };

	MoveTo* moveSenter2 = MoveTo::create(0.5f, imagePos2[type]);

	Vec2 imagePos3[3] = { Vec2(visibleSize.width * 0.5f, visibleSize.height + backEffect_image->getContentSize().height * 0.5f),
	Vec2(visibleSize.width + backEffect_image->getContentSize().width * 0.5f, visibleSize.height * 0.5f),
	Vec2(-backEffect_image->getContentSize().width * 0.5f, visibleSize.height * 0.5f) };

	MoveTo* moveOut = MoveTo::create(0.2f, imagePos3[type]);
	backEffect_image->stopAllActions();
	backEffect_image->setPosition(imagePos[type]);
	backEffect_image->runAction(Sequence::create(fadein->clone(), moveSenter, moveSenter2, moveOut, nullptr));

	for (int i = 0; i < 100; i++)
	{
		backEffect_heart[i]->stopAllActions();
		backEffect_heart[i]->setPosition(rand() % 720, -200);
		MoveBy* heartMove = MoveBy::create(0.2f, Vec2(0.f, 500 + rand() % 300));
		MoveBy* heartMove2 = MoveBy::create(0.5f, Vec2(0.f, 100 + rand() % 200));
		MoveBy* heartMove3 = MoveBy::create(0.2f, Vec2(0.f, 1000));
		backEffect_heart[i]->runAction(Sequence::create(fadein->clone(), heartMove, heartMove2, heartMove3, nullptr));
	}
}

void BlockSlideGameScene::comboEffect2()
{
	int direct = rand() % 2;


	if (direct == 1)
		backEffect_image->setFlipX(180);
	else
		backEffect_image->setFlipX(0);

	AudioMM::getInstance()->runEffect("REDKEY");

	backEffect_image->stopAllActions();
	backEffect_image->setPosition(direct == 0 ? -200 : visibleSize.width + 200, -200);
	MoveBy* move = MoveBy::create(0.4f, direct == 0 ? visibleSize * 0.5f + Size(200, 200) : Size(-visibleSize.width, visibleSize.height) * 0.5f + Size(-200, 200));
	backEffect_image->runAction(Spawn::create(FadeIn::create(0.0f), move, Sequence::create(DelayTime::create(0.4f), FadeOut::create(0.1f), MoveTo::create(0, Vec2(-200, -200)), FadeIn::create(0), nullptr), nullptr));

	for (int i = 0; i < 100; i++)
	{
		backEffect_heart[i]->stopAllActions();
		backEffect_heart[i]->setPosition(rand() % 2 == 0 ? -50 : visibleSize.width + 50, -50);

		DelayTime* startDelay = DelayTime::create(rand() % 50 * 0.01f);
		JumpTo* jump = JumpTo::create(0.4f, visibleSize * 0.5f + Size(rand() % 400 - 200, rand() % 400 - 200), 400, 1);
		backEffect_heart[i]->runAction(FadeIn::create(0));

		Sequence* fadeout = Sequence::create(DelayTime::create(0.3f), FadeOut::create(0.1f), MoveTo::create(0, Vec2(-200, -200)), FadeIn::create(0), nullptr);
		backEffect_heart[i]->runAction(Sequence::create(startDelay, Spawn::create(jump, fadeout, nullptr), nullptr));
	}
}

void BlockSlideGameScene::SkillStart()
{
	if (skill_gauge_value > 99.f)
	{
		for (auto iter = block.begin(); iter != block.end(); iter++) { (*iter)->SetType(1); }
		for (auto iter = bottomBlock.begin(); iter != bottomBlock.end(); iter++) { (*iter)->SetType(1); }
		skill_play_check = true;
		skill_progress->setColor(Color3B(50, 50, 50));
		skill_progress->setPercentage(0.f);
	}
}

void BlockSlideGameScene::SkillEnd(float dt)
{
	if (skill_play_check)
	{
		skill_gauge_value -= 50.f * dt;
		log("%f", skill_gauge_value);
		skill_progress->setPercentage(skill_gauge_value);
		if (skill_gauge_value <= 0.f) { skill_play_check = false; }
	}
}

void BlockSlideGameScene::update(float dt)
{
	if (pause_state)
		return;

	hpBar->pauseSchedulerAndActions();
	SkillEnd(dt);

	static float hpDelay = 0.3f;
	static int hpTime = clock();

	if (clock() - hpTime > 1000 && hpDelay < 1.f)
		hpDelay -= 0.01f;

	if(start)
		hpBar->setScaleX(hpBar->getScaleX() - 0.5f * dt);

	skill_progress->setScaleX(1.f);

	if (0 >= hpBar->getScaleX() && !unbeatable)
	{
		GameOverScene();
	}
	needle->setRotation(-hpBar->getScaleX() * 360);
	hpProgress->setPercentage(hpBar->getScaleX() * 100);
	hpProgress->setColor(Color3B(255, 255 * hpBar->getScaleX(), 255 * hpBar->getScaleX()));
}

void BlockSlideGameScene::HpUp()
{
	hpBar->setScaleX(1);
}

void BlockSlideGameScene::GameOverScene()
{
	AudioMM::getInstance()->runEffect("DIE");
	Scene * scene = TransitionFade::create(1.0f, GameOverScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void BlockSlideGameScene::PauseLayerOn()
{
	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 2; i < 7; i++)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}

	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)),nullptr));

	pause_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));
	
	pause_state = true;
}

void BlockSlideGameScene::PauseLayerOff(Ref * pSender)
{
	pause_layer->runAction(MoveTo::create(0, Vec2(10000, 10000)));

	openAni->setPosition(visibleSize * 0.5f);
	openAni->stopAllActions();
	Animation * oepnAnimation = Animation::create();
	oepnAnimation->setDelayPerUnit(0.05f);
	for (int i = 6; i > 1; i--)
	{
		oepnAnimation->addSpriteFrame(SpriteFrame::create(StringUtils::format("OpenEffectLayer/pause_layer_effect_0%d.png", i), Rect(0, 0, 520, 1000)));
	}
	openAni->runAction(Sequence::create(Animate::create(oepnAnimation), MoveTo::create(0, Vec2(10000, 10000)), nullptr));

	pause_state = false;
}

void BlockSlideGameScene::SetBgmSound()
{
	AudioMM::getInstance()->changeBGMState();
}

void BlockSlideGameScene::SetEffectSound()
{
	AudioMM::getInstance()->changeEffectState();
}

void BlockSlideGameScene::EndingScene()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void BlockSlideGameScene::MenuScene()
{
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void BlockSlideGameScene::AutoTouch(float dt)
{
	if (!autoKey_state)
		return;

	for (auto iter = bottomBlock.begin(); iter != bottomBlock.end(); iter++)
	{
		switch ((*iter)->type)
		{
		case Block::Type::YELLOW:
			BlockTouch((*iter)->bothSide);
			return;
		case Block::Type::RED:
			BlockTouch(0);
			BlockTouch(1);
			return;
		case Block::Type::GREEN:
			BlockTouch((*iter)->bothSide);
			BlockTouch((*iter)->bothSide);
			return;
		}
	}

}

bool BlockSlideGameScene::SetProgress(const unsigned int addpresent)
{
	if (abs((HeroMM::getInstance()->progress_percent) + addpresent - (whole * 0.5f)) <= (whole * 0.5f))
	{
		HeroMM::getInstance()->progress_percent += addpresent;
		progressBar->setPercentage(static_cast<float>(HeroMM::getInstance()->progress_percent) / static_cast<float>(whole) * 100.0f);
		//진행도 플레이어 위치 변환
		progress_player->setPosition(visibleSize.width * 0.5f + (((static_cast<float>(HeroMM::getInstance()->progress_percent) / static_cast<float>(whole)) - 0.5f) * 320) + 5, visibleSize.height - 50);
	}

	if (static_cast<float>(HeroMM::getInstance()->progress_percent) / static_cast<float>(whole) * 100 >= (static_cast<float>(HeroMM::getInstance()->phase) + 1) * 10)
		return false;

	return true;
}

void BlockSlideGameScene::CreateBlock(Vec2 pos, const unsigned int _count)
{
	int org[5][2]{ { Block::Type::YELLOW ,Block::Type::SKULL },
				   { Block::Type::YELLOW, Block::Type::POISON },
				   { Block::Type::RED, Block::Type::RED },
				   { Block::Type::GREEN, Block::Type::SKULL },
				   { Block::Type::GREEN, Block::Type::POISON } };
	int org_right_left = rand() % 2; //왼쪽 오른쪽 체크 
	int org_mod = rand() % 100;
	if (org_mod < 70)
	{
		if (org_mod < 35) { org_mod = 0; }
		else { org_mod = 1; }
	}
	else if (org_mod < 95)
	{
		org_mod = 2;
	}
	else if (org_mod == 97)
	{
		org_mod = 3;
	}
	else
	{
		org_mod = 4;
	}
	for (int x = 0; x < 2; x++)
	{
		Block *temp = new Block(poisonGrid);
		const unsigned int bothSide = x;
		unsigned int type;

		if (skill_play_check) { type = Block::Type::YELLOW; }
		else { type = org[org_mod][org_right_left]; };

		const unsigned int count = _count;
		temp->Init(bothSide, type, count);

		if (count == temp->maxCount + 1)
			bottomBlock.push_back(temp);
		else
			block.push_back(temp);
		//독병 실행중일시 생성한것도 독효과 실행
		if (poisonCheck == true)
			temp->PoisonStart();
		//좌우 변경
		(org_right_left == 0) ? (org_right_left = 1) : (org_right_left = 0);
	}
}

void BlockSlideGameScene::BlockChange()
{
	int org[5][2]{ { 1 ,0 },{ 1, 4 },{ 2, 2 },{ 3, 0 },{ 3, 4 } };
	int org_right_left = rand() % 2; //왼쪽 오른쪽 체크
	int org_mod;
	for (auto iter = block.begin(); iter != block.end();)
	{
		if ((*iter)->bothSide == Block::BothSide::BLOCK_LEFT)
		{
			org_right_left = rand() % 2; //왼쪽 오른쪽 체크
			org_mod = rand() % 100;
			if (org_mod < 70)
			{
				if (org_mod < 35)
					org_mod = 0;
				else
					org_mod = 1;
			}
			else if (org_mod < 95)
				org_mod = 2;
			else if (org_mod == 97)
				org_mod = 3;
			else
				org_mod = 4;
		}
		(*iter)->Explosion();
		(*iter)->SetType(org[org_mod][org_right_left]);
		(org_right_left == 0) ? (org_right_left = 1) : (org_right_left = 0);
		iter++;
	}

}

void BlockSlideGameScene::PoisonEnd()
{
	poisonCheck = false;
	for (auto iter = block.begin(); iter != block.end(); iter++)
	{
		(*iter)->PoisonEnd();
	}

	for (auto iter = bottomBlock.begin(); iter != bottomBlock.end(); iter++)
	{
		(*iter)->PoisonEnd();
	}
}

void BlockSlideGameScene::BlockTouch(const unsigned int block_direct)
{
	unsigned int gem_amount = 0;
	start = true;
	bool greenCheck = true;

	if (pause_state)
		return;

	if (clock() - skullTouch < 1000)
	{
		button_left->setTexture("arrow_click.png");
		button_right->setTexture("arrow_click.png");
		return;
	}
		//녹색 체크
	for (auto iter = bottomBlock.begin(); iter != bottomBlock.end();iter++)
	{
		if ((*iter)->type == Block::Type::GREEN && (*iter)->bothSide == block_direct)
		{
			greenCheck = false;
		}
	}
	auto scaleBig = ScaleTo::create(0.05f, 1.3f);
	auto scaleSmall = ScaleTo::create(0.05f, 1.f);
	auto rotation = RotateTo::create(0.05f, rand() % 50 - 25);
	auto rotation2 = RotateTo::create(0.05f, 0.f);
	auto sequence = Sequence::create(FadeIn::create(0.2f), DelayTime::create(0.1f), FadeOut::create(0.2f), NULL);
	//터치할때 맨아래 블럭 체크
	for (auto iter = bottomBlock.begin(); iter != bottomBlock.end();)
	{
		if ((*iter)->bothSide == block_direct)
		{
			switch ((*iter)->type)
			{
			case Block::Type::SKULL:
				AudioMM::getInstance()->runEffect("HEADBLOCKTOUCH");
				BlockChange();
				combo_int = 0;
				combo_sprite->stopAllActions();
				combo_sprite->runAction(FadeOut::create(0));
				for (int i = 0; i < 10; i++) 
				{
					combo_num[i]->stopAllActions();
					combo_num[i]->runAction(FadeOut::create(0)); 
				}

				button_left->setTexture("arrow_click.png");
				button_right->setTexture("arrow_click.png");
				skullTouch = clock();
				(*iter)->Destroy(Vec2(visibleSize.width * 0.5f, 1000), true);
				iter = bottomBlock.erase(iter);
				break;
				case Block::Type::POISON:
				
				//AudioMM::getInstance()->runEffect("POISONTOUCH");
				//독병먹을시 색변
				poisonCheck = true;
				for (auto iter = block.begin(); iter != block.end(); iter++)
				{
					(*iter)->PoisonStart();
				}
				//흔들림

				button_left->setTexture("arrow_click.png");
				button_right->setTexture("arrow_click.png");
				poisonGrid->stopAllActions();
				poisonGrid->runAction(Sequence::create(Waves3D::create(5, Size(10, 10), 10, 50), Waves3D::create(0, Size(10, 10), 10, 0), CallFunc::create(CC_CALLBACK_0(BlockSlideGameScene::PoisonEnd, this)), NULL));
				//콤보 0 만듬
				combo_int = 0;
				combo_sprite->stopAllActions();
				combo_sprite->runAction(FadeOut::create(0));
				for (int i = 0; i < 10; i++) {
					combo_num[i]->stopAllActions(); combo_num[i]->runAction(FadeOut::create(0)); }

				(*iter)->Destroy(Vec2(visibleSize.width * 0.5f, 1000), true);
				iter = bottomBlock.erase(iter);

				break;
			case Block::Type::GREEN2:
				HeroMM::getInstance()->res_get += HeroMM::getInstance()->res_up;
			case Block::Type::RED:
			case Block::Type::YELLOW:
				if(AudioMM::getInstance()->getEffectEnabled())
					SimpleAudioEngine::getInstance()->playEffect("sound/effect/EF_normalblock.wav");

				combo_sprite->stopAllActions();
				for (int i = 0; i < 10; i++)
				{
					combo_num[i]->stopAllActions();
				}
				
				combo_sprite->runAction(sequence->clone());
				for (int i = 0; i < 10; i++)
					combo_num[i]->runAction(sequence->clone());

				combo_sprite->runAction(Sequence::create(scaleBig, scaleSmall, NULL));
				combo_sprite->runAction(Sequence::create(rotation, rotation2, NULL));

				//자원 획득
				HeroMM::getInstance()->res_get += HeroMM::getInstance()->res_up;

				HeroMM::getInstance()->res_get += gem_amount;
				//진행도 관련
				if (!SetProgress(1))
				{//진행도 상승
					//ChangeFightScene(); //진행도에 따른 신전환
				}
				(*iter)->Destroy(Vec2(visibleSize.width * 0.5f, 1000), true);
				iter = bottomBlock.erase(iter);
				HpUp();
				combo_int++;
				moneyLabel->setString(Unit(HeroMM::getInstance()->res_get));
				//skill
				if (!skill_play_check)  
				{
					if (skill_gauge_value + 1.f <= 100.f) {	skill_gauge_value+=1.f; }
					skill_progress->setPercentage(skill_gauge_value);
					if (skill_gauge_value >= 99) { skill_progress->setColor(Color3B(255, 255, 255)); }
				}
				break;
			case Block::Type::GREEN:
				(*iter)->SetType(Block::Type::GREEN2);
				iter++;
				break;
			}
		}
		else	
		{
			if ((*iter)->type != Block::Type::RED && greenCheck == true)
			{
				(*iter)->Destroy(progress_player->getPosition(), false);
				iter = bottomBlock.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	unsigned int temp = combo_int;

	unsigned int digit = 0;
	for (int i = 0; i < 10 && temp > 0; i++)
	{
		if (temp == 0)
			break;
		temp *= 0.1f;
		digit++;
	}

	if (combo_int % 30 == 0 && combo_int != 0)
	{
		comboEffect2();
	}

	temp = combo_int;
	for (int i = 0; i < 10; i++)
	{
		combo_num[i]->setTexture(StringUtils::format("BlockCombo/combo_%d.png", temp % 10));
		combo_num[i]->setPosition(visibleSize.width * 0.5f - 40 - i * 40 + (digit - i) * 40, 1000);
		combo_num[i]->setScale(1.5);

		if (temp == 0 && i != 0)
			combo_num[i]->setVisible(false);
		else
			combo_num[i]->setVisible(true);

		temp *= 0.1f;
	}

	//블럭 아래로 가게 하기
	if (bottomBlock.size() == 0)
	{
		for (auto iter = block.begin(); iter != block.end(); )
		{
			(*iter)->Down();
			if ((*iter)->count == (*iter)->maxCount + 1)
			{
				bottomBlock.push_back(*iter);
				iter = block.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		CreateBlock(Vec2(BLOCK_RIGHT_XPOS, BLOCK_LEFT_XPOS), 0);
	}
}

void BlockSlideGameScene::ChangeFightScene()
{
	HeroMM::getInstance()->phase++;
	Scene * scene = TransitionFade::create(1.0f, ClickerScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

bool BlockSlideGameScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	if (pause_state)
		return true;

	if (touch->getLocation().y < 300)
	{
		if (touch->getLocation().x > visibleSize.width * 0.5f && clock() - skullTouch > 1000)
		{
			BlockTouch(Block::BothSide::BLOCK_RIGHT);
			button_right->setTexture("arrow_click.png");
		}
		else if (touch->getLocation().x < visibleSize.width * 0.5f && clock() - skullTouch > 1000)
		{	
			BlockTouch(Block::BothSide::BLOCK_LEFT);
			button_left->setTexture("arrow_click.png");
		}
		//else if (touch->getLocation().x > visibleSize.width * 0.5f - 40 && touch->getLocation().x < visibleSize.width * 0.5f + 40)
		//{
		//	SkillStart();
		//}
	}
	
	return true;
}



void BlockSlideGameScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	button_right->setTexture("arrow.png");
	button_left->setTexture("arrow.png");
}


void BlockSlideGameScene::torialcaseButton()
{
	torial1_layer->setVisible(false);
	torial2_layer->setVisible(true);
}


void BlockSlideGameScene::torialcaseButton1()
{
	torial2_layer->setVisible(false);
	torial3_layer->setVisible(true);
}

void BlockSlideGameScene::torialcaseButton2()
{
	torial3_layer->setVisible(false);
	torial4_layer->setVisible(true);
}
void BlockSlideGameScene::torialcaseButton3()
{
	torial4_layer->setVisible(false);
	torial5_layer->setVisible(true);
}

void BlockSlideGameScene::torialcaseButton4()
{
	torial5_layer->setVisible(false);
	torial6_layer->setVisible(true);
}

void BlockSlideGameScene::torialcaseButton5()
{
	torial6_layer->setVisible(false);
}


void BlockSlideGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
		if (clock() - skullTouch > 1000)
		{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		BlockTouch(Block::BothSide::BLOCK_LEFT);
		button_left->setTexture("arrow_click.png");
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		BlockTouch(Block::BothSide::BLOCK_RIGHT);
		button_right->setTexture("arrow_click.png");
		break;
		}
	case EventKeyboard::KeyCode::KEY_SPACE:
		SkillStart();
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	case EventKeyboard::KeyCode::KEY_A:
		autoKey_state ? autoKey_state = false : autoKey_state = true;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		ChangeFightScene();
		break;
	case EventKeyboard::KeyCode::KEY_D:
		comboEffect();
		break;
	case EventKeyboard::KeyCode::KEY_F:
		comboEffect2();
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		unbeatable ? unbeatable = false : unbeatable = true;
		break;
	}
}

void BlockSlideGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (clock() - skullTouch > 1000)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			button_left->setTexture("arrow.png");
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			button_right->setTexture("arrow.png");
			break;
		}
	}
}
