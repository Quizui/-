/*
 * SonikAllocateExUserUseSmtPtrBase.h
 *
 *  Created on: 2016/01/07
 *      Author: SONIK
 */

#ifndef SONIKALLOCATEEXUSERUSESMTPTRBASE_H_
#define SONIKALLOCATEEXUSERUSESMTPTRBASE_H_

#include "..\\SonikCASUse.h"
#include <new>
#include "SonikAllocateExUserUseObjectSmtPtr.h"

namespace SonikAllocateSmtPtrBase
{
#ifdef __SONIK_I686__
	class SonikAllocSmtPtr_Base
	{
	protected:
		int8_t* GetPtr;
		std::atomic<uint32_t>* pCount;
		SonikLib::SonikAllocObjectPtr pObj;
		uint32_t ArrayCount_;
//		SonikLib::SonikAtomicLock shortblock_;

	public:

		SonikAllocSmtPtr_Base(void)
		:GetPtr(0)
		,pCount(0)
		,ArrayCount_(0)
		{
			try
			{
				pCount = new std::atomic<uint32_t>;
			}catch(std::bad_alloc&)
			{
				throw;
			}

			pCount->store(1);
		};

		virtual ~SonikAllocSmtPtr_Base(void)
		{
			//no process;
		};

	};


#elif defined(__SONIK_x86_64__)
	class SonikAllocSmtPtr_Base
	{
	protected:
		int8_t* GetPtr;
		std::atomic<uint64_t>* pCount;
		SonikLib::SonikAllocObjectPtr pObj;
		uint64_t ArrayCount_;
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


#endif

};


#endif /* SONIKALLOCATEEXUSERUSESMTPTRBASE_H_ */
