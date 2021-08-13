#ifndef __BLOCK_SLIDE_GAME_SCENE_H__
#define __BLOCK_SLIDE_GAME_SCENE_H__

#include <time.h>

#include "cocos2d.h"

#include "HeroManagement.h"
#include "GameOverScene.h"
#include "Block.h"0

USING_NS_CC;
class BlockSlideGameScene : public cocos2d::Layer
{
public:
	Layer* backEffect_layer;
	Sprite* backEffect_image;
	Sprite* backEffect_heart[100];

	int gametime;

	bool unbeatable;
	bool start;
	int skullTouch;
	//layer
	NodeGrid* poisonGrid;
	
	//pause layer
	bool pause_state;
	Layer* pause_layer;
	MenuItemImage* pause_button[2];
	
	//setting
	Size visibleSize;
	
	//skill
	bool skill_play_check;
	float skill_gauge_value;
	ProgressTimer* skill_progress;
	
	//Hp bar
	float hpInt;
	Sprite * hpBar;
	Sprite* needle;
	ProgressTimer* hpProgress;
	
	//progress bar
	unsigned int whole;
	Sprite * progress_player; //진행도 캐릭터 애니메이션
	ProgressTimer * progressBar; //진행도
	
	//autoKey state0
	bool autoKey_state;
	
	//money
	Label* moneyLabel;
	unsigned long money;
	
	//position state
	bool poisonCheck;

	unsigned int combo_int;
	Sprite* combo_sprite;
	Sprite* combo_num[10];

	Sprite* openAni;
	Sprite * button_left;
	Sprite * button_right;

	std::vector<Block*> block; //블럭들
	std::vector<Block*> bottomBlock; // 맨 아래 블럭
	
	static Scene* createScene();
	

	//시작시 초기화 관련
	virtual bool init();
	void GameSetting();
	void InitUI();
	void InitProgressBar();
	void InitPause();
	
	void comboEffect();
	void comboEffect2();

	//스킬관련
	void SkillStart(); //스킬 실행시 
	void SkillEnd(float dt);
	void update(float dt);
	
	//체력바
	void HpUp();
	void GameOverScene();
	
	//일시정지 관련
	void PauseLayerOn();
	void PauseLayerOff(Ref* pSender);



	Layer*torial_layer;
	Layer*torial1_layer;
	Layer*torial2_layer;
	Layer*torial3_layer;
	Layer*torial4_layer;
	Layer*torial5_layer;
	Layer*torial6_layer;
	Layer*maintorial_layer;
	Layer*maintorial1_layer;
	Layer*maintorial2_layer;





	void InittutorialLayer1();
	Sprite*spr_torialnpc_layer;

	void tutorialScene();

	Sprite* tutorialBlock;
	Label* tutorialLabel;


	void torialcaseButton1();
	void torialcaseButton2();
	void torialcaseButton3();
	void torialcaseButton4();
	void torialcaseButton5();
	
	



	void SetBgmSound();
	void SetEffectSound();
	void EndingScene();
	void MenuScene();
	
	
	//오토
	void AutoTouch(float dt);
	
	//진행도 설정
	bool SetProgress(const unsigned int addpresent); 
	
	//블럭 관련
	void CreateBlock(Vec2 pos, const unsigned int _count);//블럭 생성
	void BlockChange();
	void PoisonEnd();
	void BlockTouch(const unsigned int block_direct); //터치 관련
	//콤보함수
	void ChangeFightScene(); //전투씬으로 이동
	bool onTouchBegan(Touch* touch, Event* unused_event);// 터치 했을때
	void onTouchEnded(Touch* touch, Event* unused_event);
	void torialcaseButton();
	// 터치 했을때

	//키보드
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(BlockSlideGameScene);
};

#endif
