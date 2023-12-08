/*
 * SonikAllocateFreeBlock.h
 *
 *  Created on: 2015/12/16
 *      Author: SONIK
 */

#ifndef SONIKALLOCATEFREEBLOCK_H_
#define SONIKALLOCATEFREEBLOCK_H_

#include "SonikFreeBlockDepthEnum.h"

#include <cstdint>

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

#ifdef __SONIK_I686__
//32bit definition
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

#elif defined __SONIK_x86_64__
	//第1カテゴリクラス
	class FirstFreeBlock
	{
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		uint64_t SecondaryFreeBit; //第2カテゴリのビット列
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

#endif
};


#endif /* SONIKALLOCATEFREEBLOCK_H_ */
