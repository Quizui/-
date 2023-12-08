/*
 * SonikElapsedTimer.cpp
 *
 *  Created on: 2016/03/03
 *      Author: Sonik
 */

#include <chrono>
#include <thread>
#include "SonikElapsedTimer.h"

namespace SonikLib
{
	//コンストラクタ
	SonikElapsedTimer::SonikElapsedTimer(void)
	:StartTime(0)
	,IntervalTime(0)
	{

	};

	//コピーコンストラクタ
	SonikElapsedTimer::SonikElapsedTimer(SonikElapsedTimer& t_his)
	{
		//no called faunction
		//コールされないので、実装なし。
	};

	//ムーブコンストラクタ
	SonikElapsedTimer::SonikElapsedTimer(SonikElapsedTimer&& t_his)
	{
		//no called faunction
		//コールされないので、実装なし。
	};

	//デストラクタ
	SonikElapsedTimer::~SonikElapsedTimer(void)
	{
		//no process;
	};

	//代入演算子
	SonikElapsedTimer& SonikElapsedTimer::operator =(SonikElapsedTimer& t_his)
	{
		//no called faunction
		//コールされないので、実装なし。
		return (*this);
	};

	//インターバル時間を設定します。
	//引数1: インターバルとして設定する時間をミリ秒で指定します。
	//補足: 本クラスにおける、インターバル時間は、その時間間隔が過ぎたかどうか。を判定するのに仕様します。
	//		0(Default値)を指定した場合、常に GetIntervalOverメソッドは、falseを返却します。
	void SonikElapsedTimer::SetIntervalTime(unsigned long Set_millisec)
	{
		IntervalTime = Set_millisec;
	};

	//計測開始時間を設定します。
	void SonikElapsedTimer::SetStartTime(void)
	{
		std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );

		StartTime = mill.count();
	};

	//計測開始時間からの差分を取得します。(ミリ秒)
	unsigned long SonikElapsedTimer::GetElapsedTime(void)
	{
		std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );

		return mill.count() - StartTime;
	};

	//計測開始時間から、インターバル時間を過ぎているかどうかを確認します。
	//インターバル時間を設定した場合、そのインターバル時間を過ぎていれば trueを返却します。
	//default値( 0 ) が設定されていた場合は、本関数は常にfalseを返却します。
	bool SonikElapsedTimer::GetIntervalOver(void)
	{
		std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );

		if( IntervalTime == 0 )
		{
			return false;
		};

		if( IntervalTime < (mill.count() - StartTime) )
		{
			return true;
		};

		return false;
	};

	void SonikElapsedTimer::IntervalSleep(void)
	{
		std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() );

		if( IntervalTime == 0 )
		{
			return;
		};

		unsigned long long now_interval = (mill.count() - StartTime);

		if( IntervalTime > now_interval )
		{
			std::this_thread::sleep_for(std::chrono::milliseconds( IntervalTime - now_interval));
		};

	}


};


