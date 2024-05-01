/*
 * PlayerTask.h
 *
 *  Created on: 2023/10/19
 *      Author: owner
 */

#ifndef TASK_PLAYERTASK_H_
#define TASK_PLAYERTASK_H_

#include "PlayerTaskInterface.h"
#include "../PlayStateEnums.h"

//前方宣言
namespace SonikAudioData
{
	class SonikAudioControlData;
	class SonikAudioControlDataSetForSE;
};

namespace SonikMathDataBox
{
	class Sonik3DPoint;
};

//Playerから発行されるタスクを定義、実装。
namespace SonikAudioPlayerTask
{

	//音量を設定します。
	class APTask_VolumeChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		float m_Volume; //ボリューム
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> ControlData;

	public:
		//コンストラクタ
		APTask_VolumeChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetData, float VolumeArg = 1.0f);

		//値のセット
		void SetValue(float VolumeArg);

		//タスクRUN
		void TaskRun(void);
	};

	//オーディオステータスを設定します。
	class APTask_StatusChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikAudioEnum::PlayStateID m_State;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> ControlData;

	public:
		//コンストラクタ
		APTask_StatusChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetData, SonikAudioEnum::PlayStateID SetValue = SonikAudioEnum::PlayStateID::PS_Stop);

		//値のセット
		void SetValue(SonikAudioEnum::PlayStateID SetValue);

		//タスクRUN
		void TaskRun(void);

	};

	//ポジションを設定します。
	class APTask_PositionChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_Posx;
		double m_Posy;
		double m_Posz;

		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosx = 0.0, double SetPosy = 0.0, double SetPosz = 0.0);

		//値のセット
		void SetValue(double SetPosx, double SetPosy, double SetPosz);

		//タスクRUN
		void TaskRun(void);

	};
	//X軸のみのポジションを設定します。
	class APTask_PositionChangeX : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};
	//Y軸のみのポジションを設定します。
	class APTask_PositionChangeY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};
	//Z軸のみのポジションを設定します。
	class APTask_PositionChangeZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};
	//XY軸のみのポジションを設定します。
	class APTask_PositionChangeXY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_PosX;
		double m_PosY;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosX = 0.0, double SetPosY = 0.0);

		//値のセット
		void SetValue(double SetPosX, double SetPosY);

		//タスクRUN
		void TaskRun(void);

	};
	//XZ軸のみのポジションを設定します。
	class APTask_PositionChangeXZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_PosX;
		double m_PosZ;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosX = 0.0, double SetPosZ = 0.0);

		//値のセット
		void SetValue(double SetPosX, double SetPosZ);

		//タスクRUN
		void TaskRun(void);

	};
	//YZ軸のみのポジションを設定します。
	class APTask_PositionChangeYZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_PosY;
		double m_PosZ;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetPosY = 0.0, double SetPosZ = 0.0);

		//値のセット
		void SetValue(double SetPosY, double SetPosZ);

		//タスクRUN
		void TaskRun(void);

	};

	//方向を設定します。
	class APTask_DirectionChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_Dirx;
		double m_Diry;
		double m_Dirz;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirx = 0.0, double SetDiry = 0.0, double SetDirz = 0.0);

		//値のセット
		void SetValue(double SetDirx, double SetDiry, double SetDirz);

		//タスクRUN
		void TaskRun(void);

	};

	//X軸の方向を設定します。
	class APTask_DirectionChangeX : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};

	//Y軸の方向を設定します。
	class APTask_DirectionChangeY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};

	//Z軸の方向を設定します。
	class APTask_DirectionChangeZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_value;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetValue = 0.0);

		//値のセット
		void SetValue(double SetValue);

		//タスクRUN
		void TaskRun(void);

	};

	//XY軸の方向を設定します。
	class APTask_DirectionChangeXY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_DirX;
		double m_DirY;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirX = 0.0, double SetDirY = 0.0);

		//値のセット
		void SetValue(double SetDirX, double SetDirY);

		//タスクRUN
		void TaskRun(void);

	};

	//XZ軸の方向を設定します。
	class APTask_DirectionChangeXZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_DirX;
		double m_DirZ;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirX = 0.0, double SetDirZ = 0.0);

		//値のセット
		void SetValue(double SetDirX, double SetDirZ);

		//タスクRUN
		void TaskRun(void);

	};

	//YZ軸の方向を設定します。
	class APTask_DirectionChangeYZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		double m_DirY;
		double m_DirZ;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, double SetDirY = 0.0, double SetDirZ = 0.0);

		//値のセット
		void SetValue(double SetDirY, double SetDirZ);

		//タスクRUN
		void TaskRun(void);

	};


	//ポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//X軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeX : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//Y軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//Z軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//XY軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeXY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//XZ軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeXZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//YZ軸のみのポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChangeYZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_PositionConnectChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//X軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeX : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeX(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//Y軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//Z軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//XY軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeXY : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeXY(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//XZ軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeXZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeXZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//YZ軸のみの方向のコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_DirectionConnectChangeYZ : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> ControlData;

	public:
		//コンストラクタ
		APTask_DirectionConnectChangeYZ(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> SetData, SonikMathDataBox::Sonik3DPoint* _3ddir_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3ddir_);

		//タスクRUN
		void TaskRun(void);

	};

	//リピート(繰り返し)のフラグ設定をします。
	class APTask_RepeatFlgChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		bool m_repeat;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> ControlData;

	public:
		//コンストラクタ
		APTask_RepeatFlgChange(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetData, bool SetValue);

		//値のセット
		void SetValue(bool SetValue);

		//タスクRUN
		void TaskRun(void);

	};

};



#endif /* TASK_PLAYERTASK_H_ */
