/*
 * SonikAudio_Implement.h
 *
 *  Created on: 2023/05/23
 *      Author: owner
 */

#ifndef INTERFACE_SONIKAUDIO_IMPLEMENT_H_
#define INTERFACE_SONIKAUDIO_IMPLEMENT_H_
//SonikAudioInterface のメイン実装

#include "./SonikAudio.h"
#include "../../DllAccess/SonikDllAccessManager.h"
#include "../other/SAudioAccesserTypedef.h"
#include "../AudioLoadTypedef.h"
#include "../../SmartPointer/SonikSmartPointer.hpp"

//各プラットフォームのインターフェースクラスポインタを使うため前方宣言
namespace SonikAudioPlatForm
{
	class SonikPlatformAudioInterface;
};

namespace SonikAudioData
{
	class SonikAudioControlData;
};

namespace SonikAudioPlayerTask
{
	class SonikAudioPlayerTaskManager;
};

namespace SonikAudio
{
	class SonikAudioMixer;
};


//本体定義
namespace SonikAudio
{
	class SonikAudio_Implement : public SonikAudio::SonikAudioInterface
	{
	private:
		//Platformハンドル。
		SonikLib::SDllHandle m_platformHandle;

		//SamlingRateタイプ
		SonikAudio::SCVType SamplingType;
		std::map<uint32_t, SonikAudio::SAudioFormat> audiomap;

		//プレイヤーのオーディオデータを保持するmap
		std::map<uint64_t, SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>> ap_Data;

		//プレイヤーとミキサの仲介を担うタスクマネージャー
		SonikLib::SharedSmtPtr<SonikAudioPlayerTask::SonikAudioPlayerTaskManager> m_TaskMng;

		//ミキサ
		SonikLib::SharedSmtPtr<SonikAudio::SonikAudioMixer> mp_Mixer;
		//リスナ(前方宣言はSAudioAccesserTypedef.hで宣言済)
		SonikAudio::SAudioListener mp_Listener;

	public:
		//constructor
		SonikAudio_Implement(void);
		//Destructor
		~SonikAudio_Implement(void);

		//イニシャライザ
		bool Initialize(uint32_t Set_Sampletype, SonikAudioPlatForm::SonikPlatformAudioInterface* Set_PFI_Pointer, SonikLib::SDllHandle SetHandle);

		//ピュア関数の実装
		//オーディオファイルをロードしてAudioPlayerを作成できるようにセットします。
		bool LoadAudio(const char* AudioFilePath, uint32_t SetAudioID);
		//オーディオリスナの取得
		void GetListener(SAudioListener& _out_get_);
		//BGMとしてオーディオプレイヤーを作成します。
		bool Create_BGM_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioBGMPlayer& GetPlayer);
		//SEとしてオーディオプレイヤーを作成します。
		bool Create_SE_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioSEPlayer& GetPlayer);
		//ハードウェア情報を取得します。
		bool GetAudioHardwareInfo(void);
	};
};


#endif /* INTERFACE_SONIKAUDIO_IMPLEMENT_H_ */
