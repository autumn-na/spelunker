#pragma once

#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "string.h"

using namespace cocos2d;

class ConversationMM
{
private:
	ConversationMM();
	ConversationMM(const ConversationMM&);
	ConversationMM* operator=(const ConversationMM&) {}
	~ConversationMM();
	static ConversationMM* inst;

public:
	static ConversationMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new ConversationMM();
		}
		return inst;
	}

	Sprite* sprf_npc[1];
	Sprite* sprf_conversation_panel;

	Label* lab_tutorial;

	void startConversation(int _npc, int _type);
	void nextConversation();
	void endConversation();

	bool isNextEmpty();

	std::string getString(int _npc, int _place, int _num);

	enum Place
	{
		MAIN,
		BLOCKSLIDE,
		CLICKER
	};

	enum NPC
	{
		TUTORIAL
	};
private:
	int conversation_npc;
	int conversation_num;
	int conversation_place;

#define CONVERSATION_PATH "conversation_panel.png"
#define NPC_TUTORIAL_PATH "aaaa.png"

	std::string string_tutorial_clicker[7]
	{
		"전투 방법을 설명 드리겠습니다.",
		"노란색 버튼을 터치하여 공격합니다.",
		"위험 표시와 함께 몬스터가 치명적인 공격을 가합니다.",
		"빨간색 버튼을 슬라이드하여 회피합니다.",
		"스킬 게이지를 채워서 스킬을 사용할 수 있습니다."
		"시작해볼까요?",
		""
	};
};