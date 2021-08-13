#include "Progress.h"

Progress::Progress(Layer * layer, int _whole, float *_persent)
{
	auto visible = Director::getInstance()->getVisibleSize();

	whole = _whole;
	persent = _persent;

	auto tex_onTex = Sprite::create("Game_UI_Image_InGame_Progress_Bar.png");
	tex_on = ProgressTimer::create(tex_onTex);
	tex_on->setMidpoint(ccp(0.0f, 0.5f)); 
	tex_on->setBarChangeRate(ccp(1, 0));
	tex_on->setType(kCCProgressTimerTypeBar);// kCCProgressTimerTypeHorizontalBarLR);
	tex_on->setPercentage(static_cast<float>(*persent) / static_cast<float>(whole) * 100.0f);
	tex_on->setPosition(visible.width * 0.5f, visible.height - 50);
	layer->addChild(tex_on, 4);

	tex_under = Sprite::create("Game_UI_Image_InGame_Progress_Bar_Outline.png");
	tex_under->setPosition(visible.width * 0.5f , visible.height - 50);
	layer->addChild(tex_under, 3);

	bospos = Sprite::create("BosPosUI.png");
	bospos->setPosition(visible.width * 0.5f, visible.height - 50);
	layer->addChild(bospos, 5);
}

bool Progress::SetProgress(int add_present)
{
	auto visible = Director::getInstance()->getVisibleSize();
	if (whole > (*persent) + add_present)
		(*persent) += add_present;

	if (abs(HeroMM::getInstance()->progress_percent + add_present - (whole * 0.5f)) <= (whole * 0.5f))
	{
		HeroMM::getInstance()->progress_percent += add_present;
		tex_on->setPercentage(static_cast<float>(*persent) / static_cast<float>(whole) * 100.0f);
	}
	if (static_cast<float>(*persent) / static_cast<float>(whole) * 100 >= (static_cast<float>(HeroMM::getInstance()->phase)+1) * 10)
	{
		return false;
	}
	return true;
}
