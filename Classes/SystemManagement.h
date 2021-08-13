#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class SystemMM
{
private:
	SystemMM() {}
	~SystemMM() {}
	static SystemMM* inst;

public:
	static SystemMM* getInstance()
	{
		if (inst == nullptr)
		{
			inst = new SystemMM();
		}
		return inst;
	}

private:

};