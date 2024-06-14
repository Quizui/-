/*
 * SonikAudio_Implement.cpp
 *
 *  Created on: 2023/05/23
 *      Author: owner
 */


//#include "../PlatformInterface/PlatformAudioInterface.h"
//#include "../PlatformInterface/PlatformAudioPlayerInterface.h"

#include <new>

#include "SonikAudio_Implement.h"
//#include "SonikAudioPlayer_inherit.h"
#include "../Task/AudioPlayerTaskManager.h"
#include "../Mixer/SonikAudio_Mixer.h"
#include "../Player/SonikAudioPlayer_CD_BGM.h"
#include "../Player/SonikAudioPlayer_CD_SE.h"
#include "../Listener/SonikAudioListener.h"
#include "../Player/SonikAudioBGMPlayer.h"
#include "../Player/SonikAudioSEPlayer.h"


namespace SonikAudio
{
	SonikAudio_Implement::SonikAudio_Implement(void)
	:SamplingType(SonikAudio::SCVType::B16_CH1_SR44100)
	,mp_Mixer(nullptr)
	{
		//no_process;
	};

	SonikAudio_Implement::~SonikAudio_Implement(void)
	{
		//廃棄処理
		//ミキサを先に破棄しないとプラットフォーム先のバッファリング参照でセグフォを起こす。
		if( !mp_Mixer.IsNullptr() )
		{
			mp_Mixer.ResetPointer(nullptr);
		};

		//PlatFormInterfaceのライフサイクル管理はAudioInterfaceの管轄のため
		//ここでDeleteコール。
		//DLL内でnewされているのでDLL内で開放処理をしてあげないといけない。
		//ので専用のスマートポインタを作らずにハンドル管理。
		uintptr_t func_ = 0;
		func_ = m_platformHandle->GetDllProcAddress("PlatFormDelete");

		(*reinterpret_cast<void(*)(void)>(func_))();

	};

	bool SonikAudio_Implement::Initialize(uint32_t Set_Sampletype, SonikAudioPlatForm::SonikPlatformAudioInterface* Set_PFI_Pointer, SonikLib::SDllHandle SetHandle)
	{
		//m_pfi = Set_PFI_Pointer;
		//m_handle = SetHandle;
		SamplingType = static_cast<SonikAudio::SCVType>(Set_Sampletype);

		//リスナ生成。
		SonikAudio::SonikAudioListener* lp_listener = new(std::nothrow) SonikAudio::SonikAudioListener();
		if(lp_listener == nullptr)
		{
			SamplingType = SonikAudio::SCVType::B16_CH1_SR44100;
			return false;
		};

		//スマートポインタへセット
		mp_Listener.ResetPointer(lp_listener);

		SonikAudioPlayerTask::SonikAudioPlayerTaskManager* l_mng = nullptr;
		l_mng = new(std::nothrow) SonikAudioPlayerTask::SonikAudioPlayerTaskManager;
		if(l_mng == nullptr)
		{
			return false;
		};

		//スマートポインタへセット
		m_TaskMng.ResetPointer(l_mng);

		if( !m_TaskMng->Initialize(1000) )
		{
			SamplingType = SonikAudio::SCVType::B16_CH1_SR44100;
			return false;
		};

		SonikAudio::SonikAudioMixer* l_mixer = nullptr;
		l_mixer = new(std::nothrow) SonikAudio::SonikAudioMixer();
		if( l_mixer == nullptr )
		{
			SamplingType = SonikAudio::SCVType::B16_CH1_SR44100;
			return false;
		};

		//スマートポインタへセット
		mp_Mixer.ResetPointer(l_mixer);

		uint32_t _samplingrate = (Set_Sampletype & 0x000000FF) * 1000;
		if(_samplingrate == 44000)
		{
			_samplingrate += 100;
		};

		uint32_t _bit = ((Set_Sampletype & 0x00FF0000) >> 16);
		uint16_t _ch = ((Set_Sampletype & 0x0000FF00) >> 8);

		if( !l_mixer->Initialize(1000, _bit, _ch, _samplingrate, Set_PFI_Pointer, mp_Listener))
		{

			SamplingType = SonikAudio::SCVType::B16_CH1_SR44100;
			return false;
		};

		m_platformHandle = SetHandle;

		return true;
	};


	//オーディオファイルをロードしてAudioPlayerを作成できるようにセットします。
	bool SonikAudio_Implement::LoadAudio(const char* AudioFilePath, uint32_t SetAudioID)
	{
		SonikAudio::SAudioFormat _audio;

		if( !SonikAudioLoadFunction::Load_WaveFile(AudioFilePath, _audio, SamplingType, true) )
		{
			return false;
		};

		if( !audiomap.insert( std::map<unsigned long, SonikAudio::SAudioFormat>::value_type(SetAudioID, _audio) ).second )
		{
			//Key重複
			return false;
		};

		return true;
	};

	//オーディオリスナの取得
	void SonikAudio_Implement::GetListener(SAudioListener& _out_get_)
	{
		_out_get_ = mp_Listener;
	};

	//BGMとしてオーディオプレイヤーを作成します。
	bool SonikAudio_Implement::Create_BGM_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioBGMPlayer& GetPlayer)
	{
		SonikAudio::SonikAudioBGMPlayer* l_player = nullptr;
		SonikAudioData::SonikAudioControlDataSetForBGM* l_apdata = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForBGM> apdata_smtptr;
		decltype(audiomap)::iterator _it;


		_it = audiomap.find(AudioID);
		if( _it == audiomap.end() )
		{
			//ID無し。
			return false;
		};

		l_apdata = new(std::nothrow) SonikAudioData::SonikAudioControlDataSetForBGM(mp_Listener->GetMasterVolumeRef(), _it->second);
		if( l_apdata == nullptr )
		{
			return false;
		};

		apdata_smtptr.ResetPointer(l_apdata);

		SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> _player_arg_s;
		SonikLib::SharedCast_Dynamic<SonikAudioPlayerTask::SonikAudioPlayerTaskManager, SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface>(m_TaskMng, _player_arg_s);

		l_player = new(std::nothrow) SonikAudio::SonikAudioBGMPlayer(apdata_smtptr, _player_arg_s);
		if( l_player == nullptr )
		{
			//l_apdataはスマートポインタに格納されているためdelete省略。
			return false;
		};

		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> mapset_smtptr;
		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForBGM, SonikAudioData::SonikAudioControlData>(apdata_smtptr, mapset_smtptr);
		//ControlDataを登録
		if( !ap_Data.insert( std::map<uint64_t, SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>::value_type(apdata_smtptr->Get_UniqueID(), mapset_smtptr) ).second )
		{
			//Key重複

			delete l_player;
			return false;
		};

		mp_Mixer->AddAudio(mapset_smtptr);

		//すべて完了したので返却。
		GetPlayer.ResetPointer(l_player);

		return true;

	};

	//SEとしてオーディオプレイヤーを作成します。
	bool SonikAudio_Implement::Create_SE_AudioPlayer(uint32_t AudioID, SonikAudio::SAudioSEPlayer& GetPlayer)
	{
		SonikAudio::SonikAudioSEPlayer* l_player = nullptr;
		SonikAudioData::SonikAudioControlDataSetForSE* l_apdata = nullptr;
		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> apdata_smtptr;
		decltype(audiomap)::iterator _it;


		_it = audiomap.find(AudioID);
		if( _it == audiomap.end() )
		{
			//ID無し。
			return false;
		};

		l_apdata = new(std::nothrow) SonikAudioData::SonikAudioControlDataSetForSE(mp_Listener->GetCategoryVolumeSERef(), mp_Listener->GetPosition(), mp_Listener->GetDirection(), _it->second);
		if( l_apdata == nullptr )
		{
			return false;
		};

		apdata_smtptr.ResetPointer(l_apdata);

		SonikLib::SharedSmtPtr<SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface> _player_arg_s;
		SonikLib::SharedCast_Dynamic<SonikAudioPlayerTask::SonikAudioPlayerTaskManager, SonikAudioTaskInterface::SonikAudioPlayerTaskManagerInterface>(m_TaskMng, _player_arg_s);

		l_player = new(std::nothrow) SonikAudio::SonikAudioSEPlayer(apdata_smtptr, _player_arg_s);
		if( l_player == nullptr )
		{
			//l_apdataはスマートポインタに格納されているためdelete省略。
			return false;
		};

		SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> mapset_smtptr;
		SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlDataSetForSE, SonikAudioData::SonikAudioControlData>(apdata_smtptr, mapset_smtptr);
		//ControlDataを登録
		if( !ap_Data.insert( std::map<uint64_t, SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>::value_type(apdata_smtptr->Get_UniqueID(), mapset_smtptr) ).second )
		{
			//Key重複

			delete l_player;
			return false;
		};

		mp_Mixer->AddAudio(mapset_smtptr);

		//すべて完了したので返却。
		GetPlayer.ResetPointer(l_player);

		return true;

	};

	//ハードウェア情報を取得します。
	bool SonikAudio_Implement::GetAudioHardwareInfo(void)
	{
		return true;
	};


};
