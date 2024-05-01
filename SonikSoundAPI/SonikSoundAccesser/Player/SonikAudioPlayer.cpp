/*
 * SonikAudioPlayer.cpp
 *
 *  Created on: 2023/10/21
 *      Author: owner
 */

#include <new>

#include "SonikAudioPlayer.h"
#include "SonikAudioPlayer_ControlData.h"
#include "../Task/AudioPlayerTaskManager.h"
#include "../Task/PlayerTask.h"
#include "../PlayStateEnums.h"
#include "../../../MathBit/SonikMathDistance.h"

namespace SonikAudio
{
	//コンストラクタ
	SonikAudioPlayer::SonikAudioPlayer(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng)
	:mp_AudioData(SetAudioData)
	,mp_TskMng(SetTskMng)
	{

	};

	//デストラクタ
	SonikAudioPlayer::~SonikAudioPlayer(void)
	{
		//no porcess;
	};

	//音量のセットとゲット
	bool SonikAudioPlayer::SetVolume(float SetValue)
	{
		SonikAudioPlayerTask::APTask_VolumeChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_VolumeChange(mp_AudioData, SetValue);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	const float* SonikAudioPlayer::GetVolume(void)
	{
		return mp_AudioData->GetVolume();
	};

	//ポジションのセットとゲット
	bool SonikAudioPlayer::SetPosition(double x, double y, double z)
	{
		SonikAudioPlayerTask::APTask_PositionChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChange(mp_AudioData, x, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	bool SonikAudioPlayer::SetPositionX(double x)
	{
		SonikAudioPlayerTask::APTask_PositionChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeX(mp_AudioData, x);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionY(double y)
	{
		SonikAudioPlayerTask::APTask_PositionChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeY(mp_AudioData, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionZ(double z)
	{
		SonikAudioPlayerTask::APTask_PositionChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeZ(mp_AudioData, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionXY(double x, double y)
	{
		SonikAudioPlayerTask::APTask_PositionChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeXY(mp_AudioData, x, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionXZ(double x, double z)
	{
		SonikAudioPlayerTask::APTask_PositionChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionChangeXZ(mp_AudioData, x, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionYZ(double y, double z)
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
	void SonikAudioPlayer::GetPosition(double& x, double& y, double& z)
	{
		mp_AudioData->GetPositionAll(x, y, z);

	};
	double SonikAudioPlayer::GetPositionX(void)
	{
		return mp_AudioData->GetPositionX();
	};
	double SonikAudioPlayer::GetPositionY(void)
	{
		return mp_AudioData->GetPositionY();
	};
	double SonikAudioPlayer::GetPositionZ(void)
	{
		return mp_AudioData->GetPositionZ();
	};
	void SonikAudioPlayer::GetPositionXY(double& x, double& y)
	{
		mp_AudioData->GetPositionXY(x, y);
	};
	void SonikAudioPlayer::GetPositionXZ(double& x, double& z)
	{
		mp_AudioData->GetPositionXZ(x, z);
	};
	void SonikAudioPlayer::GetPositionYZ(double& y, double& z)
	{
		mp_AudioData->GetPositionYZ(y, z);
	};

	//方向のセット
	bool SonikAudioPlayer::SetDirection(double x, double y, double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChange(mp_AudioData, x, y, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionX(double x)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeX(mp_AudioData, x);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionY(double y)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeY(mp_AudioData, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionZ(double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeZ(mp_AudioData, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionXY(double x, double y)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeXY(mp_AudioData, x, y);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionXZ(double x, double z)
	{
		SonikAudioPlayerTask::APTask_DirectionChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionChangeXZ(mp_AudioData, x, z);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionYZ(double y, double z)
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
	void SonikAudioPlayer::GetDirection(double& x, double& y, double& z)
	{
		mp_AudioData->GetDirectionAll(x, y, z);
	};
	double SonikAudioPlayer::GetDirectionX(void)
	{
		return mp_AudioData->GetDirectionX();
	};
	double SonikAudioPlayer::GetDirectionY(void)
	{
		return mp_AudioData->GetDirectionY();
	};
	double SonikAudioPlayer::GetDirectionZ(void)
	{
		return mp_AudioData->GetDirectionZ();
	};
	void SonikAudioPlayer::GetDirectionXY(double& x, double& y)
	{
		mp_AudioData->GetDirectionXY(x, y);
	};
	void SonikAudioPlayer::GetDirectionXZ(double& x, double& z)
	{
		mp_AudioData->GetDirectionXZ(x, z);
	};
	void SonikAudioPlayer::GetDirectionYZ(double& y, double& z)
	{
		mp_AudioData->GetDirectionYZ(y, z);
	};

	//ポジションコネクトのセット
	//他のオブジェクトの座標と同期させたいときに使います。
	bool SonikAudioPlayer::SetPositionConnect(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChange(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectX(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeX(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeY(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeZ(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectXY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeXY(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		SonikAudioPlayerTask::APTask_PositionConnectChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_PositionConnectChangeXZ(mp_AudioData, _3dpos_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetPositionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
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
	bool SonikAudioPlayer::SetDirectionConnect(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChange(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectX(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeX* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeX(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeY(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeZ(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectXY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeXY* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeXY(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		SonikAudioPlayerTask::APTask_DirectionConnectChangeXZ* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_DirectionConnectChangeXZ(mp_AudioData, _3ddir_);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};
	bool SonikAudioPlayer::SetDirectionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
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
	bool SonikAudioPlayer::Play(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(mp_AudioData, SonikAudioEnum::PlayStateID::PS_Play);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをStopにセットします。
	bool SonikAudioPlayer::Stop(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(mp_AudioData, SonikAudioEnum::PlayStateID::PS_Stop);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをSuspend(一時停止)に設定します。
	bool SonikAudioPlayer::Suspend(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(mp_AudioData, SonikAudioEnum::PlayStateID::PS_SUSPEND);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	bool SonikAudioPlayer::Repeat(bool RepeatState)
	{
		SonikAudioPlayerTask::APTask_RepeatFlgChange* l_task = nullptr;

		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_RepeatFlgChange(mp_AudioData, RepeatState);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};


};
