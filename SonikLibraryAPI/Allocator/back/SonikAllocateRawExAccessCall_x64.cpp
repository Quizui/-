/*
 * SonikAllocateExDllAccess.cpp
 *
 *  Created on: 2015/12/31
 *      Author: SONIK
 */

#ifdef __SONIK_x86_64__

#include "SonikAllocateRawExAccessCall.h"
#include "SonikBaundaryTagAllocateEx.h"
#include "SonikBaundaryTagAllocateExBase.h"


namespace SonikLibCall
{

	void FreeSonikMemoryAllocatorRaw(SonikBTMA::SonikBaundaryTagAllocateEx_Base* pFreeObj)
	{
                ::delete pFreeObj;
	};

	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth)
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

		SonikLib::SonikRawAllocObjectPtr Ptr(Tmp, &SonikLibCall::FreeSonikMemoryAllocatorRaw, &Tmp->RefCount);

		GetPtr = static_cast<SonikLib::SonikRawAllocObjectPtr&&>(Ptr);

		return true;
	};

};

#endif

