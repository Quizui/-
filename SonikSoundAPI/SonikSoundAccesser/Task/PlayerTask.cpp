/*
 * PlayerTask.cpp
 *
 *  Created on: 2023/10/19
 *      Author: owner
 */

#include "PlayerTask.h"
#include "../Player/SonikAudioPlayer_ControlData.h"

namespace SonikAudioPlayerTask
{
	//APTask_VolumeChange==============================================
	//コンストラクタ
	APTask_VolumeChange::APTask_VolumeChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float VolumeArg)
	:m_Volume(VolumeArg)
	{
		//SetData.CastSetPointer(ControlData);
		//ControlData = SetData;
		SonikAudioPointer::SmtPtrUpCast(SetData, ControlData);
	};

	//値のセット
	void APTask_VolumeChange::SetValue(float VolumeArg)
	{
		m_Volume = VolumeArg;
	}

	//タスクRUN
	void APTask_VolumeChange::TaskRun(void)
	{
		ControlData->SetVolume(m_Volume);
	};

	//APTask_StatusChange==============================================
	//コンストラクタ
	APTask_StatusChange::APTask_StatusChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikAudioEnum::PlayStateID SetValue)
	:m_State(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikAudioPointer::SmtPtrUpCast(SetData, ControlData);
	};

	//値のセット
	void APTask_StatusChange::SetValue(SonikAudioEnum::PlayStateID SetValue)
	{
		m_State = SetValue;
	};

	//タスクRUN
	void APTask_StatusChange::TaskRun(void)
	{
		ControlData->SetAudioState(m_State);
	};

	//APTask_StatusChange==============================================
	//コンストラクタ
	APTask_PositionChange::APTask_PositionChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float SetPosx, float SetPosy, float SetPosz)
	:m_Posx(SetPosx)
	,m_Posy(SetPosy)
	,m_Posz(SetPosz)
	{
		//SetData.CastSetPointer(ControlData);
		SonikAudioPointer::SmtPtrUpCast(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChange::SetValue(float SetPosx, float SetPosy, float SetPosz)
	{
		m_Posx = SetPosx;
		m_Posy = SetPosy;
		m_Posz = SetPosz;

	};

	//タスクRUN
	void APTask_PositionChange::TaskRun(void)
	{
		ControlData->SetPositionAll(m_Posx, m_Posy, m_Posz);
	};

	//APTask_PositionConnectChange==============================================
	//コンストラクタ
	APTask_PositionConnectChange::APTask_PositionConnectChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float* SetPosx, float* SetPosy, float* SetPosz)
	:mp_Posx(SetPosx)
	,mp_Posy(SetPosy)
	,mp_Posz(SetPosz)
	{
		//SetData.CastSetPointer(ControlData);
	};

	//値のセット
	void APTask_PositionConnectChange::SetValue(float* SetPosx, float* SetPosy, float* SetPosz)
	{
		mp_Posx = SetPosx;
		mp_Posy = SetPosy;
		mp_Posz = SetPosz;

	};

	//タスクRUN
	void APTask_PositionConnectChange::TaskRun(void)
	{
		//ConnectAllは内部で下記三つをコールしているだけなのでこちらでAllを軽油しないことで１コール減らせる。
		ControlData->SetPositonConnectX(mp_Posx);
		ControlData->SetPositonConnectY(mp_Posy);
		ControlData->SetPositonConnectZ(mp_Posz);

	};

	//APTask_RepeatFlgChange==============================================
	//コンストラクタ
	APTask_RepeatFlgChange::APTask_RepeatFlgChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, bool SetValue)
	:m_repeat(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikAudioPointer::SmtPtrUpCast(SetData, ControlData);
	}

	//値のセット
	void APTask_RepeatFlgChange::SetValue(bool SetValue)
	{
		m_repeat = SetValue;
	};

	//タスクRUN
	void APTask_RepeatFlgChange::TaskRun(void)
	{
		ControlData->SetRepeat(m_repeat);
	};


};


