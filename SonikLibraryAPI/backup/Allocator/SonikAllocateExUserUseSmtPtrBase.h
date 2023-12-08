/*
 * SonikAllocateExUserUseSmtPtrBase.h
 *
 *  Created on: 2016/01/07
 *      Author: Sonik
 */

#ifndef SONIKALLOCATEEXUSERUSESMTPTRBASE_H_
#define SONIKALLOCATEEXUSERUSESMTPTRBASE_H_

#include "..\\SonikCASLockUse.h"
#include "SonikAllocateExUserUseObjectSmtPtr.h"

namespace SonikAllocateSmtPtrBase
{
	class SonikAllocSmtPtr_Base
	{
	protected:
		char* GetPtr;
		std::atomic<unsigned long>* pCount;
		SonikLib::SonikAllocObjectPtr pObj;
		unsigned long ArrayCount_;
		SonikLib::SonikAtomicLock shortblock_;

	public:

		SonikAllocSmtPtr_Base(void)
		:GetPtr(0)
		,pCount(0)
		,ArrayCount_(0)
		{

		};

		virtual ~SonikAllocSmtPtr_Base(void)
		{
			//no process;
		};

	};


};


#endif /* SONIKALLOCATEEXUSERUSESMTPTRBASE_H_ */
