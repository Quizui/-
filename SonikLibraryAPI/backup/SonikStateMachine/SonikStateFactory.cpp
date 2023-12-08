/*
 * SonikStateFactory.cpp
 *
 *  Created on: 2016/01/25
 *      Author: SONIC_000
 */

#include "SonikStateFactory.h"


namespace SonikLib
{
	SonikStateFactory::SonikStateFactory(void)
	{
		//no process;
	};

	bool SonikStateFactory::InitStateFactory(unsigned long BiggestStateSize, unsigned long StateCount)
	{
		return SonikLibCall::CreateSonikMemoryAllocaor(AllocSmtPtr, BiggestStateSize * StateCount);
	};

};

