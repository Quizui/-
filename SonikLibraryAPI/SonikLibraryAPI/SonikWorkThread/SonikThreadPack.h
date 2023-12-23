 /*
 * SonikThreadPack.h
 *
 *  Created on: 2016/01/06
 *      Author: SONIK
 */

#ifndef SONIKWORKTHREAD_SONIKTHREADPACK_H_
#define SONIKWORKTHREAD_SONIKTHREADPACK_H_

#include "../SmartPointer/SonikSmartPointer.hpp"

namespace SonikFunctionObjectDefines
{
	class FunctionObjectSystemInterface;
};

namespace SonikThreadImpl
{
	class pImplEx;
};

namespace SonikLib
{
	using SonikFOSInterface = SonikFunctionObjectDefines::FunctionObjectSystemInterface;
	class SonikThreadManagerEx;
};


namespace SonikThreadPack
{
	class ThreadPack
	{
		friend class SonikThreadImpl::pImplEx;
		friend class SonikLib::SonikThreadManagerEx;
	private:
		SonikLib::SonikFOSInterface* pFunc;
		SonikLib::NormalSmtPtr<SonikLib::SonikFOSInterface> SmtPtrFunc;

	public:
		ThreadPack(void)
		:pFunc(0)
		{

		};

		ThreadPack(ThreadPack&&) =default;
	};

};


#endif /* SONIKWORKTHREAD_SONIKTHREADPACK_H_ */
