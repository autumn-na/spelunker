#pragma execution_character_set("utf-8")

#include "ending.h"



Scene* EndingtScene::createScene()
{
	auto scene = Scene::create();

	auto layer = EndingtScene::create();

	scene->addChild(layer);

	return scene;
}


bool EndingtScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visible = Director::getInstance()->getVisibleSize();

	ending_layer = Layer::create();
	ending_layer->setPosition(Vec2::ZERO);
	ending_layer->setVisible(false);
	this->addChild(ending_layer, 5);






	auto backgrundmap = Sprite::create("loding.png");
	backgrundmap->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f );
	backgrundmap->setScale(1);
	this->addChild(backgrundmap, 0);

Size windowSize = Director::getInstance()->getWinSize();









//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 




auto daey = DelayTime::create(1);


	

	auto label = Label::createWithSystemFont("기획 정민석", "", 80);

	/*auto actqieonTo = MoveTo::create(5, Point(0, -2750));*/

	auto  actqeieonTo = MoveTo::create(5.f, Point(360, 300));

	auto seequce = Sequence::create(daey, actqeieonTo, FadeOut::create(3), nullptr);

	label->runAction(seequce->clone());

	label->setPosition(1600, 2600);

	label->setColor(Color3B::BLACK);

	this->addChild(label, 10);


	




	spr_chang_layer = Sprite::create("downloadfile.jpg"); 

	auto  action_0 = MoveTo::create(5.f, Point(360, 800));

	auto sequence = Sequence::create(daey,action_0, FadeOut::create(3), nullptr);

	spr_chang_layer->runAction(sequence->clone());

	spr_chang_layer->setPosition(1600, 2600);

	spr_chang_layer->setScale(1);

	this->addChild(spr_chang_layer, 10);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto delaey = DelayTime::create(6);


	auto label1 = Label::createWithSystemFont("프로그래머 정윤환", "", 80);

	auto  actqeonTo = MoveTo::create(5.f, Point(360, 300));

	auto seeuce = Sequence::create(delaey, actqeonTo, FadeOut::create(3), nullptr);

	label1->runAction(seeuce->clone());

	label1->setPosition(1600, 2600);

	label1->setColor(Color3B::BLACK);

	this->addChild(label1, 10);





spr_yun_layer = Sprite::create("KakaoTalk_20170207_133400449.jpg"); 

	auto  action21 = MoveTo::create(5.f, Point(360, 800));

	   auto sequence1 = Sequence::create(delaey, action21, FadeOut::create(3), nullptr);

		spr_yun_layer->runAction(sequence1->clone());

		spr_yun_layer->setPosition(1600, 2600);
		
		spr_yun_layer->setScale(0.5);
		
		this->addChild(spr_yun_layer, 10);






		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





		auto delaey1 = DelayTime::create(11);


		auto label2 = Label::createWithSystemFont("프로그래머 최태호", "", 80);

		auto  actqeonTo1 = MoveTo::create(5.f, Point(360, 300));

		auto seeuce1 = Sequence::create(delaey1, actqeonTo1, FadeOut::create(3), nullptr);

		label2->runAction(seeuce1->clone());

		label2->setPosition(1600, 2600);

		label2->setColor(Color3B::BLACK);

		this->addChild(label2, 10);





		spr_taho_layer = Sprite::create("KakaoTalk_20170207_132542393.png"); 

		auto  action22 = MoveTo::create(5.f, Point(360, 800));

		auto sequence2 = Sequence::create(delaey1, action22, FadeOut::create(3), nullptr);

		spr_taho_layer->runAction(sequence2->clone());

		spr_taho_layer->setPosition(1600, 2600);

		spr_taho_layer->setScale(0.8);

		this->addChild(spr_taho_layer, 10);




		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		auto delaey2 = DelayTime::create(16);


		auto label3 = Label::createWithSystemFont("프로그래머 장석천", "", 80);

		auto  actqeonTo2 = MoveTo::create(5.f, Point(360, 300));

		auto seeuce2 = Sequence::create(delaey2, actqeonTo2, FadeOut::create(3), nullptr);

		label3->runAction(seeuce2->clone());

		label3->setPosition(1600, 2600);

		label3->setColor(Color3B::BLACK);

		this->addChild(label3, 10);





		spr_taho_layer = Sprite::create("naver_com_20170210_1337194.png"); 

		auto  action23 = MoveTo::create(5.f, Point(360, 800));

		auto sequence3 = Sequence::create(delaey2, action23, FadeOut::create(3), nullptr);

		spr_taho_layer->runAction(sequence3->clone());

		spr_taho_layer->setPosition(1600, 2600);

		spr_taho_layer->setScale(1);

		this->addChild(spr_taho_layer, 10);



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		auto delaey3 = DelayTime::create(21);


		auto label4 = Label::createWithSystemFont("프로그래머 나민형", "", 80);

		auto  actqeonTo3 = MoveTo::create(5.f, Point(360, 300));

		auto seeuce3 = Sequence::create(delaey3, actqeonTo3, FadeOut::create(3), nullptr);

		label4->runAction(seeuce3->clone());

		label4->setPosition(1600, 2400);

		label4->setColor(Color3B::BLACK);

		this->addChild(label4, 10);





		spr_pak_layer = Sprite::create("externalFile.jpg"); 

		auto  action24 = MoveTo::create(5.f, Point(360, 800));

		auto sequence4 = Sequence::create(delaey3, action24, FadeOut::create(3), nullptr);

		spr_pak_layer->runAction(sequence4->clone());

		spr_pak_layer->setPosition(1600, 2600);

		spr_pak_layer->setScale(0.8);

		this->addChild(spr_pak_layer, 10);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		auto delaey4 = DelayTime::create(26);


		auto label5 = Label::createWithSystemFont("그래픽 박찬영", "", 80);

		auto  actqeonTo4 = MoveTo::create(5.f, Point(360, 300));

		auto seeuce4 = Sequence::create(delaey4, actqeonTo4, FadeOut::create(3), nullptr);

		label5->runAction(seeuce4->clone());

		label5->setPosition(1600, 2600);

		label5->setColor(Color3B::BLACK);

		this->addChild(label5, 10);





		spr_Chung_layer = Sprite::create("3erfwer.jpg");

		auto  action25 = MoveTo::create(5.f, Point(360, 800));

		auto sequence5 = Sequence::create(delaey4, action25, FadeOut::create(3), nullptr);

		spr_Chung_layer->runAction(sequence5->clone());

		spr_Chung_layer->setPosition(1600, 2600);

		spr_Chung_layer->setScale(0.5);

		this->addChild(spr_Chung_layer, 10);








	auto delaey5 = DelayTime::create(34);

	


		auto label6 = Label::createWithSystemFont(" 여섯명이 한조", "fonts/arial.ttf", 100);

		label6->setBMFontSize(100);

		auto  actqeonTo5 = MoveBy::create(3.f, Point(0, -2750));

		auto seeuce5 = Sequence::create(delaey5, actqeonTo5,  nullptr);

		label6->runAction(seeuce5->clone());

		label6->setPosition(360, 3000);

		label6->setColor(Color3B::BLACK);

		this->addChild(label6, 12);




		


		auto spyer = Sprite::create("KakaoTalk_20170205_161426607.png");

		auto  action26 = MoveBy::create(3.f, Point(0, 3200));

		auto sequence6 = Sequence::create(delaey5, action26, nullptr);

		spyer->runAction(sequence6->clone());

		spyer->setPosition(360, -2400);

		spyer->setScale(0.52);

		this->addChild(spyer, 10);

		 
auto sprite341 = Sprite::create("treasure_layer_01.png");
		auto  actqeonT5 = MoveTo::create(0.f, Point(360, 800));
		auto seeuce25 = Sequence::create(delaey5, actqeonT5, nullptr);
		sprite341->runAction(seeuce25->clone());
		sprite341->setPosition(1600, 2600);
		sprite341->setScale(2);
		this->addChild(sprite341, 9);


//	// 1 초 안에 스프라이트에 페이드 인합니다.
//	auto fadeIn = FadeIn::create(1.0f);
//	label5->runAction(fadeIn);
//
//	 2 초 후에 스프라이트를 페이드 아웃합니다.
//	auto fadeOut = FadeOut::create(3);
//	label5->runAction(fadeOut);
//
//
//	auto sequence5 = Sequence::create(delay5, action_0, FadeOut::create(0), nullptr);
//	
//	spr_Chung_layer = Sprite::create("KakaoTalk_20170207_132542393.png");
//	
//	auto action_5 = MoveTo::create(5, Point(00, - 1900));
//	
//	spr_Chung_layer->runAction(sequence5->clone());
//	
//	spr_Chung_layer->setPosition(360, 2400);
//	
//	spr_Chung_layer->setScale(0.25);
//	
//	this->addChild(spr_Chung_layer, 1);
	






	//spr_backgruond_layer = Sprite::create("treasure_store_background.png");
	//spr_backgruond_layer->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);
	//spr_backgruond_layer->setScale(1.5);
	//this->addChild(spr_backgruond_layer, 0);
	//




	auto home_button = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(EndingtScene::HomeButton, this)); //홈버튼tg
	home_button->setPosition(visible.width - 75, visible.height - 60);
	home_button->setScale(0.5f);
	






	auto menu = Menu::create(home_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 10);














	return true;
}












void EndingtScene::change(float dt)
{
	/*Scene * scene = TransitionFade::create(3.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);*/

}

void EndingtScene::HomeButton()
{

	//Scene * scene = TransitionFade::create(1.0f, EndingtScene::createScene());  //메인메뉴 씬으로 이동
	//Director::getInstance()->replaceScene(scene);


	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());  //메인메뉴 씬으로 이동
	Director::getInstance()->replaceScene(scene);
}

