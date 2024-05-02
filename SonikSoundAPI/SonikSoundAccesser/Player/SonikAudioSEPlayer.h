/*
 * SonikAudioPlayer.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIO_SOUNDE_EFFECT_PLAYER_H_
#define PLAYER_SONIKAUDIO_SOUNDE_EFFECT_PLAYER_H_

#include <stdint.h>
#include "../../../SmartPointer/SonikSmartPointer.hpp"

//前方宣言
namespace SonikAudioData
{
	//SEという名前ですが、距離と方向を持つ音源全般を扱います。
	class SonikAudioControlDataSetForSE;
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
	class SonikAudioSEPlayer
	{
	private:
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> mp_AudioData;
		SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> mp_TskMng;

	public:
		//コンストラクタ
		SonikAudioSEPlayer(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng);
		//デストラクタ
		~SonikAudioSEPlayer(void);

		//音量のセットとゲット
		bool SetVolume(float SetValue);
		const float* GetVolume(void);

		//ポジションのセット
		bool SetPosition(double x, double y, double z);
		bool SetPositionX(double x);
		bool SetPositionY(double y);
		bool SetPositionZ(double z);
		bool SetPositionXY(double x, double y);
		bool SetPositionXZ(double x, double z);
		bool SetPositionYZ(double y, double z);

		//ポジションのゲット
		void GetPosition(double& x, double& y, double& z);
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);
		void GetPositionXY(double& x, double& y);
		void GetPositionXZ(double& x, double& z);
		void GetPositionYZ(double& y, double& z);

		//方向のセット
		bool SetDirection(double x, double y, double z);
		bool SetDirectionX(double x);
		bool SetDirectionY(double y);
		bool SetDirectionZ(double z);
		bool SetDirectionXY(double x, double y);
		bool SetDirectionXZ(double x, double z);
		bool SetDirectionYZ(double y, double z);

		//方向(Directionのゲット
		void GetDirection(double& x, double& y, double& z);
		double GetDirectionX(void);
		double GetDirectionY(void);
		double GetDirectionZ(void);
		void GetDirectionXY(double& x, double& y);
		void GetDirectionXZ(double& x, double& z);
		void GetDirectionYZ(double& y, double& z);

		//ポジションコネクトのセット
		//他のオブジェクトの座標と同期させたいときに使います。
		bool SetPositionConnect(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectX(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectY(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectXY(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		bool SetPositionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//方向コネクトのセット
		//他のオブジェクトの座標と同期させたいときに使います。
		bool SetDirectionConnect(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectX(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectY(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectXY(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		bool SetDirectionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);


		//オーディオステータス関連
		bool Play(void);					//オーディステータスにPlayをセットします。
		bool Stop(void);					//オーディオステータスをStopにセットします。
		bool Suspend(void);				//オーディオステータスをSuspend(一時停止)に設定します。
		bool Repeat(bool RepeatState);	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	};

}



#endif /* PLAYER_SONIKAUDIO_SOUNDE_EFFECT_PLAYER_H_ */
