 /*
 * SonikThreadPack.h
 *
 *  Created on: 2016/01/06
 *      Author: Sonik
 */

#ifndef SONIKWORKTHREAD_SONIKTHREADPACK_H_
#define SONIKWORKTHREAD_SONIKTHREADPACK_H_

#include "..\\SonikAllocateUse.h"

namespace SonikLib
{
	class FunctionSystem_Base;
};

namespace SonikThreadImpl
{
	class pImplEx;
};

namespace SonikThread
{
	class SonikThreadManagerEx;
};


namespace SonikThreadPack
{
	class ThreadPack
	{
		friend class SonikThreadImpl::pImplEx;
		friend class SonikThread::SonikThreadManagerEx;
	private:
		SonikLib::FunctionSystem_Base* pFunc;
		SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base> SmtPtrFunc;

	public:
		ThreadPack(void)
		:pFunc(0)
		{

		};

		ThreadPack(ThreadPack&&) =default;
	};

};


#endif /* SONIKWORKTHREAD_SONIKTHREADPACK_H_ */
