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
namespace SonikAudioDataInterface
{
	class SADInterface_PlayerSide;
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

	public:
		//コンストラクタ
		APTask_VolumeChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float VolumeArg = 1.0f);

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

	public:
		//コンストラクタ
		APTask_StatusChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikAudioEnum::PlayStateID SetValue = SonikAudioEnum::PlayStateID::PS_Stop);

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

	public:
		//コンストラクタ
		APTask_PositionChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, double SetPosx = 0.0, double SetPosy = 0.0, double SetPosz = 0.0);

		//値のセット
		void SetValue(double SetPosx, double SetPosy, double SetPosz);

		//タスクRUN
		void TaskRun(void);

	};

	//ポジションのコネクトを設定します。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		SonikMathDataBox::Sonik3DPoint* mp_ConnectPoint;

	public:
		//コンストラクタ
		APTask_PositionConnectChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikMathDataBox::Sonik3DPoint* _3dpos_ = nullptr);

		//値のセット
		void SetValue(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//タスクRUN
		void TaskRun(void);

	};

	//リピート(繰り返し)のフラグ設定をします。
	class APTask_RepeatFlgChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		bool m_repeat;

	public:
		//コンストラクタ
		APTask_RepeatFlgChange(SonikLib::SharedSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, bool SetValue);

		//値のセット
		void SetValue(bool SetValue);

		//タスクRUN
		void TaskRun(void);

	};

};



#endif /* TASK_PLAYERTASK_H_ */
