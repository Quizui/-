/*
 * SonikAllocateExDllAccess.h
 *
 *  Created on: 2015/12/31
 *      Author: Sonik
 */

#ifndef SonikALLOCATEEXDLLACCESS_H_
#define SonikALLOCATEEXDLLACCESS_H_

#include "SonikAllocateExUserUseSmtPtr.h"

namespace SonikLibCall
{

	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

};



#endif /* SonikALLOCATEEXDLLACCESS_H_ */
