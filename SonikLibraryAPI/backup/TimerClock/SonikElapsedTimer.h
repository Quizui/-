/*
 * SonikElapsedTimer.h
 *
 *  Created on: 2016/03/03
 *      Author: Sonik
 */

#ifndef TIMERCLOCK_SONIKELAPSEDTIMER_H_
#define TIMERCLOCK_SONIKELAPSEDTIMER_H_

//C++11以降でしか使用できません。

namespace SonikLib
{
	//ある時間からの経過時間を取得するクラスです。
	class SonikElapsedTimer
	{
	private:
		unsigned long long StartTime;

		//インターバル時間
		unsigned long IntervalTime;

	private:
		//コピーコンストラクタ
		SonikElapsedTimer(SonikElapsedTimer& t_his);
		//ムーブコンストラクタ
		SonikElapsedTimer(SonikElapsedTimer&& t_his);

		//代入演算子
		SonikElapsedTimer& operator =(SonikElapsedTimer& t_his);

	public:
		//コンストラクタ
		SonikElapsedTimer(void);

		//デストラクタ
		~SonikElapsedTimer(void);

		//インターバル時間を設定します。
		//引数1: インターバルとして設定する時間をミリ秒で指定します。
		//補足: 本クラスにおける、インターバル時間は、その時間間隔が過ぎたかどうか。を判定するのに仕様します。
		//		0(Default値)を指定した場合、常に GetIntervalOverメソッドは、falseを返却します。
		void SetIntervalTime(unsigned long Set_millisec);

		//計測開始時間を設定します。
		void SetStartTime(void);

		//計測開始時間からの差分を取得します。(ミリ秒)
		unsigned long GetElapsedTime(void);

		//計測開始時間から、インターバル時間を過ぎているかどうかを確認します。
		//インターバル時間を設定した場合、そのインターバル時間を過ぎていれば trueを返却します。
		//default値( 0 ) が設定されていた場合は、本関数は常にfalseを返却します。
		bool GetIntervalOver(void);

		//インターバル時間が過ぎるまで現在のスレッドをスリープします。
		void IntervalSleep(void);

	};

};



#endif /* TIMERCLOCK_SONIKELAPSEDTIMER_H_ */
