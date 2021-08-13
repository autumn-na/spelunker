#include <stdio.h>

#include "TreasureDeck.h"



//ΩÃ±€≈Ê	

TreasureDeck *TreasureDeck::m_pInstance = nullptr;

TreasureDeck::TreasureDeck() 
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			get[i][j] = false;
			id[i][j] = 0;
		}
	}
}

TreasureDeck::~TreasureDeck() {}


//-----------------------------------------------------------------------------
// getInstance
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
// releaseInstance
//-----------------------------------------------------------------------------

void TreasureDeck::releaseInstance()

{
	if (m_pInstance != nullptr)
		delete m_pInstance;
}


//-----------------------------------------------------------------------------
// testFunc
//-----------------------------------------------------------------------------

void TreasureDeck::testFunc()

{

	testVariable = 20;

}

