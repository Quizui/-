/*
 * SonikAllocateExDllAccess.h
 *
 *  Created on: 2015/12/31
 *      Author: Sonik
 */

#ifndef SONIKALLOCATERAWEXDLLACCESS_H_
#define SONIKALLOCATERAWEXDLLACCESS_H_

#include "SonikAllocateRawExUserUseObjectSmtPtr.h"

namespace SonikLibCall
{

	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

};



#endif /*SONIKALLOCATEEXDLLACCESS_H_ */
