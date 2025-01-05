/*
 * SonikWorkThreadManagerEx.cpp
 *
 *  Created on: 2015/09/24
 *      Author: SONIK
 */

#include "SonikWorkThreadManagerEx.h"
#include "SonikWorkThreadEx.h"
#include "../Container/SonikAtomicQueue.hpp"
#include "../FunctionObject/FunctionObjectSystemInterface.hpp"

#include <new>
#include <condition_variable>

namespace SonikLib
{
	//コンストラクタ
	SonikThreadManagerEx::SonikThreadManagerEx(void)
	:ManagedThreadNum(0)
	,m_pThreads(nullptr)
	{

	};

	//デストラクタ
	SonikThreadManagerEx::~SonikThreadManagerEx(void)
	{
		//スレッド始末。
		if( m_pThreads != nullptr )
		{
			for(uint32_t i=0; i < ManagedThreadNum; ++i)
			{
				delete m_pThreads[i];
			};

		};

	};

	//クリエイタ
	bool SonikThreadManagerEx::CreateThraedManager(SonikLib::SharedSmtPtr<SonikThreadManagerEx> _out_mng_, uint32_t UseThreadNum, uint32_t JobBufferSize)
	{
		SonikThreadManagerEx* lp_mngobj = new(std::nothrow) SonikThreadManagerEx;
		if(lp_mngobj == nullptr)
		{
			return false;
		};

		lp_mngobj->ManagedThreadNum = UseThreadNum;

		if(!SonikLib::SharedSmtPtr<std::condition_variable_any>::SmartPointerCreate(new(std::nothrow) std::condition_variable_any, lp_mngobj->m_cond))
		{
			delete lp_mngobj;
			return false;
		};
		if(lp_mngobj->m_cond.IsNullptr())
		{
			delete lp_mngobj;
			return false;
		};

		using l_sharedQueue = SonikLib::SharedSmtPtr<SonikLib::Container::SonikAtomicQueue<SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>>>;

		
		if( !l_sharedQueue::SmartPointerCreate(new(std::nothrow) SonikLib::Container::SonikAtomicQueue<SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>>(JobBufferSize), lp_mngobj->JobQueue) )
		{
			return false;
		};
		if( lp_mngobj->JobQueue.IsNullptr() )
		{
			return false;
		};

		lp_mngobj->m_pThreads = new(std::nothrow)  SonikLib::WorkThreadEx*[UseThreadNum]{};
		if( lp_mngobj->m_pThreads == nullptr )
		{
			delete lp_mngobj;
			return false;
		};

		for(uint32_t i=0; i < UseThreadNum; ++i)
		{
			lp_mngobj->m_pThreads[i] = new(std::nothrow) SonikLib::WorkThreadEx(lp_mngobj->m_cond);
			if( lp_mngobj->m_pThreads[i] == nullptr)
			{
				delete lp_mngobj;
				return false;
			};

			lp_mngobj->m_pThreads[i]->Set_ExternalQueue(lp_mngobj->JobQueue);
		};

		
		if( !SonikLib::SharedSmtPtr<SonikThreadManagerEx>::SmartPointerCreate(lp_mngobj, _out_mng_) )
		{
			delete lp_mngobj;
			return false;
		};

		return true;
	};

	//スレッド数の取得
	uint32_t SonikThreadManagerEx::Get_ManagedThreadNum(void)
	{
		return ManagedThreadNum;
	};

	//タスクセット
	bool SonikThreadManagerEx::EnqueueJob(SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& _in_task_)
	{
		return  JobQueue->EnQueue(_in_task_);
	};
	//タスクゲット（余り時間処理参加用)
	bool SonikThreadManagerEx::DequeueJob(SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& _out_task_)
	{
		return JobQueue->DeQueue(_out_task_);
	};

};//end namespace;
