/*
 * PlayerTaskInterface.h
 *
 *  Created on: 2023/10/19
 *      Author: owner
 */

#ifndef TASK_PLAYERTASKINTERFACE_H_
#define TASK_PLAYERTASKINTERFACE_H_

#include "../SAudioAccesserTypedef.h"

//前方宣言
namespace SonikAudioData
{
	class SonikAudioControlData;
};

//インターフェース定義
namespace SonikAudioTaskInterface
{
	//プレイヤーから発行されるタスクのインタフェース
	class PlayerTaskInterface
	{
	protected:

	public:
		//コンストラクタ
		PlayerTaskInterface(void)
		{
			//no process;
		};

		//デストラクタ
		virtual ~PlayerTaskInterface(void)
		{
			//no process;
		};

		//タスクRUN
		virtual void TaskRun(void) =0;
	};


	//プレイヤー側からマネージャへのアクセス用インタフェース。
	class SonikAudioPlayerTaskManagerInterface
	{
		//メンバなし。
	public:
		//コンストラクタ
		SonikAudioPlayerTaskManagerInterface(void)
		{
			//no process;
		};

		//デストラクタ
		virtual ~SonikAudioPlayerTaskManagerInterface(void)
		{
			//no process;
		};

		//タスクセット
		virtual bool AddTask(PlayerTaskInterface* pTask) =0;
	};

}



#endif /* TASK_PLAYERTASKINTERFACE_H_ */
