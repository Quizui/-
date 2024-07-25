/*
 * SonikBaundaryTagAllocateEx.h
 *
 *  Created on: 2015/12/16
 *      Author: SONIK
 */

#ifndef SONIKBAUNDARYTAGALLOCATEEX_H_
#define SONIKBAUNDARYTAGALLOCATEEX_H_

#include "../SonikCASUse.h"
#include "SonikAllocateExUserUseSmtPtr.h"
#include "SonikAllocateRawExUserUseObjectSmtPtr.h"
#include "SonikFreeBlockDepthEnum.h"
#include <new>
#include <cstdint>

//namespace SonikBaundaryBlock
//{
//	class SonikBaundaryPre;
//	class SonikBaundaryPost;
//};

namespace SonikLibCall
{
#ifdef __SONIK_I686__
	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
#elif defined(__SONIK_x86_64__)
	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
#endif
};

//(B)aundary
//(T)ag
//(M)emory
//(A)llocate
namespace SonikBTMA
{
#ifdef __SONIK_I686__
//32bit definition
	//前方宣言
	class AllocImpl;

	class SonikBaundaryTagAllocateEx : public SonikBaundaryTagAllocateEx_Base
	{
		friend bool SonikLibCall::CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
		friend bool SonikLibCall::CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint32_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	private:
		AllocImpl* pImpl;
		std::atomic<uint32_t> RefCount;

	private:
		//コピーコンストラクタの禁止
		SonikBaundaryTagAllocateEx(const SonikBaundaryTagAllocateEx& t_his);

		//代入演算子の禁止
		SonikBaundaryTagAllocateEx& operator =(const SonikBaundaryTagAllocateEx& t_his);

	public:
		//コンストラクタ
		SonikBaundaryTagAllocateEx(void);

		//デストラクタ
		~SonikBaundaryTagAllocateEx(void);

		//初期化
		bool Initialize(uint32_t SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

		//placement new
		void* operator new(size_t size, void* ptr);

		//placement delete
		void operator delete(void* p, void* ptr);
		//非placement delete
		void operator delete(void* p);

		//領域の取得
		bool GetAlloc(void*& RefGetAllocPtr, std::atomic<uint32_t>*& RefGetRefCounter, uint32_t GetAllocSize, uint32_t ArrayCount);

		//領域の開放
		void FreeAlloc(void* pFreeObj);

	};
#elif defined(__SONIK_x86_64__)
//64bit definition
	//前方宣言
	class AllocImpl;

	class SonikBaundaryTagAllocateEx : public SonikBaundaryTagAllocateEx_Base
	{
		friend bool SonikLibCall::CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
		friend bool SonikLibCall::CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, uint64_t AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	private:
		AllocImpl* pImpl;
		std::atomic<uint64_t> RefCount;

	private:
		//コピーコンストラクタの禁止
		SonikBaundaryTagAllocateEx(const SonikBaundaryTagAllocateEx& t_his);

		//代入演算子の禁止
		SonikBaundaryTagAllocateEx& operator =(const SonikBaundaryTagAllocateEx& t_his);

	public:
		//コンストラクタ
		SonikBaundaryTagAllocateEx(void);

		//デストラクタ
		~SonikBaundaryTagAllocateEx(void);

		//初期化
		bool Initialize(uint64_t SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

		//placement new
		void* operator new(size_t size, void* ptr);

		//placement delete
		void operator delete(void* p, void* ptr);
		//非placement delete
		void operator delete(void* p);

		//領域の取得
		bool GetAlloc(void*& RefGetAllocPtr, std::atomic<uint64_t>*& RefGetRefCounter, uint64_t GetAllocSize, uint64_t ArrayCount);

		//領域の開放
		void FreeAlloc(void* pFreeObj);

	};

#endif
};

#endif /* SONIKBAUNDARYTAGALLOCATEEX_H_ */
