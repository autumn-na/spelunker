#ifndef __PROGRESS_H__
#define __PROGRESS_H__

#include "cocos2d.h"
#include "HeroManagement.h"

USING_NS_CC;
class Progress
{
public:
	int whole;
	float *persent;
	int frame_count;
	
	ProgressTimer * tex_on;
	Sprite * tex_under;
	Sprite * bospos;
public:
	Progress(Layer * layer, int _whole, float *_persent);
	bool SetProgress(int add_progress);
};

#endif