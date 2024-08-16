/*
 * SonikAudioEffecter.h
 *
 *  Created on: 2024/06/16
 *      Author: SONIC
 */

#ifndef EFFECTER_SONIKAUDIOEFFECTER_H_
#define EFFECTER_SONIKAUDIOEFFECTER_H_

#include "../other/SAudioAccesserTypedef.h"
#include "../other/PlayStateEnums.h"
#include "../../SmartPointer/SonikSmartPointer.hpp"

namespace SonikAudioData
{
	class SonikAudioControlData;
};

//前方宣言====================================
namespace SonikMathDataBox
{
	class Sonik3DPoint;
};


//distanceやパンニングなどのエフェクトを適用させます。
namespace SonikAudio
{
	class SonikAudioEffecter
	{
	private:
		//リスナ
		SonikAudio::SAudioListener mp_Listener;
		//エフェクタ関数配列
		using M_SAUDIO_EFFECT_FUNC = void (SonikAudioEffecter::*)(SonikMathDataBox::Sonik3DPoint& lis_pos, SonikMathDataBox::Sonik3DPoint& lis_dir, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, double&, double&);
		M_SAUDIO_EFFECT_FUNC m_effectlist[SonikAudioEnum::PlayEffectID::EF_CNT];

    private:
        //コピーとムーヴの禁止
        SonikAudioEffecter(const SonikAudioEffecter& _copy_) = delete;
        SonikAudioEffecter(SonikAudioEffecter&& _move_) = delete;
        SonikAudioEffecter& operator =(const SonikAudioEffecter& _copy_) = delete;
        SonikAudioEffecter& operator =(SonikAudioEffecter&& _move_) = delete;

	private:
        void EffecterProc_TypeBGM(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>& PlayerControl, double& _L_out_, double& _R_out_);
        void EffecterProc_TypeSE(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>& PlayerControl, double& _L_out_, double& _R_out_);

		void SAE_PRIVATE_DISTANCE(SonikMathDataBox::Sonik3DPoint& lis_pos, SonikMathDataBox::Sonik3DPoint& lis_dir, SonikMathDataBox::Sonik3DPoint& pl_pos, SonikMathDataBox::Sonik3DPoint& pl_dir, double& _L_out_, double& _R_out_);
		void SAE_PRIVATE_PANNING(SonikMathDataBox::Sonik3DPoint& lis_pos, SonikMathDataBox::Sonik3DPoint& lis_dir, SonikMathDataBox::Sonik3DPoint& pl_pos, SonikMathDataBox::Sonik3DPoint& pl_dir, double& _L_out_, double& _R_out_);

	public:
        //コンストラクタ
        SonikAudioEffecter(SonikAudio::SAudioListener _listener_);
        //デストラクタ
        ~SonikAudioEffecter(void);

        //エフェクトセット
        void SetEffect(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> _audio_cd_, double& _L_out_, double& _R_out_);

	};


};


#endif //EFFECTER_SONIKAUDIOEFFECTER_H_
