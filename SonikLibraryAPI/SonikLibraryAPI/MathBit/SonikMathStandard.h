/*
 * SonikMathStandard.h
 *
 *  Created on: 2019/06/20
 *      Author: SONIC
 */

#ifndef MATHBIT_SONIKMATHSTANDARD_H_
#define MATHBIT_SONIKMATHSTANDARD_H_

#include <stdint.h>

//未分類や使用範囲が広い計算類を実装します。
namespace SonikMath
{
	struct SonikComplex
	{
		uint32_t r; //実部、実数
		uint32_t i; //虚部、虚数
	};

	//2を底とする対数を計算します。
	int log2(int x);
	//指定した値の2の累乗(るいじょう)数を計算します。
	int pow2(int x);

	//負の数の対応した平方根を計算します。
	double sqrt(double a);

	//FFT(高速フーリエ変換)を行います。
	void FFT_1d(SonikComplex* p_complex, int TargetSampling);
	//IFFT(逆高速フーリエ変換を行います。
	//void IFFT_1d(SonikComplex* p_complex, int TargetSampling);


};



#endif /* MATHBIT_SONIKMATHSTANDARD_H_ */
