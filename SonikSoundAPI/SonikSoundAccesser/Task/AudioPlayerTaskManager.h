/*
 * AudioPlayerTaskManager.h
 *
 *  Created on: 2023/10/20
 *      Author: owner
 */

#ifndef TASK_AUDIOPLAYERTASKMANAGER_H_
#define TASK_AUDIOPLAYERTASKMANAGER_H_

#include "PlayerTaskInterface.h"
#include "../../../SonikWorkThread/SonikWorkThreadEx.h"
#include "../../../Container/SonikAtomicQueue.hpp"

namespace SonikAudioPlayerTask
{
	//オーディオインターフェースが実態の生成と保持をします。
	class SonikAudioPlayerTaskManager : public SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface
	{
	private:
		//タスクを受け取るQueue
		SonikLib::Container::SonikAtomicQueue<SonikAudioTaskInterface::PlayerTaskInterface*>* mp_TaskQueue;
		//タスクを実行するThread
		SonikLib::WorkThreadEx* mp_TaskThread;

	private:
		//スレッドで回す用の関数。QueueからのDequeueとRunを実行する。
		void ThreadProcFunc(void);

	public:
		//コンストラクタ
		SonikAudioPlayerTaskManager(void);
		//デストラクタ
		~SonikAudioPlayerTaskManager(void);

		//イニシャライザ
		bool Initialize(uint32_t QueueItemNum);

		//純粋仮想関数の実装。
		//Queueにタスクをセットします。
		bool AddTask(SonikAudioTaskInterface::PlayerTaskInterface* pTask);

	};


};

#endif /* TASK_AUDIOPLAYERTASKMANAGER_H_ */
