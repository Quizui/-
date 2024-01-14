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

		void Distance(const SonikAudio3DPoint& _point_, double& _outdis_);
		void Distance(double _x_ = 0.0, double _y_ = 0.0, double _z_ = 0.0, double& _outdis_);

		void Panning(const SonikAudio3DPoint& _direction_, double& _outpan_L_, double& _outpan_R_);
		void Panning(double _x_, double _y_, double _z_, double& _outpan_L_, double& _outpan_R_);

	};
};



#endif /* AUDIOPOSITION_SONIKAUDIO3DPOINT_H_ */
