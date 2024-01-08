/*
 * SonikAudio3DPoint.h
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#ifndef AUDIOPOSITION_SONIKAUDIO3DPOINT_H_
#define AUDIOPOSITION_SONIKAUDIO3DPOINT_H_

#include "../../../MathBit/SonikMathDistance.h"

namespace SonikAudioPoint
{
	class SonikAudio3DPoint : public SonikMath::Sonik3DPoint
	{
	public:
		//基底クラスのprotectedをpublicにするよりこちらでアクセスを用意したほうがいいかなと..。
		double& ref_m_x;
		double& ref_m_y;
		double& ref_m_z;

		//参照変更用。(connectで切り替えられる可能性あり。
		double* mp_x;
		double* mp_y;
		double* mp_z;


	public:
		SonikAudio3DPoint(double _x_ = 0.0, double _y_ = 0.0, double _z_ =0.0);
		~SonikAudio3DPoint(void);

		double Distance(const SonikAudio3DPoint& _point_);
		double Distance(const double _x_ = 0.0, const double _y_ = 0.0, const double _z_ = 0.0);

	};
};



#endif /* AUDIOPOSITION_SONIKAUDIO3DPOINT_H_ */
