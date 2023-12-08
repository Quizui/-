/*
 * SonikAllocateExAccessCall.h
 *
 *  Created on: 2015/12/31
 *      Author: SONIK
 */

#ifndef SONIKALLOCATEEXACCESSCALL_H_
#define SONIKALLOCATEEXACCESSCALL_H_

#include "SonikAllocateExUserUseSmtPtr.h"

namespace SonikLibCall
{
#ifdef __SONIK_I686__
	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

#elif defined(__SONIK_x86_64__)
	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

#endif
};



#endif /* SONIKALLOCATEEXACCESSCALL_H_ */
