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
	SonikAudioPlayer::SonikAudioPlayer(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng)
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
	void SonikAudioPlayer::GetPosition(double& x, double& y, double& z)
	{
		mp_AudioData->GetPositionAll(x, y, z);

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
