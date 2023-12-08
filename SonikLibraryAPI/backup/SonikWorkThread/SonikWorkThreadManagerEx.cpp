/*
 * SonikWorkThreadManagerEx.cpp
 *
 *  Created on: 2015/09/24
 *      Author: Sonik
 */

#define private public
#include "SonikWorkThreadManagerEx.h"
#undef private

namespace SonikThread
{
	//コンストラクタ
	SonikThreadManagerEx::SonikThreadManagerEx(void)
	:ManagedThreadNum(0)
	,Init_(false)
	,notifycount_(0)
	,JobQueue(0)
	{

	};

	//コピーコンストラクタ
	SonikThreadManagerEx::SonikThreadManagerEx(const SonikThreadManagerEx& t_his)
	:ManagedThreadNum(0)
	,Init_(false)
	,notifycount_(0)
	,JobQueue(0)
	{
	//処理無し。本クラスはコピーを許可しない。
	};

	//代入演算子
	SonikThreadManagerEx& SonikThreadManagerEx::operator =(const SonikThreadManagerEx& t_his)
	{
		//処理無し。本クラスは代入を許可しない。
		return (*this);
	};

	//デストラクタ
	SonikThreadManagerEx::~SonikThreadManagerEx(void)
	{
		//JobQueue以外勝手に始末してくれそうな勢い

		if( JobQueue != 0 )
		{
			delete JobQueue;
		};

	};

	//イニシャライザ
	bool SonikThreadManagerEx::Initialize(unsigned long UseThreadNum, unsigned long JobBufferSize)
	{
		atmlock_.lock();

		if( Init_ )
		{
			atmlock_.Unlock();
			return true;
		};

		try
		{
			JobQueue = new SonikQueue::SonikAtomicQueue<SonikLib::SonikAllocSmtPtr<SonikThreadPack::ThreadPack>>(JobBufferSize);

		}catch(...)
		{
			atmlock_.Unlock();
			return false;
		};

		if(JobQueue == 0)
		{
			atmlock_.Unlock();
			return false;
		};


		if( !SonikLibCall::CreateSonikMemoryAllocaor(ThreadAllocate, (sizeof(SonikThread::WorkThreadEx) * UseThreadNum)) )
		{
			atmlock_.Unlock();
			return false;
		};

		if( !ThreadAllocate->GetAllocArray(ThreadPoolArray, UseThreadNum) )
		{
			ThreadAllocate.~SonikAllocObjectPtr();
			atmlock_.Unlock();
			return false;
		};

		for(unsigned long looped_=0; looped_ < UseThreadNum; ++looped_)
		{
			ThreadPoolArray[looped_].Set_ExternalQueue(JobQueue);
		};


		if( !SonikLibCall::CreateSonikMemoryAllocaor(JobAllocate, (128 * JobBufferSize)) )
		{
			ThreadPoolArray.~SonikAllocSmtPtr();
			ThreadAllocate.~SonikAllocObjectPtr();
			atmlock_.Unlock();
			return false;
		};

		if( !SonikLibCall::CreateSonikMemoryAllocaor(PackAllocate, (sizeof(SonikThreadPack::ThreadPack) * JobBufferSize)) )
		{
			ThreadPoolArray.~SonikAllocSmtPtr();
			ThreadAllocate.~SonikAllocObjectPtr();
			JobAllocate.~SonikAllocObjectPtr();
			atmlock_.Unlock();
			return false;
		};

		ManagedThreadNum = UseThreadNum;

		Init_ = true;

		atmlock_.Unlock();
		return true;
	};

	//インスタンス
	SonikThreadManagerEx& SonikThreadManagerEx::Instance(void)
	{
		static SonikThreadManagerEx _inst;

		return _inst;
	};


	//スレッド数の取得
	unsigned long SonikThreadManagerEx::Get_ManagedThreadNum(void)
	{
		return ManagedThreadNum;
	};

};//end namespace;
