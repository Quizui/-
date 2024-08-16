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
	SonikAudioControlDataSetForBGM::SonikAudioControlDataSetForBGM(const SonikLib::SharedSmtPtr<double> _bgm_mastervolume_, SonikAudio::SAudioFormat SetAudioPointer)
	:SonikAudioControlData(SetAudioPointer)
	,m_CategoryBGMVol(_bgm_mastervolume_)
	{
		//no process;
	};
	//デストラクタ
	SonikAudioControlDataSetForBGM::~SonikAudioControlDataSetForBGM(void)
	{
		//no process;
	};

    //データが属するカテゴリーのボリューム値
    double SonikAudioControlDataSetForBGM::GetCategoryVolume(void)
    {
        return (*m_CategoryBGMVol);
    };
};


