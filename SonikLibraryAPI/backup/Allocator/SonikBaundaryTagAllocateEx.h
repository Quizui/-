/*
 * SonikBaundaryTagAllocateEx.h
 *
 *  Created on: 2015/12/16
 *      Author: Sonik
 */

#ifndef SONIKBAUNDARYTAGALLOCATEEX_H_
#define SONIKBAUNDARYTAGALLOCATEEX_H_

#include "..\\SonikCASLockUse.h"
#include "SonikAllocateExUserUseSmtPtr.h"
#include "SonikFreeBlockDepthEnum.h"

//namespace SonikBaundaryBlock
//{
//	class SonikBaundaryPre;
//	class SonikBaundaryPost;
//};

namespace SonikLibCall
{
	bool CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	bool CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
};

//(S)onik
//(B)aundary
//(T)ag
//(M)emory
//(A)llocate
namespace SonikBTMA
{
	//前方宣言
	class AllocImpl;

	class SonikBaundaryTagAllocateEx : public SonikBaundaryTagAllocateEx_Base
	{
		friend bool SonikLibCall::CreateSonikMemoryAllocaor(SonikLib::SonikAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
		friend bool SonikLibCall::CreateSonikMemoryAllocaorRaw(SonikLib::SonikRawAllocObjectPtr& GetPtr, unsigned long AllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth);
	private:
		AllocImpl* pImpl;
		std::atomic<unsigned long> RefCount;

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
		bool Initialize(unsigned long SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16);

		//placement new
		void* operator new(size_t size, void* ptr);

		//placement delete
		void operator delete(void* p, void* ptr);
		//非placement delete
		void operator delete(void* p);

		//領域の取得
		bool GetAlloc(void*& RefGetAllocPtr, std::atomic<unsigned long>*& RefGetRefCounter, unsigned long GetAllocSize, unsigned long ArrayCount);

		//領域の開放
		void FreeAlloc(void* pFreeObj);

	};


};

#endif /* SONIKBAUNDARYTAGALLOCATEEX_H_ */
