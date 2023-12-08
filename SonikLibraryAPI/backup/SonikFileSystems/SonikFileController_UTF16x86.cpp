/*
 * SonikFileController_UTF16x86.cpp
 *
 *  Created on: 2018/11/20
 *      Author: USER
 */


#ifdef _WIN32

#include <algorithm>

#include "../SonikFileSystems/SonikFileController_UTF16.h"
#include "../SonikMathBitsUse.h"


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
	bool SonikFileStreamController_UTF16MODE::ReadText_CHR(char* buffer, uint32_t ReadSize)
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

		uint16_t get_c_val = 0;
		FILE* tmpfp = m_pFile;
		uint16_t* control = reinterpret_cast<uint16_t*>(buffer);
		for(unsigned long lop=0; lop < ReadSize; ++lop)
		{
			get_c_val = fgetwc(tmpfp);
			if( get_c_val == EOF)
			{
				(*control) = 0x00;
				return true;
			};

			(*control) = get_c_val;
			++control;
		};

		atmlock.Unlock();
		return true;

	};

	//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
	bool SonikFileStreamController_UTF16MODE::ReadText_Line(SonikLib::SonikString& LineStr, unsigned long GetRowCnt)
	{
		atmlock.lock();
		if( !Opend )
		{
			return false;
		};

		if((m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		wchar_t tmpbuffer[1024];
		wchar_t* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;

		std::fill_n(tmpbuffer, 1024, 0);
		LineStr = "";
		if( GetRowCnt != 0 )
		{
			for(unsigned long lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgetws(tmpbuffer, 1024, tmpfp) == nullptr )
				{
					break;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(unsigned long lopj=0; lopj < 1024; ++lopj)
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

				LineStr += tmpbuffer;
				std::fill_n(tmpbuffer, 1024, 0);
			};

		}else
		{
			//RowCntが０なら終端まで。
			while(fgetws(tmpbuffer, 1024, tmpfp) != nullptr)
			{
				//改行を削除
				controlbuffer = tmpbuffer;
				for(unsigned long lopj=0; lopj < 1024; ++lopj)
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

				LineStr += tmpbuffer;
				std::fill_n(tmpbuffer, 1024, 0);
			};

		};//end if

		atmlock.Unlock();
		return true;

	};

	//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
	bool SonikFileStreamController_UTF16MODE::ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, unsigned long GetRowCnt)
	{
		atmlock.lock();
		if( !Opend )
		{
			return false;
		};

		if((m_opmode > SonikLibFileSystems::OpenMode::OPEN_TXT_READADDWRITE) || m_opmode == SonikLibFileSystems::OpenMode::OPEN_UNKNOWN )
		{
			atmlock.Unlock();
			return false;
		};

		wchar_t tmpbuffer[1024];
		wchar_t* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;
		SonikLib::SonikString LineStr;

		std::fill_n(tmpbuffer, 1024, 0);

		if( GetRowCnt != 0 )
		{
			for(unsigned long lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgetws(tmpbuffer, 1024, tmpfp) == nullptr )
				{
					break;
				};

				//改行を削除
				controlbuffer = tmpbuffer;
				for(unsigned long lopj=0; lopj < 1024; ++lopj)
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

				LineStr = tmpbuffer;
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		}else
		{
			//RowCntが０なら終端まで。
			while(fgetws(tmpbuffer, 1024, tmpfp) != nullptr)
			{
				//改行を削除
				controlbuffer = tmpbuffer;
				for(unsigned long lopj=0; lopj < 1024; ++lopj)
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

				LineStr = tmpbuffer;
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(tmpbuffer, 1024, 0);
			};

		};//end if

		atmlock.Unlock();
		return true;

	};



};

#elif _WIN64
//64bit implementation

#endif


