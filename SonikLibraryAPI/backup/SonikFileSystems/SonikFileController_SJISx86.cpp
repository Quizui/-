/*
 * SonikFileController_SJISx86.cpp
 *
 *  Created on: 2018/11/20
 *      Author: USER
 */

#ifdef _WIN32

#include <algorithm>

#include "../SonikFileSystems/SonikFileController_SJIS.h"
#include "../SonikMathBitsUse.h"


namespace SonikLibFileSystemsControllers
{
	//コンストラクタ
	SonikFileStreamController_SJISMODE::SonikFileStreamController_SJISMODE(void)
	{
		//no process
	};
	//デストラクタ
	SonikFileStreamController_SJISMODE::~SonikFileStreamController_SJISMODE(void)
	{
		//no process
	};

	//(テキストモード専用)指定した文字数分TEXTを読み込みます。
	bool SonikFileStreamController_SJISMODE::ReadText_CHR(char* buffer, uint32_t ReadSize)
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

		int get_c_val = 0;
		unsigned long bits;
		FILE* tmpfp = m_pFile;
		char* control = buffer;
		char* tmp_pvals = nullptr;
		for(unsigned long lop=0; lop < ReadSize; ++lop)
		{
			get_c_val = fgetc(tmpfp);
			if( get_c_val == EOF)
			{
				control[0] = 0x00;
				atmlock.Unlock();
				return true;
			};

			tmp_pvals = reinterpret_cast<char*>(&get_c_val);
			bits = SonikMathBit::GetMSBFor32bit(get_c_val);
			switch( ( (bits >> 3) + 1) )
			{
			case 1:
				//1ByteCopy
				control[0] = tmp_pvals[0];

				++control;
				break;
			case 2:
				//2ByteCopy
				control[0] = tmp_pvals[0];
				control[1] = tmp_pvals[1];

				control += 2;
				break;

			case 3:
				//3ByteCopy
				control[0] = tmp_pvals[0];
				control[1] = tmp_pvals[1];
				control[2] = tmp_pvals[2];

				control += 3;
				break;

			case 4:
				//4ByteCopy
				control[0] = tmp_pvals[0];
				control[1] = tmp_pvals[1];
				control[2] = tmp_pvals[2];
				control[3] = tmp_pvals[3];

				control += 4;
				break;

			default:
				//other...
				atmlock.Unlock();
				return false;
			};//end switch
		};//end for

		atmlock.Unlock();
		return true;

	};

	//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
	bool SonikFileStreamController_SJISMODE::ReadText_Line(SonikLib::SonikString& LineStr, unsigned long GetRowCnt)
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

		char tmpbuffer[1024];
		char* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;

		std::fill_n(tmpbuffer, 1024, 0);
		LineStr = "";

		if( GetRowCnt != 0)
		{
			for(unsigned long lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgets(tmpbuffer, 1024, tmpfp) == nullptr )
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
			while(1)
			{
				if( fgets(tmpbuffer, 1024, tmpfp) == nullptr )
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
		};

		atmlock.Unlock();
		return true;

	};

	//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
	bool SonikFileStreamController_SJISMODE::ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, unsigned long GetRowCnt)
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


		char tmpbuffer[1024];
		char* controlbuffer = nullptr;
		FILE* tmpfp = m_pFile;
		SonikLib::SonikString LineStr;

		std::fill_n(tmpbuffer, 1024, 0);

		if( GetRowCnt != 0)
		{
			for(unsigned long lop =0; lop < GetRowCnt; ++lop)
			{
				if( fgets(tmpbuffer, 1024, tmpfp) == nullptr )
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
			while(1)
			{
				if( fgets(tmpbuffer, 1024, tmpfp) == nullptr )
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
		};


		atmlock.Unlock();
		return true;
	};


};

#elif _WIN64
//64bit implementation

#endif
