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
	Sprite * progress_player; //���൵ ĳ���� �ִϸ��̼�
	ProgressTimer * progressBar; //���൵
	
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

	std::vector<Block*> block; //����
	std::vector<Block*> bottomBlock; // �� �Ʒ� ��
	
	static Scene* createScene();
	

	//���۽� �ʱ�ȭ ����
	virtual bool init();
	void GameSetting();
	void InitUI();
	void InitProgressBar();
	void InitPause();
	
	void comboEffect();
	void comboEffect2();

	//��ų����
	void SkillStart(); //��ų ����� 
	void SkillEnd(float dt);
	void update(float dt);
	
	//ü�¹�
	void HpUp();
	void GameOverScene();
	
	//�Ͻ����� ����
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
	
	
	//����
	void AutoTouch(float dt);
	
	//���൵ ����
	bool SetProgress(const unsigned int addpresent); 
	
	//�� ����
	void CreateBlock(Vec2 pos, const unsigned int _count);//�� ����
	void BlockChange();
	void PoisonEnd();
	void BlockTouch(const unsigned int block_direct); //��ġ ����
	//�޺��Լ�
	void ChangeFightScene(); //���������� �̵�
	bool onTouchBegan(Touch* touch, Event* unused_event);// ��ġ ������
	void onTouchEnded(Touch* touch, Event* unused_event);
	void torialcaseButton();
	// ��ġ ������

	//Ű����
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(BlockSlideGameScene);
};

#endif
