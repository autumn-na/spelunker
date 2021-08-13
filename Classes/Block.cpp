#include "Block.h"

Block::Block(NodeGrid * _grid)
{
	m_grid = _grid;
	body = Sprite::create("block01.png");
	body->setPosition(1000, 1000);
	m_grid->addChild(body, 2);

	explosion = Sprite::create("block_explosion/1.png");
	explosion->setVisible(false);
	m_grid->addChild(explosion, 5);

	count = 0;
	maxCount = 10;
	poisonCheck = false;
}

void Block::Init(const unsigned int _bothSide, const unsigned int _type, const unsigned int _count)  
{
	bothSide = _bothSide;
	SetType(_type);
	count = _count;
	SetBlockPosition(0.f);
}


void Block::SetType(const unsigned int _type)
{
	type = _type;
	if (type != Type::GREEN2)
		body->setTexture(StringUtils::format("block0%d.png", type));
}

void Block::SetBlockPosition(const float delay)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (count == maxCount + 1)
	{
		const unsigned int movePosX = (bothSide == BothSide::BLOCK_RIGHT) ? 440 : 280;
		auto move = MoveTo::create(delay, Vec2(movePosX, 400));
		auto scale = ScaleTo::create(delay, 1.4f);
		auto spawn = Spawn::create(move->clone(), scale->clone(), NULL);
		body->runAction(spawn->clone());
		body->setVisible(true);
	}
	else
	{
		const unsigned int setX = (bothSide == BothSide::BLOCK_RIGHT) ? BLOCK_RIGHT_XPOS : BLOCK_LEFT_XPOS;
		const unsigned int setY = visibleSize.height - (count * 110) + 300;
		body->runAction(MoveTo::create(delay, Vec2(setX, setY)));
		body->setVisible(true);
	}
}

void Block::PoisonStart()
{
	poisonCheck = true;
	const unsigned int r = rand() % 255;
	const unsigned int g = rand() % 255;
	const unsigned int b = rand() % 255;
	body->runAction(TintTo::create(0, Color3B(r, g, b)));
}

void Block::PoisonEnd()
{
	poisonCheck = false;
	body->runAction(TintTo::create(0, Color3B(255, 255, 255)));
}



void Block::Down()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	body->stopAllActions();

	if (poisonCheck)
	{
		const unsigned int r = rand() % 255;
		const unsigned int g = rand() % 255;
		const unsigned int b = rand() % 255;
		body->runAction(TintTo::create(0, Color3B(r, g, b)));
	}

	if (count == maxCount)
	{ 
		count++;
		SetBlockPosition(0.1f);
	}
	else if(count < maxCount)
	{
		count++;
		SetBlockPosition(0.1f);
	}
}

bool Block::Destroy(Vec2 charactor, bool touch)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if(!touch)
	{
		auto move = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.5f, -300));
		body->runAction(Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Block::BodyDelete, this)), NULL)); 
	}
	else if (type == Type::YELLOW || type == Type::GREEN2 || type == Type::RED)
	{ 
		auto move = MoveTo::create(0.2f, charactor);
		body->runAction(Sequence::create( move, CallFunc::create(CC_CALLBACK_0(Block::BodyDelete, this)), NULL));
		body->setTexture(StringUtils::format("gem0%d.png", type));
		Explosion();
	}
	else
	{
		auto move = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.5f, -300));
		body->runAction(Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Block::BodyDelete, this)), NULL));
	}
	return true;
}

void Block::Explosion()
{
	explosion->setVisible(true);
	explosion->setPosition(body->getPosition());
	auto explosion_animation = Animation::create();
	explosion_animation->setDelayPerUnit(0.02f);
	for (int i = 1; i <= 9; i++)
	{
		explosion_animation->addSpriteFrame(SpriteFrame::create(StringUtils::format("block_explosion/%d.png", i), Rect(0, 0, 230, 230)));
	}
	explosion->runAction(Sequence::create(Animate::create(explosion_animation), CallFunc::create(CC_CALLBACK_0(Block::ExplosionDelete, this)), NULL));
}

void Block::ExplosionDelete()
{
	explosion->setVisible(false);
}

void Block::BodyDelete()
{
	body->removeFromParent();
	explosion->removeFromParent();
}