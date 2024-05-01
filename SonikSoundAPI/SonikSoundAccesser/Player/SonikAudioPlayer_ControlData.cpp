/*
 * SonikAudioPlayer_ControlData.cpp
 *
 *  Created on: 2023/10/16
 *      Author: owner
 */

#include "SonikAudioPlayer_ControlData.h"
#include "../../Format/SonikAudioFormat.h"
#include "../../../MathBit/SonikMathDistance.h"

#include <new>

namespace SonikAudioData
{
	//MainClass===========================================================
	//コンストラクタ
	SonikAudioControlData::SonikAudioControlData(SonikAudio::SAudioFormat SetAudioPointer)
	:m_AudioData(SetAudioPointer)
	,mp_ControlData(const_cast<char*>(m_AudioData->Get_WaveData()))
	,m_volume(1.0f)
	,m_repeat(false)
	,m_AudioState(SonikAudioEnum::PlayStateID::PS_Stop)
	,m_uniqueid((uintptr_t)this)
	{

	};

	//デストラクタ
	SonikAudioControlData::~SonikAudioControlData(void)
	{
	};

	//コントロールオーディオのポインタを先頭ポインタへ移動します。
	void SonikAudioControlData::TopResetAudioControlPointer(void)
	{
		mp_ControlData = const_cast<char*>(m_AudioData->Get_WaveData());
	};

	//現在のコントロールポインタの位置が終端かどうかを確認します。
	bool SonikAudioControlData::Get_EndPointer(void)
	{
		if( mp_ControlData >= (const_cast<char*>(m_AudioData->Get_WaveData()) + m_AudioData->Get_WaveDataSize()) )
		{
			return true;
		};

		return false;
	};


	//コントロールオーディオポインタのゲット
	char** SonikAudioControlData::GetAudioControlPointer(void)
	{
		return &mp_ControlData;
	};

	//音量(ボリューム)のセット
	void SonikAudioControlData::SetVolume(float SetValue)
	{
		m_volume = SetValue;
	};

	//繰り返し(リピート)フラグのセット
	void SonikAudioControlData::SetRepeat(bool SetValue)
	{
		RepeatFlgLock.lock();

		m_repeat = SetValue;

		RepeatFlgLock.unlock();
	};

	//オーディオステータスのセット
	void SonikAudioControlData::SetAudioState(SonikAudioEnum::PlayStateID SetValue)
	{
		AudioStateLock.lock();

		m_AudioState = SetValue;

		AudioStateLock.unlock();

	};
	//音量(ボリューム)のゲット
	const float* SonikAudioControlData::GetVolume(void)
	{
		return &m_volume;
	};

	//繰り返し(リピート)フラグのゲット
	bool SonikAudioControlData::GetRepeat(void)
	{
		bool _ret;

		RepeatFlgLock.lock();

		_ret = m_repeat;

		RepeatFlgLock.unlock();

		return _ret;

	};

	uint32_t SonikAudioControlData::GetAllWaveDataSize(void)
	{
		return m_AudioData->Get_WaveDataSize();
	};


	//ステータスのゲット
	SonikAudioEnum::PlayStateID SonikAudioControlData::GetPlayState(void)
	{
		SonikAudioEnum::PlayStateID _ret;

		AudioStateLock.lock();

		_ret = m_AudioState;

		AudioStateLock.unlock();

		return _ret;
	};

	//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
	uint64_t SonikAudioControlData::Get_UniqueID(void)
	{
		return m_uniqueid;
	};

};


