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
	unsigned int bothSide; //오른쪽 왼쪽 체크
	unsigned int type; //광석 종류 체크
	unsigned int count;//광석 위치 체크
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

	Block(NodeGrid* _grid);//body 텍스쳐 입력

	void Init(const unsigned int _bothSide, const unsigned int _type, const unsigned int _count);
	void SetType(const unsigned int _mod);//body 텍스쳐 설정
	void SetBlockPosition(const float delay);

	void PoisonStart();
	void PoisonEnd();
	void Down();//move_count-- 한칸씩 아래로 보내콅E
	bool Destroy(Vec2 charactor, bool touch); //없애콅E
	void Explosion();
	
	void ExplosionDelete();
	void BodyDelete();//안보이게하기
};
#endif