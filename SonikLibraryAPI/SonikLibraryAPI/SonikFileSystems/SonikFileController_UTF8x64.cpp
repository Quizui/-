/*
 * SonikFileController_UTF8x86.cpp
 *
 *  Created on: 2018/11/20
 *      Author: SONIK
 */

#ifdef __SONIK_x86_64__
#define _FILE_OFFSET_BITS 64

#ifdef _WIN64

#include "SonikFileController_UTF8.h"
#include "../MathBit/MathBit.h"

namespace SonikLibFileSystemsControllers
{
	//コンストラクタ
	SonikFileStreamController_UTF8MODE::SonikFileStreamController_UTF8MODE(void)
	{
		//no process
	};

	//デストラクタ
	SonikFileStreamController_UTF8MODE::~SonikFileStreamController_UTF8MODE(void)
	{
		//no process
	};

	//FileOpen
	bool SonikFileStreamController_UTF8MODE::OpenFile(const char* OpenFilePathStr, SonikLibFileSystems::OpenMode mode)
	{
		atmlock.lock();

		//バイナリとして読み込んですべての処理を行う。
		//ファイルサイズを取得する。
		int8_t binarybyte[1048576]; //1MB
		int8_t tmp_opmode[4];
		uint64_t tmp_fsize = 0;
		uint64_t ret = 0;
		(*reinterpret_cast<uint32_t*>(tmp_opmode)) = static_cast<uint32_t>(SonikLibFileSystems::OpenMode::OPNE_BIN_READ);


		FILE* tmp_fp = fopen64(OpenFilePathStr, reinterpret_cast<char*>(tmp_opmode));
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
		//(*reinterpret_cast<unsigned long*>(tmp_opmode)) = static_cast<unsigned long>(SonikLibFileSystems::OpenMode::OPNE_BIN_READ);
		tmp_fp = fopen64(OpenFilePathStr, reinterpret_cast<char*>(tmp_opmode));
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


	//(テキストモード専用)指定した文字数分TEXTを読み込みます。（最大char * 3倍 の容量が必要になります。)
	bool SonikFileStreamController_UTF8MODE::ReadText_CHR(int8_t* buffer, uint64_t ReadSize)
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

		int8_t readdata[4];
		uint8_t reversebit = 0;
		int8_t* controls = nullptr;
		uint32_t bitcnt = 0;
		FILE* tmpfp = m_pFile;

		for(uint32_t lop=0; lop < ReadSize; ++lop)
		{
			readdata[0] = 0x00;
			readdata[1] = 0x00;
			readdata[2] = 0x00;
			readdata[3] = 0x00;

			if( fread(readdata, 1, 1, tmpfp) < 1)
			{
				atmlock.Unlock();
				return false;
			};

			reversebit = (*readdata);
			reversebit = SonikMathBit::BitSwapFor8bit(reversebit);

			if( (reversebit & 0x01) != 1 )
			{
				(*buffer) = (*readdata);
				++buffer;
			}else
			{

				bitcnt =  ~(reversebit);

				bitcnt |= (bitcnt << 1);
				bitcnt |= (bitcnt << 2);
				bitcnt |= (bitcnt << 4);
				bitcnt |= (bitcnt << 8);
				bitcnt |= (bitcnt << 16);

				bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
				bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
				bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
				bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

				bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
				bitcnt = (32 - bitcnt);

				if( bitcnt == 0 )
				{
					++bitcnt;
				};


				(*buffer) = (*readdata);
				fread(readdata, bitcnt, 1, tmpfp);
				controls = readdata;
				for(uint64_t lopj=0; lopj < bitcnt; ++lopj)
				{
					(*buffer) = (*controls);
					++buffer;
					++controls;
				};
			};
		};

		atmlock.Unlock();
		return true;

	};

	//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
	bool SonikFileStreamController_UTF8MODE::ReadText_Line(SonikLib::SonikString& LineStr, uint64_t GetRowCnt)
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

		int8_t readdata[4];
		int8_t readstr[2048];
		int8_t* controls = nullptr;
		int8_t* controlstr = nullptr;
		uint8_t reversebit = 0;
		uint32_t bitcnt = 0;
		FILE* tmpfp = m_pFile;
		LineStr = "";

		std::fill_n(readstr, 2048, 0);

		if(GetRowCnt != 0)
		{
			for(uint64_t lop=0; lop < GetRowCnt; ++lop)
			{
				controlstr = readstr;

				for(uint64_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;

					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return false;
					};

					reversebit = (*readdata);
					reversebit = SonikMathBit::BitSwapFor8bit(reversebit);

					if( (reversebit & 0x01) != 1 )
					{
						if( (*readdata) == 0x0D )
						{
							(*readdata) = 0x00;
						}else if( (*readdata) == 0x0A )
						{
							//C:保持しない。
							//(*controlstr) = 0x00;
							break;
						};

						(*controlstr) = (*readdata);
						++controlstr;
					}else
					{

						bitcnt =  ~(reversebit);

						bitcnt |= (bitcnt << 1);
						bitcnt |= (bitcnt << 2);
						bitcnt |= (bitcnt << 4);
						bitcnt |= (bitcnt << 8);
						bitcnt |= (bitcnt << 16);

						bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
						bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
						bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
						bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

						bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
						bitcnt = (32 - bitcnt);

						if( bitcnt == 0 )
						{
							++bitcnt;
						};


						(*controlstr) = (*readdata);
						++controlstr;
						fread(readdata, bitcnt, 1, tmpfp);
						controls = readdata;
						for(uint64_t lopj=0; lopj < bitcnt; ++lopj)
						{
							(*controlstr) = (*controls);
							++controlstr;
							++controls;
						};
					};
				};

				LineStr += reinterpret_cast<char*>(readstr);
				std::fill_n(readstr, 2048, 0);

			};
		}else
		{
			while(1)
			{
				controlstr = readstr;

				for(uint64_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;

					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return false;
					};

					reversebit = (*readdata);
					reversebit = SonikMathBit::BitSwapFor8bit(reversebit);

					if( (reversebit & 0x01) != 1 )
					{
						if( (*readdata) == 0x0D )
						{
							(*readdata) = 0x00;
						}else if( (*readdata) == 0x0A )
						{
							//C:保持しない。
							//(*controlstr) = 0x00;
							break;
						};

						(*controlstr) = (*readdata);
						++controlstr;
					}else
					{

						bitcnt =  ~(reversebit);

						bitcnt |= (bitcnt << 1);
						bitcnt |= (bitcnt << 2);
						bitcnt |= (bitcnt << 4);
						bitcnt |= (bitcnt << 8);
						bitcnt |= (bitcnt << 16);

						bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
						bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
						bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
						bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

						bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
						bitcnt = (32 - bitcnt);

						if( bitcnt == 0 )
						{
							++bitcnt;
						};


						(*controlstr) = (*readdata);
						++controlstr;
						fread(readdata, bitcnt, 1, tmpfp);
						controls = readdata;
						for(uint64_t lopj=0; lopj < bitcnt; ++lopj)
						{
							(*controlstr) = (*controls);
							++controlstr;
							++controls;
						};
					};
				};

				LineStr += reinterpret_cast<char*>(readstr);
				std::fill_n(readstr, 2048, 0);

			};

		};

		atmlock.Unlock();
		return true;
	};

	bool SonikFileStreamController_UTF8MODE::ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint64_t GetRowCnt)
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

		int8_t readdata[4];
		int8_t readstr[2048];
		int8_t* controls = nullptr;
		int8_t* controlstr = nullptr;
		uint8_t reversebit = 0;
		uint32_t bitcnt = 0;
		FILE* tmpfp = m_pFile;
		SonikLib::SonikString LineStr;

		std::fill_n(readstr, 2048, 0);

		if(GetRowCnt != 0)
		{
			for(uint64_t lop=0; lop < GetRowCnt; ++lop)
			{
				controlstr = readstr;

				for(uint64_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;


					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return false;
					};

					reversebit = (*readdata);
					reversebit = SonikMathBit::BitSwapFor8bit(reversebit);

					if( (reversebit & 0x01) != 1 )
					{
						if( (*readdata) == 0x0D )
						{
							(*readdata) = 0x00;
						}else if( (*readdata) == 0x0A )
						{
							//C:保持しない。
							//(*controlstr) = 0x00;
							break;
						};

						(*controlstr) = (*readdata);
						++controlstr;
					}else
					{

						bitcnt =  ~(reversebit);

						bitcnt |= (bitcnt << 1);
						bitcnt |= (bitcnt << 2);
						bitcnt |= (bitcnt << 4);
						bitcnt |= (bitcnt << 8);
						bitcnt |= (bitcnt << 16);

						bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
						bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
						bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
						bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

						bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
						bitcnt = (32 - bitcnt);

						if( bitcnt == 0 )
						{
							++bitcnt;
						};


						(*controlstr) = (*readdata);
						++controlstr;
						fread(readdata, bitcnt, 1, tmpfp);
						controls = readdata;
						for(uint32_t lopj=0; lopj < bitcnt; ++lopj)
						{
							(*controlstr) = (*controls);
							++controlstr;
							++controls;
						};
					};
				};

				LineStr = reinterpret_cast<char*>(readstr);
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(readstr, 2048, 0);

			};
		}else
		{
			while(1)
			{
				controlstr = readstr;

				for(uint64_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;


					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return false;
					};

					reversebit = (*readdata);
					reversebit = SonikMathBit::BitSwapFor8bit(reversebit);

					if( (reversebit & 0x01) != 1 )
					{
						if( (*readdata) == 0x0D )
						{
							(*readdata) = 0x00;
						}else if( (*readdata) == 0x0A )
						{
							//C:保持しない。
							//(*controlstr) = 0x00;
							break;
						};

						(*controlstr) = (*readdata);
						++controlstr;
					}else
					{

						bitcnt =  ~(reversebit);

						bitcnt |= (bitcnt << 1);
						bitcnt |= (bitcnt << 2);
						bitcnt |= (bitcnt << 4);
						bitcnt |= (bitcnt << 8);
						bitcnt |= (bitcnt << 16);

						bitcnt = (bitcnt & 0x55555555) + ( (bitcnt >> 1) & 0x55555555 );
						bitcnt = (bitcnt & 0x33333333) + ( (bitcnt >> 2) & 0x33333333 );
						bitcnt = (bitcnt & 0x0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F );
						bitcnt = (bitcnt & 0x00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF );

						bitcnt = (bitcnt & 0x0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF);
						bitcnt = (32 - bitcnt);

						if( bitcnt == 0 )
						{
							++bitcnt;
						};


						(*controlstr) = (*readdata);
						++controlstr;
						fread(readdata, bitcnt, 1, tmpfp);
						controls = readdata;
						for(uint32_t lopj=0; lopj < bitcnt; ++lopj)
						{
							(*controlstr) = (*controls);
							++controlstr;
							++controls;
						};
					};
				};

				LineStr = reinterpret_cast<char*>(readstr);
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(readstr, 2048, 0);
			};

		};

		atmlock.Unlock();
		return true;
	};


};

#endif // _WIN64

#undef _FILE_OFFSET_BITS
#endif //__SONIK_x86_64__


