#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "string"

using namespace cocos2d;
using namespace CocosDenshion;

using namespace std;

class AudioMM
{
private:
	AudioMM() {}
	~AudioMM() {}
	static AudioMM* inst;

public:
	static AudioMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new AudioMM();
		}
		return inst;
	}

	void checkString(string _name, int _type);

	void runBGM(string _name);
	void runEffect(string _name);

	void changeBGMState();
	void changeEffectState();

	bool getBGMEnabled();
	bool getEffectEnabled();

private:
	bool isBGMEnabled = true;
	bool isEffectEnabled = true;

	const char* bgm_path[100] = 
	{
		"sound/bgm/BGM_clothes.wav",
		"sound/bgm/BGM_equipment.wav",
		"sound/bgm/BGM_gameover.wav",
		"sound/bgm/BGM_ingame1.wav",
		"sound/bgm/BGM_ingame2.wav",
		"sound/bgm/BGM_main.wav",
		"sound/bgm/BGM_skill.wav",
		"sound/bgm/BGM_title.wav",
		"sound/bgm/BGM_treasure.wav"
	};

	const char* effect_path[100] = 
	{
		"sound/effect/EF_button.wav",
		"sound/effect/EF_button_slide.wav",
		"sound/effect/EF_buy.wav",
		"sound/effect/EF_close.wav",
		"sound/effect/EF_die.wav",
		"sound/effect/EF_die_boss.wav",
		"sound/effect/EF_dodge_success.wav",
		"sound/effect/EF_dodgefail.wav",
		"sound/effect/EF_equipment_change.wav",
		"sound/effect/EF_equipment_upgrade.wav",
		"sound/effect/EF_head_block_touch.wav",
		"sound/effect/EF_hit.wav",
		"sound/effect/EF_Key.wav",
		"sound/effect/EF_meet_boss.wav",
		"sound/effect/EF_penalty.wav",
		"sound/effect/EF_penalty_touch.wav",
		"sound/effect/EF_poison_touch.wav",
		"sound/effect/EF_pop_up.wav",
		"sound/effect/EF_red_key.wav",
		"sound/effect/EF_skill1.wav",
		"sound/effect/EF_skill2.wav",
		"sound/effect/EF_skill3.wav",
		"sound/effect/EF_skill4.wav",
		"sound/effect/EF_treasure_get.wav",
		"sound/effect/EF_treasure_open.wav",
		"sound/effect/EF_upgrade_fail.wav",
		"sound/effect/EF_upgrade_success.wav",
		"sound/effect/EF_use_skill.wav",
		"sound/effect/EF_warning.wav",
		"sound/effect/EF_wear.wav",
		"sound/effect/EF_yellow_key.wav"
	};

	string bgm_name[100] = 
	{
		"CLOTHES",
		"EQUIPMENT",
		"GAMEOVER",
		"INGAME1",
		"INGAME2",
		"MAIN",
		"SKILL",
		"TITLE",
		"TREASURE"
	};

	string effect_name[100] = 
	{
		"BUTTON",
		"BUTTONSLIDE",
		"BUY",
		"CLOSE",
		"DIE",
		"DIEBOSS",
		"DODGESUCCESS",
		"DODGEFAIL",
		"EQUIPMENTCHANGE",
		"EQUIPMENTUPGRADE",
		"HEADBLOCKTOUCH",
		"HIT",
		"KEY",
		"MEETBOSS",
		"PENALTY",
		"PENALTYTOUCH",
		"POISONTOUCH",
		"POPUP",
		"REDKEY",
		"SKILL1",
		"SKILL2",
		"SKILL3",
		"SKILL4",
		"TREASUREGET",
		"TREASUREOPEN",
		"UPGRADEFAIL",
		"UPGRADESUCCESS",
		"USESKILL",
		"WARNING",
		"WEAR",
		"YELLOWKEY"
	};

	enum AudioType
	{
		BGM,
		EFFECT
	};
};