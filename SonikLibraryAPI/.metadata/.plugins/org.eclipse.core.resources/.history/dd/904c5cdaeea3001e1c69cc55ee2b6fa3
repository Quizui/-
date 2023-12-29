/*
 * SonikWorkThreadEx.cpp
 *
 *  Created on: 2015/09/23
 *      Author: SONIK
 */

#include "SonikWorkThreadEx.h"

#include "../FunctionObject/FunctionObjectSystemImpl.hpp"
#include "../SonikCAS/SonikAtomicLock.h"

#include <thread>
//#include <mutex>
#include <new>
#include <condition_variable>


namespace SonikThreadImpl
{

	//クラス定義=====================================
	//WorkThred本体
	class pImplEx
	{
	private:
		//スレッドオブジェクト
		std::thread threads_;

		//実際にコールする関数オブジェクト
		SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack> Access_; //受け取り口
		SonikThreadPack::ThreadPack FuncObj;

		//関数パックのキューオブジェクトへのポインタ
		SonikLib::SonikAtomicQueue<SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack>>* FuncQueue_;

		//CASロックオブジェクト(たぶんmutexより高速)
		SonikLib::S_CAS::SonikAtomicLock atmlock_;

		//静的関数で使う、条件変数
		std::condition_variable_any cond_;

		//1ビット目(0x01): 静的関数終了フラグ
		//2ビット目(0x02): セット関数の標準デリートフラグ
		//3ビット目(0x04): セット関数の終了フラグ(途中でセット内容を変えたい場合に使用、関数オブジェクトは標準デリートされない。)
		//		       ただし、セットしてある関数が終了しないと本フラグは意味をなさない。
		//4ビット目(0x08): デキュー停止フラグ。キューのアンセットに使用します。
		//5ビット目(0x10): スレッドが処理するジョブがなくて休止状態であるかどうか。
		//6ビット目(0x20): 各フラグのセット通知(一括変更通知でないと特定タイミングでDeleteフラグが無視されるため)
		uint32_t ThreadFlag;

		bool DetachFlag;

	private:
		static void SonikWorkThreadMainEx(void* ClassObject);

	public:
		//コンストラクタです。
		pImplEx(bool DetachThread);

		//デストラクタ
		~pImplEx(void);

		//コールする関数オブジェクトをセットします。
		bool SetCallFunction(SonikLib::SonikFOSInterface* CallFunctionObject, bool Deleted = false);
		bool SetCallFunction(SonikLib::NormalSmtPtr<SonikLib::SonikFOSInterface>& CallFunctionObject, bool Deleted = false);

		//静的関数内で使用
		SonikThreadPack::ThreadPack& GetFunctionPointer(void);
		std::condition_variable_any& GetConditionVariable(void);
		SonikLib::S_CAS::SonikAtomicLock& GetCASLockObject(void);
		uint32_t& GetThreadFlag(void);
		//キューのあんせっと
		void InnerUnsetQueue(void);



		//キューポインタが設定されていればデキューを行います。
		void UpdateQueue(void);

		//外部からコールする関数
		//スレッド終了フラグのセット
		void SetThreadExitFlag(bool Setflag);
		//セットしている関数の標準デリートフラグ
		void SetFunctionDeleteFlag(bool Setflag);
		//セット関数の終了フラグ(途中でセット内容を変えたい場合に使用、関数オブジェクトは標準デリートされない。)
		void SetChangeSetFuncFlag(bool Setflag);
		//キューアンセットフラグのセット
		void SetQueueUnsetFlag(bool Setflag);
		//サスペンド状態かどうかのフラグセット
		void SetThreadStatus_Suspend(bool Setfalg);

		//キューポインタをセットします。
		void SetFunctionQueue(SonikLib::SonikAtomicQueue<SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack>>* pSetQueue);
		//キューポインタをアンセットします。
		void UnSetFunctionQueue(void);

	};

	//静的メソッドの定義
	void SonikThreadImpl::pImplEx::SonikWorkThreadMainEx(void* ClassObject)
	{
		uint32_t& RefFlag = reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->GetThreadFlag();
		std::condition_variable_any& RefCond = reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->GetConditionVariable();
		SonikLib::S_CAS::SonikAtomicLock& RefLock = reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->GetCASLockObject();
		std::mutex localmtx;
		SonikThreadPack::ThreadPack& RefFuncObj = reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->GetFunctionPointer();


		while(1)
		{
			if(RefFuncObj.pFunc == nullptr && RefFuncObj.SmtPtrFunc == nullptr)
			{
				{
					std::unique_lock<std::mutex> lock(localmtx);
					//RefFuncが0以外になればロック解除。
					RefCond.wait(lock,
								[&RefFuncObj, &ClassObject, &RefFlag]{
																		 bool Geted_ = false;

																		 if((RefFlag & 0x08) != 0){reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->SetThreadStatus_Suspend(false);return true;};
																		 if((RefFlag & 0x01) != 0){reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->SetThreadStatus_Suspend(false);return true;};
																		 reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->UpdateQueue();
																		( RefFuncObj.pFunc == nullptr && RefFuncObj.SmtPtrFunc == nullptr ) ? Geted_ = false: Geted_ = true;
																		(Geted_) ? reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->SetThreadStatus_Suspend(false) : reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->SetThreadStatus_Suspend(true);
																		return Geted_;
																	 }
								);
				};

			};

			if( (RefFlag & 0x08) != 0 )
			{
				reinterpret_cast<SonikThreadImpl::pImplEx*>(ClassObject)->InnerUnsetQueue();
			};

			if( (RefFlag & 0x01) != 0 )
			{
				break;
			};

			if(RefFuncObj.pFunc != 0 )
			{
				RefFuncObj.pFunc->Run();
			};

			if(RefFuncObj.SmtPtrFunc != nullptr)
			{
				RefFuncObj.SmtPtrFunc->Run();
			}

			/*削除する？しない？*/
			if((RefFlag & 0x02) != 0)
			{
				if( RefFuncObj.pFunc != 0 )
				{
					delete RefFuncObj.pFunc;
					RefFuncObj.pFunc = 0;
					RefFlag &= (~0x02);
				};

				if(RefFuncObj.SmtPtrFunc != nullptr)
				{
					RefFuncObj.SmtPtrFunc.~NormalSmtPtr();
					RefFlag &= (~0x02);
				};
			};

			/*ファンクションの変更フラグが立っていれば、再生終了後、保持してるポインタ値を破棄*/
			if((RefFlag & 0x04) != 0)
			{
				RefFuncObj.pFunc = 0;
				RefFuncObj.SmtPtrFunc.~NormalSmtPtr();
				RefFlag &= (~0x04);
			};

			RefLock.Unlock();

		};

		//総合終了===================
		if(RefFuncObj.pFunc != 0)
		{
			if((RefFlag & 0x02) != 0)
			{
				delete RefFuncObj.pFunc;
				RefFuncObj.pFunc = 0;
				RefFlag &= (~0x02);
			};
		};

		if( RefFuncObj.SmtPtrFunc != nullptr)
		{
			RefFuncObj.SmtPtrFunc.~NormalSmtPtr();
			RefFlag &= (~0x02);
		}

		RefLock.Unlock();

	};

	//クラス実装=============================================
	SonikThreadImpl::pImplEx::pImplEx(bool DetachThread)
	:threads_(&SonikThreadImpl::pImplEx::SonikWorkThreadMainEx, this)
	,FuncQueue_(0)
	,ThreadFlag(0)
	,DetachFlag(DetachThread)

	{
		if( DetachThread )
		{
			threads_.detach();
		};


	};

	//デストラクタ
	SonikThreadImpl::pImplEx::~pImplEx(void)
	{
		SetThreadExitFlag(true);
		cond_.notify_one();

		if( !DetachFlag )
		{
			threads_.join();
		};



		if( (ThreadFlag & 0x02) != 0 && (FuncObj.pFunc != 0))
		{
			delete FuncObj.pFunc;
		};

		if( (ThreadFlag & 0x02) != 0 && (FuncObj.SmtPtrFunc != nullptr))
		{
			FuncObj.SmtPtrFunc.~NormalSmtPtr();
		};

	};

	//コールする関数オブジェクトをセットします。
	//本関数は成功した場合、スレッドにセットされた関数が終了するまで、再セットは行いません。
	bool pImplEx::SetCallFunction(SonikLib::SonikFOSInterface* CallFunctionObject, bool Deleted)
	{
		if( !atmlock_.TryLock() )
		{
			return false;
		};

		if( FuncQueue_ != 0 )
		{
			return false;
		};

		//セット
		FuncObj.pFunc = static_cast<SonikLib::SonikFOSInterface*&&>(CallFunctionObject);
		SetFunctionDeleteFlag(Deleted);
		cond_.notify_one();
		//ミューテックスのアンロックは静的関数内で行う。
		return true;

	};

	bool pImplEx::SetCallFunction(SonikLib::NormalSmtPtr<SonikLib::SonikFOSInterface>& CallFunctionObject, bool Deleted)
	{
		if( !atmlock_.TryLock() )
		{
			return false;
		};

		if( FuncQueue_ != 0 )
		{
			return false;
		};

		//セット
		FuncObj.SmtPtrFunc = static_cast<SonikLib::NormalSmtPtr<SonikLib::SonikFOSInterface>&&>(CallFunctionObject);
		SetFunctionDeleteFlag(Deleted);
		cond_.notify_one();
		//ミューテックスのアンロックは静的関数内で行う。
		return true;
	};

	SonikThreadPack::ThreadPack& pImplEx::GetFunctionPointer(void)
	{
		return FuncObj;
	};

	std::condition_variable_any& pImplEx::GetConditionVariable(void)
	{
		return cond_;
	};

	SonikLib::S_CAS::SonikAtomicLock& pImplEx::GetCASLockObject(void)
	{
		return atmlock_;
	};

	uint32_t& pImplEx::GetThreadFlag(void)
	{
		return ThreadFlag;
	};

	//キューポインタが設定されていればデキューを行います。
	void pImplEx::UpdateQueue(void)
	{
		if( FuncQueue_ == 0 )
		{
			return;
		};

		FuncQueue_->DeQueue(Access_);

		if( Access_ != nullptr )
		{
			FuncObj.SmtPtrFunc = Access_->SmtPtrFunc;

			Access_.~NormalSmtPtr();
			SetFunctionDeleteFlag(true);
		};
	};

	//スレッド終了フラグのセット
	void SonikThreadImpl::pImplEx::SetThreadExitFlag(bool Setflag)
	{
		(Setflag == true) ?  (ThreadFlag = ThreadFlag | 0x01) : (ThreadFlag = ThreadFlag & (~0x01));

	};
	//セットしている関数の標準デリートフラグ
	void pImplEx::SetFunctionDeleteFlag(bool Setflag)
	{
		(Setflag == true) ?  (ThreadFlag = ThreadFlag | 0x02) : (ThreadFlag = ThreadFlag & (~0x02));
	};
	//セット関数の終了フラグ(途中でセット内容を変えたい場合に使用、関数オブジェクトは標準デリートされない。)
	void pImplEx::SetChangeSetFuncFlag(bool Setflag)
	{
		(Setflag == true) ?  (ThreadFlag = ThreadFlag | 0x04) : (ThreadFlag = ThreadFlag & (~0x04));
	};

	//キューアンセットフラグのセット
	void pImplEx::SetQueueUnsetFlag(bool Setflag)
	{
		(Setflag == true) ?  (ThreadFlag = ThreadFlag | 0x08) : (ThreadFlag = ThreadFlag & (~0x08));
	};

	//サスペンド状態かどうかのフラグセット
	void pImplEx::SetThreadStatus_Suspend(bool Setflag)
	{
		(Setflag == true) ?  (ThreadFlag = ThreadFlag | 0x10) : (ThreadFlag = ThreadFlag & (~0x10));
	};


	//キューのあんせっと
	void pImplEx::InnerUnsetQueue(void)
	{
		FuncQueue_ = 0;
		SetQueueUnsetFlag(false);
	};

	//キューポインタをセットします。
	void pImplEx::SetFunctionQueue(SonikLib::SonikAtomicQueue<SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack>>* pSetQueue)

	{
		atmlock_.lock();

		FuncQueue_ = pSetQueue;

		atmlock_.Unlock();
	};

	//キューポインタをアンセットします。
	void pImplEx::UnSetFunctionQueue(void)
	{
		ThreadFlag |= 0x08;

		while( (ThreadFlag & 0x08) != 0 );

	};


};

namespace SonikLib
{

	//============================================================================================
	//Implクラスと外部をつなぐクラス実装
	//============================================================================================
	//本クラスのコンストラクタです。
	WorkThreadEx::WorkThreadEx(bool DetachThread)
	{
		ImplObject = 0;

		try
		{
			try
			{
				ImplObject = new SonikThreadImpl::pImplEx(DetachThread);

			}catch(std::bad_alloc& e)
			{
				throw -1;
			};
		}catch(...)
		{
			throw -1;
		};
	};

	//本クラスのデストラクタです。
	WorkThreadEx::~WorkThreadEx(void)
	{
		if(ImplObject != 0)
		{
			delete ImplObject;
		};

	};

	//関数オブジェクトポインタをセットします。
	//引数1: スレッドで実行する関数オブジェクトを設定します。
	//引数2: 指定した作成オブジェクトへのポインタを
	//		 new演算子より作成した場合にコール終了後にデリートするかのフラグを指定します。
	//		 ローカルで直接作成して指定した場合にデリートフラグをtrueにした場合、そのままdeletがコールされますが
	//		 動作は未定義です。 deleteをコール後実行してほしい場合はtrue, してほしくない場合はfalseを指定します。
	//		 デフォルトはfalseです。
	//戻り値; スレッドが実行中の場合はfalseが返り、セットされません。
	//		  そのままnewで指定した場合はフラグがfalseの場合はdeleteされません。(メモリリークの危険)
	//このメソッドがfalseで返ってきた場合、deleteFlag設定は無視されます。(deleteされません)
	//本関数はスレッドセーフです。
	//確実にセットしたい場合、前にセットされた関数があれば、それが終了し、関数がtrueを返却するまでループします。
	//別途QUEUEがセットされている場合、この関数は必ずfalseを返却します。
	//マルチスレッドにより、同時にキューセットと本関数が呼ばれた場合で、本関数が先にコールされた場合、本関数は、trueを返却します。
	bool WorkThreadEx::SetCallFunction(SonikLib::SonikFOSInterface* CallFunctionObject, bool DeleteFlag)
	{
		return ImplObject->SetCallFunction(CallFunctionObject, DeleteFlag);
	};
	bool WorkThreadEx::SetCallFunction(SonikLib::NormalSmtPtr<SonikLib::SonikFOSInterface> CallFunctionObject, bool DeleteFlag)
	{
		return ImplObject->SetCallFunction(CallFunctionObject, DeleteFlag);
	};

	//外部のキューをセットします。
	//本関数はSetCallFunctionと同時にコールされた場合で、SetCallFunctionが先に実行された場合、セットされた関数が終了するまで処理を返却しません。
	//本関数によりキューがセットされた後は、SetCallFunctionは無効となり、常にfalseを返却します。
	//本関数でセットしたキューにエンキューを行った場合、dispatchQueue関数をコールし、エンキューを行ったことを通知しなければデキュー処理を行いません。
	void WorkThreadEx::Set_ExternalQueue(SonikLib::SonikAtomicQueue<SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack>>* pSetQueue)
	{
		ImplObject->SetFunctionQueue(pSetQueue);
	};

	//外部のキューをアンセットします。
	void WorkThreadEx::UnSet_ExternalQueue(void)
	{
		ImplObject->UnSetFunctionQueue();
	};

	//スレッドにデキューの開始を通知します。
	void WorkThreadEx::dispatchDeQueue(void)
	{
		ImplObject->GetConditionVariable().notify_one();
	};

	//スレッド実行中に設定を変更したい場合に使う関数群========
	//デリートフラグを ON にします。 SetCalFunction（）の設定をfalseにし、後に変更したくなった場合に使用します。
	//現在のファンクションが終了し、判定箇所に来た場合に実行されます。
	//設定関数実行後、判定箇所をスレッドが通過済みの場合、次の設定関数コール終了後に判定が行われます。
	void WorkThreadEx::SetFunctionDeleteFlagOn(void)
	{
		ImplObject->SetFunctionDeleteFlag(true);
	};

	//スレッドの終了フラグをOnにします。
	//これはSetFunctionDeleteFlagOn()関数と同様の判定方法を行います。
	//よって、即時に終了されるわけではありません。
	void WorkThreadEx::SetThreadExitFlagOn(void)
	{
		ImplObject->SetThreadExitFlag(true);
	};

	//現在のスレッドがサスペンド状態にあるかどうかを取得します。
	//稼働中であればfalse, サスペンド状態であればTrueを返却します。
	bool WorkThreadEx::GetThreadStatusSuspend(void)
	{
		if( ( ImplObject->GetThreadFlag() & (0x10) ) != 0 )
		{
			return true;
		};

		return false;
	};




}; //end namespace
