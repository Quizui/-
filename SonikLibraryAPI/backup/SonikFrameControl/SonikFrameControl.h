/*
 * SonikFrameControl.h
 *
 *  Created on: 2016/05/23
 *      Author: Sonik
 */

#ifndef SONIKFRAMECONTROL_SONIKFRAMECONTROL_H_
#define SONIKFRAMECONTROL_SONIKFRAMECONTROL_H_

namespace SonikLib
{
	class SonikFrameControl
	{
	private:
		unsigned long FrameRate;	//フレームレート
		unsigned long FrameCount;	//フレームカウント

		unsigned long long FrameStartTime;	//1秒間のスタートタイム。
		unsigned long long OneFrameStartTime;	//1フレームのスタートタイム。
		unsigned long long BeforFrameTime;		//1フレーム前の時間。

	public:
		SonikFrameControl(void);
		SonikFrameControl(unsigned long SetFrameRate);
		SonikFrameControl(unsigned long SetFrameRate, unsigned long SetSampleCount);

		~SonikFrameControl(void);

//		double GetFps(void);

		void FrameSleep(void);


	};


};



#endif /* SONIKFRAMECONTROL_SONIKFRAMECONTROL_H_ */
