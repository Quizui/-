/*
 * SonikFileController.cpp
 *
 *  Created on: 2024/04/11
 *      Author: SONIC
 */

#include "SonikFileController.h"
#include "../Container/SonikAtomicQueue.hpp"

#include <stdint.h>

#if ___cplusplus <= 201703L
              //C++17 以降
              #include <filesystem>
              #define STDFSYS std::filesystem

#else
			//C++17以前
			#if defined(_WIN64)
				//Windows
				#include <Windows.h>

			#elif defined(__linux__)
				//linux

			#endif

#endif

namespace SonikLib
{
	namespace FileSystemControllers
	{
		SonikFileSystemController::SonikFileSystemController(void)
		:m_file(nullptr)
		 ,m_openmode(FileSystem::OpenMode::OPEN_UNKNOWN)
		 {
			//no process;
		 };

		SonikFileSystemController::~SonikFileSystemController(void)
		{
			CloseFile();
		};

		bool SonikFileSystemController::CreateFileController(SFileSystemController& _out_)
		{
			SonikFileStreamController* ptmp;
			ptmp = new(std::nothrow) SonikFileStreamController;

			if(ptmp == nullptr)
			{
				return false;
			};

			if(!_out_.ResetPointer(ptmp))
			{
				delete ptmp;
				return false;
			};

			return true;
		};

		//FileOpen
		bool SonikFileSystemController::OpenFile(SonikLib::SonikString _filepath_, FileSystem::OpenMode _mode_)
		{
			m_lock.lock();

			if(_mode_ == FileSystem::OpenMode::OPEN_UNKNOWN)
			{
				m_lock.unlock();
				return false;

			};

			//すでにオープンしていたら開いてるのをクローズ
			if(m_file != nullptr)
			{
				fclose(m_file);
				m_file = nullptr;
			};

			//ファイルよみこみ
			if(fopen_s(&m_file, _filepath_.c_str(), reinterpret_cast<char*>(&_mode_)) != 0)
			{
				//読み込み失敗。
				m_lock.unlock();
				return false;
			};

			m_filepath = _filepath_;
			m_lock.unlock();

			return true;
		};

		void SonikFileSystemController::CloseFile(void)
		{
			if(m_file != nullptr)
			{
				fclose(m_file);
				m_file = nullptr;
			};
		};

		//現在のファイルサイズの取得
		uint64_t SonikFileSystemController::GetFileSize(void)
		{
			#if ___cplusplus <= 201703L
				//C++17 以降
				return STDFSYS::file_size(m_filepath.c_str());

			#else
				//C++17以前
				#if defined(_WIN64)
					//Windows
					uint64_t ret_ = 0;
					HANDLE hFile = CreateFileW(reinterpret_cast<LPCWSTR>(m_filepath.c_wcstr()), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

					if(hFile == INVALID_HANDLE_VALUE)
					{
						//0返却
						return 0;
					};

					//名前空間無しの印として::を付与
					ret_ = ::GetFileSize(hFile, nullptr);
					if( ret_ == INVALID_FILE_SIZE)
					{
						//0返却
						return 0;
					};

					CloseHandle(hFile);

					return ret_;

				#elif defined(__linux__)
					//linux

				#endif

#endif
		};

		//シーク位置を最初に移動します。
		void SonikFileSystemController::SeekPointSet_Top(void)
		{
			fseek(m_file, 0, SEEK_SET);
		};

		//シーク位置を最後に移動します。
		void SonikFileSystemController::SeekPointSet_End(void)
		{
			fseek(m_file, 0, SEEK_END);
		};

		//現在ンお読み込みシーク位置から指定バイト数分移動します。
		void SonikFileSystemController::SeekPointSet_Point(uint64_t _offset_)
		{
			fseek(m_file, _offset_, SEEK_CUR);
		};

		//現在のシーク位置を取得します。
		uint64_t SonikFileSystemController::SeekPointGet(void)
		{
			fflush(m_file);
			return static_cast<uint64_t>(ftell(m_file));
		};

		//指定したサイズ文読み込みます。
		void SonikFileSystemController::Read(char* _buffer_, uint64_t _size_)
		{
			fread(_buffer_, sizeof(char), _size_, m_file);
		};

		//バイナリデータ書き込み用 4バイト配列をreinterpretで渡している場合はblocksizeはsizeof(uint32_t)等...。
		void SonikFileSystemController::Write(char* _writevalue_, uint32_t _writesize_, uint32_t _writeblocksize_)
		{
			fwrite(_writevalue_, _writesize_, _writeblocksize_, m_file);
		};

		//SonikStringの吐き出し方法で分けています。
		//テキストモードでオープンした状態だとファイル内の文字のエンコーディングがUTF-8に代わるといったことはありません。
		//バイナリで、追記以外...つまりすべての文字を再出力..となった場合は変換されるかもしれません。
		void SonikFileSystemController::Write_char(SonikLib::SonikString& _writevalue_)
		{
			_writevalue_.c_str();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.c_str(), l_writesize, 1, m_file);
		};

		void SonikFileSystemController::Write_UTF8(SonikLib::SonikString& _writevalue_)
		{
			_writevalue_.utf8_str();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.utf8_str(), l_writesize, 1, m_file);
		};

		void SonikFileSystemController::Write_UTF16(SonikLib::SonikString& _writevalue_)
		{
			_writevalue_.c_wcstr();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.c_wcstr(), l_writesize, 1, m_file);
		};

		//テキストモード専用　指定された行数文TEXTを読み込みます。
		void SonikFileSystemController::ReadText_Line(SonikLib::SonikString& _str_, uint64_t GetRowCnt)
		{
			if( ( (static_cast<uint32_t>(m_openmode) & 0x620000) >> 16) == 0x62)
			{
				//バイナリモードなので終了
				return;
			};

			char lbuf[500];
			_str_ = "";
			char* lp_buf = nullptr;

			for(uint64_t i = 0; i < GetRowCnt; ++i)
			{
				while(lp_buf != nullptr)
				{
					lp_buf = fgets(lbuf, sizeof(lbuf), m_file);
					_str_ += lbuf;

					if(strchr(lbuf, '\n') != nullptr)
					{
						break;
					};
				};

				if(lp_buf == nullptr)
				{
					break;
				};
			};

		};

		//テキストモード専用　指定された行数文TEXTを読み込ます。改行は削除され、改行で分割されたQueueとして取得します。
		void SonikFileSystemController::ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikString>& _GetLineQueue_, uint64_t GetRowCnt)
		{
			if( ( (static_cast<uint32_t>(m_openmode) & 0x620000) >> 16) == 0x62)
			{
				//バイナリモードなので終了
				return;
			};

			char lbuf[500];
			SonikString _str_ = "";
			char* lp_buf = nullptr;

			for(uint64_t i = 0; i < GetRowCnt; ++i)
			{
				_str_ = "";

				while(lp_buf != nullptr)
				{
					lp_buf = fgets(lbuf, sizeof(lbuf), m_file);
					_str_ += lbuf;

					if(strchr(lbuf, '\n') != nullptr)
					{
						break;
					};
				};

				if(lp_buf == nullptr)
				{
					break;
				};

				_GetLineQueue_.EnQueue(_str_);

			};

		};

	}; // end namespace FileSystemControllers
}; // end namespace SonikLib



