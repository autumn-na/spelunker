#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class TreasureDeck

{
public:

	TreasureDeck();

	~TreasureDeck();




	// Singleton object

	static TreasureDeck* getInstance()
	{

		if (m_pInstance == nullptr)

			m_pInstance = new TreasureDeck();

		return m_pInstance;

	}

	static void releaseInstance();

	static TreasureDeck* m_pInstance;




public:

	void testFunc();


	bool get[5][5];
	int id[5][5];



private:

	int testVariable;

};


