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
		"���� ����� ���� �帮�ڽ��ϴ�.",
		"����� ��ư�� ��ġ�Ͽ� �����մϴ�.",
		"���� ǥ�ÿ� �Բ� ���Ͱ� ġ������ ������ ���մϴ�.",
		"������ ��ư�� �����̵��Ͽ� ȸ���մϴ�.",
		"��ų �������� ä���� ��ų�� ����� �� �ֽ��ϴ�."
		"�����غ����?",
		""
	};
};