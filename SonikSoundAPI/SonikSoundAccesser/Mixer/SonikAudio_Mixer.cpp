/*
 * SonikAudio_Mixer.cpp
 *
 *  Created on: 2023/10/24
 *      Author: owner
 */

#include <algorithm>

#include "SonikAudio_Mixer.h"
#include "../Player/SonikAudioPlayer_ControlData.h"
#include "../../../DllAccess/SonikDllAccessManager.h"
#include "../PlatformInterface/PlatformAudioInterface.h"
#include "../../../FunctionObject/FunctionObjectSystemImpl.hpp"
#include "../../../SmartPointer/SonikSmartPointer.hpp"
#include "../Listener/SonikAudioListener.h"
#include "../../../MathBit/SonikNormalize.h"
#include "../../../MathBit/SonikMathDistance.h"

namespace SonikAudio
{
	//コンストラクタ
	SonikAudioMixer::SonikAudioMixer(void)
	:mp_AudioList(nullptr)
	,mp_thread(nullptr)
	,mp_platform(nullptr)
	,mp_buffer(nullptr)
	,OneSamplingByteSize(0)
	,m_samplingRate(0)
	,p_mfunc_(nullptr)
	{

	};

	//デストラクタ
	SonikAudioMixer::~SonikAudioMixer(void)
	{
		if(mp_thread != nullptr)
		{
			mp_thread->SetFunctionloopEndFlagOn();
			mp_thread->SetThreadExitFlagOn();

			delete mp_thread;
		};

		//PlatFormInterfaceはDll内でnewされているためDLL側内でDeleteさせるための関数をInterfac側で呼ぶ。
		//そのためノンタッチ。


		//オーディオリストの廃棄。
		if(mp_AudioList != nullptr)
		{
			delete mp_AudioList;
		}


	};

	//イニシャライザ
	bool SonikAudioMixer::Initialize(uint32_t SetAudioListMax, uint32_t FormatBit, uint16_t SetChannel, uint32_t SetSamplingRate, SonikAudioPlatForm::SonikPlatformAudioInterface* Set_PFI_Pointer, SonikLib::SharedSmtPtr<SonikAudio::SonikAudioListener> SetListener)
	{
		if(FormatBit == 16)
		{
			switch(SetChannel)
			{
			case 0x01:
				p_mfunc_ = &SonikAudioMixer::Mixing_16bit_1ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;
				break;

			case 0x02:
				p_mfunc_ = &SonikAudioMixer::Mixing_16bit_2ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;
				break;

			case 0x04:
				p_mfunc_ = &SonikAudioMixer::Mixing_16bit_4ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;
				break;

			case 0x33:
				p_mfunc_ = &SonikAudioMixer::Mixing_16bit_6ch; //5.1ch

				OneSamplingByteSize = (FormatBit * 0.125) * 6 * SetSamplingRate;
				break;

			case 0x47:
				p_mfunc_ = &SonikAudioMixer::Mixing_16bit_8ch; //7.1ch

				OneSamplingByteSize = (FormatBit * 0.125) * 8 * SetSamplingRate;
				break;


			default:

				return false;
			};


		}else if(FormatBit == 32)
		{
			switch(SetChannel)
			{
			case 0x01:
				p_mfunc_ = &SonikAudioMixer::Mixing_32bit_1ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;
				break;

			case 0x02:
				p_mfunc_ = &SonikAudioMixer::Mixing_32bit_2ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;;
				break;

			case 0x04:
				p_mfunc_ = &SonikAudioMixer::Mixing_32bit_4ch;

				OneSamplingByteSize = (FormatBit * 0.125) * SetChannel * SetSamplingRate;;
				break;

			case 0x33:
				p_mfunc_ = &SonikAudioMixer::Mixing_32bit_6ch; //5.1ch

				OneSamplingByteSize = (FormatBit * 0.125) * 6 * SetSamplingRate;;
				break;

			case 0x47:
				p_mfunc_ = &SonikAudioMixer::Mixing_32bit_8ch; //7.1ch

				OneSamplingByteSize = (FormatBit * 0.125) * 8 * SetSamplingRate;;
				break;

			default:

				return false;
			};
		};

		//セカンダリバッファまで作成。
		mp_buffer = new(std::nothrow) int8_t[OneSamplingByteSize];
		if( mp_buffer == nullptr )
		{
			return false;
		};

		std::fill_n(mp_buffer, OneSamplingByteSize, 0);

		mp_AudioList = new(std::nothrow) SonikLib::SonikPriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>(SetAudioListMax);
		if( mp_AudioList == nullptr )
		{
			delete[] mp_buffer;

			mp_buffer = nullptr;
			return false;
		};

		mp_thread = new(std::nothrow) SonikLib::WorkThreadEx();
		if( mp_thread == nullptr )
		{
			delete mp_AudioList;
			delete[] mp_buffer;

			mp_AudioList = nullptr;
			mp_buffer = nullptr;
			return false;
		};

		SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> l_func;
		l_func = SonikLib::Members_0_Func<SonikAudioMixer>::New(this, static_cast<void(SonikAudioMixer::*)(void)>(&SonikAudioMixer::MixerThreadFunc));
		if( l_func.IsNullptr() )
		{
			delete mp_thread;
			delete mp_AudioList;
			delete[] mp_buffer;

			mp_thread = nullptr;
			mp_AudioList = nullptr;
			mp_buffer = nullptr;
			return false;
		};

		l_func->Set_DestroyObjectFlag(false);

		if( !Set_PFI_Pointer->AudioBfferPlayngStart() )
		{
			delete mp_thread;
			delete mp_AudioList;
			delete[] mp_buffer;

			mp_thread = nullptr;
			mp_AudioList = nullptr;
			mp_buffer = nullptr;
			return false;
		};

		mp_thread->SetCallFunction(l_func, true);
		m_samplingRate = SetSamplingRate;
		mp_platform = Set_PFI_Pointer;
		mp_Listener = SetListener;

		return true;
	};

	//オーディオの追加。
	bool SonikAudioMixer::AddAudio(SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData> SetAudio)
	{
		if(mp_AudioList == nullptr)
		{
			return false;
		};

		return mp_AudioList->AddPush(SetAudio);

	}


	//スレッドで駆動させる関数。
	void SonikAudioMixer::MixerThreadFunc(void)
	{
		SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>> l_ope;

		l_ope = mp_AudioList->GetOperator();

		std::fill_n(mp_buffer, OneSamplingByteSize, 0);

		while( !l_ope.NullPtrCheck() )
		{
			if( l_ope->GetPlayState() == SonikAudioEnum::PlayStateID::PS_Stop
			   || l_ope->GetPlayState() == SonikAudioEnum::PlayStateID::PS_SUSPEND )
			{
				//対象がSTOPかSUSPEND状態なら何もしなーい。
				l_ope.NextMove();
				continue;
			};

			//mp_platform->PlayAudio(*(l_itr->GetAudioControlPointer()), l_itr->GetAllWaveDataSize());

			((this)->*p_mfunc_)(l_ope);

			l_ope.NextMove();
		};

		mp_platform->BufferUpdate(mp_buffer);

	};


//==========================================================================================================================
	//各パターンの時の処理。(内容はほぼ一緒だったりする。)
	void SonikAudioMixer::Mixing_16bit_1ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int16_t** p_wave = reinterpret_cast<int16_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 3);//1chで決定しているので直値で記載。
		int16_t* _buffer = reinterpret_cast<int16_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize; ++i)
		{
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * c_vol;
			++_buffer;
			++(*p_wave);
		};

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};

	};

	void SonikAudioMixer::Mixing_16bit_2ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int16_t** p_wave = reinterpret_cast<int16_t**>( ref_itr->GetAudioControlPointer() );
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		SonikMathDataBox::Sonik3DPoint& lis_dir = mp_Listener->GetDirection();
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& pl_dir = ref_itr->GetDirectionAll();

		//uint32_t _splitsize = (m_samplingRate >> 2);//2chで決定しているので直値で記載。/4をシフト演算で..。
		int16_t* _buffer = reinterpret_cast<int16_t*>(mp_buffer);

		double _dis = SonikMath::Distance(lis_pos, pl_pos) + 0.0000000000001;//0除算対策
		double _pan = SonikMath::Panning(lis_pos, pl_pos, lis_dir, pl_dir, 1.0, 0.2);
		double L_pan = 1.0 - _pan;
		double R_pan = _pan;
		double master_vol = mp_Listener->GetListenVolume() * (*ref_itr->GetVolume());

		//Distanceの調整
		double MaxListenVolume = mp_Listener->GetMaxListernDistance();
		_dis = (MaxListenVolume <= 0) ? 1.0 : 1.0 - (_dis / MaxListenVolume);

		//for(uint32_t i = 0; i < _splitsize; ++i)
		for(uint32_t i = 0; i < m_samplingRate; ++i)
		{
			//2chなので2ポインタ進めて１回分。
			(*_buffer) += (*(*p_wave)) * master_vol * _dis; //* L_pan; // L
			++_buffer;
			++(*p_wave);
			(*_buffer) += (*(*p_wave)) * master_vol * _dis; //* R_pan; // R
			++_buffer;
			++(*p_wave);

		};

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};


	};
	void SonikAudioMixer::Mixing_16bit_4ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int16_t** p_wave = reinterpret_cast<int16_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 2);//4chで決定しているので直値で記載。
		int16_t* _buffer = reinterpret_cast<int16_t*>(mp_buffer);

		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;


		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;

			i += 4;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};


	}

	// 5.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
	void SonikAudioMixer::Mixing_16bit_6ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int16_t** p_wave = reinterpret_cast<int16_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate * 0.166667);//6ch(5.1ch)で決定しているので直値で記載。
		int16_t* _buffer = reinterpret_cast<int16_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;
			_buffer[i+4] += (*p_wave)[i+4] * c_vol;
			_buffer[i+5] += (*p_wave)[i+5] * c_vol;

			i += 6;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};


	};

	// 7.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
	void SonikAudioMixer::Mixing_16bit_8ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int16_t** p_wave = reinterpret_cast<int16_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 3);//8ch(7.1ch)で決定しているので直値で記載。
		int16_t* _buffer = reinterpret_cast<int16_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;
			_buffer[i+4] += (*p_wave)[i+4] * c_vol;
			_buffer[i+5] += (*p_wave)[i+5] * c_vol;
			_buffer[i+6] += (*p_wave)[i+6] * c_vol;
			_buffer[i+7] += (*p_wave)[i+7] * c_vol;

			i += 8;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};

	};

	void SonikAudioMixer::Mixing_32bit_1ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int32_t** p_wave = reinterpret_cast<int32_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = m_samplingRate;//1chで決定しているので直値で記載。
		int32_t* _buffer = reinterpret_cast<int32_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize; ++i)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;

		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};
	};

	void SonikAudioMixer::Mixing_32bit_2ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int32_t** p_wave = reinterpret_cast<int32_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 1);//2chで決定しているので直値で記載。
		int32_t* _buffer = reinterpret_cast<int32_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;

			i += 2;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};

	};

	void SonikAudioMixer::Mixing_32bit_4ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int32_t** p_wave = reinterpret_cast<int32_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 2);//4chで決定しているので直値で記載。
		int32_t* _buffer = reinterpret_cast<int32_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;

			i += 4;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};

	};

	// 5.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
	void SonikAudioMixer::Mixing_32bit_6ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int32_t** p_wave = reinterpret_cast<int32_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate * 0.166667);//6ch(5.1ch)で決定しているので直値で記載。
		int32_t* _buffer = reinterpret_cast<int32_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;
			_buffer[i+4] += (*p_wave)[i+4] * c_vol;
			_buffer[i+5] += (*p_wave)[i+5] * c_vol;

			i += 6;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};

	};

	// 7.1ch (低音専用が0.1chあるが1chとしてカウントされるため。
	void SonikAudioMixer::Mixing_32bit_8ch(SonikLib::SonikLinerOperator_PriorityList<SonikLib::SharedSmtPtr<SonikAudioData::SonikAudioControlData>>& ref_itr)
	{
		int32_t** p_wave = reinterpret_cast<int32_t**>( ref_itr->GetAudioControlPointer() );
		const float* volume = ref_itr->GetVolume();
		double c_vol = 0.0;
		SonikMathDataBox::Sonik3DPoint& pl_pos = ref_itr->GetPositionAll();
		SonikMathDataBox::Sonik3DPoint& lis_pos = mp_Listener->GetPosition();
		uint32_t _splitsize = (m_samplingRate >> 3);//8ch(7.1ch)で決定しているので直値で記載。
		int32_t* _buffer = reinterpret_cast<int32_t*>(mp_buffer);
		double l_dis = 1.0;//pl_pos.Distance(lis_pos);

		c_vol = (*volume) * l_dis;

		for(uint32_t i = 0; i < _splitsize;)
		{
			_buffer[i] += (*p_wave)[i] * c_vol;
			_buffer[i+1] += (*p_wave)[i+1] * c_vol;
			_buffer[i+2] += (*p_wave)[i+2] * c_vol;
			_buffer[i+3] += (*p_wave)[i+3] * c_vol;
			_buffer[i+4] += (*p_wave)[i+4] * c_vol;
			_buffer[i+5] += (*p_wave)[i+5] * c_vol;
			_buffer[i+6] += (*p_wave)[i+6] * c_vol;
			_buffer[i+7] += (*p_wave)[i+7] * c_vol;

			i += 8;
		};

		(*p_wave) += m_samplingRate;

		if( ref_itr->Get_EndPointer() )
		{
			//ポインタの終端であればポインタを変更した上でリセット
			ref_itr->TopResetAudioControlPointer();
			ref_itr->SetAudioState(SonikAudioEnum::PlayStateID::PS_Stop);
		};
	};


};



