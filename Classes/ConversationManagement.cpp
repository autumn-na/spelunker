#include "ConversationManagement.h"

ConversationMM* ConversationMM::inst = nullptr;

ConversationMM::ConversationMM()
{
	for (int i = 0; i < 1; i ++)
	{
		sprf_npc[i] = Sprite::create(NPC_TUTORIAL_PATH);
		sprf_npc[i]->runAction(Hide::create());
		sprf_npc[i]->retain();
	}

	sprf_conversation_panel = Sprite::create(CONVERSATION_PATH);
	sprf_conversation_panel->runAction(Hide::create());
	sprf_conversation_panel->retain();

	lab_tutorial = Label::create();
	lab_tutorial->retain();
}

ConversationMM::~ConversationMM()
{
}

void ConversationMM::startConversation(int _npc, int _place)
{
	sprf_npc[_npc]->runAction(Show::create());

	lab_tutorial->setString(getString(_npc, _place, 0));

	conversation_npc = _npc;
	conversation_num = 0;
	conversation_place = _place;
}

void ConversationMM::nextConversation()
{
	//else
	//{
		lab_tutorial->setString(getString(conversation_npc, conversation_place, conversation_num));
	//}
}

void ConversationMM::endConversation()
{
	sprf_npc[conversation_npc]->runAction(Hide::create());

	conversation_npc = NULL;
	conversation_place = NULL;
	conversation_num = 0;
}

bool ConversationMM::isNextEmpty()
{
	if (string_tutorial_clicker[++conversation_num].size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string ConversationMM::getString(int _npc, int _place, int _num)
{
	return string_tutorial_clicker[_num];
}
