#pragma execution_character_set("utf-8")

#include "GameOverScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "HeroManagement.h"
#include "AudioManagement.h"

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initSprite();	
	initMenu();	
	initLabel();

	showScore();

	AudioMM::getInstance()->runBGM("GAMEOVER");


	return true;
}

void GameOverScene::initLabel()
{
	lab_res_got = Label::create("", "", 48);
	lab_res_got->setPosition(360, 400);
	lab_res_got->setColor(Color3B::WHITE);
	lab_res_got->runAction(FadeOut::create(0.0f));
	this->addChild(lab_res_got, 9999);
	lab_res_got->setString(StringUtils::format("Gem : %d", HeroMM::getInstance()->res_get));
}

void GameOverScene::initSprite()
{
	//spr_game_over = Sprite::create("game_over.png");
	//spr_game_over->setPosition(360, 900);
	//this->addChild(spr_game_over, 1);

	spr_score_line = Sprite::create("score_line.png");
	spr_score_line->setPosition(360, 600);
	spr_score_line->runAction(FadeOut::create(0.0f));
	this->addChild(spr_score_line, 1);
}

void GameOverScene::initMenu()
{
	menui_home = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_1(GameOverScene::goToMainCallback, this));
	menui_home->setPosition(360, 100);

	menu_gameover = Menu::create(menui_home, NULL);
	menu_gameover->setPosition(Vec2::ZERO);
	this->addChild(menu_gameover, 2);
}

void GameOverScene::showScore()
{
	Sequence* seq_show_score = Sequence::create(//CallFuncN::create([=](Node* node) {spr_game_over->runAction(FadeOut::create(2.5f)); }),
												DelayTime::create(0.7f),
												CallFuncN::create([=](Node* node) {spr_score_line->runAction(FadeIn::create(0));  
																				   lab_res_got->runAction(FadeIn::create(0)); 
																				   runAnimation("Animation/Pop_Score/", Vec2(360, 900)); }),
												NULL);

	this->runAction(seq_show_score);
}

void GameOverScene::setHeroData()
{
	HeroMM::getInstance()->hp = HeroMM::getInstance()->max_hp;
	HeroMM::getInstance()->skill_gauge = 0;
	HeroMM::getInstance()->exp_got = 0;
	HeroMM::getInstance()->res_get = 0;
}

void GameOverScene::goToMainCallback(Ref * pSender)
{
	HeroMM::getInstance()->res_total += HeroMM::getInstance()->res_get;
	setHeroData();
	Scene * scene_main = MenuScene::createScene();
	Director::getInstance()->replaceScene(scene_main);
}

Sprite * GameOverScene::runAnimation(const char * _path, const Vec2 & position)
{
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.125f);

		for (size_t i = 1;; i++)
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
		sprite->runAction(Animate::create(animation));

		this->addChild(sprite, 99);
		return sprite;
}
