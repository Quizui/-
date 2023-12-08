/*
 * SonikWorkThreadManagerEx.h
 *
 *  Created on: 2015/09/24
 *      Author: Sonik
 */

#ifndef SONIKWORKTHREADMANAGEREX_H_
#define SONIKWORKTHREADMANAGEREX_H_

//#include <vector>
//#include <mutex>
#include <condition_variable>

#include "..\SonikAllocateUse.h"
#include "..\Function\TemplateFuncDefinition.hpp"
#include "..\\SonikContainerUse.h"
#include "..\\SonikCASLockUse.h"
#include "SonikWorkThreadEx.h"


namespace SonikThread
{
	class SonikThreadManagerEx
	{
	private:
		//管理スレッド数
		unsigned long ManagedThreadNum;

		bool Init_;

		std::atomic<unsigned long> notifycount_;

		//スレッドプール
		SonikLib::SonikAllocSmtPtr<SonikThread::WorkThreadEx> ThreadPoolArray;

		//アロケータ
		SonikLib::SonikAllocObjectPtr ThreadAllocate;	//スレッド用
		SonikLib::SonikAllocObjectPtr JobAllocate;		//ジョブ生成用
		SonikLib::SonikAllocObjectPtr PackAllocate;		//ジョブパック生成用

		SonikLib::SonikAtomicLock atmlock_;

		//ジョブキュー(MTロックフリー)
		SonikQueue::SonikAtomicQueue<SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack>>* JobQueue;


	private:
		//コンストラクタ
		SonikThreadManagerEx(void);
		//コピーコンストラクタ
		SonikThreadManagerEx(const SonikThreadManagerEx& t_his);
		//代入演算子
		SonikThreadManagerEx& operator =(const SonikThreadManagerEx& t_his);


	public:
//		//コンストラクタ
//		SonikThreadManagerEx(void);
		//デストラクタ
		~SonikThreadManagerEx(void);

		//イニシャライザ
		bool Initialize(unsigned long UseThreadNum =2, unsigned long JobBufferSize =1200);

		//インスタンス
		static SonikThreadManagerEx& Instance(void);

		//スレッド数の取得
		unsigned long Get_ManagedThreadNum(void);

		//メンバ関数セット 関数==================================================================================================================================================================================================================================
		//引数6個まで実装
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val)
		{
			typedef SonikLib::Members_6_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNC_;

			SonikLib::SonikAllocSmtPtr<M6FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M6FUNC_>&&>(packtmp);

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_6_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNC_;

			SonikLib::SonikAllocSmtPtr<M6FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M6FUNC_>&&>(tmp);

			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val)
		{
			typedef SonikLib::Members_5_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNC_;

			SonikLib::SonikAllocSmtPtr<M5FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M5FUNC_>&&>(packtmp);

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetClassFunction(CLSTYPE* pcls,void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_5_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNC_;

			SonikLib::SonikAllocSmtPtr<M5FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M5FUNC_>&&>(tmp);

			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val)
		{
			typedef SonikLib::Members_4_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNC_;

			SonikLib::SonikAllocSmtPtr<M4FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M4FUNC_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_4_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNC_;

			SonikLib::SonikAllocSmtPtr<M4FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M4FUNC_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

			unsigned long first_ = notifycount_.load();
			unsigned long second_ = first_ + 1;

//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val)
		{
			typedef SonikLib::Members_3_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val> M3FUNC_;

			SonikLib::SonikAllocSmtPtr<M3FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M3FUNC_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_3_Func<CLSTYPE, Arg1Val, Arg2Val, Arg3Val> M3FUNC_;

			SonikLib::SonikAllocSmtPtr<M3FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M3FUNC_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val, class Arg2Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val)
		{
			typedef SonikLib::Members_2_Func<CLSTYPE, Arg1Val, Arg2Val> M2FUNC_;

			SonikLib::SonikAllocSmtPtr<M2FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M2FUNC_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val, class Arg2Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_2_Func<CLSTYPE, Arg1Val, Arg2Val> M2FUNC_;

			SonikLib::SonikAllocSmtPtr<M2FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M2FUNC_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE, class Arg1Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val), Arg1Val arg1val)
		{
			typedef SonikLib::Members_1_Func<CLSTYPE, Arg1Val> M1FUNC_;

			SonikLib::SonikAllocSmtPtr<M1FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M1FUNC_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE, class Arg1Val>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(Arg1Val), Arg1Val arg1val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_1_Func<CLSTYPE, Arg1Val> M1FUNC_;

			SonikLib::SonikAllocSmtPtr<M1FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M1FUNC_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class CLSTYPE>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(void))
		{
			typedef SonikLib::Members_0_Func<CLSTYPE> M0FUNC_;

			SonikLib::SonikAllocSmtPtr<M0FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M0FUNC_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class CLSTYPE>
		bool SetClassFunction(CLSTYPE* pcls, void (CLSTYPE::*pFunc)(void), SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_0_Func<CLSTYPE> M0FUNC_;

			SonikLib::SonikAllocSmtPtr<M0FUNC_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pcls == 0 || pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp) )
			{
				return false;
			};

			tmp->SetObject(pcls);
			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M0FUNC_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
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

                        SonikLib::SonikAllocSmtPtr<M6FUNCG_> tmp;
                        SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

                        if(!Init_)
                        {
                                return false;
                        };

                        if(pFunc == 0)
                        {
                                return false;
                        };

                        if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val) )
                        {
                                return false;
                        };

                        tmp->SetFunc(pFunc);

                        if( !PackAllocate->GetAlloc(packtmp) )
                        {
                                return false;
                        };

                        packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M6FUNCG_>&&>(tmp);

                        JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

                        unsigned long TmpThreadNum = ManagedThreadNum;

                        for(unsigned long i=0; i < TmpThreadNum; ++i)
                        {
                                if( ThreadPoolArray[i].GetThreadStatusSuspend() )
                                {
                                        ThreadPoolArray[i].dispatchDeQueue();
                                        break;
                                };

                        };

                        return true;
                };
                template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val, class Arg6Val>
                bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, Arg6Val arg6val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
                {
                        typedef SonikLib::Members_6_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val> M6FUNCG_;

                        SonikLib::SonikAllocSmtPtr<M6FUNCG_> tmp;
                        SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

                        if(!Init_)
                        {
                                return false;
                        };

                        if(pFunc == 0)
                        {
                                return false;
                        };

                        if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val, arg6val) )
                        {
                                return false;
                        };

                        tmp->SetFunc(pFunc);

                        if( !PackAllocate->GetAlloc(packtmp) )
                        {
                                return false;
                        };

                        packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M6FUNCG_>&&>(tmp);
                        GetSmtPtr = packtmp->SmtPtrFunc;

                        JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

                        unsigned long TmpThreadNum = ManagedThreadNum;

                        for(unsigned long i=0; i < TmpThreadNum; ++i)
                        {
                                if( ThreadPoolArray[i].GetThreadStatusSuspend() )
                                {
                                        ThreadPoolArray[i].dispatchDeQueue();
                                        break;
                                };

                        };

                        return true;
                };


		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val)
		{
			typedef SonikLib::Members_5_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNCG_;

			SonikLib::SonikAllocSmtPtr<M5FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M5FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val, class Arg5Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, Arg5Val arg5val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_5_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val> M5FUNCG_;

			SonikLib::SonikAllocSmtPtr<M5FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val, arg5val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M5FUNCG_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val)
		{
			typedef SonikLib::Members_4_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNCG_;

			SonikLib::SonikAllocSmtPtr<M4FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M4FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val, class Arg4Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val, Arg4Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, Arg4Val arg4val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_4_FuncG<Arg1Val, Arg2Val, Arg3Val, Arg4Val> M4FUNCG_;

			SonikLib::SonikAllocSmtPtr<M4FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val, arg4val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M4FUNCG_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val)
		{
			typedef SonikLib::Members_3_FuncG<Arg1Val, Arg2Val, Arg3Val> M3FUNCG_;

			SonikLib::SonikAllocSmtPtr<M3FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M3FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val, class Arg3Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val, Arg3Val), Arg1Val arg1val, Arg2Val arg2val, Arg3Val arg3val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_3_FuncG<Arg1Val, Arg2Val, Arg3Val> M3FUNCG_;

			SonikLib::SonikAllocSmtPtr<M3FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val, arg3val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M3FUNCG_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val, class Arg2Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val)
		{
			typedef SonikLib::Members_2_FuncG<Arg1Val, Arg2Val> M2FUNCG_;

			SonikLib::SonikAllocSmtPtr<M2FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M2FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val, class Arg2Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val, Arg2Val), Arg1Val arg1val, Arg2Val arg2val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_2_FuncG<Arg1Val, Arg2Val> M2FUNCG_;

			SonikLib::SonikAllocSmtPtr<M2FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val, arg2val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M2FUNCG_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		template <class Arg1Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val), Arg1Val arg1val)
		{
			typedef SonikLib::Members_1_FuncG<Arg1Val> M1FUNCG_;

			SonikLib::SonikAllocSmtPtr<M1FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M1FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);

//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};
		template <class Arg1Val>
		bool SetStaticFunction(void (*pFunc)(Arg1Val), Arg1Val arg1val, SonikLib::SonikAllocSmtPtr<SonikLib::FunctionSystem_Base>& GetSmtPtr)
		{
			typedef SonikLib::Members_1_FuncG<Arg1Val> M1FUNCG_;

			SonikLib::SonikAllocSmtPtr<M1FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp, arg1val) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M1FUNCG_>&&>(tmp);
			GetSmtPtr = packtmp->SmtPtrFunc;

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


		bool SetStaticFunction(void (*pFunc)(void))
		{
			typedef SonikLib::Members_0_FuncG M0FUNCG_;

			SonikLib::SonikAllocSmtPtr<M0FUNCG_> tmp;
			SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack> packtmp;

			if(!Init_)
			{
				return false;
			};

			if(pFunc == 0)
			{
				return false;
			};

			if( !JobAllocate->GetAlloc(tmp) )
			{
				return false;
			};

			tmp->SetFunc(pFunc);

			if( !PackAllocate->GetAlloc(packtmp) )
			{
				return false;
			};

			packtmp->SmtPtrFunc = static_cast<SonikLib::SonikAllocSmtPtr<M0FUNCG_>&&>(tmp);

			JobQueue->EnQueue(packtmp);


//			unsigned long first_ = notifycount_.load();
//			unsigned long second_ = first_ + 1;
//
//			if(second_ >= ManagedThreadNum)
//			{
//				second_ = 0;
//			};
//
//			while( !notifycount_.compare_exchange_strong(first_, second_) )
//			{
//				second_ = first_ + 1;
//
//				if(second_ >= ManagedThreadNum)
//				{
//					second_ = 0;
//				};
//			};
//
//			ThreadPoolArray[second_].dispatchDeQueue();

			unsigned long TmpThreadNum = ManagedThreadNum;

			for(unsigned long i=0; i < TmpThreadNum; ++i)
			{
				if( ThreadPoolArray[i].GetThreadStatusSuspend() )
				{
					ThreadPoolArray[i].dispatchDeQueue();
					break;
				};

			};

			return true;
		};


	}; //end class


};



#endif /* SONIKWORKTHREADMANAGEREX_H_ */
