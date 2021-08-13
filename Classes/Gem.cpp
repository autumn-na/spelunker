#include "Gem.h"

Gem::Gem(Layer * layer)
{
	unsigned int temp = HeroMM::getInstance()->res_total;
	for (int i = 0; i < 10; i++)
	{
		gem_tex[i] = Sprite::create(StringUtils::format("num_%d.png", temp % 10));
		layer->addChild(gem_tex[i], 5);
		temp *= 0.1f;
	}
	AddGem(0);

}

void Gem::AddGem(int addres)
{
	HeroMM::getInstance()->res_total += addres;
	unsigned int temp2 = HeroMM::getInstance()->res_total;
	unsigned int digit = 0;
	for (int i = 0; i < 10 && temp2 > 0; i++)
	{
		temp2 *= 0.1f;
		digit++;
	}

	unsigned int temp = HeroMM::getInstance()->res_total;
	for (int i = 0; i < 10 && temp > 0; i++)
	{
		if (temp == 0)
		{
			gem_tex[i]->setVisible(false);
		}
		else
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();

			gem_tex[i]->setVisible(true);
			gem_tex[i]->setTexture(StringUtils::format("num_%d.png", temp % 10));
			gem_tex[i]->setPosition(visibleSize.width*0.5f - ((i - (digit * 0.5f)) * 30), visibleSize.height * 0.5f);
			gem_tex[i]->setScale(0.5f);
			temp *= 0.1f;
		}
	}
}
