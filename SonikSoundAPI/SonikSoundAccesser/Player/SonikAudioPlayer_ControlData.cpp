/*
 * SonikAudioPlayer_ControlData.cpp
 *
 *  Created on: 2023/10/16
 *      Author: owner
 */

#include "SonikAudioPlayer_ControlData.h"
#include "../../Format/SonikAudioFormat.h"
#include "../AudioPosition/SonikAudio3DPoint.h"

#include <new>

namespace SonikAudioData
{
	//MainClass===========================================================
	//コンストラクタ
	SonikAudioControlData::SonikAudioControlData(SonikAudio::SAudioFormat SetAudioPointer)
	:m_AudioData(SetAudioPointer)
	,mp_ControlData(const_cast<char*>(m_AudioData->Get_WaveData()))
	,m_3dpos(nullptr)
	,m_volume(1.0f)
	,m_repeat(false)
	,m_AudioState(SonikAudioEnum::PlayStateID::PS_Stop)
	,m_uniqueid((uintptr_t)this)
	{
		try
		{
			m_3dpos = new SonikAudioPoint::SonikAudio3DPoint();
		}catch(std::bad_alloc& e)
		{
			throw std::bad_alloc(e);
		};

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
	void SonikAudioControlData::SetPositionX(double SetValue)
	{
		m_3dpos->ref_m_x = SetValue;
	};

	void SonikAudioControlData::SetPositionY(double SetValue)
	{
		m_3dpos->ref_m_y = SetValue;
	};

	void SonikAudioControlData::SetPositionZ(double SetValue)
	{
		m_3dpos->ref_m_z = SetValue;
	};

	void SonikAudioControlData::SetPositionAll(double x, double y, double z)
	{
		m_3dpos->ref_m_x = x;
		m_3dpos->ref_m_y = y;
		m_3dpos->ref_m_z = z;
	};


	//ポジションのポインタ先をセット。
	//別のポジションへのポインタとつなぎ、位置を一緒に動かしたいときに使います。
	//内部の個別ポジションに戻したい場合はnullptrを指定します。
	void SonikAudioControlData::SetPositonConnectX(double* x)
	{
		PositionLock[0].lock();

		if( x == nullptr )
		{
			m_3dpos->mp_x = &(m_3dpos->ref_m_x);
			PositionLock[0].Unlock();
			return;
		};

		m_3dpos->mp_x = x;

		PositionLock[0].Unlock();
	};

	void SonikAudioControlData::SetPositonConnectY(double* y)
	{
		PositionLock[1].lock();

		if( y == nullptr )
		{
			m_3dpos->mp_y = &(m_3dpos->ref_m_y);
			PositionLock[1].Unlock();
			return;
		};

		m_3dpos->mp_y = y;
		PositionLock[1].Unlock();

	};

	void SonikAudioControlData::SetPositonConnectZ(double* z)
	{
		PositionLock[2].lock();
		if( z == nullptr )
		{
			m_3dpos->mp_z = &(m_3dpos->ref_m_z);
			PositionLock[2].Unlock();
			return;
		};

		m_3dpos->mp_z = z;
		PositionLock[2].Unlock();

	};

	void SonikAudioControlData::SetPositionConnectAll(double* x, double* y, double* z)
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
	double SonikAudioControlData::GetPositionX(void)
	{
		double* _ret;

		PositionLock[0].lock();

		_ret = m_3dpos->mp_x;

		PositionLock[0].Unlock();

		return *_ret;
	};

	double SonikAudioControlData::GetPositionY(void)
	{
		double* _ret;

		PositionLock[1].lock();

		_ret = m_3dpos->mp_y;

		PositionLock[1].Unlock();

		return *_ret;
	};

	double SonikAudioControlData::GetPositionZ(void)
	{
		double* _ret;

		PositionLock[2].lock();

		_ret = m_3dpos->mp_z;

		PositionLock[2].Unlock();

		return *_ret;
	};

	void SonikAudioControlData::GetPositionAll(double& x, double& y, double& z)
	{
		PositionLock[0].lock();
		PositionLock[1].lock();
		PositionLock[2].lock();

		x = (*(m_3dpos->mp_x));
		y = (*(m_3dpos->mp_y));
		z = (*(m_3dpos->mp_z));

		PositionLock[0].Unlock();
		PositionLock[1].Unlock();
		PositionLock[2].Unlock();

	};

	SonikAudioPoint::SonikAudio3DPoint& SonikAudioControlData::GetPositionAll(void)
	{
		return (*m_3dpos);
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


