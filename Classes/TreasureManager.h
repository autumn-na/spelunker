#ifndef __TREASUREMANAGER_H__
#define __TREASUREMANAGER_H__

class TreasureMM
{ 
	static TreasureMM* Instance;
public:
	static TreasureMM* getInstance()
	{
		if (Instance == nullptr)
			Instance = new TreasureMM;

		return Instance;
	}
	unsigned int haveNum = 0;
	unsigned int id[30] = {0};
};

TreasureMM* TreasureMM::Instance = nullptr;

#endif