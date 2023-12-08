/*
 * SonikBaundaryTagAllocateEx.cpp
 *
 *  Created on: 2015/12/16
 *      Author: Sonik
 */

#include <new>
#include <algorithm>
#include "SonikAllocateFreeBlock.h"
#include "SonikBaundaryBlock.h"
#include "SonikBaundaryTagAllocateEx.h"
#include "SonikFreeBlockManager.h"

#define SonikBTMADefaultAllocSize 1024000	//デフォルトサイズ(1MB)
//#define SonikBTMADefaultReAllocSize 10240	//デフォルト再確保追加サイズ(10KB)

using namespace SonikBaundaryBlock;
using namespace SonikInnerPtr;

namespace SonikBTMA
{

	//メモリアロケータ本体実装
	class AllocImpl
	{
	private:

		unsigned long ManagedMemorySize;	//管理メモリサイズ
		unsigned long RemainderMemorySize;	//残メモリサイズ

		char* pMem;							//管理メモリ配列の先頭ポインタ

		SonikBTMAFreeBlock::FreeBlockManager* FreeList;	//フリーリスト管理クラス

		SonikLib::SonikAtomicLock atmblock_;

	public:
		//デフォルトコンストラクタ
		AllocImpl(void)
		:ManagedMemorySize(SonikBTMADefaultAllocSize + sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost))
		,RemainderMemorySize(SonikBTMADefaultAllocSize + sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost))
		,FreeList(0)
		{
			SonikBaundaryPre* PrePtr	=0;
			SonikBaundaryPost* PostPtr	=0;
			char* pMemEnd =0;

			try
			{
				//実使用メモリ領域の確保
				pMem = new char[ManagedMemorySize];
				std::fill_n(pMem, ManagedMemorySize, 0);

				//フリーリストメモリ領域の確保
				FreeList = new SonikBTMAFreeBlock::FreeBlockManager;
				if(!FreeList->Initialize(ManagedMemorySize, STLSF_Depth16))
				{
					throw std::bad_alloc();
				};

			}catch(std::bad_alloc& e)
			{
				if(pMem != 0)
				{
					delete[] pMem;
				};

				if(FreeList != 0)
				{
					delete FreeList;
				};
				throw e;
			};


			pMemEnd = pMem;

			//placement new で取得するので失敗しない。
			PrePtr = new(pMemEnd) SonikBaundaryPre;

			pMemEnd += sizeof(SonikBaundaryPre);
			PrePtr->SetUseFlag(false);
			PrePtr->UseUserMemorySize = (ManagedMemorySize - (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost)));

			pMemEnd += (ManagedMemorySize - (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost)));

			PostPtr = new(pMemEnd) SonikBaundaryPost;
			pMemEnd += sizeof(SonikBaundaryPost);
			PostPtr->PrePointer = PrePtr;

			FreeList->SetFreeBlock(PrePtr);
			RemainderMemorySize -= ( sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost) );
		};

		//コンストラクタオーバーロード
		AllocImpl(unsigned long SetAllocSize, SonikTLSFSecondCategoryBitDepth SetDepth = STLSF_Depth16)
		:ManagedMemorySize(SetAllocSize + sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost))
		,RemainderMemorySize(SetAllocSize + sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost))
		,pMem(0)
		,FreeList(0)
		{
			SonikBaundaryPre* PrePtr	=0;
			SonikBaundaryPost* PostPtr	=0;
			char* pMemEnd =0;

			if(ManagedMemorySize == 0)
			{
				ManagedMemorySize = SonikBTMADefaultAllocSize + sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost);
				RemainderMemorySize = ManagedMemorySize;
			};

			try
			{
				//実使用メモリ領域の確保
				pMem = new char[ManagedMemorySize];
				std::fill_n(pMem, ManagedMemorySize, 0);

				//フリーリストメモリ領域の確保
				FreeList = new SonikBTMAFreeBlock::FreeBlockManager;
				if(!FreeList->Initialize(ManagedMemorySize, SetDepth))
				{
					throw std::bad_alloc();
				};

			}catch(std::bad_alloc& e)
			{
				if(pMem != 0)
				{
					delete[] pMem;
				};

				if(FreeList != 0)
				{
					delete FreeList;
				};
				throw e;
			};


			pMemEnd = pMem;

			//placement new で取得するので失敗しない。
			PrePtr = new(pMemEnd) SonikBaundaryPre;

			pMemEnd += sizeof(SonikBaundaryPre);
			PrePtr->SetUseFlag(false);
			PrePtr->UseUserMemorySize = (ManagedMemorySize - (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost)));

			pMemEnd += (ManagedMemorySize - (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost)));

			PostPtr = new(pMemEnd) SonikBaundaryPost;
			pMemEnd += sizeof(SonikBaundaryPost);
			PostPtr->PrePointer = PrePtr;

			FreeList->SetFreeBlock(PrePtr);
			RemainderMemorySize -= ( sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost) );
		};

		~AllocImpl(void)
		{
			//フリーリストの開放
			delete FreeList;

			//管理メモリの開放
			delete[] pMem;

		};

		//メモリの取得
		SonikBaundaryPre* GetAlloc(unsigned long AllocSize)
		{
			if(AllocSize == 0)
			{
				return 0;
			};

			//1. フリーリストのチェック
			//2. あれば分割試行
			//3. 返却

			//フリーリストのチェック==========
			unsigned long tmpsize = AllocSize + (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost));
			SonikBaundaryPre* PrePtr = 0;

			//マルチスレッドブロック開始====
			atmblock_.lock();

			PrePtr = FreeList->GetFreeBlock(AllocSize);
			if(PrePtr == 0)
			{
				//なければ終了
				atmblock_.Unlock();
				return 0;
			};


			//分割試行====
//			pTmp = (pInnerTmp->Ptr - sizeof(SonikBaundaryPre));
//			PrePtr = reinterpret_cast<SonikBaundaryPre*>(pTmp);

			//条件が一致すれば分割せずにそのまま返却
			if( PrePtr->UseUserMemorySize <= tmpsize)
			{
				RemainderMemorySize -= PrePtr->UseUserMemorySize;
				PrePtr->Flag = true;
				PrePtr->RefCounter = 1;

				atmblock_.Unlock();
				return PrePtr;
			};

			//一致しなければ分割試行開始==
			char* pTmp = reinterpret_cast<char*>(PrePtr);
			SonikBaundaryPost* PostPtr =0;

			pTmp += ( sizeof(SonikBaundaryPre) + (PrePtr->UseUserMemorySize - tmpsize) );
			PostPtr = new(pTmp) SonikBaundaryPost;
			PostPtr->PrePointer = PrePtr;
			PrePtr->UseUserMemorySize -= tmpsize;
			pTmp += sizeof(SonikBaundaryPost);

			RemainderMemorySize -= tmpsize;

			//フリーリストに再登録
			FreeList->SetFreeBlock(PrePtr);


			//返却領域の作成
			PrePtr = new(pTmp) SonikBaundaryPre;
			PrePtr->Flag = true;
			PrePtr->UseUserMemorySize = AllocSize;
			PrePtr->RefCounter = 1;

			pTmp += (sizeof(SonikBaundaryPre) + AllocSize);
			PostPtr = reinterpret_cast<SonikBaundaryPost*>(pTmp);
			PostPtr->PrePointer = PrePtr;


			//マルチスレッドブロック解除
			atmblock_.Unlock();

			return PrePtr;
		};

		//領域の開放
		void FreeAlloc(void* pFree)
		{
			char* pTmp =0;
			SonikBaundaryPre* pControlPre = 0;
			SonikBaundaryPre* M_TopPrePtr = 0; //マージ前置タグ
			SonikBaundaryPost* pControlPost =0;
			SonikBaundaryPost* M_EndPostPtr = 0; //マージ後置タグ
			unsigned long remainder_ = 0;

			pTmp = reinterpret_cast<char*>(pFree);
			pControlPre = reinterpret_cast<SonikBaundaryPre*>( pTmp - sizeof(SonikBaundaryPre) );

			remainder_ += pControlPre->UseUserMemorySize;

			M_TopPrePtr = pControlPre;
			M_EndPostPtr = reinterpret_cast<SonikBaundaryPost*>( pTmp + pControlPre->UseUserMemorySize );

			//マルチスレッドブロック
			atmblock_.lock();

			pControlPre->Flag = false;

			//メモリ配列の先頭であればPrevは無いので前のポインタ結合は行わない。
			if(reinterpret_cast<char*>(pControlPre) != pMem)
			{
				pControlPost = reinterpret_cast<SonikBaundaryPost*>( pTmp - (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost)) );

				if( !pControlPost->PrePointer->Flag )
				{
					//未使用であれば、左マージ先をリストから外す。
//					Flags |= 0x02;
					M_TopPrePtr = pControlPost->PrePointer;
					FreeList->PtrListOff(pControlPost->PrePointer);

					remainder_ += (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost));
				};
			};

			//メモリ配列の終端であればNextは無いので後のポインタ結合は行わない。
			//メモリ配列の終端は、(メモリ配列の先頭(pMem)) + 総合管理メモリサイズ(ManagedMemorySize) - 後置タグサイズ
			if( (pTmp + pControlPre->UseUserMemorySize) != ((pMem + ManagedMemorySize) - sizeof(SonikBaundaryPost)) )
			{
				pControlPre = reinterpret_cast<SonikBaundaryPre*>( pTmp + pControlPre->UseUserMemorySize + sizeof(SonikBaundaryPost) );

				//未使用であれば、右マージ先をリストから外す。
				if( !pControlPre->Flag )
				{
//					Flags |= 0x01;
					FreeList->PtrListOff(pControlPre);

					pTmp = reinterpret_cast<char*>(pControlPre);
					pTmp += (sizeof(SonikBaundaryPre) + pControlPre->UseUserMemorySize);
					M_EndPostPtr = reinterpret_cast<SonikBaundaryPost*>(pTmp);

					remainder_ += (sizeof(SonikBaundaryPre) + sizeof(SonikBaundaryPost));
				};
			};

			M_EndPostPtr->PrePointer = M_TopPrePtr;

			pTmp = reinterpret_cast<char*>( M_TopPrePtr );
			pTmp += sizeof(SonikBaundaryPre);

			M_TopPrePtr->UseUserMemorySize = ( reinterpret_cast<unsigned long>(M_EndPostPtr) - reinterpret_cast<unsigned long>(pTmp) );

			std::fill( pTmp, reinterpret_cast<char*>(M_EndPostPtr), 0 );

			if( M_EndPostPtr->PrePointer == 0 )
			{
				M_EndPostPtr->PrePointer = M_TopPrePtr;
			};

			//フリーリストにセット
			RemainderMemorySize += remainder_;
			FreeList->SetFreeBlock(M_TopPrePtr);

			atmblock_.Unlock();
		};


	};//end class

	//pImplの親クラス実装==================================================

	//基底クラスデストラクタ
	SonikBaundaryTagAllocateEx_Base::~SonikBaundaryTagAllocateEx_Base(void)
	{
		//no process;
	};


	//コンストラクタ
	SonikBaundaryTagAllocateEx::SonikBaundaryTagAllocateEx(void)
	{
		pImpl = 0;
		RefCount = 1;
	};

	//コピーコンストラクタの禁止
	SonikBaundaryTagAllocateEx::SonikBaundaryTagAllocateEx(const SonikBaundaryTagAllocateEx& t_his)
	:pImpl(0)
	,RefCount(1)
	{

	};

	//デストラクタ
	SonikBaundaryTagAllocateEx::~SonikBaundaryTagAllocateEx(void)
	{
		if( pImpl != 0 )
		{
			::delete pImpl;
		};

	};

	//代入演算子の禁止
	SonikBaundaryTagAllocateEx& SonikBaundaryTagAllocateEx::operator =(const SonikBaundaryTagAllocateEx& t_his)
	{
		return (*this);
	};

	//初期化
	bool SonikBaundaryTagAllocateEx::Initialize(unsigned long SetAllocateSize, SonikTLSFSecondCategoryBitDepth SetDepth)
	{
		try
		{
			pImpl = new AllocImpl(SetAllocateSize, SetDepth);
		}catch(...)
		{
			return false;
		};

		return true;
	};

	//placement new
	void* SonikBaundaryTagAllocateEx::operator new(size_t size, void* ptr)
	{
		return ptr;
	};

	//placement delete
	void SonikBaundaryTagAllocateEx::operator delete(void* p, void* ptr)
	{
		return;
	}

	void SonikBaundaryTagAllocateEx::operator delete(void* p)
	{
		return;
	};

	//取得
	bool SonikBaundaryTagAllocateEx::GetAlloc(void*& RefGetAllocPtr, std::atomic<unsigned long>*& RefGetRefCounter, unsigned long GetAllocSize, unsigned long ArrayCount)
	{
		SonikBaundaryPre* ret_;
		char* pTmp;

		if( ArrayCount == 0)
		{
			return false;
		};

		ret_ = pImpl->GetAlloc(GetAllocSize * ArrayCount);

		if(ret_ == 0)
		{
			return false;
		};

		RefGetRefCounter = &ret_->RefCounter;

		pTmp = reinterpret_cast<char*>(ret_);
		RefGetAllocPtr = pTmp + sizeof(SonikBaundaryPre);

		return true;
	};


	//開放
	void SonikBaundaryTagAllocateEx::FreeAlloc(void* pFreeObj)
	{
		pImpl->FreeAlloc(pFreeObj);
	};


};//end namespace
