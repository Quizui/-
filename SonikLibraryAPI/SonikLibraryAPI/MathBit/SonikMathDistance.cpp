/*
 * SonikMathDistance.cpp
 *
 *  Created on: 2015/08/17
 *      Author: SONIK
 */

#include "SonikMathDistance.h"

#include <cstdint>

namespace SonikMath
{

	//2点間の距離の差分を計算します。
	//引数1: 地点A となる値を指定します。
	//引数2: 地点B となる値を指定します。
	//引数3: 地点間の距離差分の計算を、AからB（Aを主体）とみるか、BからA（B主体)と見るかを設定します。(省略可能です)
	double TwoPointDistance(double SetPointA, double SetPointB, TwoPointeToPoint ToPoint)
	{
		double ret = 0;
		uint8_t signedvalue = 1;
		double offset_ = 0.0;
		uint8_t Woffset_ = 0;

		double* LargeValue =0;
		double* SmallValue =0;


		if(SetPointA < 0)
		{
			offset_ += SetPointA * (-1);

			Woffset_ += 1;
		};

		if(SetPointB < 0)
		{
			offset_ += SetPointB * (-1);

			++Woffset_ += 1;
		};

		if( SetPointA > SetPointB )
		{
			LargeValue = &SetPointA;
			SmallValue = &SetPointB;

			if(ToPoint == AtoB)
			{
				signedvalue = -1;
			};

		}else
		{
			LargeValue = &SetPointB;
			SmallValue = &SetPointA;

			if(ToPoint == BtoA)
			{
				signedvalue = -1;
			};

		};

		switch(Woffset_)
		{
		case 0:
			ret = (*LargeValue) - (*SmallValue);

			break;
		case 1:
			ret = (*LargeValue) + offset_;

			break;

		case 2:
			ret = ( (*SmallValue) * (-1) ) - ( (*LargeValue) * (-1) );

			break;

		default:
			break;
		};

		return ret * signedvalue;

	};


	//ベジェ曲線の位置点を算出します。(float版)
	//引数1: ベジェ曲線の設定クラスである、BazierBoxクラスに任意の値を設定して指定します。
	//引数2: 結果であるX値を格納するために変数を指定します。
	//引数3: 結果であるY値を格納するために変数を指定します。
	//引数4: 始点から終点までの総合フレームの中で、何フレーム目の値を取得するのかを指定します。
	void Bezier_curveLineF(const SonikMathDataBox::BazierBoxF& StateBox, float& GetX, float& GetY, float GetFrame)
	{
		float time = 0.0f;

		if(StateBox.Elapsed_Frame < GetFrame)
		{
			time = 1.0f;
		}else
		{
			time = GetFrame * (1 * StateBox.Elapsed_Frame);
		};

		GetX = ((1.0f - time) * (1.0f - time) * StateBox.StartX) + (2 * (1.0f - time) * time * StateBox.PivotX) + (time * time * StateBox.EndX);
		GetY = ((1.0f - time) * (1.0f - time) * StateBox.StartY) + (2 * (1.0f - time) * time * StateBox.PivotY) + (time * time * StateBox.EndY);
	};


};

