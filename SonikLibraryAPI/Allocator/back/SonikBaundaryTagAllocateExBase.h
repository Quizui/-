/*
 * SonikBaundaryTagAllocateExBase.h
 *
 *  Created on: 2016/01/02
 *      Author: SONIK
 */

#ifndef ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_
#define ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_

#include <atomic>

#include "SonikFreeBlockDepthEnum.h"

namespace SonikBTMA
{
#ifdef __SONIK_I686__
	class SonikBaundaryTagAllocateEx_Base
	{
	public:
		//デストラクタ
		virtual ~SonikBaundaryTagAllocateEx_Base(void);

		//初期化
		virtual bool Initialize(uint32_t SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth) =0;

		//領域の取得
		virtual bool GetAlloc(void*& RefGetAllocPtr, std::atomic<uint32_t>*& RefGetRefCounter, uint32_t GetAllocSize, uint32_t ArrayCount) =0;

		//領域の開放
		virtual void FreeAlloc(void* pFreeObj) =0;

	};

#elif defined(__SONIK_x86_64__)
	class SonikBaundaryTagAllocateEx_Base
	{
	public:
		//デストラクタ
		virtual ~SonikBaundaryTagAllocateEx_Base(void);

		//初期化
		virtual bool Initialize(uint64_t SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth) =0;

		//領域の取得
		virtual bool GetAlloc(void*& RefGetAllocPtr, ::std::atomic<uint64_t>*& RefGetRefCounter, uint64_t GetAllocSize, uint64_t ArrayCount) =0;

		//領域の開放
		virtual void FreeAlloc(void* pFreeObj) =0;

	};
#endif
};



#endif /* ALLOCATOR_SONIKBAUNDARYTAGALLOCATEEXBASE_H_ */
