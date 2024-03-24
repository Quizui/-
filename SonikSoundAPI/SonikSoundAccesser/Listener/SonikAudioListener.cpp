/*
 * SonikAudioListener.cpp
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#include "SonikAudioListener.h"
#include "../../../MathBit/SonikMathDistance.h"

#include <new>

namespace SonikAudio
{

	//コンストラクタ
	SonikAudioListener::SonikAudioListener(void)
	:max_listen_distance(1000.0)
	,listen_volume(1.0)
	,m_3dpos(nullptr)
	,m_3ddir(nullptr)
	{
		try
		{

			m_3dpos = new SonikMathDataBox::Sonik3DPoint;
			m_3ddir = new SonikMathDataBox::Sonik3DPoint(0.0, 0.0, 1.0);
		}catch(std::bad_alloc&)
		{
			if(m_3dpos != nullptr)
			{
				delete m_3dpos;
			};

			throw;
		};

	};

	//デストラクタ
	SonikAudioListener::~SonikAudioListener(void)
	{
		if(m_3dpos != nullptr)
		{
			delete m_3dpos;
		};

		if(m_3ddir != nullptr)
		{
			delete m_3ddir;
		};
	};

	//最大聞こえる距離のセットゲット
	void SonikAudioListener::SetMaxListenDistance(double _setmaxdistance_)
	{
		max_listen_distance = _setmaxdistance_;
	};

	double SonikAudioListener::GetMaxListernDistance(void)
	{
		return max_listen_distance;
	};

	//聞こえる音量(マスターボリューム)のセットゲット
	void SonikAudioListener::SetListenVolume(double setvolume)
	{
		if(setvolume > 1.0)
		{
			listen_volume = 1.0;
			return;
		};

		listen_volume = setvolume;
		return;
	};
	double SonikAudioListener::GetListenVolume(void)
	{
		return listen_volume;
	};


	//ポジションのセット
	void SonikAudioListener::SetPosition(double x, double y, double z)
	{
		m_3dpos->Set3Point(x, y, z);
	};

	void SonikAudioListener::SetPositionX(double x)
	{
		m_3dpos->SetX(x);
	};

	void SonikAudioListener::SetPositionY(double y)
	{
		m_3dpos->SetY(y);
	};

	void SonikAudioListener::SetPositionZ(double z)
	{
		m_3dpos->SetZ(z);

	};

	//ポジションのゲット
	void SonikAudioListener::GetPosition(double& x, double& y, double& z)
	{
		m_3dpos->Get3Point(x ,y ,z);

	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioListener::GetPosition(void)
	{
		return (*m_3dpos);
	};

	double SonikAudioListener::GetPositionX(void)
	{
		return m_3dpos->GetX();
	};

	double SonikAudioListener::GetPositionY(void)
	{
		return m_3dpos->GetY();
	};

	double SonikAudioListener::GetPositionZ(void)
	{
		return m_3dpos->GetZ();
	};


	//方向のセット
	void SonikAudioListener::SetDirection(double x, double y, double z)
	{
		m_3ddir->Set3Point(x, y, z);
	};
	void SonikAudioListener::SetDirectionX(double x)
	{
		m_3ddir->SetX(x);
	};
	void SonikAudioListener::SetDirectionY(double y)
	{
		m_3ddir->SetY(y);
	};
	void SonikAudioListener::SetDirectionZ(double z)
	{
		m_3ddir->SetZ(z);
	};

	//方向のゲット
	void SonikAudioListener::GetDirection(double& x, double& y, double& z)
	{
		m_3ddir->Get3Point(x, y, z);
	};
	SonikMathDataBox::Sonik3DPoint& SonikAudioListener::GetDirection(void)
	{
		return (*m_3ddir);
	};
	double SonikAudioListener::GetDirectionX(void)
	{
		return m_3ddir->GetX();
	};
	double SonikAudioListener::GetDirectionY(void)
	{
		return m_3ddir->GetY();
	};
	double SonikAudioListener::GetDirectionZ(void)
	{
		return m_3ddir->GetZ();
	};


};

