/*
 * PlatformAudioInterface.h
 *
 *  Created on: 2020/04/23
 *      Author: SONIC
 */

//実装自体は別プロジェクトから継承して実装します。
//そのプロジェクトで生成したライブラリファイル(Dll)へのアクセス用クラスです。

#ifndef PLATFORMINTERFACE_PLATFORMAUDIOINTERFACE_H_
#define PLATFORMINTERFACE_PLATFORMAUDIOINTERFACE_H_

#include <stdint.h>

namespace SonikAudioPlatForm
{
	class SonikPlatformAudioPlayerInterface;
};

namespace SonikAudioPlatForm
{
	class SonikPlatformAudioInterface
	{
	public:
		//Constructor
		SonikPlatformAudioInterface(void)
		{
			//no process
		};
		//Destrucotr
		virtual ~SonikPlatformAudioInterface(void)
		{
			//no process
		};

		//Pure Function
		//オーディオのストリーミング再生を開始します。
		virtual bool AudioBfferPlayngStart(void) =0;
		//オーディオのストリーミングのバッファの空きバッファをセットされたバッファ情報で更新します。
		virtual void BufferUpdate(int8_t* SetBuffer) =0;
	};


};


#endif /* PLATFORMINTERFACE_PLATFORMAUDIOINTERFACE_H_ */
