#include "./SonikAudioEffecter.h"
#include "../Player/SonikAudioPlayer_ControlData.h"
#include "../Player/SonikAudioPlayer_CD_BGM.h"
#include "../Player/SonikAudioPlayer_CD_SE.h"
#include "../Listener/SonikAudioListener.h"
#include "../../MathBit/SonikMathDistance.h"
#include "../../MathBit/MathBit.h"


namespace SonikAudio
{
    SonikAudioEffecter::SonikAudioEffecter(SonikAudio::SAudioListener _listener_)
    :mp_Listener(_listener_)
    ,m_effectlist{&SonikAudioEffecter::SAE_PRIVATE_DISTANCE,
                  &SonikAudioEffecter::SAE_PRIVATE_PANNING,
                 }
    {

    };
    //デストラクタ
    SonikAudioEffecter::~SonikAudioEffecter(void)
    {

    };

     //エフェクトセット
    void SonikAudioEffecter::SetEffect(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> _audio_cd_, double& _L_out_, double& _R_out_)
    {
        switch(_audio_cd_->Get_UniqueID())
        {
        case SonikAudioEnum::PlayerCDType::PCDTYPE_BGM:
            EffecterProc_TypeBGM(_audio_cd_, _L_out_, _R_out_);

            break;
        case SonikAudioEnum::PlayerCDType::PCDTYPE_SE:
            EffecterProc_TypeSE(_audio_cd_, _L_out_, _R_out_);
            break;

        default:

            break;
        };

        return;
    };

    void SonikAudioEffecter::EffecterProc_TypeBGM(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>& PlayerControl, double& _L_out_, double& _R_out_)
    {
        //BGM_SEへ返還
        SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForBGM> l_bgm;

        SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlData, SonikAudioData::SonikAudioControlDataSetForBGM>(PlayerControl, l_bgm);

        //現状BGMのマスターボリューム適用のみ
        _L_out_ = mp_Listener->GetMasterVolume() * l_bgm->GetVolume() * l_bgm->GetCategoryVolume();
        _R_out_ = _L_out_;
    };
    
    void SonikAudioEffecter::EffecterProc_TypeSE(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>& PlayerControl, double& _L_out_, double& _R_out_)
    {
        //CD_SEへ変換
        SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlDataSetForSE> l_se;

        SonikLib::SharedCast_Reinterpret<SonikAudioData::SonikAudioControlData, SonikAudioData::SonikAudioControlDataSetForSE>(PlayerControl, l_se);

        uint32_t flgbit = l_se->GetEffectFlgBit();
        SonikMathDataBox::Sonik3DPoint& l_lis_3dpos = mp_Listener->GetPosition();
        SonikMathDataBox::Sonik3DPoint& l_lis_3ddir = mp_Listener->GetDirection();
        SonikMathDataBox::Sonik3DPoint& l_pl_3dpos = l_se->GetPositionAll();
        SonikMathDataBox::Sonik3DPoint& l_pl_3ddir = l_se->GetDirectionAll();
        double l_L = 0.0;
        double l_R = 0.0;

        _L_out_ = mp_Listener->GetMasterVolume() * l_se->GetVolume() * l_se->GetCategoryVolume();
        _R_out_ = _L_out_;

        while(flgbit != 0)
        {
            (this->*m_effectlist[SonikMathBit::GetLSBFor32bit(flgbit)])(l_lis_3dpos, l_lis_3ddir, l_pl_3dpos, l_pl_3ddir, l_L, l_R); 

            flgbit &= ~(static_cast<uint32_t>(0b00000000000000000000000000000001) << SonikMathBit::GetLSBFor32bit(flgbit));

            _L_out_ *= l_L;
            _R_out_ *= l_R;
        };

    };

	void SonikAudioEffecter::SAE_PRIVATE_DISTANCE(SonikMathDataBox::Sonik3DPoint& lis_pos, SonikMathDataBox::Sonik3DPoint& lis_dir, SonikMathDataBox::Sonik3DPoint& pl_pos, SonikMathDataBox::Sonik3DPoint& pl_dir, double& _L_out_, double& _R_out_)
    {
        _L_out_ = 1.0 - (SonikMath::Distance(lis_pos, pl_pos) * mp_Listener->GetMaxListnerDistance_Inv());
        if(_L_out_ <= 0)
        {
            _L_out_ = 0.0;
        };

        _R_out_ = _L_out_;
    };

	void SonikAudioEffecter::SAE_PRIVATE_PANNING(SonikMathDataBox::Sonik3DPoint& lis_pos, SonikMathDataBox::Sonik3DPoint& lis_dir, SonikMathDataBox::Sonik3DPoint& pl_pos, SonikMathDataBox::Sonik3DPoint& pl_dir, double& _L_out_, double& _R_out_)
    {
        double lo_pan = SonikMath::Panning(lis_pos, pl_pos, lis_dir, pl_dir);

        _L_out_ = 1.0 - lo_pan;
        _R_out_ = lo_pan;
    };


};