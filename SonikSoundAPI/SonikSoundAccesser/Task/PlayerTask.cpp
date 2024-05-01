/*
 * PlayerTask.cpp
 *
 *  Created on: 2023/10/19
 *      Author: owner
 */

#include "PlayerTask.h"
#include "../Player/SonikAudioPlayer_ControlData.h"
#include "../Player/SonikAudioPlayer_CD_SE,h"

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

	//APTask_PositionChange=============================================
	//コンストラクタ
	APTask_PositionChange::APTask_PositionChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosx, double SetPosy, double SetPosz)
	:m_Posx(SetPosx)
	,m_Posy(SetPosy)
	,m_Posz(SetPosz)
	,ControlData(SetData)
	{
		//SetData.CastSetPointer(ControlData);
		//SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
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

	//APTask_PositionChangeX=============================================
	//コンストラクタ
	APTask_PositionChangeX::APTask_PositionChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	,ControlData(SetData)
	{
		//SetData.CastSetPointer(ControlData);
		//SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeX::SetValue(double SetValue)
	{
		m_value = SetValue;

	};

	//タスクRUN
	void APTask_PositionChangeX::TaskRun(void)
	{
		ControlData->SetPositionX(m_value);
	};

	//APTask_PositionChangeY=============================================
	//コンストラクタ
	APTask_PositionChangeY::APTask_PositionChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	,ControlData(SetData)
	{
		//SetData.CastSetPointer(ControlData);
		//SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeY::SetValue(double SetValue)
	{
		m_value = SetValue;

	};

	//タスクRUN
	void APTask_PositionChangeY::TaskRun(void)
	{
		ControlData->SetPositionY(m_value);
	};

	//APTask_PositionChangeZ=============================================
	//コンストラクタ
	APTask_PositionChangeZ::APTask_PositionChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeZ::SetValue(double SetValue)
	{
		m_value = SetValue;

	};

	//タスクRUN
	void APTask_PositionChangeZ::TaskRun(void)
	{
		ControlData->SetPositionZ(m_value);
	};

	//APTask_PositionChangeXY=============================================
	//コンストラクタ
	APTask_PositionChangeXY::APTask_PositionChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosX, double SetPosY)
	:m_PosX(SetPosX)
	,m_PosY(SetPosY)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeXY::SetValue(double SetPosX, double SetPosY)
	{
		m_PosX = SetPosX;
		m_PosY = SetPosY;

	};

	//タスクRUN
	void APTask_PositionChangeXY::TaskRun(void)
	{
		ControlData->SetPositionXY(m_PosX, m_PosY);
	};

	//APTask_PositionChangeXZ=============================================
	//コンストラクタ
	APTask_PositionChangeXZ::APTask_PositionChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosX, double SetPosZ)
	:m_PosX(SetPosX)
	,m_PosZ(SetPosZ)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeXZ::SetValue(double SetPosX, double SetPosZ)
	{
		m_PosX = SetPosX;
		m_PosZ = SetPosZ;

	};

	//タスクRUN
	void APTask_PositionChangeXZ::TaskRun(void)
	{
		ControlData->SetPositionXZ(m_PosX, m_PosZ);
	};

	//APTask_PositionChangeYZ=============================================
	//コンストラクタ
	APTask_PositionChangeYZ::APTask_PositionChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosY, double SetPosZ)
	:m_PosY(SetPosY)
	,m_PosZ(SetPosZ)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionChangeYZ::SetValue(double SetPosY, double SetPosZ)
	{
		m_PosY = SetPosY;
		m_PosZ = SetPosZ;

	};

	//タスクRUN
	void APTask_PositionChangeYZ::TaskRun(void)
	{
		ControlData->SetPositionYZ(m_PosY, m_PosZ);
	};

	//APTask_DirectionChange=============================================
	//コンストラクタ
	APTask_DirectionChange::APTask_DirectionChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirx, double SetDiry, double SetDirz)
	:m_Dirx(SetDirx)
	,m_Diry(SetDiry)
	,m_Dirz(SetDirz)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChange::SetValue(double SetDirx, double SetDiry, double SetDirz)
	{
		m_Dirx = SetDirx;
		m_Diry = SetDiry;
		m_Dirz = SetDirz;

	};

	//タスクRUN
	void APTask_DirectionChange::TaskRun(void)
	{
		ControlData->SetDirectionAll(m_Dirx, m_Diry, m_Dirz);
	};

	//APTask_DirectionChangeX=============================================
	//コンストラクタ
	APTask_DirectionChangeX::APTask_DirectionChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeX::SetValue(double SetValue)
	{
		m_value = SetValue;
	};

	//タスクRUN
	void APTask_DirectionChangeX::TaskRun(void)
	{
		ControlData->SetDirectionX(m_value);
	};

	//APTask_DirectionChangeY=============================================
	//コンストラクタ
	APTask_DirectionChangeY::APTask_DirectionChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeY::SetValue(double SetValue)
	{
		m_value = SetValue;
	};

	//タスクRUN
	void APTask_DirectionChangeY::TaskRun(void)
	{
		ControlData->SetDirectionY(m_value);
	};

	//APTask_DirectionChangeZ=============================================
	//コンストラクタ
	APTask_DirectionChangeZ::APTask_DirectionChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue)
	:m_value(SetValue)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeZ::SetValue(double SetValue)
	{
		m_value = SetValue;
	};

	//タスクRUN
	void APTask_DirectionChangeZ::TaskRun(void)
	{
		ControlData->SetDirectionZ(m_value);
	};

	//APTask_DirectionChangeXY=============================================
	//コンストラクタ
	APTask_DirectionChangeXY::APTask_DirectionChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirX, double SetDirY)
	:m_DirX(SetDirX)
	,m_DirY(SetDirY)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeXY::SetValue(double SetDirX, double SetDirY)
	{
		m_DirX = SetDirX;
		m_DirY = SetDirY;
	};

	//タスクRUN
	void APTask_DirectionChangeXY::TaskRun(void)
	{
		ControlData->SetDirectionXY(m_DirX, m_DirY);
	};

	//APTask_DirectionChangeXZ=============================================
	//コンストラクタ
	APTask_DirectionChangeXZ::APTask_DirectionChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirX, double SetDirZ)
	:m_DirX(SetDirX)
	,m_DirZ(SetDirZ)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeXZ::SetValue(double SetDirX, double SetDirZ)
	{
		m_DirX = SetDirX;
		m_DirZ = SetDirZ;
	};

	//タスクRUN
	void APTask_DirectionChangeXZ::TaskRun(void)
	{
		ControlData->SetDirectionXZ(m_DirX, m_DirZ);
	};

	//APTask_DirectionChangeYZ=============================================
	//コンストラクタ
	APTask_DirectionChangeYZ::APTask_DirectionChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirY, double SetDirZ)
	:m_DirY(SetDirY)
	,m_DirZ(SetDirZ)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionChangeYZ::SetValue(double SetDirY, double SetDirZ)
	{
		m_DirY = SetDirY;
		m_DirZ = SetDirZ;
	};

	//タスクRUN
	void APTask_DirectionChangeYZ::TaskRun(void)
	{
		ControlData->SetDirectionYZ(m_DirY, m_DirZ);
	};

	//APTask_PositionConnectChange==============================================
	//コンストラクタ
	APTask_PositionConnectChange::APTask_PositionConnectChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
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

	//APTask_PositionConnectChangeX==============================================
	//コンストラクタ
	APTask_PositionConnectChangeX::APTask_PositionConnectChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeX::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeX::TaskRun(void)
	{
		ControlData->SetPositionConnectX(mp_ConnectPoint);
	};

	//APTask_PositionConnectChangeY==============================================
	//コンストラクタ
	APTask_PositionConnectChangeY::APTask_PositionConnectChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeY::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeY::TaskRun(void)
	{
		ControlData->SetPositionConnectY(mp_ConnectPoint);
	};

	//APTask_PositionConnectChangeZ==============================================
	//コンストラクタ
	APTask_PositionConnectChangeZ::APTask_PositionConnectChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeZ::TaskRun(void)
	{
		ControlData->SetPositionConnectZ(mp_ConnectPoint);
	};

	//APTask_PositionConnectChangeXY==============================================
	//コンストラクタ
	APTask_PositionConnectChangeXY::APTask_PositionConnectChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeXY::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeXY::TaskRun(void)
	{
		ControlData->SetPositionConnectXY(mp_ConnectPoint);
	};

	//APTask_PositionConnectChangeXZ==============================================
	//コンストラクタ
	APTask_PositionConnectChangeXZ::APTask_PositionConnectChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeXZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeXZ::TaskRun(void)
	{
		ControlData->SetPositionConnectXY(mp_ConnectPoint);
	};

	//APTask_PositionConnectChangeYZ==============================================
	//コンストラクタ
	APTask_PositionConnectChangeYZ::APTask_PositionConnectChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_)
	:mp_ConnectPoint(_3dpos_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_PositionConnectChangeYZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		mp_ConnectPoint = _3dpos_;

	};

	//タスクRUN
	void APTask_PositionConnectChangeYZ::TaskRun(void)
	{
		ControlData->SetPositionConnectXY(mp_ConnectPoint);
	};

	//APTask_DirectionConnectChange==============================================
	//コンストラクタ
	APTask_DirectionConnectChange::APTask_DirectionConnectChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChange::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChange::TaskRun(void)
	{
		ControlData->SetDirectionConnectAll(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeX==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeX::APTask_DirectionConnectChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeX::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeX::TaskRun(void)
	{
		ControlData->SetDirectionConnectX(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeY==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeY::APTask_DirectionConnectChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeY::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeY::TaskRun(void)
	{
		ControlData->SetDirectionConnectY(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeZ==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeZ::APTask_DirectionConnectChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeZ::TaskRun(void)
	{
		ControlData->SetDirectionConnectZ(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeXY==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeXY::APTask_DirectionConnectChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeXY::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeXY::TaskRun(void)
	{
		ControlData->SetDirectionConnectXY(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeXZ==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeXZ::APTask_DirectionConnectChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeXZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeXZ::TaskRun(void)
	{
		ControlData->SetDirectionConnectXZ(mp_ConnectPoint);

	};

	//APTask_DirectionConnectChangeYZ==============================================
	//コンストラクタ
	APTask_DirectionConnectChangeYZ::APTask_DirectionConnectChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_)
	:mp_ConnectPoint(_3ddir_)
	{
		//SetData.CastSetPointer(ControlData);
		SonikLib::SharedCast_Reinterpret<SonikAudioDataInterface::SADInterface_PlayerSide, SonikAudioData::SonikAudioControlData>(SetData, ControlData);
	};

	//値のセット
	void APTask_DirectionConnectChangeYZ::SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		mp_ConnectPoint = _3ddir_;

	};

	//タスクRUN
	void APTask_DirectionConnectChangeYZ::TaskRun(void)
	{
		ControlData->SetDirectionConnectYZ(mp_ConnectPoint);

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


