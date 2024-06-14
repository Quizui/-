/*
 * SonikAudioPlayer_CD_SE.cpp
 *
 *  Created on: 2024/03/31
 *      Author: SONIC
 */

#include "SonikAudioPlayer_CD_SE.h"
#include "../../../MathBit/SonikMathDistance.h"
#include "../../../MathBit/MathBit.h"
#include "../../../FunctionObject/FunctionObjectSystemImpl.hpp"

namespace SonikAudioData
{

	SonikAudioControlDataSetForSE::SonikAudioControlDataSetForSE(SonikLib::SharedSmtPtr<double> _se_mastervolume_, SonikMathDataBox::Sonik3DPoint& _listner_pos_, SonikMathDataBox::Sonik3DPoint& _listner_dir_, SonikAudio::SAudioFormat SetAudioPointer)
	:SonikAudioControlData(SetAudioPointer)
	,m_CategorySEVol(_se_mastervolume_)
	,flgbit_effect(0)
	{
		//m_effectlist
		m_effectlist[0] = &SonikAudioControlDataSetForSE::SAC_PRIVATEFUNC_EFFECT_DISTANCE;
		m_effectlist[1] = &SonikAudioControlDataSetForSE::SAC_PRIVATEFUNC_EFFECT_PANNING;


		try
		{
			m_3dpos = new SonikMathDataBox::Sonik3DPoint;
			m_3ddir = new SonikMathDataBox::Sonik3DPoint;

			m_listner_3dpos = new SonikMathDataBox::Sonik3DPoint;
			m_listner_3ddir = new SonikMathDataBox::Sonik3DPoint;

		}catch(std::bad_alloc&)
		{
			if(m_3dpos != nullptr)
			{
				delete m_3dpos;
			};

			if(m_3ddir != nullptr)
			{
				delete m_3ddir;
			};

			if(m_listner_3dpos != nullptr)
			{
				delete m_listner_3dpos;
			};

			if(m_listner_3ddir != nullptr)
			{
				delete m_listner_3ddir;
			};


			//initialize failed;
			throw;
		};

		m_listner_3dpos->LinkPointAll(_listner_pos_);
		m_listner_3ddir->LinkPointAll(_listner_dir_);

	};

	SonikAudioControlDataSetForSE::~SonikAudioControlDataSetForSE(void)
	{
		if(m_3dpos != nullptr)
		{
			delete m_3dpos;
		};

		if(m_3ddir != nullptr)
		{
			delete m_3ddir;
		};

		if(m_listner_3dpos != nullptr)
		{
			delete m_listner_3dpos;
		};

		if(m_listner_3ddir != nullptr)
		{
			delete m_listner_3ddir;
		};

	};

	//データが最終的にミキシングしてほしいボリューム値を取得
	void SonikAudioControlDataSetForSE::GetMixingVolume(double& _GetLMixingValue_, double& _GetRMixingValue_)
	{
		double l_outvol = m_volume * (*m_CategorySEVol);

		if( flgbit_effect == 0)
		{
			_GetLMixingValue_ = l_outvol;
			_GetRMixingValue_ = l_outvol;

			return;
		};

		//switch-loop
		//立っているビットをカウント
		uint8_t l_bitcnt = SonikMathBit::OnBitCountFor32bit(flgbit_effect);
		uint32_t l_ControlBit = flgbit_effect;
		uint8_t l_lsb = 0;

		double l_Lvol = 1.0;
		double l_Rvol = 1.0;
		double l_retL = 1.0;
		double l_retR = 1.0;

		for(uint32_t i=0; i < l_bitcnt; ++i)
		{
			//最小ビット位置を取得
			l_lsb = SonikMathBit::GetLSBFor32bit(l_ControlBit) -1;
			//該当のビット位置を下げる
			l_ControlBit &= (~(1 << l_lsb));

			(this->*m_effectlist[l_lsb])(l_Lvol, l_Rvol);

			l_retL *= l_Lvol;
			l_retR *= l_Rvol;

		};

		_GetLMixingValue_ = l_outvol * l_retL;
		_GetRMixingValue_ = l_outvol * l_retR;
	};

	//エフェクトのフラグ設定とエフェクトの設定
	void SonikAudioControlDataSetForSE::EnableEffect(SonikAudioEnum::PlayEffectID _effected_)
	{
		if( (flgbit_effect & _effected_) != 0 )
		{
			//すでにビットが立っている、フラグON済み。
			return;
		};

		flgbit_effect |= _effected_;
		return;
	};

	//エフェクトの無効化
	void SonikAudioControlDataSetForSE::DisableEffect(SonikAudioEnum::PlayEffectID _disable_effect_)
	{
		if( (flgbit_effect & _disable_effect_) == 0 )
		{
			//すでにビットが降りている。無効化済。
			return;
		};

		flgbit_effect &= (~_disable_effect_);

	};

	void SonikAudioControlDataSetForSE::SAC_PRIVATEFUNC_EFFECT_DISTANCE(double& _L_out_, double& _R_out_)
	{
		double ret = SonikMath::Distance((*m_listner_3dpos), (*m_3dpos));

		_L_out_ = ret;
		_R_out_ = ret;
	};

	void SonikAudioControlDataSetForSE::SAC_PRIVATEFUNC_EFFECT_PANNING(double& _L_out_, double& _R_out_)
	{
		double ret = SonikMath::Panning((*m_listner_3dpos), (*m_3dpos), (*m_listner_3ddir), (*m_3ddir));

		_L_out_ = (1.0 - ret);
		_R_out_ = ret;
	};


	void SonikAudioControlDataSetForSE::SetPositionALL(SonikMathDataBox::Sonik3DPoint& _3dpos_)
	{
		(*m_3dpos) = _3dpos_;
	};

	void SonikAudioControlDataSetForSE::SetPositionAll(double x, double y, double z)
	{
		m_3dpos->Set3Point(x, y, z);
	};

	void SonikAudioControlDataSetForSE::SetPositionXY(double x, double y)
	{
		m_3dpos->SetXY(x, y);
	};

	void SonikAudioControlDataSetForSE::SetPositionXZ(double x, double z)
	{
		m_3dpos->SetXZ(x, z);
	};

	void SonikAudioControlDataSetForSE::SetPositionYZ(double y, double z)
	{
		m_3dpos->SetYZ(y, z);
	};

	void SonikAudioControlDataSetForSE::SetPositionX(double x)
	{
		m_3dpos->SetX(x);
	};

	void SonikAudioControlDataSetForSE::SetPositionY(double y)
	{
		m_3dpos->SetY(y);
	};

	void SonikAudioControlDataSetForSE::SetPositionZ(double z)
	{
		m_3dpos->SetZ(z);
	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioControlDataSetForSE::GetPositionAll(void)
	{
		return (*m_3dpos);
	};

	void SonikAudioControlDataSetForSE::GetPositionAll(double& x, double& y, double& z)
	{
		m_3dpos->Get3Point(x, y, z);
	};

	void SonikAudioControlDataSetForSE::GetPositionXY(double& x, double& y)
	{
		m_3dpos->GetXY(x, y);
	};

	void SonikAudioControlDataSetForSE::GetPositionXZ(double& x, double& z)
	{
		m_3dpos->GetXZ(x, z);
	};

	void SonikAudioControlDataSetForSE::GetPositionYZ(double& y, double& z)
	{
		m_3dpos->GetYZ(y, z);
	};

	double SonikAudioControlDataSetForSE::GetPositionX(void)
	{
		return m_3dpos->GetX();
	};

	double SonikAudioControlDataSetForSE::GetPositionY(void)
	{
		return m_3dpos->GetY();
	};

	double SonikAudioControlDataSetForSE::GetPositionZ(void)
	{
		return m_3dpos->GetZ();
	};

	void SonikAudioControlDataSetForSE::SetDirectionALL(SonikMathDataBox::Sonik3DPoint& _3ddir_)
	{
		(*m_3ddir) = _3ddir_;
	};

	void SonikAudioControlDataSetForSE::SetDirectionAll(double x, double y, double z)
	{
		m_3ddir->Set3Point(x, y, z);
	};

	void SonikAudioControlDataSetForSE::SetDirectionXY(double x, double y)
	{
		m_3ddir->SetXY(x, y);
	};

	void SonikAudioControlDataSetForSE::SetDirectionXZ(double x, double z)
	{
		m_3ddir->SetXZ(x, z);
	};

	void SonikAudioControlDataSetForSE::SetDirectionYZ(double y, double z)
	{
		m_3ddir->SetXY(y, z);
	};

	void SonikAudioControlDataSetForSE::SetDirectionX(double x)
	{
		m_3ddir->SetX(x);
	};

	void SonikAudioControlDataSetForSE::SetDirectionY(double y)
	{
		m_3ddir->SetY(y);
	};

	void SonikAudioControlDataSetForSE::SetDirectionZ(double z)
	{
		m_3ddir->SetZ(z);
	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioControlDataSetForSE::GetDirectionAll(void)
	{
		return (*m_3ddir);
	};

	void SonikAudioControlDataSetForSE::GetDirectionAll(double& x, double& y, double& z)
	{
		m_3ddir->Get3Point(x, y, z);
	};

	void SonikAudioControlDataSetForSE::GetDirectionXY(double& x, double& y)
	{
		m_3ddir->GetXY(x, y);
	};

	void SonikAudioControlDataSetForSE::GetDirectionXZ(double& x, double& z)
	{
		m_3ddir->GetXY(x, z);
	};

	void SonikAudioControlDataSetForSE::GetDirectionYZ(double& y, double& z)
	{
		m_3ddir->GetXY(y, z);
	};

	double SonikAudioControlDataSetForSE::GetDirectionX(void)
	{
		return m_3ddir->GetX();
	}

	double SonikAudioControlDataSetForSE::GetDirectionY(void)
	{
		return m_3ddir->GetY();
	};

	double SonikAudioControlDataSetForSE::GetDirectionZ(void)
	{
		return m_3ddir->GetZ();
	};


};


