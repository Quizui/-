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
        class SonikFileSystemController::InnerFileSystemFunction
        {
            public:
            FILE* m_file;
            SonikLib::SonikString m_filepath;

            public:
                InnerFileSystemFunction(void);
                ~InnerFileSystemFunction(void);

                //Open成功中に呼ばれる関数
                void OpenFunction_CloseFile(void);
                uint64_t OpenFunction_GetFileSize(void);
                void OpenFunction_SeekPointSet_Top(void);
                void OpenFunction_SeekPointSet_End(void);
                void OpenFunction_SeekPointSet_Point(uint64_t);
                uint64_t OpenFunction_SeekPointGet(void);
                void OpenFunction_Read(char*, uint64_t);
                void OpenFunction_Write(char*, uint32_t, uint32_t);
                void OpenFunction_Write_char(SonikLib::SonikString&);
                void OpenFunction_Write_UTF8(SonikLib::SonikString&);
                void OpenFunction_Write_UTF16(SonikLib::SonikString&);
                void OpenFunction_ReadText_Line(SonikLib::SonikString&, uint64_t);
                void OpenFunction_ReadText_LineQueue(SonikLib::Container::SonikAtomicQueue<SonikString>&, uint64_t);
            
                //Close中に呼ばれる関数
                void NoOpenFunction_CloseFile(void);
                uint64_t NoOpenFunction_GetFileSize(void);
                void NoOpenFunction_SeekPointSet_Top(void);
                void NoOpenFunction_SeekPointSet_End(void);
                void NoOpenFunction_SeekPointSet_Point(uint64_t);
                uint64_t NoOpenFunction_SeekPointGet(void);
                void NoOpenFunction_Read(char*, uint64_t);
                void NoOpenFunction_Write(char*, uint32_t, uint32_t);
                void NoOpenFunction_Write_char(SonikLib::SonikString&);
                void NoOpenFunction_Write_UTF8(SonikLib::SonikString&);
                void NoOpenFunction_Write_UTF16(SonikLib::SonikString&);
                void NoOpenFunction_ReadText_Line(SonikLib::SonikString&, uint64_t);
                void NoOpenFunction_ReadText_LineQueue(SonikLib::Container::SonikAtomicQueue<SonikString>&, uint64_t);

        };

        SonikFileSystemController::InnerFileSystemFunction::InnerFileSystemFunction(void)
        :m_file(nullptr)
        {

        };
        SonikFileSystemController::InnerFileSystemFunction::~InnerFileSystemFunction(void)
        {

        };

        //Open成功中に呼ばれる関数
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_CloseFile(void)
        {

        };
        uint64_t SonikFileSystemController::InnerFileSystemFunction::OpenFunction_GetFileSize(void)
        {
            #if ___cplusplus <= 201703L
				//C++17 以降
                std::error_code l_ec;
				return STDFSYS::file_size(m_filepath.str_c(), l_ec);
			#else
				//C++17以前
				#if defined(_WIN64)
					//Windows
					uint64_t ret_ = 0;
					HANDLE hFile = CreateFileW(reinterpret_cast<LPCWSTR>(m_filepath.c_wcstr()), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

					if(hFile == INVALID_HANDLE_VALUE)
					{
						//0返却
						return static_cast<uint64_t>(-1);
					};

					//名前空間無しの印として::を付与
					ret_ = ::GetFileSize(hFile, nullptr);
					if( ret_ == INVALID_FILE_SIZE)
					{
						//0返却
						return static_cast<uint64_t>(-1);
					};

					CloseHandle(hFile);

					return ret_;

				#elif defined(__linux__)
					//linux

				#endif
            #endif

        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_SeekPointSet_Top(void)
        {
            fseek(m_file, 0, SEEK_SET);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_SeekPointSet_End(void)
        {
            fseek(m_file, 0, SEEK_END);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_SeekPointSet_Point(uint64_t _offset_)
        {
            fseek(m_file, _offset_, SEEK_CUR);
        };
        uint64_t SonikFileSystemController::InnerFileSystemFunction::OpenFunction_SeekPointGet(void)
        {
            fflush(m_file);
			return static_cast<uint64_t>(ftell(m_file));
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_Read(char* _buffer_, uint64_t _size_)
        {
            fread(_buffer_, sizeof(char), _size_, m_file);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_Write(char* _writevalue_, uint32_t _writesize_, uint32_t _writeblocksize_)
        {
			fwrite(_writevalue_, _writesize_, _writeblocksize_, m_file);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_Write_char(SonikLib::SonikString& _writevalue_)
        {
            _writevalue_.str_c();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.str_c(), l_writesize, 1, m_file);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_Write_UTF8(SonikLib::SonikString& _writevalue_)
        {
			_writevalue_.str_utf8();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.str_utf8(), l_writesize, 1, m_file);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_Write_UTF16(SonikLib::SonikString& _writevalue_)
        {
			_writevalue_.str_utf16();
			uint64_t l_writesize = _writevalue_.Count_Byte_NotNull();

			fwrite(_writevalue_.str_utf16(), l_writesize, 1, m_file);
        };
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_ReadText_Line(SonikLib::SonikString& _str_, uint64_t GetRowCnt)
        {
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
        void SonikFileSystemController::InnerFileSystemFunction::OpenFunction_ReadText_LineQueue(SonikLib::Container::SonikAtomicQueue<SonikString>& _GetLineQueue_, uint64_t GetRowCnt)
        {
			char lbuf[500];
			SonikLib::SonikString _str_ = "";
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
    
        //Close中に呼ばれる関数
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_CloseFile(void)
        {
            return;
        };
        uint64_t SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_GetFileSize(void)
        {
            return static_cast<uint64_t>(-1);
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Top(void)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_SeekPointSet_End(void)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Point(uint64_t)
        {
            return;
        };
        uint64_t SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_SeekPointGet(void)
        {
            return static_cast<uint64_t>(-1);
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_Read(char*, uint64_t)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_Write(char*, uint32_t, uint32_t)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_Write_char(SonikLib::SonikString&)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_Write_UTF8(SonikLib::SonikString&)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_Write_UTF16(SonikLib::SonikString&)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_ReadText_Line(SonikLib::SonikString&, uint64_t)
        {
            return;
        };
        void SonikFileSystemController::InnerFileSystemFunction::NoOpenFunction_ReadText_LineQueue(SonikLib::Container::SonikAtomicQueue<SonikString>&, uint64_t)
        {
            return;
        };




        //コンストラクタ
    	SonikFileSystemController::SonikFileSystemController(void)
        :mp_f_sys_func(nullptr)
		,m_openmode(FileSystem::OpenMode::OPEN_UNKNOWN)
        ,m_run_vv_func{&InnerFileSystemFunction::NoOpenFunction_CloseFile,
                       &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Top,
                       &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_End}
        ,m_run_u64v_func{&InnerFileSystemFunction::NoOpenFunction_GetFileSize,
                         &InnerFileSystemFunction::NoOpenFunction_SeekPointGet}
        ,m_run_vu64_func(&InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Point)
        ,m_run_read_func(&InnerFileSystemFunction::NoOpenFunction_Read)
        ,m_run_write_func(&InnerFileSystemFunction::NoOpenFunction_Write)
        ,m_run_writestr_func{&InnerFileSystemFunction::NoOpenFunction_Write_char,
                             &InnerFileSystemFunction::NoOpenFunction_Write_UTF8,
                             &InnerFileSystemFunction::NoOpenFunction_Write_UTF16}
        ,m_run_readline_func(&InnerFileSystemFunction::NoOpenFunction_ReadText_Line)
        ,m_run_rlqueue_func(&InnerFileSystemFunction::NoOpenFunction_ReadText_LineQueue)
        {

        };

    	//デストラクタ
    	SonikFileSystemController::~SonikFileSystemController(void)
        {
            CloseFile();
        };

        bool SonikFileSystemController::CreateFileController(SFileSystemController& _out_)
		{
			SonikFileSystemController* ptmp;
			ptmp = new(std::nothrow) SonikFileSystemController;
			if(ptmp == nullptr)
			{
				return false;
			};

            SonikFileSystemController::InnerFileSystemFunction* ptmp_inner;
            ptmp_inner = new(std::nothrow) SonikFileSystemController::InnerFileSystemFunction;
            if(ptmp_inner == nullptr)
            {
                delete ptmp;
                return false;
            };

            ptmp->mp_f_sys_func = ptmp_inner;

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
            (mp_f_sys_func->*m_run_vv_func[0])();
            m_run_vv_func[0] = &InnerFileSystemFunction::NoOpenFunction_CloseFile;
            m_run_vv_func[1] = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Top;
            m_run_vv_func[2] = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_End;
            m_run_u64v_func[0] = &InnerFileSystemFunction::NoOpenFunction_GetFileSize;
            m_run_u64v_func[1] = &InnerFileSystemFunction::NoOpenFunction_SeekPointGet;
            m_run_vu64_func = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Point;
            m_run_read_func = &InnerFileSystemFunction::NoOpenFunction_Read;
            m_run_write_func = &InnerFileSystemFunction::NoOpenFunction_Write;
            m_run_writestr_func[0] = &InnerFileSystemFunction::NoOpenFunction_Write_char;
            m_run_writestr_func[1] = &InnerFileSystemFunction::NoOpenFunction_Write_UTF8;
            m_run_writestr_func[2] = &InnerFileSystemFunction::NoOpenFunction_Write_UTF16;
            m_run_readline_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_Line;
            m_run_rlqueue_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_LineQueue;
            //======================================


			//ファイルよみこみ
			if(fopen_s(&mp_f_sys_func->m_file, _filepath_.str_c(), reinterpret_cast<char*>(&_mode_)) != 0)
			{
				//読み込み失敗。
				m_lock.unlock();
				return false;
			};

            m_run_vv_func[0] = &InnerFileSystemFunction::OpenFunction_CloseFile;
            m_run_vv_func[1] = &InnerFileSystemFunction::OpenFunction_SeekPointSet_Top;
            m_run_vv_func[2] = &InnerFileSystemFunction::OpenFunction_SeekPointSet_End;
            m_run_u64v_func[0] = &InnerFileSystemFunction::OpenFunction_GetFileSize;
            m_run_u64v_func[1] = &InnerFileSystemFunction::OpenFunction_SeekPointGet;
            m_run_vu64_func = &InnerFileSystemFunction::OpenFunction_SeekPointSet_Point;
            m_run_read_func = &InnerFileSystemFunction::OpenFunction_Read;
            m_run_write_func = &InnerFileSystemFunction::OpenFunction_Write;
            m_run_writestr_func[0] = &InnerFileSystemFunction::OpenFunction_Write_char;
            m_run_writestr_func[1] = &InnerFileSystemFunction::OpenFunction_Write_UTF8;
            m_run_writestr_func[2] = &InnerFileSystemFunction::OpenFunction_Write_UTF16;

            if( ( (static_cast<uint32_t>(m_openmode) & 0x620000) >> 16) == 0x62)
			{
				//バイナリモード終了関数設定
                m_run_readline_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_Line;
                m_run_rlqueue_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_LineQueue;
			}else
            {
                m_run_readline_func = &InnerFileSystemFunction::OpenFunction_ReadText_Line;
                m_run_rlqueue_func = &InnerFileSystemFunction::OpenFunction_ReadText_LineQueue;
            };

			mp_f_sys_func->m_filepath = _filepath_;
			m_lock.unlock();

			return true;
		};

		void SonikFileSystemController::CloseFile(void)
		{
            m_lock.lock();

            (mp_f_sys_func->*m_run_vv_func[0])();

            m_run_vv_func[0] = &InnerFileSystemFunction::NoOpenFunction_CloseFile;
            m_run_vv_func[1] = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Top;
            m_run_vv_func[2] = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_End;
            m_run_u64v_func[0] = &InnerFileSystemFunction::NoOpenFunction_GetFileSize;
            m_run_u64v_func[1] = &InnerFileSystemFunction::NoOpenFunction_SeekPointGet;
            m_run_vu64_func = &InnerFileSystemFunction::NoOpenFunction_SeekPointSet_Point;
            m_run_read_func = &InnerFileSystemFunction::NoOpenFunction_Read;
            m_run_write_func = &InnerFileSystemFunction::NoOpenFunction_Write;
            m_run_writestr_func[0] = &InnerFileSystemFunction::NoOpenFunction_Write_char;
            m_run_writestr_func[1] = &InnerFileSystemFunction::NoOpenFunction_Write_UTF8;
            m_run_writestr_func[2] = &InnerFileSystemFunction::NoOpenFunction_Write_UTF16;
            m_run_readline_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_Line;
            m_run_rlqueue_func = &InnerFileSystemFunction::NoOpenFunction_ReadText_LineQueue;

            m_lock.unlock();
		};

		//現在のファイルサイズの取得
		uint64_t SonikFileSystemController::GetFileSize(void)
		{
            m_lock.lock();

            uint64_t ret = (mp_f_sys_func->*m_run_u64v_func[0])();

            m_lock.unlock();

            return ret;
		};

		//シーク位置を最初に移動します。
		void SonikFileSystemController::SeekPointSet_Top(void)
		{
			m_lock.lock();
            (mp_f_sys_func->*m_run_vv_func[1])();
            m_lock.unlock();
		};

		//シーク位置を最後に移動します。
		void SonikFileSystemController::SeekPointSet_End(void)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_vv_func[2])();
            m_lock.unlock();

		};

		//現在の読み込みシーク位置から指定バイト数分移動します。
		void SonikFileSystemController::SeekPointSet_Point(uint64_t _offset_)
		{
			m_lock.lock();
            (mp_f_sys_func->*m_run_vu64_func)(_offset_);
            m_lock.unlock();
			
		};

		//現在のシーク位置を取得します。
		uint64_t SonikFileSystemController::SeekPointGet(void)
		{
            m_lock.lock();
            uint64_t ret = (mp_f_sys_func->*m_run_u64v_func[1])();
            m_lock.unlock();

            return ret;
		};

		//指定したサイズ文読み込みます。
		void SonikFileSystemController::Read(char* _buffer_, uint64_t _size_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_read_func)(_buffer_, _size_);
            m_lock.unlock();


		};

		//バイナリデータ書き込み用 4バイト配列をreinterpretで渡している場合はblocksizeはsizeof(uint32_t)等...。
		void SonikFileSystemController::Write(char* _writevalue_, uint32_t _writesize_, uint32_t _writeblocksize_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_write_func)(_writevalue_, _writesize_, _writeblocksize_);
            m_lock.unlock();

		};

		//SonikStringの吐き出し方法で分けています。
		//テキストモードでオープンした状態だとファイル内の文字のエンコーディングがUTF-8に代わるといったことはありません。
		//バイナリで、追記以外...つまりすべての文字を再出力..となった場合は変換されるかもしれません。
        void SonikFileSystemController::Write_char(SonikLib::SonikString _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[0])(_writevalue_);
            m_lock.unlock();

		};
		void SonikFileSystemController::Write_char(SonikLib::SonikString& _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[0])(_writevalue_);
            m_lock.unlock();

		};

		void SonikFileSystemController::Write_UTF8(SonikLib::SonikString _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[1])(_writevalue_);
            m_lock.unlock();

		};
		void SonikFileSystemController::Write_UTF8(SonikLib::SonikString& _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[1])(_writevalue_);
            m_lock.unlock();

		};

		void SonikFileSystemController::Write_UTF16(SonikLib::SonikString _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[2])(_writevalue_);
            m_lock.unlock();

		};
		void SonikFileSystemController::Write_UTF16(SonikLib::SonikString& _writevalue_)
		{
            m_lock.lock();
            (mp_f_sys_func->*m_run_writestr_func[2])(_writevalue_);
            m_lock.unlock();

		};

		//テキストモード専用　指定された行数文TEXTを読み込みます。
		void SonikFileSystemController::ReadText_Line(SonikLib::SonikString& _str_, uint64_t GetRowCnt)
		{
			m_lock.lock();
            (mp_f_sys_func->*m_run_readline_func)(_str_, GetRowCnt);
            m_lock.unlock();

		};

		//テキストモード専用　指定された行数文TEXTを読み込ます。改行は削除され、改行で分割されたQueueとして取得します。
		void SonikFileSystemController::ReadText_LineQueue(SonikLib::Container::SonikAtomicQueue<SonikString>& _GetLineQueue_, uint64_t GetRowCnt)
		{
			m_lock.lock();
            (mp_f_sys_func->*m_run_rlqueue_func)(_GetLineQueue_, GetRowCnt);
            m_lock.unlock();

		};

	}; // end namespace FileSystemControllers
}; // end namespace SonikLib



