/*
 * SonikAllocateFreeBlock.h
 *
 *  Created on: 2015/12/16
 *      Author: Sonik
 */

#ifndef SONIKALLOCATEFREEBLOCK_H_
#define SONIKALLOCATEFREEBLOCK_H_

#include "SonikFreeBlockDepthEnum.h"

namespace SonikBaundaryBlock
{
	class SonikBaundaryPre;
};

namespace SonikInnerPtr
{
	class BTMAInnerPtr;
};

namespace SonikBTMAFreeBlock
{
	//フリーブロックリストを管理するクラスです。
	class FreeBlockManager;
};

//アロケータ内で使用する、フリーブロッククラス
namespace SonikBTMAFreeBlock
{
	//前方宣言
	class SecondaryFreeBlock;

	//第1カテゴリクラス
	class FirstFreeBlock
	{
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		unsigned long SecondaryFreeBit; //第2カテゴリのビット列
		SecondaryFreeBlock* SecondaryArray;

	public:
		FirstFreeBlock(void);
		~FirstFreeBlock(void);

		bool Initialize(SonikTLSFSecondCategoryBitDepth SetSecondBitDepth);

	};

	//第2カテゴリクラス
	class SecondaryFreeBlock
	{
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		SonikBaundaryBlock::SonikBaundaryPre* FreePrePtr_s;	//先頭ポインタ

	public:
		SecondaryFreeBlock(void);
		~SecondaryFreeBlock(void);

	};

};


#endif /* SONIKALLOCATEFREEBLOCK_H_ */
