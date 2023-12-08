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
		APTask_VolumeChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float VolumeArg = 1.0f);

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
		APTask_StatusChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, SonikAudioEnum::PlayStateID SetValue = SonikAudioEnum::PlayStateID::PS_Stop);

		//値のセット
		void SetValue(SonikAudioEnum::PlayStateID SetValue);

		//タスクRUN
		void TaskRun(void);

	};

	//ポジションを設定します。
	class APTask_PositionChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		float m_Posx;
		float m_Posy;
		float m_Posz;

	public:
		//コンストラクタ
		APTask_PositionChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float SetPosx = 0.0f, float SetPosy = 0.0f, float SetPosz = 0.0f);

		//値のセット
		void SetValue(float SetPosx, float SetPosy, float SetPosz);

		//タスクRUN
		void TaskRun(void);

	};

	//ポジションのコネクトを設定します。
	//設定したポインタはDeleteがよばれません。
	//コネクトを解除したい場合は各引数にnullptrを指定します。
	class APTask_PositionConnectChange : public SonikAudioTaskInterface::PlayerTaskInterface
	{
	private:
		float* mp_Posx;
		float* mp_Posy;
		float* mp_Posz;

	public:
		//コンストラクタ
		APTask_PositionConnectChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, float* SetPosx = nullptr, float* SetPosy = nullptr, float* SetPosz = nullptr);

		//値のセット
		void SetValue(float* SetPosx, float* SetPosy, float* SetPosz);

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
		APTask_RepeatFlgChange(SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudioDataInterface::SADInterface_PlayerSide> SetData, bool SetValue);

		//値のセット
		void SetValue(bool SetValue);

		//タスクRUN
		void TaskRun(void);

	};

};



#endif /* TASK_PLAYERTASK_H_ */
