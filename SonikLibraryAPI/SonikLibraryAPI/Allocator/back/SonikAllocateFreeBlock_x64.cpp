/*
 * SonikAllocateFreeBlock.cpp
 *
 *  Created on: 2015/12/16
 *      Author: SONIK
 */
#ifdef __SONIK_x86_64__

#include "SonikAllocateFreeBlock.h"

#include <new>
#include <cstdint>

namespace SonikBTMAFreeBlock
{

	//第１カテゴリクラス
	FirstFreeBlock::FirstFreeBlock(void)
	:SecondaryFreeBit(0)
	,SecondaryArray(0)
	{

	};

	FirstFreeBlock::~FirstFreeBlock(void)
	{
		if(SecondaryArray != 0)
		{
			delete[] SecondaryArray;
		};
	};

	bool FirstFreeBlock::Initialize(SonikTLSFSecondCategoryBitDepth SetSecondBitDepth)
	{

		SecondaryArray = new(std::nothrow) SecondaryFreeBlock[static_cast<uint64_t>(SetSecondBitDepth)];

		if(SecondaryArray == nullptr || SecondaryArray == 0)
		{
			return false;
		};

		return true;

//		try
//		{
//			SecondaryArray = ::new SecondaryFreeBlock[SetSecondBitDepth];
//		}catch(std::bad_alloc& e)
//		{
//			return false;
//		};
//		return true;
	};

	//第２カテゴリクラス
	SecondaryFreeBlock::SecondaryFreeBlock(void)
	:FreePrePtr_s(0)
	{
//		try
//		{
//			//番兵用オブジェクトを生成しておく。
//			InnerPtr_s = new SonikInnerPtr::BTMAInnerPtr;
//		}catch(std::bad_alloc& e)
//		{
//			throw;
//		};
//
//		InnerPtr_e = InnerPtr_s;

	};

	SecondaryFreeBlock::~SecondaryFreeBlock(void)
	{
//		if(InnerPtr_s != 0)
//		{
//			delete InnerPtr_s;
//		};
	};



};

#endif
