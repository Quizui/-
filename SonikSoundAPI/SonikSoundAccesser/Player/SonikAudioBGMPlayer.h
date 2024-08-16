/*
 * SonikAudioPlayer.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIO_BACKGROUND_MUSIC_PLAYER_H_
#define PLAYER_SONIKAUDIO_BACKGROUND_MUSIC_PLAYER_H_

#include "../../SmartPointer/SonikSmartPointer.hpp"

//前方宣言
namespace SonikAudioData
{
	//SEという名前ですが、距離と方向を持つ音源全般を扱います。
	class SonikAudioControlDataSetForBGM;
};

namespace SonikAudioTaskInterface
{
	//プレイヤー側からマネージャへのアクセス用インタフェース。
	class SonikAudioPlayerTaskManagerInterface;
};

namespace SonikMathDataBox
{
	class Sonik3DPoint;
};

namespace SonikAudio
{
	//いわゆるオーディオコントローラーさん。
	class SonikAudioBGMPlayer
	{
	private:
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForBGM> mp_AudioData;
		SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> mp_TskMng;

	public:
		//コンストラクタ
		SonikAudioBGMPlayer(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForBGM> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng);
		//デストラクタ
		~SonikAudioBGMPlayer(void);

		//音量のセットとゲット
		bool SetVolume(float SetValue);
		float GetVolume(void);

		//オーディオステータス関連
		bool Play(void);					//オーディステータスにPlayをセットします。
		bool Stop(void);					//オーディオステータスをStopにセットします。
		bool Suspend(void);				//オーディオステータスをSuspend(一時停止)に設定します。
		bool Repeat(bool RepeatState);	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	};

}



#endif /* PLAYER_SONIKAUDIO_BACKGROUND_MUSIC_PLAYER_H_ */
