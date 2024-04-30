/*
 * SonikAudioPlayer_CD_SE.h
 *
 *  Created on: 2024/03/28
 *      Author: owner
 */

#ifndef __PLAYER_SONIKAUDIOPLAYER_CD_SE_H__
#define __PLAYER_SONIKAUDIOPLAYER_CD_SE_H__

#include "SonikAudioPlayer_ControlData.h"
#include "../PlayStateEnums.h"
#include "../../../SmartPointer/SonikSmartPointer.hpp"

namespace SonikMathDataBox
{
	class Sonik3DPoint;
};

namespace SonikFunctionObjectDefines
{
	class FunctionObjectSystemInterface;
	template<class Rtype>
	class FunctionObjectSystemTemplateInterface;
};

namespace SonikLib
{
	using SonikFOSInterface = SonikFunctionObjectDefines::FunctionObjectSystemInterface;
	template <class Rtype>
	using SonikFOSTemplateInterface = SonikFunctionObjectDefines::FunctionObjectSystemTemplateInterface<Rtype>;

};


namespace SonikAudioData
{
	//SEという名前ですが、距離と方向を持つ音源全般を扱います。
	class SonikAudioControlDataSetForSE :  public SonikAudioData::SonikAudioControlData
	{
	private:
		SonikLib::SharedSmtPtr<float> m_mastervolume_se;
		SonikMathDataBox::Sonik3DPoint* m_3dpos; //3D座標
		SonikMathDataBox::Sonik3DPoint* m_3ddir; //3D方向

		SonikMathDataBox::Sonik3DPoint* m_listner_3dpos; //3D座標
		SonikMathDataBox::Sonik3DPoint* m_listner_3ddir; //3D方向

		//1bit_distance
		//2bit_panning
		uint32_t flgbit_effect;
		//effect_pointerlist
		SonikLib::SharedSmtPtr<SonikLib::SonikFOSTemplateInterface<double>> effect;
		//RandamAccessArray
		SonikLib::SharedSmtPtr<SonikLib::SonikFOSTemplateInterface<double>>* RA_effect[sizeof(flgbit_effect) * 8];

	private:
		//コピー禁止
		SonikAudioControlDataSetForSE(SonikAudioControlDataSetForSE& _this_) = delete;
		SonikAudioControlDataSetForSE& operator =(SonikAudioControlDataSetForSE& _this_) = delete;

	public:
		SonikAudioControlDataSetForSE(SonikLib::SharedSmtPtr<float> _se_mastervolume_, SonikMathDataBox::Sonik3DPoint& _listner_pos_, SonikMathDataBox::Sonik3DPoint& _listner_dir_, SonikAudio::SAudioFormat SetAudioPointer);
		~SonikAudioControlDataSetForSE(void);

		//データが最終的にミキシングしてほしいボリューム値を取得
		float GetMixingVolume(void);

		//エフェクトのフラグ設定とエフェクトの設定
		void EnableEffect(SonikAudioEnum::PlayEffectID _enable_effect_);
		void DisableEffect(SonikAudioEnum::PlayEffectID _disable_effect_);

		void SetPositionALL(SonikMathDataBox::Sonik3DPoint& _3dpos_);
		void SetPositionAll(double x, double y, double z);
		void SetPositionXY(double x, double y);
		void SetPositionXZ(double x, double z);
		void SetPositionYZ(double y, double z);
		void SetPositionX(double x);
		void SetPositionY(double y);
		void SetPositionZ(double z);

		SonikMathDataBox::Sonik3DPoint& GetPositionAll(void);
		void GetPositionAll(double& x, double& y, double& z);
		void GetPositionXY(double& x, double& y);
		void GetPositionXZ(double& x, double& z);
		void GetPositionYZ(double& y, double& z);
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);

		void SetDirectionALL(SonikMathDataBox::Sonik3DPoint& _3ddir_);
		void SetDirectionAll(double x, double y, double z);
		void SetDirectionXY(double x, double y);
		void SetDirectionXZ(double x, double z);
		void SetDirectionYZ(double y, double z);
		void SetDirectionX(double x);
		void SetDirectionY(double y);
		void SetDirectionZ(double z);

		SonikMathDataBox::Sonik3DPoint& GetDirectionAll(void);
		void GetDirectionAll(double& x, double& y, double& z);
		void GetDirectionXY(double& x, double& y);
		void GetDirectionXZ(double& x, double& z);
		void GetDirectionYZ(double& y, double& z);
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);



	};

#endif //__PLAYER_SONIKAUDIOPLAYER_CD_SE_H__
