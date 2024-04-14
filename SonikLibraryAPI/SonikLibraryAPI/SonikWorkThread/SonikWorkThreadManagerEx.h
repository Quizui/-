/*
 * SonikWorkThreadManagerEx.h
 *
 *  Created on: 2015/09/24
 *      Author: SONIK
 */

#ifndef SONIKWORKTHREADMANAGEREX_H_
#define SONIKWORKTHREADMANAGEREX_H_

#include "../SmartPointer/SonikSmartPointer.hpp"

//前方宣言===================================
namespace SonikFunctionObjectDefines
{
	class FunctionObjectSystemInterface;
};
//using
namespace SonikLib
{
	using SonikFOSInterface = SonikFunctionObjectDefines::FunctionObjectSystemInterface;

	namespace Container
	{
		template<class QueueType>
		class SonikAtomicQueue;
	};

	class WorkThreadEx;
};

namespace std
{
#if defined(_MSC_VER)
	class condition_variable_any;

#elif defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
	namespace _LIBCPP_ABI_NAMESPACE
	{
		class condition_variable_any;
	};

#else
	class condition_variable_any;

#endif
};

//========================================

namespace SonikLib
{
	class SonikThreadManagerEx
	{
	private:
		//管理スレッド数
		uint32_t ManagedThreadNum;
		//スレッドプール
		SonikLib::WorkThreadEx** m_pThreads;
		//ジョブキュー(MTロックフリー)
		SonikLib::SharedSmtPtr<SonikLib::Container::SonikAtomicQueue<SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>>> JobQueue;
		//スレッドに与えるcondition_variable_any
		SonikLib::SharedSmtPtr<std::condition_variable_any> m_cond;

	private:
		//コピーとムーブの禁止
		SonikThreadManagerEx(const SonikThreadManagerEx& _copy_) = delete;
		SonikThreadManagerEx(SonikThreadManagerEx&& _move_) = delete;
		SonikThreadManagerEx& operator =(const SonikThreadManagerEx& _copy_) = delete;
		SonikThreadManagerEx& operator =(SonikThreadManagerEx&& _move_) = delete;

		//コンストラクタ
		SonikThreadManagerEx(void);
	public:
		//デストラクタ
		~SonikThreadManagerEx(void);

		//クリエイタ
		static bool CreateThraedManager(SonikLib::SharedSmtPtr<SonikThreadManagerEx> _out_mng_, uint32_t UseThreadNum =2, uint32_t JobBufferSize =1200);

		//スレッド数の取得
		uint32_t Get_ManagedThreadNum(void);

		//タスクセット
		bool EnqueueJob(SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& _in_task_);
		//タスクゲット（余り時間処理参加用)
		bool DequeueJob(SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>& _out_task_);

	}; //end class


};



#endif /* SONIKWORKTHREADMANAGEREX_H_ */
