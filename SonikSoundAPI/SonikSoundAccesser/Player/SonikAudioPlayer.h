/*
 * SonikAudioPlayer.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIOPLAYER_H_
#define PLAYER_SONIKAUDIOPLAYER_H_

#include <stdint.h>
#include "../../../SmartPointer/SonikSmartPointer.hpp"

//前方宣言
namespace SonikAudioDataInterface
{
	//プレイヤー側に渡す用のクラス。
	class SADInterface_PlayerSide;
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
	class SonikAudioPlayer
	{
	private:
		SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> mp_AudioData;
		SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> mp_TskMng;

	public:
		//コンストラクタ
		SonikAudioPlayer(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng);
		//デストラクタ
		~SonikAudioPlayer(void);

		//音量のセットとゲット
		bool SetVolume(float SetValue);
		const float* GetVolume(void);

		//ポジションのセットとゲット
		bool SetPosition(double x, double y, double z);
		void GetPosition(double& x, double& y, double& z);

		//ポジションコネクトのセット
		//他のオブジェクトの座標と同期させたいときに使います。
		bool SetPositionConnect(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//オーディオステータス関連
		bool Play(void);					//オーディステータスにPlayをセットします。
		bool Stop(void);					//オーディオステータスをStopにセットします。
		bool Suspend(void);				//オーディオステータスをSuspend(一時停止)に設定します。
		bool Repeat(bool RepeatState);	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	};

}



#endif /* PLAYER_SONIKAUDIOPLAYER_H_ */
