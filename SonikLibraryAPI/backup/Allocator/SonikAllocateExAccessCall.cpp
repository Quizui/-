/*
 * SonikAllocateExDllAccess.cpp
 *
 *  Created on: 2015/12/31
 *      Author: Sonik
 */

#include "SonikAllocateExAccessCall.h"
#include "SonikBaundaryTagAllocateEx.h"

namespace SonikLibCall
{

	void FreeSonikMemoryAllocator(SonikBTMA::SonikBaundaryTagAllocateEx_Base* pFreeObj)
	{
		::delete pFreeObj;
	};

	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth)
	{
		SonikBTMA::SonikBaundaryTagAllocateEx* Tmp =0;

		try
		{
			Tmp = ::new SonikBTMA::SonikBaundaryTagAllocateEx;
			if( ! Tmp->Initialize(AllocateSize, SetDepth) )
			{
				::delete Tmp;
				throw -1;
			};

		}catch(...)
		{
			return false;
		};

		SonikLib::SonikAllocObjectPtr Ptr(Tmp, &SonikLibCall::FreeSonikMemoryAllocator, &Tmp->RefCount);

		GetPtr = static_cast<SonikLib::SonikAllocObjectPtr&&>(Ptr);

		return true;
	};

};

