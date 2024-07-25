/*
 * SonikAllocateExDllAccess.h
 *
 *  Created on: 2015/12/31
 *      Author: SONIK
 */

#ifndef SONIKALLOCATERAWEXDLLACCESS_H_
#define SONIKALLOCATERAWEXDLLACCESS_H_

#include "SonikAllocateRawExUserUseObjectSmtPtr.h"
#include "SonikFreeBlockDepthEnum.h"
#include <cstdint>

namespace SonikLibCall
{
#ifdef __SONIK_I686__
	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

#elif defined(__SONIK_x86_64__)
	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

#endif
};



#endif /* SONIKALLOCATEEXDLLACCESS_H_ */
