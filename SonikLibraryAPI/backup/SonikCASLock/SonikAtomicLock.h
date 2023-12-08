/*
 * SonikAtomicBlock.h
 *
 *  Created on: 2015/10/07
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef SONIKATOMICBLOCK_H_
#define SONIKATOMICBLOCK_H_

#include <atomic>

#ifdef _DEBUG
#include "..//SonikLoggerUse.h"

#endif

namespace SonikLib
{
	class SonikAtomicLock
	{
	private:
		std::atomic<bool> _lock;

	private:
		//コピーコンストラクタ
		SonikAtomicLock(const SonikAtomicLock& t_his);

		//代入演算子
		SonikAtomicLock& operator =(const SonikAtomicLock& t_his);

	public:
		//コンストラクタ
		SonikAtomicLock(void);

		//デストラクタ
		~SonikAtomicLock(void);

		//ロックの開始
		//ロックの権利が取得出来た場合に処理が返されます。
		void lock(void);

		//ロックが取得出来た場合はtrue
		//できなかった場合はfalseを返却します。
		bool TryLock(void);

		//ロックの終了
		void Unlock(void);

	};


};


#endif /* SONIKATOMICBLOCK_H_ */
