/*
 * SonikFileController_UTF8x86.cpp
 *
 *  Created on: 2018/11/20
 *      Author: USER
 */

#ifdef _WIN32

#include "../SonikFileSystems/SonikFileController_UTF8.h"
#include "../SonikMathBitsUse.h"

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
		char binarybyte[1048576]; //1MB
		char tmp_opmode[4];
		unsigned long tmp_fsize = 0;
		unsigned long ret = 0;
		(*reinterpret_cast<unsigned long*>(tmp_opmode)) = static_cast<unsigned long>(SonikLibFileSystems::OpenMode::OPNE_BIN_READ);
//		SonikLib::SonikString str;
//		str = tmp_opmode;
//		str += ", ccs=UTF-8";
		FILE* tmp_fp = fopen(OpenFilePathStr, tmp_opmode);
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
		tmp_fp = fopen(OpenFilePathStr, tmp_opmode);
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
	bool SonikFileStreamController_UTF8MODE::ReadText_CHR(char* buffer, uint32_t ReadSize)
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

		char readdata[4];
		unsigned char reversebit = 0;
		char* controls = nullptr;
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
				break;
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
				bitcnt = (32 - bitcnt) -1;

				(*buffer) = (*readdata);
				fread(readdata, bitcnt, 1, tmpfp);
				controls = readdata;
				for(uint32_t lopj=0; lopj < bitcnt; ++lopj)
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
	bool SonikFileStreamController_UTF8MODE::ReadText_Line(SonikLib::SonikString& LineStr, unsigned long GetRowCnt)
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

		char readdata[4];
		char readstr[2048];
		char* controls = nullptr;
		char* controlstr = nullptr;
		unsigned char reversebit = 0;
		uint32_t bitcnt = 0;
		FILE* tmpfp = m_pFile;
		LineStr = "";

		std::fill_n(readstr, 2048, 0);

		if(GetRowCnt != 0)
		{
			for(uint32_t lop=0; lop < GetRowCnt; ++lop)
			{
				controlstr = readstr;

				for(uint32_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;

					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return true;
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
						bitcnt = (32 - bitcnt) -1;

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

				LineStr += readstr;
				std::fill_n(readstr, 2048, 0);

			};
		}else
		{
			while(1)
			{
				controlstr = readstr;

				for(uint32_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;

					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return true;
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
						bitcnt = (32 - bitcnt) -1;

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

				LineStr += readstr;
				std::fill_n(readstr, 2048, 0);

			};

		};

		atmlock.Unlock();
		return true;
	};

	bool SonikFileStreamController_UTF8MODE::ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, unsigned long GetRowCnt)
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

		char readdata[4];
		char readstr[2048];
		char* controls = nullptr;
		char* controlstr = nullptr;
		unsigned char reversebit = 0;
		uint32_t bitcnt = 0;
		FILE* tmpfp = m_pFile;
		SonikLib::SonikString LineStr;

		std::fill_n(readstr, 2048, 0);

		if(GetRowCnt != 0)
		{
			for(uint32_t lop=0; lop < GetRowCnt; ++lop)
			{
				controlstr = readstr;

				for(uint32_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;


					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return true;
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
						bitcnt = (32 - bitcnt) -1;

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

				LineStr = readstr;
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(readstr, 2048, 0);

			};
		}else
		{
			while(1)
			{
				controlstr = readstr;

				for(uint32_t lopi=0; lopi < 2048; ++lopi)
				{
					readdata[0] = 0x00;
					readdata[1] = 0x00;
					readdata[2] = 0x00;
					readdata[3] = 0x00;


					if( fread(readdata, 1, 1, tmpfp) < 1)
					{
						atmlock.Unlock();
						return true;
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
						bitcnt = (32 - bitcnt) -1;


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

				LineStr = readstr;
				LineStrQueue.EnQueue(LineStr);
				std::fill_n(readstr, 2048, 0);
			};

		};

		atmlock.Unlock();
		return true;
	};


};

#endif


