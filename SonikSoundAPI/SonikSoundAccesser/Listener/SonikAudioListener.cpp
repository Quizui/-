/*
 * SonikAudioListener.cpp
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#include "SonikAudioListener.h"
#include "../../MathBit/SonikMathDistance.h"
#include "../../SmartPointer/SonikSmartPointer.hpp"

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

			if(!m_Vol_Master.ResetPointer(new double))
			{
				throw std::bad_alloc();
			};

			if(!m_Vol_SE.ResetPointer(new double))
			{
				throw std::bad_alloc();
			};

			if(!m_Vol_BGM.ResetPointer(new double))
			{
				throw std::bad_alloc();
			};


			(*m_Vol_Master) = 1.0;
			(*m_Vol_SE) = 1.0;

		}catch(std::bad_alloc&)
		{
			if(m_3dpos != nullptr)
			{
				delete m_3dpos;
			};

			if(m_3ddir != nullptr)
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
        if( max_listen_distance == 0 )
        {
            max_listen_distance_inv = 0.0;
            return;
        };
        
        max_listen_distance_inv = 1.0 / max_listen_distance;
	};

	double SonikAudioListener::GetMaxListnerDistance(void)
	{
		return max_listen_distance;
	};
    double SonikAudioListener::GetMaxListnerDistance_Inv(void)
    {
        return max_listen_distance_inv;
    };

	//全体のマスターボリュームのセットゲット
	void SonikAudioListener::SetMasterVolume(double _setvolume_)
	{
		if(_setvolume_ > 1.0)
		{
			(*m_Vol_Master) = 1.0;
			return;
		};

		(*m_Vol_Master) = _setvolume_;

		return;
	};
	double SonikAudioListener::GetMasterVolume(void)
	{
		return (*m_Vol_Master);
	};
	const SonikLib::SharedSmtPtr<double> SonikAudioListener::GetMasterVolumeRef(void)
	{
		return m_Vol_Master;
	};

	//カテゴリボリューム SEのセットゲット
	void SonikAudioListener::SetCategoryVolumeSE(double _setvolume_)
	{
		if(_setvolume_ > 1.0)
		{
			(*m_Vol_SE) = 1.0;
			return;
		};

		(*m_Vol_SE) = _setvolume_;

		return;
	};
	double SonikAudioListener::GetCategoryVolumeSE(void)
	{
		return (*m_Vol_SE);
	};
	const SonikLib::SharedSmtPtr<double> SonikAudioListener::GetCategoryVolumeSERef(void)
	{
		return m_Vol_SE;
	};

	//カテゴリボリューム SEのセットゲット
	void SonikAudioListener::SetCategoryVolumeBGM(double _setvolume_)
	{
		if(_setvolume_ > 1.0)
		{
			(*m_Vol_BGM) = 1.0;
			return;
		};

		(*m_Vol_BGM) = _setvolume_;

		return;
	};
	double SonikAudioListener::GetCategoryVolumeBGM(void)
	{
		return (*m_Vol_BGM);
	};
	const SonikLib::SharedSmtPtr<double> SonikAudioListener::GetCategoryBGMVolumeRef(void)
	{
		return m_Vol_BGM;
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

