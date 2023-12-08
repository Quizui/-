/*
 * SonikAudioPlayer_ControlData.cpp
 *
 *  Created on: 2023/10/16
 *      Author: owner
 */

#include "SonikAudioPlayer_ControlData.h"
#include "../../Format/SonikAudioFormat.h"

namespace SonikAudioData
{
	//MainClass===========================================================
	//コンストラクタ
	SonikAudioControlData::SonikAudioControlData(SonikAudio::SAudioFormat SetAudioPointer)
	:m_AudioData(SetAudioPointer)
	,mp_ControlData(const_cast<char*>(m_AudioData->Get_WaveData()))
	,m_posx(0.0f)
	,m_posy(0.0f)
	,m_posz(0.0f)
	,mp_posx(&m_posx)
	,mp_posy(&m_posy)
	,mp_posz(&m_posz)
	,m_volume(1.0f)
	,m_repeat(false)
	,m_AudioState(SonikAudioEnum::PlayStateID::PS_Stop)
	,m_uniqueid((uintptr_t)this)
	{

	};

	//デストラクタ
	SonikAudioControlData::~SonikAudioControlData(void)
	{
		//あくまでポインタを使うだけなので何もしない。(音量調整等で値は変更しちゃうかもなので非const)

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

	//ポジションのセット
	void SonikAudioControlData::SetPositionX(float SetValue)
	{
		m_posx = SetValue;
	};

	void SonikAudioControlData::SetPositionY(float SetValue)
	{
		m_posy = SetValue;
	};

	void SonikAudioControlData::SetPositionZ(float SetValue)
	{
		m_posz = SetValue;
	};

	void SonikAudioControlData::SetPositionAll(float x, float y, float z)
	{
		m_posx = x;
		m_posy = y;
		m_posz = z;
	};


	//ポジションのポインタ先をセット。
	//別のポジションへのポインタとつなぎ、位置を一緒に動かしたいときに使います。
	//内部の個別ポジションに戻したい場合はnullptrを指定します。
	void SonikAudioControlData::SetPositonConnectX(float* x = nullptr)
	{
		PositionLock[0].lock();

		if( x == nullptr )
		{
			mp_posx = &m_posx;
			PositionLock[0].Unlock();
			return;
		};

		mp_posx = x;

		PositionLock[0].Unlock();
	};

	void SonikAudioControlData::SetPositonConnectY(float* y = nullptr)
	{
		PositionLock[1].lock();

		if( y == nullptr )
		{
			mp_posy = &m_posy;
			PositionLock[1].Unlock();
			return;
		};

		mp_posy = y;
		PositionLock[1].Unlock();

	};

	void SonikAudioControlData::SetPositonConnectZ(float* z = nullptr)
	{
		PositionLock[2].lock();
		if( z == nullptr )
		{
			mp_posz = &m_posz;
			PositionLock[2].Unlock();
			return;
		};

		mp_posz = z;
		PositionLock[2].Unlock();

	};

	void SonikAudioControlData::SetPositionConnectAll(float* x = nullptr, float* y = nullptr, float* z = nullptr)
	{
		SetPositonConnectX(x);
		SetPositonConnectY(y);
		SetPositonConnectZ(z);
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

		RepeatFlgLock.Unlock();
	};

	//オーディオステータスのセット
	void SonikAudioControlData::SetAudioState(SonikAudioEnum::PlayStateID SetValue)
	{
		AudioStateLock.lock();

		m_AudioState = SetValue;

		AudioStateLock.Unlock();

	};

	//継承元の純粋仮想関数の実装====================================
	//ポジションのゲット
	float SonikAudioControlData::GetPositionX(void)
	{
		float * _ret;

		PositionLock[0].lock();

		_ret = mp_posx;

		PositionLock[0].Unlock();

		return *_ret;
	};

	float SonikAudioControlData::GetPositionY(void)
	{
		float * _ret;

		PositionLock[1].lock();

		_ret = mp_posy;

		PositionLock[1].Unlock();

		return *_ret;
	};

	float SonikAudioControlData::GetPositionZ(void)
	{
		float * _ret;

		PositionLock[2].lock();

		_ret = mp_posz;

		PositionLock[2].Unlock();

		return *_ret;
	};

	void SonikAudioControlData::GetPositionAll(float& x, float& y, float& z)
	{
		PositionLock[0].lock();
		PositionLock[1].lock();
		PositionLock[2].lock();

		x = *mp_posx;
		y = *mp_posy;
		z = *mp_posz;

		PositionLock[0].Unlock();
		PositionLock[1].Unlock();
		PositionLock[2].Unlock();

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

		RepeatFlgLock.Unlock();

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

		AudioStateLock.Unlock();

		return _ret;
	};

	//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
	uint64_t SonikAudioControlData::Get_UniqueID(void)
	{
		return m_uniqueid;
	};

};


