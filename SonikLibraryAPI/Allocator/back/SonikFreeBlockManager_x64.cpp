/*
 * SonikFreeBlockManager.cpp
 *
 *  Created on: 2015/12/16
 *      Author: SONIK
 */

#ifdef __SONIK_x86_64__

#include "SonikFreeBlockManager.h"

#include "..\\SonikMathBitsUse.h"
#include <new>
#include <cstdint>
#include "SonikAllocateFreeBlock.h"

namespace SonikBTMAFreeBlockGlobal
{
	//カテゴリ算出
	void GetCategory(uint64_t Val, uint64_t& First, uint64_t& Second, SonikTLSFSecondCategoryBitDepth SetDepth)
	{
		First = Val;
		Second = Val;

		//ファーストカテゴリの特定
		First = SonikMathBit::GetMSBFor32bit(Val);

		//セカンドカテゴリの特定
		uint64_t bit_ = 1;

		Second &= ((bit_ << First) -1);
		bit_ = 1;

		if(SetDepth == STLSF_Depth16)
		{
			Second =  (Second & (~((bit_ << (First - 4)) - 1))) >> (First - 4);

		}else if(SetDepth == STLSF_Depth32)
		{
			Second =  (Second & (~((bit_ << (First - 5)) - 1))) >> (First - 5);
		};

		//ファーストカテゴリのオフセット(配列の添字に合わせると 最大値は15なのでオフセット値として -1する)
		--First;

	};
};

namespace SonikBTMAFreeBlock
{
	//コンストラクタ
	FreeBlockManager::FreeBlockManager(void)
	:FirstFreeBit(0)
	,SecondCategoryBitDepth_(STLSF_Depth16)
	,FirstFreeList(0)
	{

	};

	//コピーコンストラクタの禁止
	FreeBlockManager::FreeBlockManager(const FreeBlockManager& t_his)
	:FirstFreeBit(0)
	,SecondCategoryBitDepth_(STLSF_Depth16)
	,FirstFreeList(0)
	{
		//処理無し。
	};

	//代入演算子の禁止
	FreeBlockManager& FreeBlockManager::operator =(const FreeBlockManager& t_his)
	{
		//処理無し。

		return (*this);
	};


	//デストラクタ
	FreeBlockManager::~FreeBlockManager(void)
	{
		if(FirstFreeList != 0)
		{
			delete[] FirstFreeList;
		};
	};

	//イニシャライザ
	bool FreeBlockManager::Initialize(uint64_t SetSize, SonikTLSFSecondCategoryBitDepth SetSecondBitDepth)
	{
		uint64_t Bit = SonikMathBit::GetMSBFor32bit(SetSize);

		//配列を作成する。
		try
		{
			FirstFreeList = new FirstFreeBlock[Bit];
		}catch(std::bad_alloc& e)
		{
			FirstFreeList = 0;
			return false;
		};

		for(uint64_t looped_ =0; looped_ < Bit; ++looped_)
		{
			if( !FirstFreeList[looped_].Initialize(SetSecondBitDepth) )
			{
				delete[] FirstFreeList;
				FirstFreeList = 0;
				return false;
			}

		};

		SecondCategoryBitDepth_ = SetSecondBitDepth;
		return true;
	};

	//フリーブロックをセットします。
	void FreeBlockManager::SetFreeBlock(SonikBaundaryBlock::SonikBaundaryPre* SetPtr)
	{
		uint64_t pValFirst =0;
		uint64_t pValSecondary = 0;

		if(SetPtr == 0)
		{
			return ;
		};

		pValFirst = SetPtr->UseUserMemorySize;

		//カテゴリの特定
		SonikBTMAFreeBlockGlobal::GetCategory(pValFirst, pValFirst, pValSecondary, SecondCategoryBitDepth_);


		if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s == 0 )
		{
			//一個もセットされていない場合。
			FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s = SetPtr;
		}else
		{
			//1個でもセットされている
			SetPtr->freelist_next = FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s;
			FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s->freelist_prev = SetPtr;
			FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s = SetPtr;

		};

		//ファーストビット列設定
		FirstFreeBit |= (0x01 << pValFirst);

		//セカンダリビット列設定
		FirstFreeList[pValFirst].SecondaryFreeBit |= (0x01 << pValSecondary);

	};

	//フリーブロックを取得します。
	SonikBaundaryBlock::SonikBaundaryPre* FreeBlockManager::GetFreeBlock(uint64_t GetSize)
	{
		uint64_t pValFirst = GetSize;
		uint64_t pValSecondary =  GetSize;
		uint64_t msbcount = 0;

		//カテゴリの特定
		SonikBTMAFreeBlockGlobal::GetCategory(GetSize, pValFirst, pValSecondary, SecondCategoryBitDepth_);

		SonikBaundaryBlock::SonikBaundaryPre* pControl = FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s;
		if(pControl != 0)
		{
			while(pControl != 0)
			{
				if( pControl->UseUserMemorySize < GetSize )
				{
					//取得値より小さければ次のポインタへ
					pControl = pControl->freelist_next;
					continue;
				};

				//見つかったらリストから外して返却
				if( pControl->freelist_prev == 0 )
				{
					//一番先頭のオブジェクトだった場合。
					FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s = pControl->freelist_next;
					if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s != 0 )
					{
						FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s->freelist_prev = 0;
					};

				}else
				{
					//違う場合。
					pControl->freelist_prev->freelist_next = pControl->freelist_next;
				};

				//ビット列フラグの変更
				if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s == 0)
				{
					//リストに何も無ければフラグを下ろす。
					FirstFreeList[pValFirst].SecondaryFreeBit &= (~(0x01 << pValSecondary));
				};

				if(FirstFreeList[pValFirst].SecondaryFreeBit == 0)
				{
					//セカンダリがすべてなくなったらファーストカテゴリのフラグもおろしておく。
					FirstFreeBit &= (~(0x01 << pValFirst));
				};

				pControl->freelist_next = 0;
				pControl->freelist_prev = 0;
				return pControl;
			};
		};//end while;

		//セカンダリリストになければ上のブロックを取得
		msbcount = FirstFreeList[pValFirst].SecondaryFreeBit & (~((0x01 << (pValSecondary+1)) -1));
		msbcount = SonikMathBit::GetLSBFor32bit(msbcount);
		if(msbcount == 0)
		{
			//セカンダリには一つもフリーリストが無いので第１カテゴリーから上位を探す。
			msbcount = FirstFreeBit & (~((0x01 << (pValFirst +1)) -1));
			msbcount = SonikMathBit::GetLSBFor32bit(msbcount);
			if(msbcount == 0)
			{
				//それもなければ取得失敗
				return 0;
			};

			//あればそのファーストカテゴリのセカンドカテゴリを見る。
			pValFirst = msbcount;
			pValSecondary = SonikMathBit::GetLSBFor32bit( FirstFreeList[pValFirst].SecondaryFreeBit );

		}else
		{
			pValSecondary = msbcount;
		};

		//分割とかは、外でやるので、返すだけ。
		pControl = FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s;
		if(pControl->freelist_next != 0)
		{
			pControl->freelist_next->freelist_prev = pControl->freelist_prev;
		};

		FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s = pControl->freelist_next;

		//ビット列フラグの変更
		if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s == 0)
		{
			FirstFreeList[pValFirst].SecondaryFreeBit &= (~(0x01 << pValSecondary));
		};

		if(FirstFreeList[pValFirst].SecondaryFreeBit == 0)
		{
			FirstFreeBit &= (~(0x01 << pValFirst));
		};

		pControl->freelist_next =0;
		pControl->freelist_prev =0;
		return pControl;
	};


	//指定された前置タグの連結を解除します。
	void FreeBlockManager::PtrListOff(SonikBaundaryBlock::SonikBaundaryPre* UnListPtr)
	{
		uint64_t pValFirst; 		//ファーストカテゴリ値
		uint64_t pValSecondary;	//セカンダリカテゴリ値

		//カテゴリの特定
		SonikBTMAFreeBlockGlobal::GetCategory(UnListPtr->UseUserMemorySize, pValFirst, pValSecondary, SecondCategoryBitDepth_);

		if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s ==  UnListPtr )
		{
			//フリーリストの先頭ポインタであればNextの置き換えを行う。
			if( UnListPtr->freelist_next != 0 )
			{
				UnListPtr->freelist_next->freelist_prev = 0;
			};

			FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s = UnListPtr->freelist_next;

		}else
		{
			//違えば自分の両脇を置き換え
			if( UnListPtr->freelist_next != 0 )
			{
				UnListPtr->freelist_next->freelist_prev = UnListPtr->freelist_prev;
			};

			if( UnListPtr->freelist_prev != 0 )
			{
				UnListPtr->freelist_prev->freelist_next = UnListPtr->freelist_next;
			};

		};

		//ビット列フラグの変更
		if( FirstFreeList[pValFirst].SecondaryArray[pValSecondary].FreePrePtr_s == 0)
		{
			//リストに何も無ければフラグを下ろす。
			FirstFreeList[pValFirst].SecondaryFreeBit &= (~(0x01 << pValSecondary));
		};

		if(FirstFreeList[pValFirst].SecondaryFreeBit == 0)
		{
			//セカンダリがすべてなくなったらファーストカテゴリのフラグもおろしておく。
			FirstFreeBit &= (~(0x01 << pValFirst));
		};

		UnListPtr->freelist_next = 0;
		UnListPtr->freelist_prev = 0;
	};


};

#endif
