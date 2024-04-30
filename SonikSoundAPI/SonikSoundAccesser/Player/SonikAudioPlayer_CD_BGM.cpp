/*
 * SonikAudioPlayer_CD_BGM.cpp
 *
 *  Created on: 2024/03/30
 *      Author: SONIC
 */

#include "SonikAudioPlayer_CD_BGM.h"

namespace SonikAudioData
{
	//コンストラクタ
	SonikAudioControlDataSetForBGM::SonikAudioControlDataSetForBGM(SonikLib::SharedSmtPtr<float> _bgm_mastervolume_, SonikAudio::SAudioFormat SetAudioPointer)
	:SonikAudioControlData(SetAudioPointer)
	,m_mastervolume_bgm(_mastervolue_)
	{
		//no process;
	};
	//デストラクタ
	SonikAudioControlDataSetForBGM::~SonikAudioControlDataSetForBGM(void)
	{
		//no process;
	};

	//データが最終的にミキシングしてほしいボリューム値を取得
	float SonikAudioControlDataSetForBGM::GetMixingVolume(void)
	{
		return m_volume * (*m_mastervolume_bgm);
	};
};


