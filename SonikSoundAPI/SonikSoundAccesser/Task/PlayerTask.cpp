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
	APTask_VolumeChange::APTask_VolumeChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float VolumeArg)
	:m_Volume(VolumeArg)
	{
		//SetData.CastSetPointer(ControlData);
		//ControlData = SetData;
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
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
	APTask_StatusChange::APTask_StatusChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikAudioEnum::PlayStateID SetValue)
	:m_State(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
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
	APTask_PositionChange::APTask_PositionChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, double SetPosx, double SetPosy, double SetPosz)
	:m_Posx(SetPosx)
	,m_Posy(SetPosy)
	,m_Posz(SetPosz)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChange::SetValue(double SetPosx, double SetPosy, double SetPosz)
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
	APTask_PositionConnectChange::APTask_PositionConnectChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChange::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChange::TaskRun(void)
	{
		ControlData->SetPositionConnectAll(mp_ConnectPoint);

	};

	//APTask_RepeatFlgChange==============================================
	//コンストラクタ
	APTask_RepeatFlgChange::APTask_RepeatFlgChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, bool SetValue)
	:m_repeat(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
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


