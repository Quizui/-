/*
 * SonikFreeBlockDepthEnum.h
 *
 *  Created on: 2016/01/07
 *      Author: SONIK
 */

#ifndef ALLOCATOR_SONIKFREEBLOCKDEPTHENUM_H_
#define ALLOCATOR_SONIKFREEBLOCKDEPTHENUM_H_

//セカンドカテゴリのビット深度
enum SonikTLSFSecondCategoryBitDepth
{
	STLSF_Depth16 = 16,	//セカンドカテゴリの分割数(ビット深度)を16に設定します。(分割数16)
	STLSF_Depth32 = 32,	//セカンドカテゴリの分割数(ビット深度)を32に設定します。(分割数32)

};


#endif /* ALLOCATOR_SONIKFREEBLOCKDEPTHENUM_H_ */
