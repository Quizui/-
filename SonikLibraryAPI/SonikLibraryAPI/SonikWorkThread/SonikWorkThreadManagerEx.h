/*
 * SonikWorkThreadManagerEx.h
 *
 *  Created on: 2015/09/24
 *      Author: SONIK
 */

#ifndef SONIKWORKTHREADMANAGEREX_H_
#define SONIKWORKTHREADMANAGEREX_H_

#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../FunctionObject/FunctionObjectSystemImpl.hpp"
#include "../Container/SonikAtomicQueue.hpp"
#include "../SonikCAS/SonikAtomicLock.h"
#include "SonikWorkThreadEx.h"

namespace SonikLib
{
	class SonikThreadManagerEx
	{
	private:
		//管理スレッド数
		uint32_t ManagedThreadNum;

		bool Init_;

		std::atomic<uint32_t> notifycount_;

		//スレッドプール
		SonikLib::WorkThreadEx* m_pThreads;

		S_CAS::SonikAtomicLock atmlock_;

		//ジョブキュー(MTロックフリー)
		SonikAtomicQueue<SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>>* JobQueue;


	private:
		//コンストラクタ
		///SonikThreadManagerEx(void);
		//コピーコンストラクタ
		SonikThreadManagerEx(const SonikThreadManagerEx& t_his);
		//代入演算子
		//スレッドコピーとかしだすと管理もめっちゃめんどくさくなるので...。
		SonikThreadManagerEx& operator =(const SonikThreadManagerEx& t_his);


	public:
		//コンストラクタ
		SonikThreadManagerEx(void);
		//デストラクタ
		~SonikThreadManagerEx(void);

		//イニシャライザ
		bool Initialize(uint32_t UseThreadNum =2, uint32_t JobBufferSize =1200);

		//スレッド数の取得
		uint32_t Get_ManagedThreadNum(void);

		//メンバ関数セット 関数==================================================================================================================================================================================================================================
		//引数6個まで実装
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val)
		{
			typedef SonikLib::Members_6_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M6FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_6_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M6FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val)
		{
			typedef SonikLib::Members_5_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M5FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val, arg5val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_5_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M5FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val, arg5val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			uint32_t TmpThreadNum = ManagedThreadNum;

			for(uint32_t i=0; i < TmpThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val)
		{
			typedef SonikLib::Members_4_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M4FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_4_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M4FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val, arg4val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val)
		{
			typedef SonikLib::Members_3_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val> M3FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M3FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_3_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val> M3FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M3FUNC_::New(pcls, pFunc, arg1val, arg2val, arg3val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val)
		{
			typedef SonikLib::Members_2_Func<CLSTYPE, Arg1Val, Arg2Val> M2FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M2FUNC_::New(pcls, pFunc, arg1val, arg2val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_2_Func<CLSTYPE, Arg1Val, Arg2Val> M2FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M2FUNC_::New(pcls, pFunc, arg1val, arg2val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val), Arg1Val arg1val)
		{
			typedef SonikLib::Members_1_Func<CLSTYPE, Arg1Val> M1FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M1FUNC_::New(pcls, pFunc, arg1val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val), Arg1Val arg1val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_1_Func<CLSTYPE, Arg1Val> M1FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M1FUNC_::New(pcls, pFunc, arg1val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(void))
		{
			typedef SonikLib::Members_0_Func<CLSTYPE> M0FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M0FUNC_::New(pcls, pFunc);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, std::enable_if_t<!std::is_pointer_v<CLSTYPE>, bool> = true>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(void), SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_0_Func<CLSTYPE> M0FUNC_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == nullptr || pFunc == nullptr)
			{
				return false;
			};

			tmp = M0FUNC_::New(pcls, pFunc);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		//静的関数セット 関数==============================================================================================================================================================================================================
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val)
		{
			typedef SonikLib::Members_6_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M6FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_6_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M6FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val)
		{
			typedef SonikLib::Members_5_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M5FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val, arg5val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_5_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M5FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val, arg5val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val)
		{
			typedef SonikLib::Members_4_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M4FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_4_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M4FUNCG_::New(pFunc, arg1val, arg2val, arg3val, arg4val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val)
		{
			typedef SonikLib::Members_3_FuncG<Arg1Val, Arg2Val, Arg3Val> M3FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M3FUNCG_::New(pFunc, arg1val, arg2val, arg3val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_3_FuncG<Arg1Val, Arg2Val, Arg3Val> M3FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M3FUNCG_::New(pFunc, arg1val, arg2val, arg3val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val)
		{
			typedef SonikLib::Members_2_FuncG<Arg1Val, Arg2Val> M2FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M2FUNCG_::New(pFunc, arg1val, arg2val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_2_FuncG<Arg1Val, Arg2Val> M2FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M2FUNCG_::New(pFunc, arg1val, arg2val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val), Arg1Val arg1val)
		{
			typedef SonikLib::Members_1_FuncG<Arg1Val> M1FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M1FUNCG_::New(pFunc, arg1val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val), Arg1Val arg1val, SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& GetSmtPtr)
		{
			typedef SonikLib::Members_1_FuncG<Arg1Val> M1FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M1FUNCG_::New(pFunc, arg1val);
			if(tmp.IsNullptr())
			{
				return false;
			};

			GetSmtPtr = tmp;

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		bool SetStaticFunction(void (*pFunc)(void))
		{
			typedef SonikLib::Members_0_FuncG M0FUNCG_;

			SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> tmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == nullptr)
			{
				return false;
			};

			tmp = M0FUNCG_::New(pFunc);
			if(tmp.IsNullptr())
			{
				return false;
			};

			JobQueue->EnQueue(tmp);

			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				if( m_pThreads[i].GetThreadStatusSuspend() )
				{
					m_pThreads[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};

		//c: セットしてあるジョブをキューから取得します。
		bool GetJobFunction(SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& jobfunc)
		{
			if( !JobQueue->DeQueue(jobfunc) )
			{
				return false;
			};

			return true;
		};

	}; //end class


};



#endif /* SONIKWORKTHREADMANAGEREX_H_ */
