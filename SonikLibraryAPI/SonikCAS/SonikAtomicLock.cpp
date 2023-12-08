/*
 * SonikAtomicLock.cpp
 *
 *  Created on: 2016/01/09
 *      Author: SONIK
 */
#include "SonikAtomicLock.h"

namespace SonikLib
{
	namespace S_CAS
	{
		//コピーコンストラクタ
		SonikAtomicLock::SonikAtomicLock(const SonikAtomicLock& t_his)
			:_lock(false)
			 {
			 };

		//代入演算子
		SonikAtomicLock& SonikAtomicLock::operator =(const SonikAtomicLock& t_his)
		{
			return (*this);
		};

		//コンストラクタ
		SonikAtomicLock::SonikAtomicLock(void)
		:_lock(false)
		{

		};

		//デストラクタ
		SonikAtomicLock::~SonikAtomicLock(void)
		{

		};

		//ロックの開始
		//ロックの権利が取得出来た場合に処理が返されます。
		void SonikAtomicLock::lock(void)
		{
			bool a_right = false;

			//権利が false になるまでビジーループ
			while( !_lock.compare_exchange_strong(a_right, true, std::memory_order_acq_rel) )
			{
				//false の場合、 a_right は trueの値に書き換えられるので、falseに戻す。
				a_right = false;
			};

			//権利が獲得できたら関数を終了。処理を返す。

#ifdef _DEBUG
			//デバッグログ
//				SonikLogger::SonikLog::Instance().WriteLog("SonikAtomicBlock、　＝＝＝ ブロッキング獲得 ＝＝＝");
#endif
		};

		//ロックが取得出来た場合はtrue
		//できなかった場合はfalseを返却します。
		bool SonikAtomicLock::TryLock(void)
		{
			bool a_right = false;

			//権利が false になるまでビジーループ
			while( !_lock.compare_exchange_strong(a_right, true, std::memory_order_acq_rel) )
			{
				//false の場合、 a_right は trueの値に書き換えられるので、falseに戻す。
				return false;
			};

			return true;
		};

		//ロックの終了
		void SonikAtomicLock::Unlock(void)
		{
#ifdef _DEBUG
			//デバッグログ
//				SonikLogger::SonikLog::Instance().WriteLog("SonikAtomicBlock、　＝＝＝ ブロッキング終了 ＝＝＝");
#endif
			_lock.store(false, std::memory_order_release);
		};

	}; //end namespace CAS
}; //end namespace SonikLib


