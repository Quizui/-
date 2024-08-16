/*
 * SonikAudioPlayer.cpp
 *
 *  Created on: 2023/10/21
 *      Author: owner
 */

#include "SonikAudioBGMPlayer.h"
#include "SonikAudioPlayer_CD_BGM.h"
#include "../Task/PlayerTask.h"
#include "../other/PlayStateEnums.h"


namespace SonikAudio
{
	//コンストラクタ
	SonikAudioBGMPlayer::SonikAudioBGMPlayer(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForBGM> SetAudioData, SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> SetTskMng)
	:mp_AudioData(SetAudioData)
	,mp_TskMng(SetTskMng)
	{

	};

	//デストラクタ
	SonikAudioBGMPlayer::~SonikAudioBGMPlayer(void)
	{
		//no porcess;
	};

	//音量のセットとゲット
	bool SonikAudioBGMPlayer::SetVolume(float SetValue)
	{
		SonikAudioPlayerTask::APTask_VolumeChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_VolumeChange(l_audiodata, SetValue);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);
	};

	float SonikAudioBGMPlayer::GetVolume(void)
	{
		return mp_AudioData->GetVolume();
	};

	//オーディオステータス関連
	//オーディステータスにPlayをセットします。
	bool SonikAudioBGMPlayer::Play(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_Play);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをStopにセットします。
	bool SonikAudioBGMPlayer::Stop(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_Stop);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//オーディオステータスをSuspend(一時停止)に設定します。
	bool SonikAudioBGMPlayer::Suspend(void)
	{
		SonikAudioPlayerTask::APTask_StatusChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_StatusChange(l_audiodata, SonikAudioEnum::PlayStateID::PS_SUSPEND);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};
	//再生終了後リピート再生するかを設定します。true=リピートします。 false=リピートせず停止します。
	bool SonikAudioBGMPlayer::Repeat(bool RepeatState)
	{
		SonikAudioPlayerTask::APTask_RepeatFlgChange* l_task = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> l_audiodata;

		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(mp_AudioData, l_audiodata);
		l_task = new(std::nothrow) SonikAudioPlayerTask::APTask_RepeatFlgChange(l_audiodata, RepeatState);
		if(l_task == nullptr)
		{
			return false;
		};

		return mp_TskMng->AddTask(l_task);

	};


};
