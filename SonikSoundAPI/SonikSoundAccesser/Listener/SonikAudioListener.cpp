/*
 * SonikAudioListener.cpp
 *
 *  Created on: 2024/01/04
 *      Author: SONIC
 */

#include "SonikAudioListener.h"
#include "../AudioPosition/SonikAudio3DPoint.h"

#include <new>

namespace SonikAudio
{

	//コンストラクタ
	SonikAudioListener::SonikAudioListener(void)
	:max_listen_distance(1000.0)
	,m_3dpos(nullptr)
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
	SonikAudioListener::~SonikAudioListener(void)
	{
		if(m_3dpos != nullptr)
		{
			delete m_3dpos;
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


	//ポジションのセット
	void SonikAudioListener::SetPosition(double x, double y, double z)
	{
		m_3dpos->ref_m_x = x;
		m_3dpos->ref_m_y = y;
		m_3dpos->ref_m_z = z;
	};

	void SonikAudioListener::SetPositionX(double x)
	{
		m_3dpos->ref_m_x = x;
	};

	void SonikAudioListener::SetPositionY(double y)
	{
		m_3dpos->ref_m_y = y;
	};

	void SonikAudioListener::SetPositionZ(double z)
	{
		m_3dpos->ref_m_z = z;
	};

	//ポジションのゲット
	void SonikAudioListener::GetPosition(double& x, double& y, double& z)
	{
		x = (*(m_3dpos->mp_x));
		y = (*(m_3dpos->mp_y));
		z = (*(m_3dpos->mp_z));
	};

	void SonikAudioListener::GetPosition(double*& x, double*& y, double*& z)
	{
		x = m_3dpos->mp_x;
		y = m_3dpos->mp_y;
		z = m_3dpos->mp_z;
	};

	SonikAudioPoint::SonikAudio3DPoint& SonikAudioListener::GetPosition(void)
	{
		return (*m_3dpos);
	};

	double SonikAudioListener::GetPositionX(void)
	{
		return (*(m_3dpos->mp_x));
	};

	void SonikAudioListener::GetPositionX(const double* _out_)
	{
		_out_ = m_3dpos->mp_x;
	};

	double SonikAudioListener::GetPositionY(void)
	{
		return (*(m_3dpos->mp_y));
	};

	void SonikAudioListener::GetPositionY(const double* _out_)
	{
		_out_ = m_3dpos->mp_y;
	};

	double SonikAudioListener::GetPositionZ(void)
	{
		return (*(m_3dpos->mp_z));
	};

	void SonikAudioListener::GetPositionZ(const double* _out_)
	{
		_out_ = m_3dpos->mp_z;
	};

};

