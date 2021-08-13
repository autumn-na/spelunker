#include "TreasureStoreScene.h"
#include "TreasureDeck.h"
#include "AudioManagement.h"

Scene* TreasureStoreScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TreasureStoreScene::create();

	scene->addChild(layer);

	return scene;
}

bool TreasureStoreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitUpdaaLayer();
	InitUpdataLayer();
	InitUPLayer();
	InitBuyLayer();
	InitOpenLayer();
	InitUILayer();
	InitOpenLayere();

	Sprite* background = Sprite::create("treasure_layer_01.png");
	background->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f - 60);
	background->setScale(1.02);
	this->addChild(background, 0);



	operwher_layer = Layer::create();
	operwher_layer->setPosition(Vec2::ZERO);
	operwher_layer->setVisible(false);
	this->addChild(operwher_layer, 1);
	

	spr_background = Sprite::create("treasure_store_background.png");
	spr_background->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f - 24);
	spr_background->setScale(1.02);
	this->addChild(spr_background, 0);



	update_layer_bool = false;
	up_layer_bool = false;

	return true;
}





//보물 애니메이션
void TreasureStoreScene::IpenLayer()
{



	auto yspr_treasure_layer_5 = Sprite::create("treasure_layer_02.png");
	yspr_treasure_layer_5->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 40 - 60);  //보물획득 이미지t
	operwher_layer->addChild(yspr_treasure_layer_5, 1);
	yspr_treasure_layer_5->setScale(1);

	/*visible.width * 0.5f, visible.height * 0.5f - 60*/
	//에니메이션
	auto progress_player = Sprite::create("Animation/Open_Box/pit_01.png");
	progress_player->setPosition(360, 600);//visible.width * 0.5f + (((static_cast<float>(HeroMM::getInstance()->progress_percent) / static_cast<float>(whole)) - 0.5f) * 640) + 5, visible.height - 50);
	this->addChild(progress_player, 4);

	Animation * player_animation = Animation::create();
	player_animation->setDelayPerUnit(0.3f);
	for (int i = 1; i < 11; i++)
	{
		player_animation->addSpriteFrame(SpriteFrame::create(StringUtils::format("Animation/Open_Box/pit_0%d.png", i), Rect(0, 0, 740, 760)));
	}
	progress_player->runAction(Animate::create(player_animation));
	/*(::create RepeatForever*/
	progress_player->setScale(1);
	//애니메이션 끝


	auto anter_button = MenuItemImage::create("anter.png", "anter.png", CC_CALLBACK_0(TreasureStoreScene::TreasureOpenSceneButton, this));
	anter_button->setPosition(visibleSize.width * 0.5f, 120 - 50);
	auto menu = Menu::create(anter_button, NULL);
	menu->setPosition(Vec2::ZERO);
	operwher_layer->addChild(menu, 6);
	anter_button->setScale(1.4);


}






//헹템 만들화면 뛰우기
void TreasureStoreScene::InitOpenLayere()
{
	orepen_layer = Layer::create();
	orepen_layer->setPosition(Vec2::ZERO);
	orepen_layer->setVisible(false);
	this->addChild(orepen_layer, 10);



	Size windowSize = Director::getInstance()->getWinSize();

	treaName = Label::createWithSystemFont("깨진 팬던트", "", 50);

	treaName->setPosition( 440 , 860);

	treaName->setColor(Color3B::WHITE);

	orepen_layer->addChild(treaName, 10);


	treaText = Label::createWithSystemFont("스킬 쿨타임 감소 5%", "", 50);


	treaText->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 40 - 120);

	treaText->setColor(Color3B::WHITE);



	orepen_layer->addChild(treaText, 10);



	spr_treasure_layer_5 = Sprite::create("skillpopup.png");
	spr_treasure_layer_5->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f + 40 - 60);  //보물획득 이미지t
	orepen_layer->addChild(spr_treasure_layer_5, 2);
	spr_treasure_layer_5->setScale(2.);

	spr_open_box = Sprite::create("Animation/Open_Box/pit_10.png");
	spr_open_box->setPosition(visibleSize.width * 0.5f - 190, visibleSize.height * 0.5f + 100 + 120);   //보물상자 오픈 이미지t
	orepen_layer->addChild(spr_open_box, 2);
	spr_open_box->setScale(1);


	auto anter_buttoon = MenuItemImage::create("delete.png", "delete.png", CC_CALLBACK_0(TreasureStoreScene::luck, this));
	anter_buttoon->setPosition(visibleSize.width * 0.5f + 260, 940);
	auto menu = Menu::create(anter_buttoon, NULL);
	menu->setPosition(Vec2::ZERO);
	orepen_layer->addChild(menu, 2);
	anter_buttoon->setScale(1.4);

}



void TreasureStoreScene::InitBuyLayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	buy_layer = Layer::create();
	
	buy_layer->setPosition(Vec2::ZERO);
	this->addChild(buy_layer, 1);

	spr_treasure_layer_2 = Sprite::create("treasure_layer_02.png");
	spr_treasure_layer_2->setPosition(visible.width * 0.5f, visible.height * 0.5f + 40 - 60);
	spr_treasure_layer_2->setScale(1.);
	buy_layer->addChild(spr_treasure_layer_2, 2);

	treasure_buttoncase = Sprite::create("treasure_buttoncase.png");
	treasure_buttoncase->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	treasure_buttoncase->setScale(1.);
	buy_layer->addChild(treasure_buttoncase, 2);

	 treasure_buttoncase_02 = Sprite::create("treasure_buttoncase_02.png");
	treasure_buttoncase_02->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	treasure_buttoncase_02->setScale(1.);
	buy_layer->addChild(treasure_buttoncase_02, 2);

	auto treasure_buttoncase_03 = Sprite::create("treasure_buttoncase_03.png");
	treasure_buttoncase_03->setPosition(visible.width * 0.5f, visible.height * 0.5f + 300);
	treasure_buttoncase_03->setScale(1.);
	buy_layer->addChild(treasure_buttoncase_03, 2);

	spr_collection = Sprite::create("treasure_text_collection.png");
	spr_collection->setPosition(visible.width * 0.5f, visible.height * 0.5f + 485);
	spr_collection->setScale(1.);
	buy_layer->addChild(spr_collection, 2);

	spr_open_text_case = Sprite::create("treasure_textcase.png");
	spr_open_text_case->setPosition(visible.width * 0.5f, visible.height * 0.5f - 320 - 60);
	spr_open_text_case->setScale(1.);
	buy_layer->addChild(spr_open_text_case, 3);

	auto treasure_collection_text_button1 = MenuItemImage::create("treasure_text_collection_02_off.png", "treasure_text_collection_02.png", CC_CALLBACK_0(TreasureStoreScene::Button, this)); //창바꾸는 버튼 -> Button으로 이동t
	treasure_collection_text_button1->setPosition(visible.width * 0.5f + 140, 1020);

	spr_open_text = Sprite::create("treasure_text_touchbox.png");
	spr_open_text->setPosition(visible.width * 0.5f, visible.height * 0.5f - 320 - 60);
	spr_open_text->setScale(1.);
	buy_layer->addChild(spr_open_text, 3);

	auto treasure_box = MenuItemImage::create("treasure_iconbutton_box.png", "treasure_iconbutton_box.png", CC_CALLBACK_0(TreasureStoreScene::TrpennButton, this));
	treasure_box->setPosition(visible.width * 0.5f,600 - 60);
	auto mernu = Menu::create(treasure_box, NULL);
	mernu->setPosition(Vec2::ZERO);
	buy_layer->addChild(mernu, 3);
	treasure_box->setScale(1.2);

	auto treasure_open_text_button3 = MenuItemImage::create("treasure_text_treasure.png", "treasure_text_treasure_off.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this)); //창바꾸는 버튼 -> Button으로 이동
	treasure_open_text_button3->setPosition(visible.width * 0.5f - 140, 1020);

	auto dio = Menu::create(treasure_collection_text_button1, treasure_open_text_button3, NULL);
	dio->setPosition(Vec2::ZERO);
	buy_layer->addChild(dio, 10);

}

//콜렉션화면
void TreasureStoreScene::InitUpdataLayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	left_layer = Layer::create();                                                      // 강화창 레이어 제작
	left_layer->setPosition(Vec2::ZERO);
	left_layer->setVisible(false);
	this->addChild(left_layer, 5);

	spr_treasure_layer_3 = Sprite::create("treasure_layer_01.png");
	spr_treasure_layer_3->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);
	spr_treasure_layer_3->setScale(1.02);
	left_layer->addChild(spr_treasure_layer_3, 1);

	spr_treasure_layer_4 = Sprite::create("treasure_layer_02.png");
	spr_treasure_layer_4->setPosition(visible.width * 0.5f, visible.height * 0.5f + 40 - 60);
	spr_treasure_layer_4->setScale(1.);
	left_layer->addChild(spr_treasure_layer_4, 2);

	spr_button_case = Sprite::create("treasure_buttoncase.png");
	spr_button_case->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case->setScale(1.);
	left_layer->addChild(spr_button_case, 2);


	spr_button_case2 = Sprite::create("treasure_buttoncase_02.png");
	spr_button_case2->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case2->setScale(1.);
	left_layer->addChild(spr_button_case2, 2);

	spr_button_case3 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case3->setPosition(visible.width * 0.5f, visible.height * 0.5f + 300);
	spr_button_case3->setScale(1.);
	left_layer->addChild(spr_button_case3, 2);



	//컬렉션 화면 에서 컬렉션 버튼 on,off
	auto treasure_collection_text_button = MenuItemImage::create("treasure_text_collection_02.png", "treasure_text_collection_02_off.png", CC_CALLBACK_0(TreasureStoreScene::T4yrButton, this));
	treasure_collection_text_button->setPosition(visible.width * 0.5f + 140, 1020);
	/*treasure_collection_text->setRotation(180);*/


	//컬렉션 화면 에서 텍스트 버튼 off,on
	auto treasure_open_text_button = MenuItemImage::create("treasure_text_treasure_off.png", "treasure_text_treasure.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this));
	treasure_open_text_button->setPosition(visible.width * 0.5f - 140, 1020);


	spr_button_case4 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case4->setPosition(visible.width * 0.5f + 140, 1020);
	spr_button_case4->setScale(1.);
	left_layer->addChild(spr_button_case4);






	auto text = Menu::create(treasure_collection_text_button, treasure_open_text_button, NULL);
	text->setPosition(Vec2::ZERO);
	left_layer->addChild(text, 19);

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			auto inventory = MenuItemImage::create("treasure_itemcase_02.png", "treasure_itemcase_02.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this)); //창바꾸는 버튼 -> Button으로 이동
			inventory->setPosition(140 + (x * 108), 860 - (y * 140));
			text->addChild(inventory);
		}
	}



	
}






//콜렉션화면2
void TreasureStoreScene::InitUpdaaLayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	coll_layer = Layer::create();                                                      // 강화창 레이어 제작
	coll_layer->setPosition(Vec2::ZERO);
	coll_layer->setVisible(false);
	this->addChild(coll_layer, 5);

	spr_collection = Sprite::create("treasure_text_collection.png");
	spr_collection->setPosition(visible.width * 0.5f, visible.height * 0.5f + 485);
	spr_collection->setScale(1.);
	coll_layer->addChild(spr_collection, 2);

	spr_treasure_layer_3 = Sprite::create("treasure_layer_01.png");
	spr_treasure_layer_3->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);
	spr_treasure_layer_3->setScale(1.02);
	coll_layer->addChild(spr_treasure_layer_3, 1);

	spr_treasure_layer_4 = Sprite::create("treasure_layer_02.png");
	spr_treasure_layer_4->setPosition(visible.width * 0.5f, visible.height * 0.5f + 40 - 60);
	spr_treasure_layer_4->setScale(1.);
	coll_layer->addChild(spr_treasure_layer_4, 2);

	spr_button_case = Sprite::create("treasure_buttoncase.png");
	spr_button_case->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case->setScale(1.);
	coll_layer->addChild(spr_button_case, 2);


	spr_button_case2 = Sprite::create("treasure_buttoncase_02.png");
	spr_button_case2->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case2->setScale(1.);
	coll_layer->addChild(spr_button_case2, 2);

	spr_button_case3 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case3->setPosition(visible.width * 0.5f, visible.height * 0.5f + 300);
	spr_button_case3->setScale(1.);
	coll_layer->addChild(spr_button_case3, 2);

	auto exit_button2 = MenuItemImage::create("treasure_button_exit.png", "treasure_button_exit.png", CC_CALLBACK_0(TreasureStoreScene::TreasureOpennButton, this));
	exit_button2->setPosition(visible.width * 0.5f, 120 - 50);
	auto menu = Menu::create(exit_button2, NULL);
	menu->setPosition(Vec2::ZERO);
	coll_layer->addChild(menu, 2);
	exit_button2->setScale(1.2);

	auto exit_buttton2 = MenuItemImage::create("pit_10.png", "pit_10.png", CC_CALLBACK_0(TreasureStoreScene::T4yrButtonn, this));
	exit_buttton2->setPosition(140, 860);
	auto mendiu = Menu::create(exit_buttton2, NULL);
	mendiu->setPosition(Vec2::ZERO);
	coll_layer->addChild(mendiu, 50);
	exit_buttton2->setScale(0.25);


	//컬렉션 화면 에서 컬렉션 버튼 on,off
	auto treasure_collection_text_button = MenuItemImage::create("treasure_text_collection_02.png", "treasure_text_collection_02_off.png", CC_CALLBACK_0(TreasureStoreScene::T4yrButton, this));
	treasure_collection_text_button->setPosition(visible.width * 0.5f + 140, 1020);
	/*treasure_collection_text->setRotation(180);*/


	//컬렉션 화면 에서 텍스트 버튼 off,on
	auto treasure_open_text_button = MenuItemImage::create("treasure_text_treasure_off.png", "treasure_text_treasure.png", CC_CALLBACK_0(TreasureStoreScene::TreasureOpenSceneButton, this));
	treasure_open_text_button->setPosition(visible.width * 0.5f - 140, 1020);


	spr_button_case4 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case4->setPosition(visible.width * 0.5f + 140, 1020);
	spr_button_case4->setScale(1.);
	coll_layer->addChild(spr_button_case4);






	auto text = Menu::create(treasure_collection_text_button, treasure_open_text_button, NULL);
	text->setPosition(Vec2::ZERO);
	coll_layer->addChild(text, 19);

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			inventory[y][x] = MenuItemImage::create("treasure_itemcase_02.png", "treasure_itemcase_02.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this)); //창바꾸는 버튼 -> Button으로 이동
			inventory[y][x]->setPosition(140 + (x * 108), 860 - (y * 140));
			text->addChild(inventory[y][x]);
		}
	}
}









//새로운 페이지 완전 새로움
void TreasureStoreScene::InitUPLayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	right_layer = Layer::create();                  // 강화창 레이어 제작
	right_layer->setPosition(Vec2::ZERO);
	right_layer->setVisible(false);
	this->addChild(right_layer, 6);


	spr_collection = Sprite::create("treasure_text_collection.png");
	spr_collection->setPosition(visible.width * 0.5f, visible.height * 0.5f + 485);
	spr_collection->setScale(1.);
	right_layer->addChild(spr_collection, 2);

	spr_treasure_layer_3 = Sprite::create("treasure_layer_01.png");
	spr_treasure_layer_3->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);
	spr_treasure_layer_3->setScale(1.02);
	right_layer->addChild(spr_treasure_layer_3, 1);

	spr_treasure_layer_4 = Sprite::create("treasure_layer_02.png");
	spr_treasure_layer_4->setPosition(visible.width * 0.5f, visible.height * 0.5f + 40 - 60);
	spr_treasure_layer_4->setScale(1.);
	right_layer->addChild(spr_treasure_layer_4, 2);

	spr_button_case = Sprite::create("treasure_buttoncase.png");
	spr_button_case->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case->setScale(1.);
	right_layer->addChild(spr_button_case, 2);



	spr_button_case2 = Sprite::create("treasure_buttoncase_02.png");
	spr_button_case2->setPosition(visible.width * 0.5f, visible.height * 0.5f + 375);
	spr_button_case2->setScale(1.);
	right_layer->addChild(spr_button_case2, 2);

	spr_button_case3 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case3->setPosition(visible.width * 0.5f, visible.height * 0.5f + 300);
	spr_button_case3->setScale(1.);
	right_layer->addChild(spr_button_case3, 2);

	auto exit_button2 = MenuItemImage::create("treasure_button_exit.png", "treasure_button_exit.png", CC_CALLBACK_0(TreasureStoreScene::TreasureOpennButton, this));
	exit_button2->setPosition(visible.width * 0.5f, 120 - 50);
	auto menu = Menu::create(exit_button2, NULL);
	menu->setPosition(Vec2::ZERO);
	right_layer->addChild(menu, 2);
	exit_button2->setScale(1.2);

	spr_open_text_case = Sprite::create("treasure_textcase.png");
	spr_open_text_case->setPosition(visible.width * 0.5f, visible.height * 0.5f - 320 - 60);
	spr_open_text_case->setScale(1.);
	right_layer->addChild(spr_open_text_case, 3);

	spr_open_text = Sprite::create("treasure_text_touchbox.png");
	spr_open_text->setPosition(visible.width * 0.5f, visible.height * 0.5f - 320 - 60);
	spr_open_text->setScale(1.);
	right_layer->addChild(spr_open_text, 3);


	auto treasure_opewn_text_button = MenuItemImage::create("treasure_iconbutton_box.png", "treasure_iconbutton_box.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this)); //창바꾸는 버튼 -> Button으로 이동
	treasure_opewn_text_button->setPosition(visible.width * 0.5f, 600 - 60);
	treasure_opewn_text_button->setScale(1.2);

	auto treasure_collection_text_button = MenuItemImage::create("treasure_text_collection_02_off.png", "treasure_text_collection_02.png", CC_CALLBACK_0(TreasureStoreScene::T4yreButtonn, this)); //창바꾸는 버튼 -> Button으로 이동
	treasure_collection_text_button->setPosition(visible.width * 0.5f + 140, 1020);
	/*treasure_collection_text->setRotation(180);*/

	auto treasure_open_text_button = MenuItemImage::create("treasure_text_treasure.png", "treasure_text_treasure_off.png", CC_CALLBACK_1(TreasureStoreScene::TyrButton, this)); //창바꾸는 버튼 -> Button으로 이동
	treasure_open_text_button->setPosition(visible.width * 0.5f - 140, 1020);

	spr_button_case4 = Sprite::create("treasure_buttoncase_03.png");
	spr_button_case4->setPosition(visible.width * 0.5f + 140, 1020);
	spr_button_case4->setScale(1.);
	right_layer->addChild(spr_button_case4);






	auto text = Menu::create(treasure_collection_text_button, treasure_open_text_button, treasure_opewn_text_button, NULL);
	text->setPosition(Vec2::ZERO);
	right_layer->addChild(text, 19);

	//auto menu = Menu::create(, NULL);
	//menu->setPosition(Vec2::ZERO);
	//ui_layer->addChild(menu, 10);


}

void TreasureStoreScene::InitUILayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	ui_layer = Layer::create();
	ui_layer->setPosition(Vec2::ZERO);
	this->addChild(ui_layer, 2);

	auto gem = Sprite::create("main_gem.png");                //보석이미지
	gem->setPosition(Point(70, visible.height - 60));
	gem->setScale(0.7);
	ui_layer->addChild(gem, 1);
	//숫자	
	unsigned int temp = HeroMM::getInstance()->res_total;

	unsigned int digit = 0;
	for (int i = 0; i < 10 && temp >= 0; i++)
	{
		if (temp == 0)
			break;
		digit++;
		temp *= 0.1f;
	}
	

	if (digit == 0)
		digit++;

	temp = HeroMM::getInstance()->res_total;





	for (int i = 0; i < 10; i++)
	{
		gem_tex[i] = Sprite::create(StringUtils::format("num_%d.png", temp % 10));
		gem_tex[i]->setPosition(90 + (digit - i) * 30, visible.height - 60);
		gem_tex[i]->setScale(0.5f);
		gem_tex[i]->setVisible(true);
		ui_layer->addChild(gem_tex[i], 2);

		if (temp == 0 && i != 0)
			gem_tex[i]->setVisible(false);

		temp *= 0.1f;
	}

	auto home_button = MenuItemImage::create("home_button.png", "home_button.png", CC_CALLBACK_0(TreasureStoreScene::HomeButton, this)); //홈버튼tg
	home_button->setPosition(visible.width - 150, visible.height - 60);
	home_button->setScale(0.5f); 

    auto setting_button = MenuItemImage::create("setting_button.png", "setting_button.png", CC_CALLBACK_0(TreasureStoreScene::SettingButton, this)); //홈버튼
	setting_button->setPosition(visible.width - 75, visible.height - 60);
	setting_button->setScale(0.5f);

	


		


	auto menu = Menu::create(home_button, setting_button, NULL);
	menu->setPosition(Vec2::ZERO);
	ui_layer->addChild(menu, 10);

}



//보물획득 화면
void TreasureStoreScene::InitOpenLayer()
{
	auto visible = Director::getInstance()->getVisibleSize();

	open_layer = Layer::create();
	open_layer->setPosition(Vec2::ZERO);
	open_layer->setVisible(false);
	this->addChild(open_layer, 1);

	



	spr_treasure_layer_5 = Sprite::create("treasure_layer_02.png");
	spr_treasure_layer_5->setPosition(visible.width * 0.5f, visible.height * 0.5f + 40 - 60);  //보물획득 이미지t
	open_layer->addChild(spr_treasure_layer_5, 2);
	spr_treasure_layer_5->setScale(1);

	spr_open_box = Sprite::create("treasure_box_open.png");
	spr_open_box->setPosition(visible.width * 0.5f, visible.height * 0.5f - 60);   //보물상자 오픈 이미지t
	open_layer->addChild(spr_open_box, 2);
	spr_open_box->setScale(1.4);

	spr_get_treasure_text = Sprite::create("obtain_treasure.png");
	spr_get_treasure_text->setPosition(visible.width * 0.5f, 1000);  //보물획득 이미지t
	open_layer->addChild(spr_get_treasure_text, 2);
	spr_get_treasure_text->setScale(1.4);


	auto anter_button = MenuItemImage::create("anter.png", "anter.png", CC_CALLBACK_0(TreasureStoreScene::TreasureOpenSceneButton, this));
	anter_button->setPosition(visible.width * 0.5f, 120 - 50);
	auto menu = Menu::create(anter_button, NULL);
	menu->setPosition(Vec2::ZERO);
	open_layer->addChild(menu, 2);
	anter_button->setScale(1.4);

	/*int random = rand() % 10;*/
}



void TreasureStoreScene::TreasureOpenButton()
{
	if (HeroMM::getInstance()->res_total - 50 >= 0)
	{
		buy_layer->setVisible(false);
		open_layer->setVisible(true);
		
		HeroMM::getInstance()->res_total -= 50;
		unsigned int temp = HeroMM::getInstance()->res_total;
		unsigned int digit = 0;
		for (int i = 0; i < 10 && temp >= 0; i++)
		{
			if (temp == 0)
				break;
			digit++;
			temp *= 0.1f;
		}
		temp = HeroMM::getInstance()->res_total;
		for (int i = 0; i < 10; i++)
		{
			gem_tex[i]->setTexture(StringUtils::format("num_%d.png", temp % 10));
			if (temp == 0 && i != 0)
				gem_tex[i]->setVisible(false);

			temp *= 0.1f;
		}
	}
}




void TreasureStoreScene::TrpennButton()
{

	buy_layer->setVisible(false);
	ui_layer->setVisible(false);
	open_layer->setVisible(false);
	operwher_layer->setVisible(true);
	IpenLayer();
}


void TreasureStoreScene::TreasureOpennButton()
{
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void TreasureStoreScene::TreasureOpenSceneButton() 
{
	buy_layer->setVisible(false);
	ui_layer->setVisible(false);
	open_layer->setVisible(false);
	right_layer->setVisible(true);
}


void TreasureStoreScene::jiButton()
{
	if (update_layer_bool == false)  //left layer
	{
		update_layer_bool = true;
	}
	else
	{
		update_layer_bool = false;
	}


	left_layer->setVisible(update_layer_bool);


}

void TreasureStoreScene::HomeButton()
{
	Scene * scene = TransitionFade::create(1.0f, MenuScene::createScene());  //메인메뉴 씬으로 이동
	Director::getInstance()->replaceScene(scene);
}



void TreasureStoreScene::SettingButton()
{
}

void TreasureStoreScene::ReButton()
{ 
	left_layer->setVisible(false);
	right_layer->setVisible(true);
}

void TreasureStoreScene::EeButton()
{
	right_layer->setVisible(false);
	left_layer->setVisible(true);
}

void TreasureStoreScene::FeButton()
{
	right_layer->setVisible(false);
	
	buy_layer->setVisible(true);
}

void TreasureStoreScene::TyrButton(Ref* pSender)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			if (inventory[y][x]->_ID == pSender->_ID && TreasureDeck::getInstance()->get[y][x] == true)
			{
				treaName->setString(names[TreasureDeck::getInstance()->id[y][x]]);
				treaText->setString(texts[TreasureDeck::getInstance()->id[y][x]]);


				left_layer->setVisible(false);
				buy_layer->setVisible(true);
			}
		}
	}


}


void TreasureStoreScene::luck()
{
	orepen_layer->setVisible(false);
}



void TreasureStoreScene::T4yrButtonn()
{
	orepen_layer->setVisible(true);
	
}

void TreasureStoreScene::T4yreButtonn()
{
	buy_layer->setVisible(false);
	right_layer->setVisible(false);
	ui_layer->setVisible(false);
	open_layer->setVisible(false);
	left_layer->setVisible(false);
	coll_layer->setVisible(true);
}

void TreasureStoreScene::T4yrButton()
{

}

void TreasureStoreScene::Button()
{

	if (update_layer_bool == false)  //left layer
	{
		update_layer_bool = true;
	}
	else
	{
		update_layer_bool = false;
	}


	left_layer->setVisible(update_layer_bool);



}

