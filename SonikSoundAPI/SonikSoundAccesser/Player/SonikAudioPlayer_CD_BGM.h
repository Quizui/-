/*
 * SonikAudioPlayer_CD_BGM.h
 *
 *  Created on: 2024/03/28
 *      Author: owner
 */

#include "SonikAudioPlayer_ControlData.h"
#include "../../../SmartPointer/SonikSmartPointer.hpp"

#ifndef PLAYER_SONIKAUDIOPLAYER_CD_BGM_H_
#define PLAYER_SONIKAUDIOPLAYER_CD_BGM_H_

namespace SonikAudioData
{
	//BGM用のデータは位置情報等必要ないため持ちません。
	class SonikAudioControlDataSetForBGM : public SonikAudioData::SonikAudioControlData
	{
	private:
		SonikLib::SharedSmtPtr<float> m_mastervolume_bgm;

	private:
		//コピー禁止
		SonikAudioControlDataSetForBGM(SonikAudioControlDataSetForBGM& _this_) = delete;
		SonikAudioControlDataSetForBGM& operator =(SonikAudioControlDataSetForBGM& _this_) = delete;

	public:
		//コンストラクタ
		SonikAudioControlDataSetForBGM(SonikLib::SharedSmtPtr<float> _bgm_mastervolume_, SonikAudio::SAudioFormat SetAudioPointer);
		//デストラクタ
		~SonikAudioControlDataSetForBGM(void);

		//データが最終的にミキシングしてほしいボリューム値を取得
		float GetMixingVolume(void);

	};

};

#endif /* PLAYER_SONIKAUDIOPLAYER_CD_BGM_H_ */
