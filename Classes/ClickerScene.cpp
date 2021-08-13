#pragma execution_character_set("utf-8")

#include "ClickerScene.h"
#include "BlockSlideGameScene.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "SkillManagement.h"
#include "AudioManagement.h"
#include "ending.h"
#include "ConversationManagement.h"

Scene* ClickerScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ClickerScene::create();

    scene->addChild(layer);

    return scene;
}

bool ClickerScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	initHeroData();
	initEffect();
	initLayer();
	initSkillScrollView();
	initAction();
	initSprite();
	createMonster();
	initProgressBar();
	initLabel();
	initMenu();
	initListener();
	initPopup();

	AudioMM::getInstance()->runBGM("INGAME2");

	if (HeroMM::getInstance()->phase_for_announcement == 2)
	{
		//AudioMM::getInstance()->runEffect("MEETBOSS");
	}
	else
	{
		//AudioMM::getInstance()->runEffect("KEY");
	}

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);

	this->schedule(schedule_selector(ClickerScene::monsterAttack), 3.0f);
	this->scheduleUpdate();

	//startTutorial();

    return true;
}

void ClickerScene::initLayer()
{
	pause_layer = LayerColor::create(Color4B(0, 0, 0, 122));
	pause_layer->setVisible(false);
	this->addChild(pause_layer, 99);

	layer_skill_back = LayerColor::create(Color4B::BLACK);
	layer_skill_back->setOpacity(185.5f);
	layer_skill_back->setVisible(false);
	this->addChild(layer_skill_back, 80);

	layer_skill = LayerColor::create(Color4B(0, 0, 0, 0));
	layer_skill->setPosition(0, -500);
	layer_skill->setContentSize(Size(720, 570));
	this->addChild(layer_skill, 90);

	layer_tutorial = LayerColor::create(Color4B(0, 0, 0, 122));
	layer_tutorial->setVisible(false);
	this->addChild(layer_tutorial, 999);
}

void ClickerScene::update(float dt)
{
	if (checkAllArrowIsDefault())
	{
		setArrow();
	}

	checkHp();
	checkPTimer();
	checkSkillGauge();

	if (isPlayerHPLow())
	{
		if (!spr_blood->isVisible())
		{
 			spr_hero_hp_bar->setColor(Color3B::RED);
			spr_blood->runAction(player_low_hp);
		}
	}
	else
	{
		if (spr_blood->isVisible())
		{
			spr_blood->runAction(player_high_hp);

			spr_hero_hp_bar->setColor(Color3B(255, 255, 255));
		}
	}

	updateLabel();
}

void ClickerScene::startTutorial()
{
	isTutorial = true;

	this->pauseSchedulerAndActions();

	spr_monster->pauseSchedulerAndActions();
	//spr_hero->pauseSchedulerAndActions();

	menui_skill->setEnabled(false);

	isGamePaused = true;

	layer_tutorial->setVisible(true);

	spr_tutorial_npc = Sprite::createWithSpriteFrame(ConversationMM::getInstance()->sprf_npc[ConversationMM::getInstance()->NPC::TUTORIAL]->getSpriteFrame());
	spr_tutorial_npc->setPosition(200, 200);
	layer_tutorial->addChild(spr_tutorial_npc);

	spr_conversation_panel = Sprite::createWithSpriteFrame(ConversationMM::getInstance()->sprf_conversation_panel->getSpriteFrame());
	spr_conversation_panel->setPosition(360, 300);
	layer_tutorial->addChild(spr_conversation_panel);

	ConversationMM::getInstance()->startConversation(ConversationMM::getInstance()->NPC::TUTORIAL, ConversationMM::getInstance()->Place::CLICKER);

	lab_tutorial = Label::create("", "", 48);
	lab_tutorial->setString(ConversationMM::getInstance()->lab_tutorial->getString());
	layer_tutorial->addChild(lab_tutorial);
	lab_tutorial->setPosition(spr_conversation_panel->getPosition());
}

void ClickerScene::endTutorial()
{
	this->setTouchEnabled(true);

	this->resumeSchedulerAndActions();
	spr_monster->resumeSchedulerAndActions();
	//spr_hero->resumeSchedulerAndActions();

	this->scheduleUpdate();
	this->schedule(schedule_selector(ClickerScene::monsterAttack), 3.0f);

	isGamePaused = false;

	layer_tutorial->setVisible(false);

	isTutorial = false;
}

void ClickerScene::changeButtonState(int state)
{
	switch (state)
	{
	case BUTTONSTATE::NORMAL:
		button_state = BUTTONSTATE::NORMAL;
		break;
	case BUTTONSTATE::LOCKED:
		AudioMM::getInstance()->runEffect("PENALTY");
		button_state = BUTTONSTATE::LOCKED;
		setLockVisible(true);
		this->runAction(Sequence::create(lock_to_normal_delay, CallFuncN::create([=](Node* node){button_state = BUTTONSTATE::NORMAL; setLockVisible(false); }), NULL));
		break;
	case BUTTONSTATE::SKILL:
		button_state = BUTTONSTATE::SKILL;
		break;
	}
}

void ClickerScene::updateLabel()
{
	lab_monster_hp->setString(StringUtils::format("%d / %d", MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num], MonsterMM::getInstance()->max_hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num]));
	lab_hero_hp->setString(StringUtils::format("%d / %d", HeroMM::getInstance()->hp, HeroMM::getInstance()->max_hp));
}

void ClickerScene::initSprite()
{
	spr_arrow_panel = Sprite::create("arrow_panel.png");
	spr_arrow_panel->setPosition(360, 310);
	spr_arrow_panel->setScale(0.8);
	this->addChild(spr_arrow_panel, ZOrder::OBJECT);

	spr_game_over = Sprite::create("game_over.png");
	spr_game_over->setPosition(360, 900);
	spr_game_over->runAction(FadeOut::create(0));
	this->addChild(spr_game_over, ZOrder::NOTIFICATION + 4);;

	spr_game_over_back = Sprite::create("skill_back_black.png");
	spr_game_over_back->setPosition(360, 640);
	spr_game_over_back->setOpacity(0);
	spr_game_over->runAction(FadeOut::create(0));
	this->addChild(spr_game_over_back, ZOrder::NOTIFICATION + 3);

	for (int i = 0; i < 4; i++)
	{
		spr_arrow[i] = Sprite::create("direction.png");
		spr_arrow[i]->setPosition(vec2_arrow[i]);
		//spr_arrow[i]->setRotation(rotate_arrow[i]);

		switch (i)
		{
		case 0:
			spr_arrow[i]->runAction(FlipX::create(true));
			break;
		case 1:
			spr_arrow[i]->runAction(FlipX::create(true));
			spr_arrow[i]->runAction(FlipY::create(true));
			break;
		case 2:
			break;
		case 3:
			spr_arrow[i]->runAction(FlipY::create(true));
			break;
		}

		spr_arrow[i]->setScale(0.8);
		this->addChild(spr_arrow[i], ZOrder::OBJECT + 1);

		rect_arrow[i] = spr_arrow[i]->getBoundingBox();
	}

	spr_arrow_default = Sprite::create("direction.png");
	spr_arrow_default->setVisible(false);
	this->addChild(spr_arrow_default, ZOrder::OBJECT);

	spr_arrow_sel = Sprite::create("direction_set.png");
	spr_arrow_sel->setVisible(false);
	this->addChild(spr_arrow_sel, ZOrder::OBJECT);

	spr_arrow_warning = Sprite::create("direction_warning.png");
	spr_arrow_warning->setVisible(false);
	this->addChild(spr_arrow_warning, ZOrder::OBJECT);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//spr_hero = Sprite::create("hero.png");
	//spr_hero->setPosition(Vec2(-65, 820));
	//this->addChild(spr_hero, ZOrder::OBJECT);

	spr_monster = Sprite::create(StringUtils::format("monster_%d.png", HeroMM::getInstance()->phase_for_announcement));
	spr_monster->setPosition(Vec2(360, 950));
	this->addChild(spr_monster, ZOrder::OBJECT);

	auto move_monster = MoveBy::create(2.0f, Vec2(-225, 0));
	auto move_hero = MoveBy::create(2.0f, Vec2(225, 0));

	//spr_hero->runAction(move_hero);
	//spr_monster->runAction(move_monster);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	
	spr_background = Sprite::create("clicker_background.png");
	spr_background->setAnchorPoint(Vec2(0, 0));
	spr_background->setPosition(0, 0);
	this->addChild(spr_background, ZOrder::BACKGROUND);

	spr_warning = Sprite::create("warning.png");
	spr_warning->setVisible(false);
	spr_warning->runAction(seq_scale_warning);
	spr_warning->setPosition(360, spr_monster->getPositionY());
	this->addChild(spr_warning, ZOrder::NOTIFICATION);

	spr_shield = Sprite::create("shield.png");
	spr_shield->setVisible(false);
	spr_shield->setPosition(360, 820);
	this->addChild(spr_shield, ZOrder::NOTIFICATION);

	spr_chain = Sprite::create("chain.png");
	spr_chain->setPosition(360, 310);
	spr_chain->setScale(0.8);
	spr_chain->setVisible(false);
	this->addChild(spr_chain, ZOrder::UI + 2);

	spr_lock = Sprite::create("lock.png");
	spr_lock->setPosition(360, 310);
	spr_lock->setScale(0.8);
	spr_lock->setVisible(false);
	this->addChild(spr_lock, ZOrder::UI + 2);

	spr_skill_not_enabled = Sprite::create("notice_skill_not_enabled.png");
	spr_skill_not_enabled->setPosition(360, 820);
	spr_skill_not_enabled->setVisible(false);
	this->addChild(spr_skill_not_enabled, ZOrder::NOTIFICATION);

	spr_hero_portrait_back = Sprite::create("hero_portrait_back.png");
	spr_hero_portrait_back->setPosition(80, 650);
	this->addChild(spr_hero_portrait_back, ZOrder::UI + 2);

	spr_hero_portrait_default = Sprite::create("hero_portrait_default.png");
	spr_hero_portrait_default->setVisible(false);
	this->addChild(spr_hero_portrait_default);

	spr_hero_portrait_damaged = Sprite::create("hero_portrait_damaged.png");
	spr_hero_portrait_damaged->setVisible(false);
	this->addChild(spr_hero_portrait_damaged);

	spr_hero_portrait_fever = Sprite::create("hero_portrait_fever.png");
	spr_hero_portrait_fever->setVisible(false);
	this->addChild(spr_hero_portrait_fever);

	spr_hero_portrait = Sprite::create("portrait.png");
	spr_hero_portrait->setPosition(70, 85);
	spr_hero_portrait->setScale(0.6f);
	spr_hero_portrait->setSpriteFrame(spr_hero_portrait_default->getSpriteFrame());
	spr_hero_portrait_back->addChild(spr_hero_portrait, ZOrder::UI + 2);

	spr_monster_portrait = Sprite::create("portrait.png");
	spr_monster_portrait->setPosition(620, 1080);
	spr_monster_portrait->setScale(0.8f);
	//this->addChild(spr_monster_portrait, ZOrder::OBJECT);

	spr_hero_portrait_default = Sprite::create("hero_portrait_default.png");
	spr_hero_portrait_default->setVisible(false);
	this->addChild(spr_hero_portrait_default);

	spr_hero_portrait_damaged = Sprite::create("hero_portrait_damaged.png");
	spr_hero_portrait_damaged->setVisible(false);
	this->addChild(spr_hero_portrait_damaged);

	spr_hero_portrait_fever = Sprite::create("hero_portrait_fever.png");
	spr_hero_portrait_fever->setVisible(false);
	this->addChild(spr_hero_portrait_fever);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	spr_blood = Sprite::create("blood.png");
	spr_blood->setScale(2.0f);
	spr_blood->setVisible(false);
	this->addChild(spr_blood);

	spr_red = Sprite::create("player_damaged.png");
	spr_red->setScale(2.0f);
	spr_red->runAction(FadeOut::create(0.0f));
	this->addChild(spr_red, ZOrder::UI + 99);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	spr_pause_popup = Sprite::create("pause_popup.png");
	spr_pause_popup->setPosition(Vec2(360, 640));
	pause_layer->addChild(spr_pause_popup);

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	spr_skill_gauge_on = Sprite::create("skill_gauge_on.png");
	spr_skill_gauge_on->setPosition(spr_arrow_panel->getPosition());
	spr_skill_gauge_on->setVisible(false);
	this->addChild(spr_skill_gauge_on, ZOrder::UI + 1);
}

void ClickerScene::initLabel()
{
	lab_hero_hp = Label::createWithSystemFont("", "arami", 30);
	lab_hero_hp->setPosition(ptimer_hero_hp->getPosition());
	this->addChild(lab_hero_hp, ZOrder::UI);

	lab_monster_hp = Label::createWithSystemFont("", "arami", 30);
	lab_monster_hp->setPosition(ptimer_monster_hp->getPosition() + Vec2(100, 0));
	this->addChild(lab_monster_hp, ZOrder::UI);

	lab_monster_name = Label::create("", "", 30);
	lab_monster_name->setString(StringUtils::format("%s", MonsterMM::getInstance()->monster_name[HeroMM::getInstance()->phase_for_announcement]));
	lab_monster_name->setPosition(ptimer_monster_hp->getPosition() + Vec2(-100, 0));
	this->addChild(lab_monster_name, ZOrder::UI);
}

void ClickerScene::initProgressBar()
{
	spr_hero_hp_bar_back = Sprite::create("hp_bar_back.png");
	spr_hero_hp_bar_back->setPosition(400, 650);
	this->addChild(spr_hero_hp_bar_back, ZOrder::UI);
	
	spr_hero_hp_bar = Sprite::create("hp_bar.png");

	ptimer_hero_hp = ProgressTimer::create(spr_hero_hp_bar);
	ptimer_hero_hp->setPosition(400, 650);
	ptimer_hero_hp->setMidpoint(Vec2(0, 0.5f));
	ptimer_hero_hp->setBarChangeRate(Vec2(1, 0));
	ptimer_hero_hp->setType(kCCProgressTimerTypeBar);
	this->addChild(ptimer_hero_hp, ZOrder::UI);

	ptimer_hero_hp->setPercentage(100.0f);

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	if (HeroMM::getInstance()->phase_for_announcement == 2)
	{
		spr_boss_portrait = Sprite::create("boss_portrait.png");
		spr_boss_portrait->setPosition(45, 1230);
		this->addChild(spr_boss_portrait, ZOrder::UI + 1);
		
		spr_monster_hp_bar_back = Sprite::create("boss_hp_bar_back.png");
		spr_monster_hp_bar_back->setPosition(360, 1230);
		this->addChild(spr_monster_hp_bar_back, ZOrder::UI);

		spr_monster_hp_bar = Sprite::create("boss_hp_bar.png");
	}
	else
	{
		spr_monster_hp_bar_back = Sprite::create("hp_bar_back.png");
		spr_monster_hp_bar_back->setPosition(360, 1230);
		this->addChild(spr_monster_hp_bar_back, ZOrder::UI);

		spr_monster_hp_bar = Sprite::create("monster_hp_bar.png");
	}

	ptimer_monster_hp = ProgressTimer::create(spr_monster_hp_bar);
	ptimer_monster_hp->setPosition(360, 1230);
	ptimer_monster_hp->setMidpoint(Vec2(0, 0.5f));
	ptimer_monster_hp->setBarChangeRate(Vec2(1, 0));
	ptimer_monster_hp->setType(kCCProgressTimerTypeBar);
	this->addChild(ptimer_monster_hp, ZOrder::UI);

	ptimer_monster_hp->setPercentage(100.0f);

	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////

	spr_skill_gauge = Sprite::create("skill_bar.png");
	//spr_skill_gauge->setScaleX(1.f);
	//spr_skill_gauge->setScaleY(0.85f);

	spr_skill_gauge_back = Sprite::create("skill_bar_back.png");
	spr_skill_gauge_back->setPosition(250, 685);
	this->addChild(spr_skill_gauge_back, ZOrder::UI);

	ptimer_skill_gauge = ProgressTimer::create(spr_skill_gauge);
	ptimer_skill_gauge->setPosition(250, 685);
	ptimer_skill_gauge->setMidpoint(Vec2(0, 0.5f));
	ptimer_skill_gauge->setBarChangeRate(Vec2(1, 0));
	ptimer_skill_gauge->setType(kCCProgressTimerTypeBar);
	//ptimer_skill_gauge->setScaleX(0.6f);
	//ptimer_skill_gauge->setScaleY(0.85f);
	this->addChild(ptimer_skill_gauge, ZOrder::UI);

	ptimer_skill_gauge->setPercentage(HeroMM::getInstance()->skill_gauge);
}

void ClickerScene::initMenu()
{
	menui_skill = MenuItemImage::create("skill_button.png", "skill_button.png",
		CC_CALLBACK_1(ClickerScene::changeButtonStateToSkillCallback, this));
	menui_skill->setPosition(spr_arrow_panel->getPosition());

	const Vec2 vec2_frame = Vec2(360,100);
	const Vec2 vec2_icon[4] = { Vec2(150,100) ,Vec2(290,100) ,Vec2(430,100) ,Vec2(570,100) };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spr_skill_frame = Sprite::create("frame.png");
	spr_skill_frame->setPosition(vec2_frame);
	spr_skill_frame->setOpacity(122);
	layer_skill->addChild(spr_skill_frame);

	spr_skill_use_panel = Sprite::createWithSpriteFrame(SkillMM::getInstance()->sprf_skill_use_panel->getSpriteFrame()->clone());
	spr_skill_use_panel->setPosition(-360, 640);
	layer_skill->addChild(spr_skill_use_panel, 5);

	for (int i = 0; i < 4; i++)
	{	
		spr_skill_icon[i] = Sprite::createWithSpriteFrame(SkillMM::getInstance()->sprf_skill_icon[i]->getSpriteFrame()->clone());
		spr_skill_icon[i]->setPosition(600, 700);
		spr_skill_use_panel->addChild(spr_skill_icon[i]);

		spr_icon_frame[i] = Sprite::create("itemimage.png");
		spr_icon_frame[i]->setPosition(vec2_icon[i]);
		layer_skill->addChild(spr_icon_frame[i]);

		spr_use_skill_icon[i] = Sprite::createWithSpriteFrame(SkillMM::getInstance()->sprf_skill_icon[i]->getSpriteFrame()->clone());
		menui_use_skill[i] = MenuItemSprite::create(spr_use_skill_icon[i], spr_use_skill_icon[i], CC_CALLBACK_0(ClickerScene::useSkillCallback, this, i));
		menui_use_skill[i]->setScale(0.75);
		menui_use_skill[i]->setPosition(vec2_icon[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		if (SkillMM::getInstance()->isSkillBought[i] != true)
		{
			menui_use_skill[i]->setEnabled(false);

			Sprite* spr_locker = Sprite::create("chain.png");
			//spr_locker->setPosition(menui_use_skill[i]->getPosition());
			//spr_locker->setScale(0.25f);
			//layer_skill->addChild(spr_locker, ZOrder::NOTIFICATION);
			
			MenuItemSprite* menui_locker = MenuItemSprite::create(spr_locker, spr_locker, CC_CALLBACK_1(ClickerScene::closeSkillLayerCallback, this));
			menui_locker->setPosition(menui_use_skill[i]->getPosition());
			menui_locker->setScale(0.25f);
			//layer_skill->addChild(menui_locker, ZOrder::NOTIFICATION);

			Menu* menu_locker = Menu::create(menui_locker, NULL);
			menu_locker->setPosition(0, 0);
			layer_skill->addChild(menu_locker, ZOrder::NOTIFICATION);
		}
	}

	menu_skill = Menu::create(menui_use_skill[0], menui_use_skill[1], menui_use_skill[2], menui_use_skill[3], NULL);
	menu_skill->setPosition(Vec2::ZERO);
	layer_skill->addChild(menu_skill);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	spr_pause = Sprite::create("pause.png");

	menui_pause = MenuItemSprite::create(spr_pause, spr_pause, CC_CALLBACK_1(ClickerScene::pauseCallback, this));
	menui_pause->setPosition(670, 1230);

	menu_clicker = Menu::create(menui_pause, menui_skill, NULL);
	menu_clicker->setPosition(0, 0);
	this->addChild(menu_clicker, ZOrder::UI);

	spr_skill_back = Sprite::create("skill_back.png");
	spr_skill_back_sel = Sprite::create("skill_back_sel.png");

	menui_skill_back = MenuItemSprite::create(spr_skill_back, spr_skill_back_sel, CC_CALLBACK_1(ClickerScene::closeSkillLayerCallback, this));
	menui_skill_back->setPosition(menui_skill->getPosition());

	menu_skill_back = Menu::create(menui_skill_back, NULL);
	menu_skill_back->setPosition(0, 0);
	layer_skill_back->addChild(menu_skill_back);
}

void ClickerScene::initAction()
{
	move_monster_back = MoveBy::create(0.5f, Vec2(-50, 0));
	move_monster_back->retain();
	move_monster_back->setTag(MOVEMONSTER);

	move_monster_front = MoveBy::create(0.5f, Vec2(50, 0));
	move_monster_front->retain();
	move_monster_front->setTag(MOVEMONSTER);

	ease_monster_back = EaseBackIn::create(move_monster_back);
	ease_monster_back->retain();
	ease_monster_back->setTag(MOVEMONSTER);

	ease_monster_front = EaseBackIn::create(move_monster_front);
	ease_monster_front->retain();
	ease_monster_front->setTag(MOVEMONSTER);

	move_monster_back_critical = MoveBy::create(0.5f, Vec2(-150, 0));
	move_monster_back_critical->retain();
	move_monster_back_critical->setTag(MOVEMONSTER);

	move_monster_front_critical = MoveBy::create(0.5f, Vec2(150, 0));
	move_monster_front_critical->retain();
	move_monster_front_critical->setTag(MOVEMONSTER);

	ease_monster_back_critical = EaseBackIn::create(move_monster_back_critical);
	ease_monster_back_critical->retain();
	ease_monster_back_critical->setTag(MOVEMONSTER);

	ease_monster_front_critical = EaseBackIn::create(move_monster_front_critical);
	ease_monster_front_critical->retain();
	ease_monster_front_critical->setTag(MOVEMONSTER);

	place_monster_base = Place::create(Vec2(820 - 225, 740));
	place_monster_base->retain();

	seq_monster_attack = Sequence::create(ease_monster_back,
										  CallFuncN::create([=](Node* node) {
																				spr_hero_portrait->setSpriteFrame(spr_hero_portrait_damaged->getSpriteFrame());
																			}),
										  CallFuncN::create([=](Node* node) {giveDamageTo(TargetType::HERO, MonsterMM::getInstance()->dmg[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num], false); }),
										  ease_monster_front,
										  DelayTime::create(1.0f),
										  CallFuncN::create([=](Node* node) {spr_hero_portrait->setSpriteFrame(spr_hero_portrait_default->getSpriteFrame()); }),
										  NULL);
	seq_monster_attack->setTag(99);
	seq_monster_attack->retain();

	seq_monster_critical_attack = Sequence::create(CallFuncN::create([=](Node* node) {AudioMM::getInstance()->runEffect("WARNING");  spr_warning->setVisible(true); }),
													DelayTime::create(1.0f),
													CallFuncN::create([=](Node* node) {setWarningArrow(); }),
													ease_monster_back_critical->clone(),
													 CallFuncN::create([=](Node* node) {
																						  if (checkIsPlayerDodged())
																						  {
																							  AudioMM::getInstance()->runEffect("DODGESUCCESS");

																							  HeroMM::getInstance()->state = HeroMM::getInstance()->HeroState::DEFAULT;
																							  log("Dodged!");
																						
																							  //spr_hero->runAction(seq_hero_dodge);
																							  spr_warning->setVisible(false);

																							  spr_shield->setVisible(true);
																							  spr_shield->runAction(move_shield);
																							  spr_shield->runAction(seq_shield);
																							  plusSkillGauge(2);
																						  }
																						  else
																						  {
																							  AudioMM::getInstance()->runEffect("DODGEFAIL");

																							  giveDamageTo(TargetType::HERO, MonsterMM::getInstance()->dmg[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num], true);

																							  spr_hero_portrait->setSpriteFrame(spr_hero_portrait_damaged->getSpriteFrame());
																							  //spr_hero->runAction(player_damaged_by_monster);

																							  spr_red->runAction(player_damaged_effect);

																							  setWarningArrowToDefault();

																							  spr_warning->setVisible(false);
																						  }
																					   }),
													ease_monster_front_critical->clone(),
													//DelayTime::create(1.0f),
													CallFunc::create([]() {log("aasas"); }),
													 CallFuncN::create([=](Node* node) {spr_hero_portrait->setSpriteFrame(spr_hero_portrait_default->getSpriteFrame()); }),
												   NULL);
	seq_monster_critical_attack->retain();
	seq_monster_critical_attack->setTag(99);

	lock_to_normal_delay = DelayTime::create(3.0f);
	lock_to_normal_delay->retain();

	move_hero_dodge = MoveBy::create(0.3f, Vec2(-90, 0));
	move_hero_dodge->retain();

	seq_hero_dodge = Sequence::create(move_hero_dodge, move_hero_dodge->reverse(), NULL);
	seq_hero_dodge->retain();

	scale_warning_big = ScaleBy::create(1, 1.5);
	scale_warning_small = ScaleBy::create(1, 0.666666);
	seq_scale_warning = RepeatForever::create(Sequence::create(scale_warning_big, scale_warning_small, NULL));
	seq_scale_warning->retain();

	move_shield = MoveBy::create(0.5f, Vec2(0, 200));
	move_shield->retain();

	fade_shield = FadeOut::create(0.5f);
	fade_shield->retain();

	fadein_shield = FadeIn::create(0.f);
	fadein_shield->retain();

	hide_shield = Hide::create();
	hide_shield->retain();

	place_shield = Place::create(Vec2(360, 820));
	place_shield->retain();

	seq_shield = Sequence::create(place_shield, fadein_shield, fade_shield, hide_shield, fadein_shield, place_shield, NULL);
	seq_shield->retain();
}

void ClickerScene::initHeroData()
{
	HeroMM::getInstance()->dmg = EquipmentMM::getInstance()->weapon_damage[EquipmentMM::getInstance()->weapon_level];
	HeroMM::getInstance()->res_up = EquipmentMM::getInstance()->pickaxe_res_up[EquipmentMM::getInstance()->pickaxe_level];
	HeroMM::getInstance()->isAlive = true;
	MonsterMM::getInstance()->isAlive = true;
	button_state = BUTTONSTATE::NORMAL;
}

void ClickerScene::initListener()
{
	lis_key_debug = EventListenerKeyboard::create();
	lis_key_debug->onKeyPressed = CC_CALLBACK_2(ClickerScene::onKeyPressed, this);
	lis_key_debug->onKeyReleased = CC_CALLBACK_2(ClickerScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis_key_debug, this);

}

void ClickerScene::initPopup()
{
	openAni = Sprite::create("OpenEffectLayer/pause_layer_effect_01.png");
	openAni->setPosition(10000, 10000);
	this->addChild(openAni, 50);

	auto visibleSize = Director::getInstance()->getVisibleSize();

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
	auto setting_bgm_button = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ClickerScene::toggleBackgroundCallback, this), sound_bgm_on, sound_bgm_off, NULL);
	setting_bgm_button->setScale(0.75f); 
	setting_bgm_button->setPosition(visibleSize.width * 0.5f + 100, 875);

	auto sound_effect_on = MenuItemSprite::create(Sprite::create(spriteName[2]), Sprite::create(spriteName[3]));
	auto sound_effect_off = MenuItemSprite::create(Sprite::create(spriteName[3]), Sprite::create(spriteName[2]));
	auto setting_effect_button = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ClickerScene::toggleEffectCallback, this), sound_effect_on, sound_effect_off, NULL);
	setting_effect_button->setScale(0.75f);
	setting_effect_button->setPosition(visibleSize.width * 0.5f + 100, 675);

	auto paused_paused = Sprite::create("pause_base.png");
	paused_paused->setPosition(visibleSize * 0.5f);
	pause_layer->addChild(paused_paused, 1);

	auto paused_done = MenuItemImage::create("paused_done.png", "paused_done.png", CC_CALLBACK_1(ClickerScene::returnGameCallback, this));
	paused_done->setPosition(visibleSize.width * 0.5f + 130, 190);

	auto menuScene_button = MenuItemImage::create("pause_home_button.png", "pause_home_button_click.png", CC_CALLBACK_0(ClickerScene::menuSceneCallBack, this));
	menuScene_button->setPosition(visibleSize.width * 0.5f - 130, 190);

	auto ending_scene = MenuItemImage::create("credit_button.png", "credit_button_click.png", CC_CALLBACK_0(ClickerScene::endingSceneCallBack, this));
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

void ClickerScene::initEffect()
{
	monster_damaged = MonsterDamaged::create();
	monster_damaged->retain(); 

	player_damaged_by_monster = PlayerDamagedByMonster::create(spr_background);
	player_damaged_by_monster->retain();

	player_low_hp = PlayerLowHP::create();
	player_low_hp->retain();

	player_high_hp = PlayerHighHP::create();
	player_high_hp->retain();

	player_damaged_effect = PlayerDamagedEffect::create();
	player_damaged_effect->retain();

	arrow_fade_big = ArrowFadeOut::create();
	arrow_fade_big->retain();

	arrow_fade_small = ArrowFadeIn::create();
	arrow_fade_small->retain();

	portrait_tint_red = DamagedPortrait::create();
	portrait_tint_red->retain();
	portrait_tint_red->setTag(EFFECTTAG::PORTRAIT_TINT_RED);

	damaged_bar = DamagedHPBar::create();
	damaged_bar->retain();
	damaged_bar->setTag(EFFECTTAG::DAMAGED_BAR);

	skill_gauge_up = SkillGaugeUp::create();
	skill_gauge_up->retain();
}

void ClickerScene::initSkillScrollView()
{

}

void ClickerScene::setDirection(int arrow_num)
{
	srand((unsigned)time(NULL));

	if (arrow_num == 1)
	{
		for (;;)
		{
			arrow_direction_1 = rand() % 4;

			if (warning_arrow_direciton != arrow_direction_1)
			{
				arrow_direction_2 = ArrowDirection::NONE;

				break;
			}
		}
	}
	else if (arrow_num == 2)
	{
		for (;;)
		{
			arrow_direction_1 = rand() % 4;
			arrow_direction_2 = rand() % 4;

			if (arrow_direction_1 != arrow_direction_2 && warning_arrow_direciton != arrow_direction_1 && warning_arrow_direciton != arrow_direction_2)
			{
				break;
			}
		}
	}
}

void ClickerScene::setArrow()
{
	srand((unsigned)time(NULL));

	if (MonsterMM::getInstance()->isAlive)
	{
		arrow_num = rand() % 2 + 1;

		if (arrow_num == 1)
		{		
			for (;;)
			{
				setDirection(1);

				if (arrow_type[arrow_direction_1] != ArrowType::WARNING)
				{
					arrow_type[arrow_direction_1] = ArrowType::SET;
					spr_arrow[arrow_direction_1]->setSpriteFrame(spr_arrow_sel->getSpriteFrame());

					break;
				}
			}
					
		}
		else if (arrow_num == 2)
		{
			setDirection(2);

			for (;;)
			{
				if (arrow_type[arrow_direction_1] != ArrowType::WARNING && arrow_type[arrow_direction_2] != ArrowType::WARNING)
				{
					arrow_type[arrow_direction_1] = ArrowType::SET;
					arrow_type[arrow_direction_2] = ArrowType::SET;

					spr_arrow[arrow_direction_1]->setSpriteFrame(spr_arrow_sel->getSpriteFrame());
					spr_arrow[arrow_direction_2]->setSpriteFrame(spr_arrow_sel->getSpriteFrame());

					break;
				}
			}
		}
	 }
}

void ClickerScene::setWarningArrow()
{
	srand((unsigned)time(NULL));

	int tmp_rand_arrow_warning;

	for (;;)
	{
		tmp_rand_arrow_warning = rand() % 4;
		
		if (arrow_type[tmp_rand_arrow_warning] == DEFAULT)
		{
			arrow_type[tmp_rand_arrow_warning] = ArrowType::WARNING;

			spr_arrow[tmp_rand_arrow_warning]->setVisible(true);
			spr_arrow[tmp_rand_arrow_warning]->setSpriteFrame(spr_arrow_warning->getSpriteFrame());

			warning_arrow_direciton = tmp_rand_arrow_warning;

			break;
		}
	}
}

void ClickerScene::setWarningValueToDefaultValue()
{
	AudioMM::getInstance()->runEffect("REDKEY");

	HeroMM::getInstance()->state = HeroMM::getInstance()->HeroState::DODGE;

	warning_touch_id = 99;

	Sequence* seq_change = Sequence::create(CallFunc::create([=] {spr_arrow[warning_arrow_direciton]->runAction(arrow_fade_big); }),
											DelayTime::create(0.25f),
										    CallFunc::create([=] {spr_arrow[warning_arrow_direciton]->setSpriteFrame(spr_arrow_default->getSpriteFrame()); }),
											NULL);

	spr_arrow[warning_arrow_direciton]->runAction(seq_change);

	arrow_type[warning_arrow_direciton] = ArrowType::DEFAULT;
}

void ClickerScene::setWarningArrowToDefault()
{
	for (int i = 0; i < 4; i++)
	{
		if (arrow_type[i] == ArrowType::WARNING)
		{
			arrow_type[i] = ArrowType::DEFAULT;
			
			spr_arrow[i]->setSpriteFrame(spr_arrow_default->getSpriteFrame());

			log("%d", arrow_type[i]);
		}
	}
}

bool ClickerScene::checkAllArrowIsDefault()
{
	if (arrow_type[0] == DEFAULT && arrow_type[1] == DEFAULT && arrow_type[2] == DEFAULT && arrow_type[3] == DEFAULT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ClickerScene::onTouchesBegan(const std::vector<Touch*>& touches, Event * unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;

	if (isTutorial)
	{
		if (ConversationMM::getInstance()->isNextEmpty())
		{
			endTutorial();
			ConversationMM::getInstance()->nextConversation();
		}
		else
		{
			log("asdf");
			ConversationMM::getInstance()->nextConversation();
			lab_tutorial->setString(ConversationMM::getInstance()->lab_tutorial->getString());
		}
	}
	else if (HeroMM::getInstance()->isAlive == true && MonsterMM::getInstance()->isAlive == true && (button_state != LOCKED))
	{
		if (button_state == NORMAL)
		{
			for (int i = 0; i < touches.size(); i++)
			{
				touch = (Touch*)(*it);

				for (int j = 0; j < 4; j++)
				{
					if (rect_arrow[j].containsPoint(touch->getLocation()))
					{
						switch (arrow_type[j])
						{
						case ArrowType::SET:
							changeSetArrowToDefault(j);

							//if (checkAllArrowIsDefault())
							//{
								heroAttack(arrow_num);
							//}

							log("hit!");

							plusSkillGauge(2);

							break;

						case ArrowType::WARNING:
							
							warning_touch_location = touch->getLocation();
							warning_touch_id = touch->getID();

							break;

						case ArrowType::DEFAULT:
							setWarningArrowToDefault();
							log("changed to locked!");
							changeButtonState(BUTTONSTATE::LOCKED);
							break;
						}	
					}
				}

				it++;
			}
		}
	}
	else
	{
		AudioMM::getInstance()->runEffect("PENALTYTOUCH");
		log("locked!");
	}
}

void ClickerScene::onTouchesMoved(const std::vector<Touch*>& touches, Event * unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch* touch;

	if (HeroMM::getInstance()->isAlive == true && MonsterMM::getInstance()->isAlive == true && (button_state != LOCKED))
	{
		for (int i = 0; i < touches.size(); i++)
		{
			touch = (Touch*)(*it);
			 
			if (i == warning_touch_id)
			{
				Vec2 tmp_direction_index[4] = { Vec2(-15, 15), Vec2(-15, -15), Vec2(15, 15), Vec2(15, -15) };

				switch (warning_arrow_direciton)
				{
				case ArrowDirection::LEFT_UP:
					if (touch->getLocation().x <= warning_touch_location.x + tmp_direction_index[warning_arrow_direciton].x && touch->getLocation().y >= warning_touch_location.y + tmp_direction_index[warning_arrow_direciton].y)
					{
						setWarningValueToDefaultValue();
					}
					else
					{
						setWarningArrowToDefault();
					}
					break;
				case ArrowDirection::LEFT_DOWN:
					if (touch->getLocation().x <= warning_touch_location.x + tmp_direction_index[warning_arrow_direciton].x && touch->getLocation().y <= warning_touch_location.y + tmp_direction_index[warning_arrow_direciton].y)
					{
						setWarningValueToDefaultValue();
					}
					else
					{
						setWarningArrowToDefault();
					}
					break;
				case ArrowDirection::RIGHT_UP:
					if (touch->getLocation().x >= warning_touch_location.x + tmp_direction_index[warning_arrow_direciton].x && touch->getLocation().y >= warning_touch_location.y + tmp_direction_index[warning_arrow_direciton].y)
					{
						setWarningValueToDefaultValue();
					}
					else
					{
						setWarningArrowToDefault();
					}
					break;
				case ArrowDirection::RIGHT_DOWN:
					if (touch->getLocation().x >= warning_touch_location.x + tmp_direction_index[warning_arrow_direciton].x && touch->getLocation().y <= warning_touch_location.y + tmp_direction_index[warning_arrow_direciton].y)
					{
						setWarningValueToDefaultValue();
					}
					else
					{
						setWarningArrowToDefault();
					}
					break;
				}
			}
		}
	}
}

void ClickerScene::onTouchesEnded(const std::vector<Touch*>& touches, Event * unused_event)
{
}

void ClickerScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (isGamePaused == false)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_SPACE:
			checkKeyboardForDebug();
			break;
		case EventKeyboard::KeyCode::KEY_K:
			changeButtonStateToSkillCallback(0);
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			HeroMM::getInstance()->hp = 0;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			HeroMM::getInstance()->skill_gauge = 100;
			break;
		case EventKeyboard::KeyCode::KEY_E:
			MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			if (isDebuging == false)
			{
				isDebuging = true;
			}
			else
			{
				isDebuging = false;
			}
			break;
		case EventKeyboard::KeyCode::KEY_R:
			if (isHeroEternalLife == false)
			{
				isHeroEternalLife = true;
			}
			else
			{
				isHeroEternalLife = false;
			}
			break;
		}
	}
}

void ClickerScene::checkKeyboardForDebug()
{
	if (HeroMM::getInstance()->isAlive == true && MonsterMM::getInstance()->isAlive == true && (button_state != LOCKED))
	{
		for (int i = 0; i < 4; i++)
		{
			switch (arrow_type[i])
			{
			case ArrowType::SET:
				changeSetArrowToDefault(i);

				//if (checkAllArrowIsDefault())
			//	{
					heroAttack(arrow_num);
				//}

				log("hit!");

				plusSkillGauge(2);

				i = 5;

				break;

			case ArrowType::WARNING:
				setWarningValueToDefaultValue();

				i = 5;

				break;
			}
		}
	}
}

void ClickerScene::createMonster()
{
	if (MonsterMM::getInstance()->monster_num == 9)
	{
		MonsterMM::getInstance()->monster_num = 0;
	}
	else
	{
		MonsterMM::getInstance()->monster_num = HeroMM::getInstance()->phase_for_announcement;
	}
	MonsterMM::getInstance()->isAlive = true;
	MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] = MonsterMM::getInstance()->max_hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num];
}

bool ClickerScene::criticalGamble(int _percent)
{
	srand((unsigned)time(NULL));

	int tmp_rand;

	tmp_rand = rand() % 101;

	if (tmp_rand <= _percent)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ClickerScene::monsterAttack(float dt)
{
	if (!isTutorial)
	{
		srand((unsigned)time(NULL));

		if (isMonsterStunned)
		{
			noticeCondition(TargetType::MONSTER, ConditionType::STUNNED);
		}
		else
		{
			if (criticalGamble(55))
			{
				spr_monster->runAction(seq_monster_critical_attack);

				log("monster critical attack!");
			}
			else
			{
				spr_monster->runAction(seq_monster_attack);
			}
		}
	}
}

void ClickerScene::heroAttack(int arrow_num)
{
	//SimpleAudioEngine::getInstance()->playEffect("sound/effect/EF_yellow_key.wav");
	AudioMM::getInstance()->runEffect("YELLOWKEY");

	giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg, false);
}

void ClickerScene::giveDamageTo(int type, float damage, bool isCritical)
{
	Label* label_damage = Label::create("", "", 48);
	label_damage->setString(StringUtils::format("-%d", static_cast<int>(damage)));
	label_damage->setPosition(-500, 0);
	this->addChild(label_damage, 3);

	MoveBy* moveby_damage = MoveBy::create(0.7f, Vec2(0, 150));
	FadeOut* fadeout_damage = FadeOut::create(0.7f);

	label_damage->runAction(Sequence::create(Spawn::create(moveby_damage->clone(), fadeout_damage->clone(), NULL),
											 CallFuncN::create([](Node* node) {node->removeFromParent(); }),
											 NULL));

	unsigned int temp = damage;

	unsigned int digit = 0;
	for (int i = 0; i < 10 && temp > 0; i++)
	{
		if (temp == 0)
			break;
		temp *= 0.1f;
		digit++;
	}

	switch (type)
	{
	case TargetType::HERO:
		if (MonsterMM::getInstance()->hp > 0)
		{
			if (isHeroEternalLife)
			{
				label_damage->setPosition(ptimer_hero_hp->getPosition() + Vec2(0, 30));

				label_damage->setString("불사!");
				label_damage->setColor(Color3B::YELLOW);
			}
			else
			{
				AudioMM::getInstance()->runEffect("HIT");

				spr_hero_hp_bar_back->runAction(damaged_bar->clone());
				ptimer_hero_hp->runAction(damaged_bar->clone());
				spr_hero_portrait_back->runAction(portrait_tint_red->clone());
				ptimer_skill_gauge->runAction(damaged_bar->clone());
				spr_skill_gauge_back->runAction(damaged_bar->clone());

				lab_hero_hp->runAction(damaged_bar->clone());

				if (isCritical)
				{
					HeroMM::getInstance()->hp -= static_cast<int>(damage) * 2;
					if (HeroMM::getInstance()->hp <= 1 && isDebuging == true)
					{
						HeroMM::getInstance()->hp = 1;
					}
					temp = damage * 2;
				}
				else
				{
					HeroMM::getInstance()->hp -= static_cast<int>(damage);
					if (HeroMM::getInstance()->hp <= 1 && isDebuging == true)
					{
						HeroMM::getInstance()->hp = 1;
					}
					temp = damage;
				}
				
				for (int i = 0; i < 10; i++)
				{
					spr_damage_hero[i] = Sprite::create();
					this->addChild(spr_damage_hero[i], 99);

					spr_damage_hero[i]->setTexture(StringUtils::format("fonts/Red_Font/%d.png", temp % 10));
					spr_damage_hero[i]->setPosition((720 * 0.5f - 23 - i * 23 + (digit - i) * 28), spr_monster->getPositionY());
					spr_damage_hero[i]->setColor(Color3B(209, 178, 255));

					spr_damage_hero[i]->runAction(Sequence::create(Spawn::create(moveby_damage->clone()->reverse(), fadeout_damage->clone(), NULL),
						CallFuncN::create([](Node* node) {node->removeFromParent(); }),
						NULL));

					spr_hit_monster = Sprite::create("fonts/Red_Font/hit.png");
					spr_hit_monster->setPosition(420, spr_damage_hero[0]->getPositionY() - 47);
					spr_hit_monster->setColor(Color3B(128, 65, 217));
					spr_hit_monster->runAction(Sequence::create(Spawn::create(moveby_damage->clone()->reverse(), fadeout_damage->clone(), NULL),
						CallFuncN::create([](Node* node) {node->removeFromParent(); }),
						NULL));
					spr_hit_monster->setScale(0.3f);
					this->addChild(spr_hit_monster, 100);

					if (temp == 0 && i != 0)
						spr_damage_hero[i]->setVisible(false);
					else
						spr_damage_hero[i]->setVisible(true);

					temp *= 0.1f;
				}
			}
		}
		break;
	case TargetType::MONSTER:

		runAnimation("Animation/Normal_Attack/", spr_monster->getPosition());

		temp = damage;
		for (int i = 0; i < 10; i++)
		{
			spr_damage_hero[i] = Sprite::create();
			this->addChild(spr_damage_hero[i], 99);

			spr_damage_hero[i]->setTexture(StringUtils::format("fonts/Red_Font/%d.png", temp % 10));
			spr_damage_hero[i]->setPosition(720 * 0.5f - 27 - i * 27 + (digit - i) * 27, spr_monster->getPositionY() + 100);
			spr_damage_hero[i]->setColor(Color3B(255, 228, 0));
			spr_damage_hero[i]->setScale(1.2f);

			spr_damage_hero[i]->runAction(Sequence::create(Spawn::create(moveby_damage->clone(), fadeout_damage->clone(), NULL),
															CallFuncN::create([](Node* node) {node->removeFromParent(); }),
															NULL));

			if (temp == 0 && i != 0)
				spr_damage_hero[i]->setVisible(false);
			else
				spr_damage_hero[i]->setVisible(true);

			temp *= 0.1f;
		}

		spr_hit_monster = Sprite::create("fonts/Red_Font/hit.png");
		spr_hit_monster->setPosition(300, spr_damage_hero[0]->getPositionY() + 47);
		spr_hit_monster->runAction(Sequence::create(Spawn::create(moveby_damage->clone(), fadeout_damage->clone(), NULL),
													CallFuncN::create([](Node* node) {node->removeFromParent(); }),
													NULL));
		spr_hit_monster->setColor(Color3B(255, 228, 0));
		spr_hit_monster->setScale(0.3f);
		this->addChild(spr_hit_monster, 100);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			portrait_tint_red->setTag(EFFECTTAG::PORTRAIT_TINT_RED);

			//spr_monster_portrait->runAction(portrait_tint_red);

			spr_monster_hp_bar_back->runAction(damaged_bar->clone());

			if (HeroMM::getInstance()->phase_for_announcement == 2)
			{
				spr_boss_portrait->runAction(damaged_bar->clone());
			}

			ptimer_monster_hp->runAction(damaged_bar->clone());

			spr_monster->runAction(monster_damaged->clone());

			lab_monster_name->runAction(damaged_bar->clone());
			lab_monster_hp->runAction(damaged_bar->clone());

		if (isCritical)
		{
			MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] -= static_cast<int>(damage) * 2;
		}
		else
		{
			MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] -= static_cast<int>(damage);
		}

		break;
	}
}

void ClickerScene::noticeCondition(int type, int condition)
{
	Vec2 vec2_label_position;

	switch (type)
	{
	case TargetType::HERO:
		vec2_label_position = ptimer_hero_hp->getPosition() + Vec2(0, 30);
		break;
	case TargetType::MONSTER:
		vec2_label_position = spr_monster->getPosition() + Vec2(-100, 100);
		break;
	default:
		break;
	}

	Label* label_condition = Label::create("", "", 48);
	label_condition->setPosition(vec2_label_position);
	this->addChild(label_condition, 3);

	MoveBy* moveby_stun = MoveBy::create(0.5f, Vec2(0, 100));
	FadeOut* fadeout_stun = FadeOut::create(0.5f);

	switch (condition)
	{
	case ConditionType::STUNNED:
		label_condition->setString("기절!");
		label_condition->setColor(Color3B::YELLOW);
		label_condition->setPosition(vec2_label_position + Vec2(100, 0));

		label_condition->runAction(Spawn::create(moveby_stun, fadeout_stun, NULL));
		break;
	case ConditionType::BURNNED:
		label_condition->setString("화상!");
		label_condition->setColor(Color3B::RED);

		MoveBy* moveby_damage = MoveBy::create(0.5f, Vec2(0, 100));
		FadeOut* fadeout_damage = FadeOut::create(0.5f);
		label_condition->runAction(Spawn::create(moveby_damage, fadeout_damage, NULL));
		break;
	}
}

bool ClickerScene::checkIsPlayerDodged()
{
	if (HeroMM::getInstance()->state == HeroMM::getInstance()->HeroState::DODGE)
	{
		return true;
	}
	else
	{

		return false;
	}
}

void ClickerScene::checkHp()
{
	if (HeroMM::getInstance()->hp <= 0)
	{
		clickerLose();
	}

	if (MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] <= 0)
	{
		clickerWin();
	}
}

void ClickerScene::checkPTimer()
{
	hero_hp_percent = float(float(HeroMM::getInstance()->hp) / float(HeroMM::getInstance()->max_hp) * 100);
	monster_hp_percent = float(float(MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num]) / float(MonsterMM::getInstance()->max_hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num]) * 100);

	ptimer_hero_hp->setPercentage(hero_hp_percent);
	ptimer_monster_hp->setPercentage(monster_hp_percent);
}

void ClickerScene::clickerWin()
{
	if (!isDebuging)
	{
		AudioMM::getInstance()->runEffect("DIEBOSS");

		MonsterMM::getInstance()->hp[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] = 0;
		MonsterMM::getInstance()->isAlive = false;
		
		offAllArrow();

		this->unschedule(schedule_selector(ClickerScene::monsterAttack));
		this->unscheduleUpdate();

		spr_monster->stopActionByTag(99);

		spr_monster->runAction(Sequence::create(FadeOut::create(2.0f),
												DelayTime::create(1.0f),
			CallFuncN::create([=](Node* node) {
												if (HeroMM::getInstance()->phase_for_announcement == 2)
												changeScene(SceneType::MAIN); 
												else
												{
													HeroMM::getInstance()->phase_for_announcement++;
													changeScene(SceneType::CLICKER);
												}}),
												NULL));
	}
}

void ClickerScene::clickerLose()
{
	if (!isDebuging)
	{
		AudioMM::getInstance()->runEffect("DIE");

		HeroMM::getInstance()->hp = 0;
		HeroMM::getInstance()->isAlive = false;

		menui_skill->setEnabled (false);

		offAllArrow();

		this->unschedule(schedule_selector(ClickerScene::monsterAttack));


		offAllArrow();

		this->unschedule(schedule_selector(ClickerScene::monsterAttack));
		this->unscheduleUpdate();

		spr_monster->stopActionByTag(99);

		spr_monster->runAction(Sequence::create(CallFuncN::create([=](Node* node) { spr_game_over->runAction(FadeIn::create(1.5f)); spr_game_over_back->setOpacity(180); }),
												DelayTime::create(2.5f),
			CallFuncN::create([=](Node* node) { changeScene(SceneType::GAMEOVER); }),
												NULL));
	}
}

void ClickerScene::changeScene(int _type)
{
	Scene* scene_block;
	Scene* scene_gameover;
	Scene* scene_main;
	Scene* scene_clicker;

	switch (_type)
	{
	case SceneType::BLOCKSLIDE:
		scene_block = TransitionFade::create(1.0f, BlockSlideGameScene::createScene());
		Director::getInstance()->replaceScene(scene_block);
		break;
	case SceneType::GAMEOVER:
		scene_gameover = TransitionFade::create(1.0f, GameOverScene::createScene());
		Director::getInstance()->replaceScene(scene_gameover);
		break;
	case SceneType::MAIN:
		scene_main = TransitionFade::create(1.0f, MenuScene::createScene());
		Director::getInstance()->replaceScene(scene_main);
		break;
	case SceneType::CLICKER:
		scene_clicker = TransitionFade::create(1.0f, ClickerScene::createScene());
		Director::getInstance()->replaceScene(scene_clicker);
		break;
	}
}

void ClickerScene::useSkill(int num)
{
	
}

void ClickerScene::noticeSkillNotEnabled()	
{
	spr_skill_not_enabled->stopAllActions();

	spr_skill_not_enabled->setVisible(true);

	spr_skill_not_enabled->runAction(fadein_shield);
	spr_skill_not_enabled->runAction(place_shield);

	spr_skill_not_enabled->runAction(move_shield);
	spr_skill_not_enabled->runAction(seq_shield);
}

void ClickerScene::offAllArrow()
{
	for (int i = 0; i < 4; i++)
	{
		spr_arrow[i]->setSpriteFrame(spr_arrow_default->getSpriteFrame());
		arrow_type[i] = ArrowType::DEFAULT;
	}
}

void ClickerScene::setLockVisible(int num)
{
	if (num == false)
	{
		spr_chain->setVisible(false);
		spr_lock->setVisible(false);
	}
	else if (num == true)
	{
		spr_chain->setVisible(true);
		spr_lock->setVisible(true);
	}
}

void ClickerScene::plusSkillGauge(int num)
{
	ptimer_skill_gauge->setPercentage(HeroMM::getInstance()->skill_gauge + num);
	//ptimer_skill_gauge->runAction(skill_gauge_up->clone());

	HeroMM::getInstance()->skill_gauge += num;
}

void ClickerScene::checkSkillGauge()
{
	if (static_cast<int>(ptimer_skill_gauge->getPercentage()) < 100)
	{
		if (isSkillEnable)
		{
			isSkillEnable = false;
		}
	}
	if (static_cast<int>(ptimer_skill_gauge->getPercentage()) >= 100)
	{
		spr_skill_gauge_on->setVisible(true);
		isSkillEnable = true;
	}
}

bool ClickerScene::isPlayerHPLow()
{
	if ((float)((float)HeroMM::getInstance()->hp / (float)HeroMM::getInstance()->max_hp) <= 0.3f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ClickerScene::changeSetArrowToDefault(int num)
{
	spr_arrow[num]->stopAllActions();
	spr_arrow[num]->setScale(1.0f);
	
	seq_change = Sequence::create(arrow_fade_big->clone(),
								  CallFunc::create([=] {arrow_type[num] = ArrowType::DEFAULT; }),
								  CallFunc::create([=] {spr_arrow[num]->setSpriteFrame(spr_arrow_default->getSpriteFrame());}),
								  NULL);

	spr_arrow[num]->runAction(seq_change);
}

void ClickerScene::setHeroData()
{
	HeroMM::getInstance()->hp = HeroMM::getInstance()->max_hp;
}

//스킬 관련 ////////////////////////////////////////////////////////////////////////////////////////

void ClickerScene::ruinFire()
{
	AudioMM::getInstance()->runEffect("SKILL1");

	stunTarget(TargetType::MONSTER, 3);
	giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 2.4f, true);

	runAnimation("Animation/Ruin_Fire/", spr_monster->getPosition());
}

void ClickerScene::ruinEye()
{
	AudioMM::getInstance()->runEffect("SKILL2");

	burnTarget(TargetType::MONSTER);
	this->runAction(Sequence::create(CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.6f, true); }),
									 DelayTime::create(0.125f),	
									 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.6f, true); }),
									 DelayTime::create(0.125f),
									 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.6f, true); }),
									 NULL));

	runAnimation("Animation/Ruin_Eye/", spr_monster->getPosition());
	
	Sprite* spr_thunder = Sprite::create("Animation/Ruin_Eye/lightning.png");
	spr_thunder->setPosition(spr_monster->getPosition());
	this->addChild(spr_thunder,98);

	spr_thunder->runAction(FadeOut::create(0.75f));
}

void ClickerScene::wailGust()
{
	AudioMM::getInstance()->runEffect("SKILL3");

	stunTarget(TargetType::MONSTER, 1);
	this->runAction(Sequence::create(CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 1.2f, true); }),
								 	 DelayTime::create(0.125f),
									 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 1.2f, true); }),
									 NULL));

	runAnimation("Animation/Wail_Gust/", spr_monster->getPosition());
}

void ClickerScene::eternalLife()
{
	AudioMM::getInstance()->runEffect("SKILL4");

	isHeroEternalLife = true;

	Sequence* seq_eternal = Sequence::create(DelayTime::create(3.0f), 
											 CallFunc::create([=] {isHeroEternalLife = false;}),
											 NULL);
	this->runAction(seq_eternal);
}

void ClickerScene::stunTarget(int type, int sec)
{
	noticeCondition(type, ConditionType::STUNNED);
	isMonsterStunned = true;

	Sequence* seq_stun = Sequence::create(DelayTime::create(static_cast<float>(sec)),
						 CallFunc::create([=] {isMonsterStunned = false; }),
					     NULL);

	Sequence* seq_stun_notice = Sequence::create(DelayTime::create(static_cast<float>(sec) / 3),
								CallFunc::create([=] {noticeCondition(type, ConditionType::STUNNED);}),
								DelayTime::create(static_cast<float>(sec) / 3),
								CallFunc::create([=] {noticeCondition(type, ConditionType::STUNNED); }),
								DelayTime::create(static_cast<float>(sec) / 3),
								CallFunc::create([=] {noticeCondition(type, ConditionType::STUNNED); }),
								NULL);

	this->runAction(seq_stun);
	this->runAction(seq_stun_notice);
}

void ClickerScene::burnTarget(int type)
{
	switch (type)
	{
	case TargetType::HERO:
		giveDamageTo(TargetType::HERO, MonsterMM::getInstance()->dmg[HeroMM::getInstance()->stage][MonsterMM::getInstance()->monster_num] * 0.2f, false);
		break;
	case TargetType::MONSTER:
		this->runAction(Sequence::create(DelayTime::create(1.0f),
										 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.2f, true); 	noticeCondition(type, ConditionType::BURNNED); }),
										 DelayTime::create(1.0f),
										 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.2f, false); noticeCondition(type, ConditionType::BURNNED); }),
										 DelayTime::create(1.0f),
										 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.2f, false); noticeCondition(type, ConditionType::BURNNED); }),
										 DelayTime::create(1.0f),
										 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.2f, false); noticeCondition(type, ConditionType::BURNNED); }),
										 DelayTime::create(1.0f),
										 CallFunc::create([=] {giveDamageTo(TargetType::MONSTER, HeroMM::getInstance()->dmg * 0.2f, false); noticeCondition(type, ConditionType::BURNNED); }),
										 NULL));
		break;
	}
}

Sprite* ClickerScene::runAnimation(const char * _path, const Vec2& position)
{
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.075f);

	for(size_t i = 1;; i ++)
	{
		Sprite* sprite = Sprite::create(StringUtils::format("%s%u.png", _path, i));
		if (sprite == nullptr)
		{
			break;
		}

		animation->addSpriteFrame(sprite->getSpriteFrame());
	}

	Sprite* sprite = Sprite::create();
	sprite->setPosition(position);
	sprite->runAction(Sequence::create(
		Animate::create(animation),
		CallFuncN::create([](Node* node)
		{
			node->removeFromParent();
		}), nullptr));

	this->addChild(sprite, 99);
	return sprite;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ClickerScene::pauseCallback(Ref * pSender)
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

	pause_layer->runAction(Sequence::create(DelayTime::create(0.25f), MoveTo::create(0, Vec2::ZERO), nullptr));

	this->setTouchEnabled(false);

	this->pauseSchedulerAndActions();

	spr_monster->pauseSchedulerAndActions();
	//spr_hero->pauseSchedulerAndActions();

	menui_skill->setEnabled(false);

	isGamePaused = true;
}

void ClickerScene::returnGameCallback(Ref * pSender)
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
	
	this->setTouchEnabled(true);

	this->resumeSchedulerAndActions();
	spr_monster->resumeSchedulerAndActions();
	//spr_hero->resumeSchedulerAndActions();
	
	this->scheduleUpdate();
	this->schedule(schedule_selector(ClickerScene::monsterAttack), 3.0f);

	isGamePaused = false;
}
 
void ClickerScene::goToMainCallback(Ref * pSender)
{
	setHeroData();

	auto scene_main = MenuScene::createScene();
	Director::getInstance()->replaceScene(scene_main);
}

void ClickerScene::toggleBackgroundCallback(Ref* pSender)
{
	AudioMM::getInstance()->changeBGMState();
	auto toggleItem = dynamic_cast<MenuItemToggle*>(pSender);
	if (toggleItem->getSelectedIndex() == 0)
	{
		log("Turn On BGM");
	}
	else if (toggleItem->getSelectedIndex() == 1)
	{
		log("Turn Off BGM");
	}
}

void ClickerScene::toggleEffectCallback(Ref* pSender)
{
	AudioMM::getInstance()->changeEffectState();
	auto toggleItem = dynamic_cast<MenuItemToggle*>(pSender);
	if (toggleItem->getSelectedIndex() == 0) 
	{
		log("Turn On FX");
	}
	else if (toggleItem->getSelectedIndex() == 1) 
	{
		log("Turn Off FX");
	}
}

void ClickerScene::changeButtonStateToSkillCallback(Ref * pSender)
{
	if (ptimer_skill_gauge->getPercentage() >= 100 && layer_skill->getPositionY() == -500)
	{
		layer_skill_back->setVisible(true);

		layer_skill->runAction(MoveBy::create(0.15f, Vec2(0, 500)));

		//this->setTouchEnabled(false);

		this->pauseSchedulerAndActions();

		spr_monster->pauseSchedulerAndActions();
		//spr_hero->pauseSchedulerAndActions();

		menui_skill->setEnabled(false);

		menui_pause->setEnabled(false);

		isGamePaused = true;
	}
}

void ClickerScene::closeSkillLayerCallback(Ref * pSender)
{
	spr_skill_gauge_on->setVisible(false);

	layer_skill_back->setVisible(false);

	layer_skill->runAction(MoveBy::create(0.15f, Vec2(0, -500)));

	this->setTouchEnabled(true);

	this->resumeSchedulerAndActions();
	spr_monster->resumeSchedulerAndActions();
	//spr_hero->resumeSchedulerAndActions();

	menui_pause->setEnabled(true);
	menui_skill->setEnabled(true);

	this->scheduleUpdate();
	this->schedule(schedule_selector(ClickerScene::monsterAttack), 3.0f);

	isGamePaused = false;

	this->setTouchEnabled(true);
}

void ClickerScene::useSkillCallback(int num)
{
	{
		AudioMM::getInstance()->runEffect("USESKILL");

		ptimer_skill_gauge->setPercentage(0.0f);
		HeroMM::getInstance()->skill_gauge = 0.0f;

		for (int i = 0; i < 4; i++)
		{
			spr_skill_icon[i]->setVisible(false);

			menui_use_skill[i]->setEnabled(false);
		}

		spr_skill_icon[num]->setVisible(true);
		spr_skill_icon[num]->runAction(SkillMM::getInstance()->seq_skill_icon->clone());
		spr_skill_use_panel->runAction(Sequence::create(SkillMM::getInstance()->seq_skill_use->clone(),
			CallFunc::create([=] {for (int i = 0; i < 4; i++) { spr_skill_icon[i]->setVisible(false); }; }),
			NULL));

		layer_skill->runAction(Sequence::create(DelayTime::create(1.550f),
			CallFunc::create([=] {closeSkillLayerCallback(0); }),
			DelayTime::create(0.2f),
			CallFunc::create([=]
		{
			switch (num)
			{
			case SkillName::RUINFIRE:
				ruinFire();
				log("skill ruin fire was used!");
				break;
			case SkillName::RUINEYE:
				ruinEye();
				log("skill ruin eye used!");
				break;
			case SkillName::WAILGUST:
				wailGust();
				log("skill wail gust used!");
				break;
			case SkillName::ETERNALLIFE:
				eternalLife();
				log("skill eternal life used!");
				break;
			default:
				log("undefined skill used!");
				break;
			}
		}),
			CallFunc::create([=] {for (int i = 0; i < 4; i++) { menui_use_skill[i]->setEnabled(true); }; }),
			NULL));
	}
}

void ClickerScene::menuSceneCallBack()
{
	auto scene_main = MenuScene::createScene();
	Director::getInstance()->replaceScene(scene_main);
}

void ClickerScene::endingSceneCallBack()
{
	auto scene_main = EndingtScene::createScene();
	Director::getInstance()->replaceScene(scene_main);
}

