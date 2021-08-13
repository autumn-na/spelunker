#include "HeroManagement.h"

HeroMM* HeroMM::inst = nullptr;

HeroMM::HeroMM()
{
	for (int i = 0; i < 30; i++)
	{
		levelup_exp[i] = 500 * i + 1;
	}
}

void HeroMM::checkExp()
{
	if (levelup_exp[level] <= exp)
	{
		levelUp();
	}
}

void HeroMM::levelUp()
{
	if (level < 30)
	{
		level += 1;
		exp = 0;
	}
}

void HeroMM::initBattle()
{
	
}

void HeroMM::heroAttack()
{
}

void HeroMM::heroAttacked()
{
}

void HeroMM::breakBlock()
{
}
