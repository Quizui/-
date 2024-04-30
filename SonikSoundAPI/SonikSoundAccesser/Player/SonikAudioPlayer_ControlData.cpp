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
	,m_3dpos(nullptr)
	,m_volume(1.0f)
	,m_repeat(false)
	,m_AudioState(SonikAudioEnum::PlayStateID::PS_Stop)
	,m_uniqueid((uintptr_t)this)
	{
		try
		{
			m_3dpos = new SonikMathDataBox::Sonik3DPoint;
			m_3ddir = new SonikMathDataBox::Sonik3DPoint(0.0, 0.0, -1.0);
		}catch(std::bad_alloc&)
		{
			throw;
		};

	};

	//デストラクタ
	SonikAudioControlData::~SonikAudioControlData(void)
	{
		//あくまでポインタを使うだけなので何もしない。(音量調整等で値は変更しちゃうかもなので非const)
		if(m_3dpos != nullptr)
		{
			delete m_3dpos;
		};

		if(m_3ddir != nullptr)
		{
			delete m_3ddir;
		};

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
		m_3dpos->SetX(SetValue);
	};

	void SonikAudioControlData::SetPositionY(double SetValue)
	{
		m_3dpos->SetY(SetValue);
	};

	void SonikAudioControlData::SetPositionZ(double SetValue)
	{
		m_3dpos->SetZ(SetValue);
	};

	void SonikAudioControlData::SetPositionAll(double x, double y, double z)
	{
		m_3dpos->Set3Point(x, y, z);
	};

	void SonikAudioControlData::SetPositionXY(double x, double y)
	{
		m_3dpos->SetXY(x, y);
	};
	void SonikAudioControlData::SetPositionXZ(double x, double z)
	{
		m_3dpos->SetXZ(x, z);
	};
	void SonikAudioControlData::SetPositionYZ(double y, double z)
	{
		m_3dpos->SetYZ(y, z);
	};


	//ポジションのポインタ先をセット。
	//別のポジションへのポインタとつなぎ、位置を一緒に動かしたいときに使います。
	//内部の個別ポジションに戻したい場合はnullptrを指定します。
	void SonikAudioControlData::SetPositionConnectX(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointX(_3dpos_);
	};

	void SonikAudioControlData::SetPositionConnectY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointY(_3dpos_);

	};

	void SonikAudioControlData::SetPositionConnectZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointZ(_3dpos_);
	};

	void SonikAudioControlData::SetPositionConnectAll(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointAll(_3dpos_);
	};

	void SonikAudioControlData::SetPositionConnectXY(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointXY(_3dpos_);
	};
	void SonikAudioControlData::SetPositionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointXZ(_3dpos_);
	};
	void SonikAudioControlData::SetPositionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3dpos_)
	{
		m_3dpos->LinkPointYZ(_3dpos_);
	};

	//方向のセット
	void SonikAudioControlData::SetDirectionX(double SetValue)
	{
		m_3ddir->SetX(SetValue);
	};

	void SonikAudioControlData::SetDirectionY(double SetValue)
	{
		m_3ddir->SetY(SetValue);
	};

	void SonikAudioControlData::SetDirectionZ(double SetValue)
	{
		m_3ddir->SetZ(SetValue);
	};

	void SonikAudioControlData::SetDirectionAll(double x, double y, double z)
	{
		m_3ddir->Set3Point(x, y, z);
	};

	void SonikAudioControlData::SetDirectionXY(double x, double y)
	{
		m_3ddir->SetXY(x, y);
	};
	void SonikAudioControlData::SetDirectionXZ(double x, double z)
	{
		m_3ddir->SetXZ(x, z);
	};
	void SonikAudioControlData::SetDirectionYZ(double y, double z)
	{
		m_3ddir->SetYZ(y, z);
	};

	//別の方向へのポインタとつなぎ、位置を一緒に動かしたいときに使います。
	//内部の個別ポジションに戻したい場合はnullptrを指定します。
	void SonikAudioControlData::SetDirectionConnectX(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointX(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointY(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointZ(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectAll(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointAll(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectXY(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointXY(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointXZ(_3ddir_);
	};
	void SonikAudioControlData::SetDirectionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3ddir_)
	{
		m_3ddir->LinkPointYZ(_3ddir_);
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
		m_3dpos->GetX();
	};

	double SonikAudioControlData::GetPositionY(void)
	{
		m_3dpos->GetY();
	};

	double SonikAudioControlData::GetPositionZ(void)
	{
		m_3dpos->GetZ();
	};

	void SonikAudioControlData::GetPositionAll(double& x, double& y, double& z)
	{
		m_3dpos->Get3Point(x, y, z);
	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioControlData::GetPositionAll(void)
	{
		return (*m_3dpos);
	};
	void SonikAudioControlData::GetPositionXY(double& x, double& y)
	{
		m_3dpos->GetXY(x, y);
	};
	void SonikAudioControlData::GetPositionXZ(double& x, double& z)
	{
		m_3dpos->GetXZ(x, z);
	};
	void SonikAudioControlData::GetPositionYZ(double& y, double& z)
	{
		m_3dpos->GetYZ(y, z);
	};

	//方向(Directionのゲット
	double SonikAudioControlData::GetDirectionX(void)
	{
		m_3ddir->GetX();
	};
	double SonikAudioControlData::GetDirectionY(void)
	{
		m_3ddir->GetY();
	};
	double SonikAudioControlData::GetDirectionZ(void)
	{
		m_3ddir->GetZ();
	};
	void SonikAudioControlData::GetDirectionAll(double& x, double& y, double& z)
	{
		m_3ddir->Get3Point(x, y, z);
	};
	SonikMathDataBox::Sonik3DPoint& SonikAudioControlData::GetDirectionAll(void)
	{
		return (*m_3ddir);
	};
	void SonikAudioControlData::GetDirectionXY(double& x, double& y)
	{
		m_3ddir->GetXY(x, y);
	};
	void SonikAudioControlData::GetDirectionXZ(double& x, double& z)
	{
		m_3ddir->GetXZ(x, z);
	};
	void SonikAudioControlData::GetDirectionYZ(double& y, double& z)
	{
		m_3ddir->GetXY(y, z);

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


