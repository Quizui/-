/*
 * SonikBaundaryTagAllocateExBase.h
 *
 *  Created on: 2016/01/02
 *      Author: Sonik
 */

#ifndef ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_
#define ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_

#include <atomic>

#include "SonikFreeBlockDepthEnum.h"

namespace SonikBTMA
{
	class SonikBaundaryTagAllocateEx_Base
	{
	public:
		//デストラクタ
		virtual ~SonikBaundaryTagAllocateEx_Base(void);

		//初期化
		virtual bool Initialize(unsigned long SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth) =0;

		//領域の取得
		virtual bool GetAlloc(void*& RefGetAllocPtr, std::atomic<unsigned long>*& RefGetRefCounter, unsigned long GetAllocSize, unsigned long ArrayCount) =0;

		//領域の開放
		virtual void FreeAlloc(void* pFreeObj) =0;

	};

};



#endif /* ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_ */
