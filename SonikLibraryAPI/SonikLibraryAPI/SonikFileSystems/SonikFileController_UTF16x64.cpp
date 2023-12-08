/*
 * SonikFileController_UTF16x86.cpp
 *
 *  Created on: 2018/11/20
 *      Author: SONIK
 */


#ifdef __SONIK_x86_64__
#define _FILE_OFFSET_BITS 64

#ifdef _WIN64

#include <algorithm>

#include "SonikFileController_UTF16.h"
#include "../MathBit/MathBit.h"


namespace SonikLibFileSystemsControllers
{
	//コンストラクタ
	SonikFileStreamController_UTF16MODE::SonikFileStreamController_UTF16MODE(void)
	{
		//no process
	};
	//デストラクタ
	SonikFileStreamController_UTF16MODE::~SonikFileStreamController_UTF16MODE(void)
	{
		//no process
	};

	//(テキストモード専用)指定した文字数分TEXTを読み込みます。
	bool SonikFileStreamController_UTF16MODE::ReadText_CHR(int8_t* buffer, uint64_t ReadSize)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return false;
		};

		if((m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		int16_t get_c_val = 0;
		FILE* tmpfp = m_pFile;
		int16_t* control = reinterpret_cast<int16_t*>(buffer);
		for(uint64_t lop=0; lop < ReadSize; ++lop)
		{
			get_c_val = fgetwc(tmpfp);
			if( get_c_val == EOF)
			{
				(*control) = 0x00;
				return false;
			};

			(*control) = get_c_val;
			++control;
		};

		atmlock.Unlock();
		return true;

	};

	//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
	bool SonikFileStreamController_UTF16MODE::ReadText_Line(SonikLib::SonikString& LineStr, uint64_t GetRowCnt)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return false;
		};

		if((m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		int16_t tmpbuffer[1024];
		int16_t* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;

		std::fill_n(tmpbuffer, 1024, 0);
		LineStr = "";
		if( GetRowCnt != 0 )
		{
			for(uint32_t lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgetws(reinterpret_cast<wchar_t*>(tmpbuffer), 1024, tmpfp) == nullptr )
				{
					atmlock.Unlock();
					return false;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(uint64_t lopj=0; lopj < 1024; ++lopj)
				{
					if( ((*controlbuffer) == '\r') || ((*controlbuffer) == '\n') )
					{
						(*controlbuffer) = 0x00;

					}else if( (*controlbuffer) == 0x00 )
					{
						break;
					};

					++controlbuffer;
				};

				LineStr += reinterpret_cast<char16_t*>(tmpbuffer);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		}else
		{
			//RowCntが０なら終端まで。
			while(1)
			{
				if( fgetws(reinterpret_cast<wchar_t*>(tmpbuffer), 1024, tmpfp) == nullptr )
				{
					atmlock.Unlock();
					return false;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(uint64_t lopj=0; lopj < 1024; ++lopj)
				{
					if( ((*controlbuffer) == '\r') || ((*controlbuffer) == '\n') )
					{
						(*controlbuffer) = 0x00;

					}else if( (*controlbuffer) == 0x00 )
					{
						break;
					};

					++controlbuffer;
				};

				LineStr += reinterpret_cast<char16_t*>(tmpbuffer);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		};//end if

		atmlock.Unlock();
		return true;

	};

	//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
	bool SonikFileStreamController_UTF16MODE::ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint64_t GetRowCnt)
	{
		atmlock.lock();
		if( !Opend )
		{
			atmlock.Unlock();
			return false;
		};

		if((m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		int16_t tmpbuffer[1024];
		int16_t* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;
		SonikLib::SonikString LineStr;

		std::fill_n(tmpbuffer, 1024, 0);

		if( GetRowCnt != 0 )
		{
			for(uint64_t lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgetws(reinterpret_cast<wchar_t*>(tmpbuffer), 1024, tmpfp) == nullptr )
				{
					atmlock.Unlock();
					return false;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(uint64_t lopj=0; lopj < 1024; ++lopj)
				{
					if( ((*controlbuffer) == '\r') || ((*controlbuffer) == '\n') )
					{
						(*controlbuffer) = 0x00;

					}else if( (*controlbuffer) == 0x00 )
					{
						break;
					};

					++controlbuffer;
				};

				LineStr = reinterpret_cast<char16_t*>(tmpbuffer);
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		}else
		{
			//RowCntが０なら終端まで。
			while(1)
			{
				if( fgetws(reinterpret_cast<wchar_t*>(tmpbuffer), 1024, tmpfp) == nullptr )
				{
					atmlock.Unlock();
					return false;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(uint32_t lopj=0; lopj < 1024; ++lopj)
				{
					if( ((*controlbuffer) == '\r') || ((*controlbuffer) == '\n') )
					{
						(*controlbuffer) = 0x00;

					}else if( (*controlbuffer) == 0x00 )
					{
						break;
					};

					++controlbuffer;
				};

				LineStr = reinterpret_cast<char16_t*>(tmpbuffer);
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		};//end if

		atmlock.Unlock();
		return true;

	};



};

#endif // _WIN64

#undef _FILE_OFFSET_BITS
#endif //__SONIK_x86_64__

