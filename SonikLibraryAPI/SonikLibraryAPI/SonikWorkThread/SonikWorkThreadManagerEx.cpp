/*
 * SonikWorkThreadManagerEx.cpp
 *
 *  Created on: 2015/09/24
 *      Author: SONIK
 */

#include <new>

//#define private public
#include "SonikWorkThreadManagerEx.h"
//#undef private

namespace SonikLib
{
	//コンストラクタ
	SonikThreadManagerEx::SonikThreadManagerEx(void)
	:ManagedThreadNum(0)
	 ,m_pThreads(nullptr)
	,Init_(false)
	,notifycount_(0)
	,JobQueue(0)
	{

	};

	//コピーコンストラクタ
	SonikThreadManagerEx::SonikThreadManagerEx(const SonikThreadManagerEx& t_his)
	:ManagedThreadNum(0)
	,m_pThreads(nullptr)
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
		//スレッド始末。
		if( m_pThreads != nullptr)
		{
			delete[] m_pThreads;
		};

		//JobQueue始末
		if( JobQueue != nullptr )
		{
			delete JobQueue;
		};

	};

	//イニシャライザ
	bool SonikThreadManagerEx::Initialize(uint32_t UseThreadNum, uint32_t JobBufferSize)
	{
		atmlock_.lock();

		if( Init_ )
		{
			atmlock_.Unlock();
			return true;
		};

		try
		{
			JobQueue = new SonikLib::SonikAtomicQueue<SonikLib::NormalSmtPtr<SonikThreadPack::ThreadPack>>(JobBufferSize);
			m_pThreads = new SonikLib::WorkThreadEx[UseThreadNum];

		}catch(...)
		{
			delete[] m_pThreads;
			delete JobQueue;

			atmlock_.Unlock();
			return false;
		};

		for(unsigned long looped_=0; looped_ < UseThreadNum; ++looped_)
		{
			m_pThreads[looped_].Set_ExternalQueue(JobQueue);
		};

		ManagedThreadNum = UseThreadNum;

		Init_ = true;

		atmlock_.Unlock();
		return true;
	};

	//スレッド数の取得
	uint32_t SonikThreadManagerEx::Get_ManagedThreadNum(void)
	{
		return ManagedThreadNum;
	};

};//end namespace;
