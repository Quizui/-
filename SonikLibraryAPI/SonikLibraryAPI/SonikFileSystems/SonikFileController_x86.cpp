/*
 * SonikFileController_x86.cpp
 *
 *  Created on: 2018/11/16
 *      Author: SONIK
 */

#ifdef __SONIK_I686__

#include "SonikFileController.h"
#include "../SonikMathBitsUse.h"

namespace SonikLibFileSystemsControllers
{
	//constructor
	SonikFileStreamController::SonikFileStreamController(void)
	:m_pFile(nullptr)
	,FileSize(0)
	,m_opmode(SonikLibFileSystems::OpenMode::OPEN_UNKNOWN)
	,Opend(false)
	{

	};

	//destrucotr
	SonikFileStreamController::~SonikFileStreamController(void)
	{
		if(Opend)
		{
			fclose(m_pFile);
		};

	};

	//FileOpen
	bool SonikFileStreamController::OpenFile(const char* OpenFilePathStr, SonikLibFileSystems::OpenMode mode)
	{
		atmlock.lock();

		//先にバイナリで読み込んで、ファイルサイズを取得する。
		int8_t binarybyte[1048576]; //1MB
		int8_t tmp_opmode[4];
		uint32_t tmp_fsize = 0;
		uint32_t ret = 0;
		(*reinterpret_cast<uint32_t*>(tmp_opmode)) = static_cast<uint32_t>(SonikLibFileSystems::OpenMode::OPNE_BIN_READ);
		FILE* tmp_fp = fopen(OpenFilePathStr, reinterpret_cast<char*>(tmp_opmode));
		if(tmp_fp == nullptr || tmp_fp == 0)
		{
			Opend = false;
			atmlock.Unlock();
			return false;
		};
		//1Byteずつ読み込み。遅そう。
		while(1)
		{
			ret = fread(binarybyte, 1, 1048576, tmp_fp);
			tmp_fsize += ret;

			if( ret < 1048576 )
			{
				break;
			};
		};

		fclose(tmp_fp);
		tmp_fp = nullptr;

		//本OPEN
		(*reinterpret_cast<uint32_t*>(tmp_opmode)) = static_cast<uint32_t>(mode);
		tmp_fp = fopen(OpenFilePathStr, reinterpret_cast<char*>(tmp_opmode));
		if(tmp_fp == nullptr || tmp_fp == 0)
		{
			Opend = false;
			atmlock.Unlock();
			return false;
		};


		m_pFile = tmp_fp;
		Opend = true;
		FileSize = tmp_fsize;
		m_opmode = mode;
		atmlock.Unlock();
		return true;
	};

	//FileClose
	bool SonikFileStreamController::CloseFile(void)
	{
		atmlock.lock();

		if(Opend)
		{
			fclose(m_pFile);
			Opend = false;
		};

		atmlock.Unlock();
		return true;
	};

	//読み込み位置を一番最初に移動します。
	void SonikFileStreamController::ReadSeekPointSet_Top(void)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return;
		};

		if(m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return;
		};

		fseek(m_pFile, 0, SEEK_SET);

		atmlock.Unlock();
		return;
	};

	//読み込み位置を一番最後に移動します。
	void SonikFileStreamController::ReadSeekPointSet_End(void)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return;
		};

		if(m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return;
		};

		if(m_opmode < SonikLibFileSystems::OpenMode::OPNE_BIN_READ)
		{
			//text mode
			fseek(m_pFile, 0, SEEK_END);
			atmlock.Unlock();
			return;

		}else if(m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE)
		{
			//Binary mode
			fseek(m_pFile, 0, SEEK_SET);
			fseek(m_pFile, FileSize, SEEK_CUR);

			atmlock.Unlock();
			return;
		};

	};

	//現在の読み込み位置を取得します。
	uint32_t SonikFileStreamController::ReadSeekPointGet(void)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return 0xFFFFFFFF;
		};

		if(m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return 0xFFFFFFFF;
		};

		atmlock.Unlock();
		return ftell(m_pFile);
	};

	//現在の読み込み位置から指定文字数分或いは、指定サイズ分移動します。
	void SonikFileStreamController::ReadSeekPointSet_Point(uint32_t offset)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return;
		};

		if(m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return;
		};

		fseek(m_pFile, offset, SEEK_CUR);
		atmlock.Unlock();

	};

	//(バイナリモード専用)指定したサイズ分読み込みます。
	bool SonikFileStreamController::ReadBinary(int8_t* buffer, uint32_t size)
	{
		atmlock.lock();
		if( !Opend )
		{
			return false;
		};

		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return false;
		};

		if((m_opmode < SonikLibFileSystems::OpenMode::OPNE_BIN_READ) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		if( fread(buffer, 1, size, m_pFile)	< size )
		{
			atmlock.Unlock();
			return false;
		};

		atmlock.Unlock();
		return true;
	};


};



#endif
