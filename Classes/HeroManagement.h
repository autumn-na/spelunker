#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class HeroMM
{
private:
	HeroMM();
	~HeroMM() {}
	static HeroMM* inst;

public:
	static HeroMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new HeroMM();
		}
		return inst;
	}

public:
	//Sprite, Animation 등 이미지
	Sprite* spr_hero;

	//레벨 관련
	int levelup_exp[30];
	int level = 1;
	int exp = 0;
	int exp_got = 0;

	//전투 관련
	bool isAlive = true;
	int max_hp = 1000;
	int hp = 1000;
	float dmg = 0;

	//자원 관련
	int res_total = 5000;
	int res_up = 1;
	int res_get = 0; //이게 블럭 신에서 모은 총 자원 갯수

	//스테이지 관련
	int stage = 0;
	float progress_percent = 0;
	float skill_gauge = 0;
	int phase = 0;

	//플레이어의 상태(클리커 씬)
	int state;

	//플레이어의 상태의 종류
	enum HeroState
	{
		DEFAULT,
		DODGE
	};

	int phase_for_announcement = 0;

	////////////////////////////////////////
	////////////////////////////////////////

	//레벨 관련 함수
	void checkExp();
	void levelUp();

	//전투 관련 함수
	void initBattle();
	void heroAttack();
	void heroAttacked();

	//블록 관련 함수
	void breakBlock();
};