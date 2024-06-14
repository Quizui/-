/*
 * SonikAudioPlayer.cpp
 *
 *  Created on: 2023/10/21
 *      Author: owner
 */

#include <new>

#include "SonikAudioSEPlayer.h"
#include "SonikAudioPlayer_CD_SE.h"
#include "../Task/AudioPlayerTaskManager.h"
#include "../Task/PlayerTask.h"
#include "../PlayStateEnums.h"
#include "../../../MathBit/SonikMathDistance.h"


namespace SonikAudio
{
	//コンストラクタ
	SonikAudioSEPlayer::SonikAudioSEPlayer(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng)
	:mp_AudioData(SetAudioData)
	,mp_TskMng(SetTskMng)
	{

	};

	//デストラクタ
	SonikAudioSEPlayer::~SonikAudioSEPlayer(void)
	{
		//no porcess;
	};

	//音量のセットとゲット
	bool SonikAudioSEPlayer::SetVolume(float SetValue)
	{
		SonikAudioPlayerTask::APTask_VolumeChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_VolumeChange(l_audiodata, SetValue);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	const float* SonikAudioSEPlayer::GetVolume(void)
	{
		return mp_AudioData->GetVolume();
	};

	//ポジションのセットとゲット
	bool SonikAudioSEPlayer::SetPosition(double x, double y, double z)
	{
		SonikAudioPlayerTask::APTask_PositionChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChange(mp_AudioData, x, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};

	//エフェクトセット
	void SonikAudioSEPlayer::EnableEffect(SonikAudioEnum::PlayEffectID _enable_effectid_)
	{
		mp_AudioData->EnableEffect(_enable_effectid_);
	};

	void SonikAudioSEPlayer::DisableEffecct(SonikAudioEnum::PlayEffectID _disbale_effectid_)
	{
		mp_AudioData->DisableEffect(_disbale_effectid_);
	};

	bool SonikAudioSEPlayer::SetPositionX(double x)
	{
		SonikAudioPlayerTask::APTask_PositionChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeX(mp_AudioData, x);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionY(double y)
	{
		SonikAudioPlayerTask::APTask_PositionChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeY(mp_AudioData, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionZ(double z)
	{
		SonikAudioPlayerTask::APTask_PositionChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeZ(mp_AudioData, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionXY(double x, double y)
	{
		SonikAudioPlayerTask::APTask_PositionChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeXY(mp_AudioData, x, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionXZ(double x, double z)
	{
		SonikAudioPlayerTask::APTask_PositionChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeXZ(mp_AudioData, x, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionYZ(double y, double z)
	{
		SonikAudioPlayerTask::APTask_PositionChangeYZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeYZ(mp_AudioData, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	//ポジションのゲット
	void SonikAudioSEPlayer::GetPosition(double& x, double& y, double& z)
	{
		mp_AudioData->GetPositionAll(x, y, z);
	};

	double SonikAudioSEPlayer::GetPositionX(void)
	{
		return mp_AudioData->GetPositionX();
	};
	double SonikAudioSEPlayer::GetPositionY(void)
	{
		return mp_AudioData->GetPositionY();
	};
	double SonikAudioSEPlayer::GetPositionZ(void)
	{
		return mp_AudioData->GetPositionZ();
	};
	void SonikAudioSEPlayer::GetPositionXY(double& x, double& y)
	{
		mp_AudioData->GetPositionXY(x, y);
	};
	void SonikAudioSEPlayer::GetPositionXZ(double& x, double& z)
	{
		mp_AudioData->GetPositionXZ(x, z);
	};
	void SonikAudioSEPlayer::GetPositionYZ(double& y, double& z)
	{
		mp_AudioData->GetPositionYZ(y, z);
	};

	//方向のセット
	bool SonikAudioSEPlayer::SetDirection(double x, double y, double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChange(mp_AudioData, x, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionX(double x)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeX(mp_AudioData, x);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionY(double y)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeY(mp_AudioData, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionZ(double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeZ(mp_AudioData, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionXY(double x, double y)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeXY(mp_AudioData, x, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionXZ(double x, double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeXZ(mp_AudioData, x, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionYZ(double y, double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeYZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeYZ(mp_AudioData, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	//方向(Directionのゲット
	void SonikAudioSEPlayer::GetDirection(double& x, double& y, double& z)
	{
		mp_AudioData->GetDirectionAll(x, y, z);
	};

	double SonikAudioSEPlayer::GetDirectionX(void)
	{
		return mp_AudioData->GetDirectionX();
	};

	double SonikAudioSEPlayer::GetDirectionY(void)
	{
		return mp_AudioData->GetDirectionY();
	};

	double SonikAudioSEPlayer::GetDirectionZ(void)
	{
		return mp_AudioData->GetDirectionZ();
	};

	void SonikAudioSEPlayer::GetDirectionXY(double& x, double& y)
	{
		mp_AudioData->GetDirectionXY(x, y);
	};

	void SonikAudioSEPlayer::GetDirectionXZ(double& x, double& z)
	{
		mp_AudioData->GetDirectionXZ(x, z);
	};

	void SonikAudioSEPlayer::GetDirectionYZ(double& y, double& z)
	{
		mp_AudioData->GetDirectionYZ(y, z);
	};

	//ポジションコネクトのセット
	//他のオブジェクトの座標と同期させたいときに使います。
	bool SonikAudioSEPlayer::SetPositionConnect(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChange(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectX(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeX(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeY(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeZ(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectXY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeXY(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeXZ(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetPositionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeYZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeYZ(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	//方向コネクトのセット
	//他のオブジェクトの座標と同期させたいときに使います。
	bool SonikAudioSEPlayer::SetDirectionConnect(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChange(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectX(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeX(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeY(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeZ(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectXY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeXY(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeXZ(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioSEPlayer::SetDirectionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeYZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeYZ(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	//オーディオステータス関連
	//オーディステータスにPlayをセットします。
	bool SonikAudioSEPlayer::Play(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_Play);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをStopにセットします。
	bool SonikAudioSEPlayer::Stop(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_Stop);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをSuspend(一時停止)に設定します。
	bool SonikAudioSEPlayer::Suspend(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_SUSPEND);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	bool SonikAudioSEPlayer::Repeat(bool RepeatState)
	{
		SonikAudioPlayerTask::APTask_RepeatFlgChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_RepeatFlgChange(l_audiodata, RepeatState);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};


};
