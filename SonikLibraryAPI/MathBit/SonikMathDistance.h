/*
 * SonikMathDistance.h
 *
 *  Created on: 2015/08/17
 *      Author: SONIK
 */

#ifndef SONIKMATHDISTANCE_H_
#define SONIKMATHDISTANCE_H_

enum TwoPointeToPoint
{
	AtoB = 1,
	BtoA,
};

namespace SonikMathDataBox
{
	class BazierBoxF
	{
	public:
		float StartX, StartY; //始点
		float EndX, EndY;	  //終点
		float PivotX, PivotY; //制御点
		float Elapsed_Frame;  //始点から終点まで、何フレームで到達するか。

	public:
		BazierBoxF(void);
		~BazierBoxF(void);
	};

};

namespace SonikMath
{

	//2点間の距離の差分を計算します。
	//引数1: 地点A となる値を指定します。
	//引数2: 地点B となる値を指定します。
	//引数3: 地点間の距離差分の計算を、AからB（Aを主体）とみるか、BからA（B主体)と見るかを設定します。(省略可能です)
	double TwoPointDistance(double SetPointA, double SetPointB, TwoPointeToPoint ToPoint = AtoB);

	//2次のベジェ曲線の位置点を算出します。(float版)
	//引数1: ベジェ曲線の設定クラスである、BazierBoxクラスに任意の値を設定して指定します。
	//引数2: 結果であるX値を格納するために変数を指定します。
	//引数3: 結果であるY値を格納するために変数を指定します。
	//引数4: 始点から終点までの総合フレームの中で、何フレーム目の値を取得するのかを指定します。
	void Bezier_curveLineF(const SonikMathDataBox::BazierBoxF& StateBox, float& GetX, float& GetY, float GetFrame);

};



#endif /* SONIKMATHDISTANCE_H_ */
