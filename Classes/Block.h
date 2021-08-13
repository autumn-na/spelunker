#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
USING_NS_CC;

#define BLOCK_LEFT_XPOS 100
#define BLOCK_RIGHT_XPOS 640

class Block
{
public:
	NodeGrid* m_grid;

	bool poisonCheck;
	unsigned int bothSide; //������ ���� üũ
	unsigned int type; //���� ���� üũ
	unsigned int count;//���� ��ġ üũ
	unsigned int maxCount;
	Sprite * body; 
	Sprite * explosion;

public:
	enum BothSide
	{
		BLOCK_LEFT,
		BLOCK_RIGHT,
	};
	enum Type
	{
		SKULL = 0,
		YELLOW = 1,
		RED = 2,
		GREEN = 3,
		POISON = 4,
		GREEN2 = 5,
	};

	Block(NodeGrid* _grid);//body �ؽ��� �Է�

	void Init(const unsigned int _bothSide, const unsigned int _type, const unsigned int _count);
	void SetType(const unsigned int _mod);//body �ؽ��� ����
	void SetBlockPosition(const float delay);

	void PoisonStart();
	void PoisonEnd();
	void Down();//move_count-- ��ĭ�� �Ʒ��� ������E
	bool Destroy(Vec2 charactor, bool touch); //���ֱ�E
	void Explosion();
	
	void ExplosionDelete();
	void BodyDelete();//�Ⱥ��̰��ϱ�
};
#endif