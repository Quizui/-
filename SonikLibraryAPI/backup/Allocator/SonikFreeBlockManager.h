/*
 * SonikFreeBlockManager.h
 *
 *  Created on: 2015/12/16
 *      Author: Sonik
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
	//フリーブロックリストを管理するクラスです。
	class FreeBlockManager
	{
	private:
		unsigned long FirstFreeBit; //第1カテゴリのビット列
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
		bool Initialize(unsigned long SetSize, SonikTLSFSecondCategoryBitDepth SetSecondBitDepth = STLSF_Depth16 );

		//フローブロックをセットします。
		void SetFreeBlock(SonikBaundaryBlock::SonikBaundaryPre* SetPtr);

		//フリーブロックを取得します。
		SonikBaundaryBlock::SonikBaundaryPre* GetFreeBlock(unsigned long GetSize);

		//指定された前置タグの連結を解除します。
		void PtrListOff(SonikBaundaryBlock::SonikBaundaryPre* UnListPtr);

	};


};

#endif /* SONIKFREEBLOCKMANAGER_H_ */
