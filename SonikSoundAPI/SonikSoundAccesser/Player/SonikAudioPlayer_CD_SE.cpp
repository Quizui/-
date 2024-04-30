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

	SonikAudioControlDataSetForSE::SonikAudioControlDataSetForSE(SonikLib::SharedSmtPtr<float> _se_mastervolume_, SonikMathDataBox::Sonik3DPoint& _listner_pos_, SonikMathDataBox::Sonik3DPoint& _listner_dir_, SonikAudio::SAudioFormat SetAudioPointer)
	:SonikAudioControlData(SetAudioPointer)
	,flgbit_effect(0)
	,RA_effect{}
	,m_mastervolume_se(_se_mastervolume_)
	{
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
	float SonikAudioControlDataSetForSE::GetMixingVolume(void)
	{
		double _ret = m_volume * (*m_mastervolume_se);

		if( flgbit_effect == 0)
		{
			return _ret;
		};

		SonikLib::SharedSmtPtr<SonikLib::SonikFOSTemplateInterface<double>> l_effect = effect;
		while( !l_effect.IsNullptr() )
		{
			_ret *= l_effect->Run();
			l_effect = l_effect->GetNext_strong();
		};

		return _ret;

	};

	//エフェクトのフラグ設定とエフェクトの設定
	void SonikAudioControlDataSetForSE::SetEffect(SonikAudioEnum::PlayEffectID _effected_)
	{
		if( (flgbit_effect & _effected_) != 0 )
		{
			//すでにビットが立っている、フラグON済み。
			return;
		};

		//フラグがONになっていなければオブジェクト作成して流れへ追加。
		//関数オブジェクトの作成。
		SonikLib::SharedSmtPtr<SonikLib::SonikFOSTemplateInterface<double>> l_effectobj;

		switch(_effected_)
		{
		case SonikAudioEnum::PlayEffectID::EF_DISTANCE:
			{
				using DISTANCEFUNCOBJ = SonikLib::Members_2_FuncRG<double, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&>;
				using DISTANCEFUNC = double (*)(double, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&);

				l_effectobj = DISTANCEFUNCOBJ::New(static_cast<DISTANCEFUNC>(&SonikMath::Distance), (*m_listner_3dpos), (*m_3dpos));
			}
			break;

		case SonikAudioEnum::PlayEffectID::EF_PANNING:
			{
				using PANINGFUNCOBJ = SonikLib::Members_6_FuncRG<double, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, double, double>;
				using PANNINGFUNC = double (*)(double, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, SonikMathDataBox::Sonik3DPoint&, double, double);

				l_effectobj = PANINGFUNCOBJ::New(static_cast<PANNINGFUNC>(&SonikMath::Panning), (*m_listner_3dpos), (*m_3dpos), (*m_listner_3dpos), (*m_listner_3ddir), 1.0, 0.3);

			}
			break;

		default:
			//処理無し。
			return;
			break;
		};

		if(l_effectobj.IsNullptr())
		{
			//作成二失敗しているのでさらば～
			return;
		};


		//失敗していなければ挿入箇所を探す。
		//LSBでもMSBでもどっちでもええ
		uint32_t l_effected_flpoint = SonikMathBit::GetMSBFor32bit(static_cast<uint32_t>(_effected_));

		//フラグが一つも立ってなければ最初へ挿入して、RandamAccess用に設定して終了
		if( flgbit_effect == 0 )
		{
			effect = l_effectobj;
			RA_effect[l_effected_flpoint];

			flgbit_effect |= static_cast<uint32_t>(_effected_);
			return;
		};

		//一つでも立っているようなら、途中挿入処理
		uint32_t tmpflg = flgbit_effect;

		//自分より上位のビットをマスク
		tmpflg &= (~((_effected_ - 1) | _effected_));

		//自分より下位のビットフラグが立っていないなら、自分が一番最初
		if( tmpflg == 0 )
		{
			l_effectobj->SetNext_Strong(effect);
			effect =l_effectobj;
			return;
		};

		//自分以外の上位ビットをマスクして0以外なら下位ビットが立っている。
		//下位の最上位ビットの位置を取得し、その下(後)へ挿入。
		SonikLib::SharedSmtPtr<SonikLib::SonikFOSTemplateInterface<double>> tmp_RA_effect;
		tmp_RA_effect = RA_effect[tmpflg];

		l_effectobj->SetNext_Strong(tmp_RA_effect->GetNext_strong());
		tmp_RA_effect->SetNext_Strong(l_effectobj);

		//エフェクト二セット
		RA_effect[l_effected_flpoint];
		flgbit_effect |= static_cast<uint32_t>(_effected_);
		return;

	};

	void SonikAudioControlDataSetForSE::SetPositionALL(SonikMathDataBox::Sonik3DPoint& _3dpos_)
	{
		(*m_3dpos) = _3dpos_;
	};

	void SonikAudioControlDataSetForSE::SetPositionAll(double x, double y, double z)
	{
		(*(m_3dpos->x)) = x;
		(*(m_3dpos->y)) = y;
		(*(m_3dpos->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetPositionXY(double x, double y)
	{
		(*(m_3dpos->x)) = x;
		(*(m_3dpos->y)) = y;
	};

	void SonikAudioControlDataSetForSE::SetPositionXZ(double x, double z)
	{
		(*(m_3dpos->x)) = x;
		(*(m_3dpos->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetPositionYZ(double y, double z)
	{
		(*(m_3dpos->y)) = y;
		(*(m_3dpos->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetPositionX(double x)
	{
		(*(m_3dpos->x)) = x;
	};

	void SonikAudioControlDataSetForSE::SetPositionY(double y)
	{
		(*(m_3dpos->y)) = y;
	};

	void SonikAudioControlDataSetForSE::SetPositionZ(double z)
	{
		(*(m_3dpos->z)) = z;
	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioControlDataSetForSE::GetPositionAll(void)
	{
		return (*m_3dpos);
	};

	void SonikAudioControlDataSetForSE::GetPositionAll(double& x, double& y, double& z)
	{
		x = (*(m_3dpos->x));
		y = (*(m_3dpos->y));
		z = (*(m_3dpos->z));
	};

	void SonikAudioControlDataSetForSE::GetPositionXY(double& x, double& y)
	{
		x = (*(m_3dpos->x));
		y = (*(m_3dpos->y));
	};

	void SonikAudioControlDataSetForSE::GetPositionXZ(double& x, double& z)
	{
		x = (*(m_3dpos->x));
		z = (*(m_3dpos->z));
	};

	void SonikAudioControlDataSetForSE::GetPositionYZ(double& y, double& z)
	{
		y = (*(m_3dpos->y));
		z = (*(m_3dpos->z));
	};

	double SonikAudioControlDataSetForSE::GetPositionX(void)
	{
		return (*(m_3dpos->x));
	};

	double SonikAudioControlDataSetForSE::GetPositionY(void)
	{
		return (*(m_3dpos->y));
	};

	double SonikAudioControlDataSetForSE::GetPositionZ(void)
	{
		return (*(m_3dpos->z));
	};

	void SonikAudioControlDataSetForSE::SetDirectionALL(SonikMathDataBox::Sonik3DPoint& _3ddir_)
	{
		(*m_3ddir) = _3ddir_;
	};

	void SonikAudioControlDataSetForSE::SetDirectionAll(double x, double y, double z)
	{
		(*(m_3ddir->x)) = x;
		(*(m_3ddir->y)) = y;
		(*(m_3ddir->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetDirectionXY(double x, double y)
	{
		(*(m_3ddir->x)) = x;
		(*(m_3ddir->y)) = y;
	};

	void SonikAudioControlDataSetForSE::SetDirectionXZ(double x, double z)
	{
		(*(m_3ddir->x)) = x;
		(*(m_3ddir->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetDirectionYZ(double y, double z)
	{
		(*(m_3ddir->y)) = y;
		(*(m_3ddir->z)) = z;
	};

	void SonikAudioControlDataSetForSE::SetDirectionX(double x)
	{
		(*(m_3ddir->x)) = x;
	};

	void SonikAudioControlDataSetForSE::SetDirectionY(double y)
	{
		(*(m_3ddir->y)) = y;
	};

	void SonikAudioControlDataSetForSE::SetDirectionZ(double z)
	{
		(*(m_3ddir->z)) = z;
	};

	SonikMathDataBox::Sonik3DPoint& SonikAudioControlDataSetForSE::GetDirectionAll(void)
	{
		return (*m_3ddir);
	};

	void SonikAudioControlDataSetForSE::GetDirectionAll(double& x, double& y, double& z)
	{
		(*(m_3ddir->x)) = x;
		(*(m_3ddir->y)) = y;
		(*(m_3ddir->z)) = z;
	};

	void SonikAudioControlDataSetForSE::GetDirectionXY(double& x, double& y)
	{
		x = (*(m_3ddir->x));
		y = (*(m_3ddir->y));
	};

	void SonikAudioControlDataSetForSE::GetDirectionXZ(double& x, double& z)
	{
		x = (*(m_3ddir->x));
		z = (*(m_3ddir->z));
	};

	void SonikAudioControlDataSetForSE::GetDirectionYZ(double& y, double& z)
	{
		y = (*(m_3ddir->y));
		z = (*(m_3ddir->z));
	};

	double SonikAudioControlDataSetForSE::GetPositionX(void)
	{
		return (*(m_3ddir->x));
	};

	double SonikAudioControlDataSetForSE::GetPositionY(void)
	{
		return (*(m_3ddir->y));
	};

	double SonikAudioControlDataSetForSE::GetPositionZ(void)
	{
		return (*(m_3ddir->z));
	};


};


