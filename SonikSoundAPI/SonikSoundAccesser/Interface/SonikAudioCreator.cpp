/*
 * SonikAudioCreator.cpp
 *
 *  Created on: 2020/04/24
 *      Author: SONIC
 */

#include "../../SonikString/SonikString.h"
#include "./SonikAudioCreator.h"
#include "../PlatformInterface/PlatformAudioInterface.h"

#include "../../DllAccess/SonikDllAccessManager.h"
#include "./SonikAudio_Implement.h"


namespace SonikAudio
{

	//Constructor
	SonikAudioCreator::SonikAudioCreator(void)
	{

	};

	//Copy Constructor
	SonikAudioCreator::SonikAudioCreator(const SonikAudioCreator& t_his)
	{
		_interface = t_his._interface;
	};

	//override operator equal
	SonikAudioCreator& SonikAudioCreator::operator =(const SonikAudioCreator& t_his)
	{
		return (*this);
	};


	//Destrucotr
	SonikAudioCreator::~SonikAudioCreator(void)
	{
		//インスタンス変数をスマートポインタ管理に変更したのでデストラクタのお仕事なし。
//		if( _interface != nullptr )
//		{
//			delete _interface;
//		};

	}

	SonikAudioCreator& SonikAudioCreator::Instance(void)
	{
		static SonikAudioCreator _inst;

		return _inst;
	};

	bool SonikAudioCreator::CreatAudioInterface(char* DllPath, unsigned long SetBit, unsigned long SetSampling, unsigned long SetCh, SonikAudio::SAudioInterface& RefGetInterface)
	{
		_lock.lock();

		if( !_interface.IsNullptr() ) //!=演算子オーバーライドまだしてないので否定演算子 ! で代用。
		{
			RefGetInterface = _interface;
			_lock.unlock();
			return true;
		}

		SonikLib::SonikString dllstr;
		dllstr = DllPath;
		dllstr += "/PlatFormSound_OpenAL";

		//Dllロード
		SonikLib::SDllHandle l_handle;
		SonikLib::SonikDllHandleManager l_dllmng;
		if( !l_dllmng.DllGetLoad(dllstr.str_c(), l_handle) )
		{
			_lock.unlock();
			return false;
		};


		//ハンドルが取得できたので関数を取得
		uintptr_t FuncPointer = 0;
		FuncPointer = l_handle->GetDllProcAddress("PlatFormInitialize");
		if( FuncPointer == 0 )
		{
			l_handle.ResetPointer(nullptr);
			_lock.unlock();
			return false;
		};

		//関数が取得できたのでCall
		SonikAudioPlatForm::SonikPlatformAudioInterface* l_pltInterfacePointer = nullptr;
		if( !(*reinterpret_cast<bool(*)(char*,unsigned long,unsigned long,unsigned long,SonikAudioPlatForm::SonikPlatformAudioInterface*&)>(FuncPointer))(DllPath, SetBit, SetSampling, SetCh, l_pltInterfacePointer) )
		{
			l_handle.ResetPointer(nullptr);
			_lock.unlock();
			return false;
		};

		//プラットフォーム側のイニシャライザまで完了したら次はユーザー側インターフェースの作成と初期化。

		//作成
		SonikAudio::SonikAudio_Implement* l_interface = nullptr;
		l_interface = new(std::nothrow) SonikAudio::SonikAudio_Implement();
		if( l_interface == nullptr )
		{
			l_handle.ResetPointer(nullptr);
			_lock.unlock();
			return false;
		};

		//初期化。
		uint32_t sampletype = 0 ;
		//sampletype = SetBit;
		//sampletype = (sampletype << 8) | SetCh;
		//sampletype = (sampletype << 8) | static_cast<uint32_t>(SetSampling * 0.001);
		//↑を一行で...。
		sampletype = ( ( (SetBit << 8) | SetCh ) << 8 ) | static_cast<uint32_t>( (SetSampling * 0.001) );

		if( !l_interface->Initialize(sampletype, l_pltInterfacePointer, l_handle) )
		{
			delete l_interface;
			l_handle.ResetPointer(nullptr);
			_lock.unlock();
			return false;
		};


		_interface.ResetPointer(l_interface);
		RefGetInterface = _interface;
		_lock.unlock();

		return true;
	};

	void SonikAudioCreator::DeleteAudioInterface(void)
	{
		_lock.lock();

		_interface.ResetPointer(nullptr);
//		_interface = nullptr;

		_lock.unlock();

	};


}


