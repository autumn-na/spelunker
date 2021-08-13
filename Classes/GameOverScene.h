#pragma once

#include "cocos2d.h"

USING_NS_CC;
class GameOverScene : public cocos2d::Layer
{
public:
	static Scene* createScene();

	Label* lab_res_got;
	Label* lab_exp_got;

	Sprite* spr_game_over;
	Sprite* spr_score_line;

	MenuItemSprite* menui_home;

	Menu* menu_gameover;
	
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	virtual bool init();
	void initLabel();
	void initSprite();
	void initMenu();

	void showScore();
	void setHeroData();

	void goToMainCallback(Ref* pSender);

	Sprite* runAnimation(const char* _path, const Vec2& position);

	CREATE_FUNC(GameOverScene);
};
