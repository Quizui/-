/*
 * SonikFreeBlockManager.h
 *
 *  Created on: 2015/12/16
 *      Author: SONIK
 */

#ifndef SONIKFREEBLOCKMANAGER_H_
#define SONIKFREEBLOCKMANAGER_H_

#include "SonikBaundaryBlock.h"
#include "SonikFreeBlockDepthEnum.h"

namespace SonikInnerPtr
{
	class BTMAInnerPtr;
};

namespace SonikBTMAFreeBlock
{
	//第1カテゴリクラス
	class FirstFreeBlock;
};

namespace SonikBTMAFreeBlock
{
#ifdef __SONIK_I686__
	//フリーブロックリストを管理するクラスです。
	class FreeBlockManager
	{
	private:
		uint32_t FirstFreeBit; //第1カテゴリのビット列
		SonikTLSFSecondCategoryBitDepth SecondCategoryBitDepth_;	//第２カテゴリビット深度(分割数)
		FirstFreeBlock* FirstFreeList; //第1カテゴリのフリーリスト配列

	private:
		//コピーコンストラクタの禁止
		FreeBlockManager(const FreeBlockManager& t_his);

		//代入演算子の禁止
		FreeBlockManager& operator =(const FreeBlockManager& t_his);

	public:
		//コンストラクタ
		FreeBlockManager(void);
		//デストラクタ
		~FreeBlockManager(void);

		//イニシャライザ
		bool Initialize(uint32_t SetSize, SonikTLSFSecondCategoryBitDepth SetSecondBitDepth = STLSF_Depth16 );

		//フローブロックをセットします。
		void SetFreeBlock(SonikBaundaryBlock::SonikBaundaryPre* SetPtr);

		//フリーブロックを取得します。
		SonikBaundaryBlock::SonikBaundaryPre* GetFreeBlock(uint32_t GetSize);

		//指定された前置タグの連結を解除します。
		void PtrListOff(SonikBaundaryBlock::SonikBaundaryPre* UnListPtr);

	};

#elif defined(__SONIK_x86_64__)

	//フリーブロックリストを管理するクラスです。
	class FreeBlockManager
	{
	private:
		uint64_t FirstFreeBit; //第1カテゴリのビット列
		SonikTLSFSecondCategoryBitDepth SecondCategoryBitDepth_;	//第２カテゴリビット深度(分割数)
		FirstFreeBlock* FirstFreeList; //第1カテゴリのフリーリスト配列

	private:
		//コピーコンストラクタの禁止
		FreeBlockManager(const FreeBlockManager& t_his);

		//代入演算子の禁止
		FreeBlockManager& operator =(const FreeBlockManager& t_his);

	public:
		//コンストラクタ
		FreeBlockManager(void);
		//デストラクタ
		~FreeBlockManager(void);

		//イニシャライザ
		bool Initialize(uint64_t SetSize, SonikTLSFSecondCategoryBitDepth SetSecondBitDepth = STLSF_Depth16 );

		//フローブロックをセットします。
		void SetFreeBlock(SonikBaundaryBlock::SonikBaundaryPre* SetPtr);

		//フリーブロックを取得します。
		SonikBaundaryBlock::SonikBaundaryPre* GetFreeBlock(uint64_t GetSize);

		//指定された前置タグの連結を解除します。
		void PtrListOff(SonikBaundaryBlock::SonikBaundaryPre* UnListPtr);

	};

#endif
};

#endif /* SONIKFREEBLOCKMANAGER_H_ */
