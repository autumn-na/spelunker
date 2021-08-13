#include "Start.h"
#include "AudioManagement.h"

Scene* StrartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StrartScene::create();

	scene->addChild(layer);

	return scene;
}


bool StrartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/BGM_title.wav");

	auto visible = Director::getInstance()->getVisibleSize();

	eve_layer = Layer::create();                                                     
	eve_layer->setPosition(Vec2::ZERO);
	eve_layer->setVisible(false);
	this->addChild(eve_layer, 5);




	Size windowSize = Director::getInstance()->getWinSize();

		auto label = Label::createWithSystemFont("여섯명이 한조","", 50);

		label->setPosition(400, 250);

		label->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60 - 150);

		label->setColor(Color3B::BLACK);
		label->setVisible(false);
		label->runAction(FadeOut::create(0.0f));



		this->addChild(label,10);


auto eeve_layer = Sprite::create("treasure_layer_01.png");
	eeve_layer->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);
	eeve_layer->setScale(1.5);
	this->addChild(eeve_layer, 0);


	auto evee_layer = Sprite::create("KakaoTalk_20170205_161426607.png");
	evee_layer->setPosition(visible.width * 0.5f, visible.height * 0.5f + 200 );
	evee_layer->setScale(0.3);
	evee_layer->runAction(FadeOut::create(0.0f));
	this->addChild(evee_layer, 0);
	evee_layer->setVisible(false);
	eve_layer = false;


	Sprite* spr_title = Sprite::create("title.png");
	spr_title->setPosition(360, 640);
	spr_title->runAction(FadeOut::create(0.0f));
	spr_title->setVisible(false);
	this->addChild(spr_title, 1);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* title = Sprite::create("titleScene.png");
	title->setVisible(false);
	title->setPosition(visibleSize * 0.5f);
	this->addChild(title, 5);


	abcdef = false;

	spr_title->runAction(Sequence::create(
											CallFuncN::create([=](Node* node) {evee_layer->setVisible(true); label->setVisible(true); }),
											DelayTime::create(0.5f),
											CallFuncN::create([=](Node* node) {evee_layer->runAction(FadeIn::create(0.8f)); label->runAction(FadeIn::create(0.8f)); }),
											DelayTime::create(1.25f),
											CallFuncN::create([=](Node* node) {evee_layer->runAction(FadeOut::create(0.8f)); label->runAction(FadeOut::create(0.8f)); spr_title->setVisible(true); }),
											DelayTime::create(1.5f),
											FadeIn::create(1.25f),
											DelayTime::create(1.5f),
						CallFuncN::create([=](Node* node) { title->setVisible(true); abcdef = true; }),
											FadeOut::create(1.25f),
											NULL));


	//this->schedule(schedule_selector(StrartScene::change, this), 1);
	
	
	return true;
}

void StrartScene::change()
{
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());

	Director::getInstance()->replaceScene(scene);
}

bool StrartScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	if (abcdef == true)
	{
		Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());

		Director::getInstance()->replaceScene(scene);
	}
	return true;
}