#include "SkillIcon.h"

Skill::Skill(Layer * layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto under = Sprite::create("skill_button.png");
	under->setAnchorPoint(Vec2(0.5f, 0.0f));
	under->setPosition(Vec2(visibleSize.width * 0.5f, 70));
	layer->addChild(under, 5);

	icon = Sprite::create("skill_gauge_on.png");
	icon->setAnchorPoint(Vec2(0.5f, 0.0f));
	icon->setPosition(Vec2(visibleSize.width * 0.5f, 70 + 12));
	icon->setColor(Color3B(100, 100, 100));
	icon->setVisible(false);
	layer->addChild(icon, 6);

	effect = Sprite::create("res/obj_4.png");
	effect->setPosition(Vec2(visibleSize.width * 0.5f, 160));
	effect->setScale(0);
	layer->addChild(effect, 4);

	effect_under = Sprite::create("res/outline_1.png");
	effect_under->setPosition(Vec2(visibleSize.width * 0.5f, 160));
	effect_under->setScale(1.6f);
	effect_under->runAction(RepeatForever::create(RotateBy::create(1, 360)));
	effect_under->setVisible(false);
	layer->addChild(effect_under, 7);

	size = icon->getContentSize();
	whole = 100;
	prosent = 0;
	skill_use = false;
	skill_on = false;

	skill_time = 10; //스킬 플레이 시간 설정
}

void Skill::UpProsent(int add_prosent)
{
	prosent += add_prosent;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (prosent/whole >= 1)
	{
		Upgrade();
	}
	else
	{
		icon->setVisible(true);
		icon->setPosition(Vec2(visibleSize.width * 0.5f,70 + 12 - size.y) + (Vec2(0, (static_cast<float>(prosent)/static_cast<float>(whole)) * size.y)));
		icon->setTextureRect(Rect(0, size.y - (static_cast<float>(prosent)/ static_cast<float>(whole))*size.y, size.x, size.y));
	}
}

void Skill::Upgrade()
{
	icon->setColor(Color3B(255, 255, 255));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	icon->setTexture("skill_gauge_on.png");
	icon->setPosition(Vec2(visibleSize.width * 0.5f, 70 + 10));
	skill_use = true;

	effect->runAction(ScaleTo::create(0.1f, 2.0f));
//	effect_under->setVisible(true);
}

void Skill::play()
{
	skill_use = false;
	skill_on = true;

	prosent = 0;
	UpProsent(0);
	icon->runAction(Sequence::create(DelayTime::create(skill_time), CallFunc::create(CC_CALLBACK_0(Skill::playoff, this)), NULL));
	icon->setVisible(false);

	effect_under->setVisible(false);

	effect->stopAllActions();
	effect->runAction(ScaleTo::create(0.1f, 0));
}
     
void Skill::playoff()
{
	icon->setColor(Color3B(100, 100, 100));
	icon->setTexture("skill_gauge_on.png");
	prosent = 0;
	UpProsent(0);
	skill_use = false;
	skill_on = false;

	effect->stopAllActions();
	effect->runAction(ScaleTo::create(0.1f, 0));
	effect_under->setVisible(false);
}