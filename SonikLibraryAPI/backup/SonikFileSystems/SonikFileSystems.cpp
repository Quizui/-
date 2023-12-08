/*
 * SonikFileSystems.cpp
 *
 *  Created on: 2018/11/14
 *      Author: USER
 */

#include "../SonikFileSystems/SonikFileSystems.h"

#include "../SonikFileSystems/SonikFileController.h"
#include "../SonikFileSystems/SonikFileController_SJIS.h"
#include "../SonikFileSystems/SonikFileController_UTF16.h"
#include "../SonikFileSystems/SonikFileController_UTF8.h"


#if (WINVER >= 0x0600)
		//Windows処理
#include <windows.h>


#elif __linux__

#endif



namespace SonikLibFileSystems
{

	//指定したフォーマットでファイルを操作オブジェクトを生成します。
	bool CreateFileObject(SonikFileController& getfo_, const char* FilePath, FOTYPE CreateType)
	{
		SonikLibFileSystemsControllers::SonikFileStreamController* ptmp;

		switch(CreateType)
		{
		case FOTYPE::SonikFO_SJIS:
			ptmp = new(std::nothrow) SonikLibFileSystemsControllers::SonikFileStreamController_SJISMODE;
			if(ptmp == nullptr || ptmp == 0)
			{
				return false;
			};

			getfo_.ResetPointer(ptmp);

			break;

		case FOTYPE::SonikFO_UTF16:
			ptmp = new(std::nothrow) SonikLibFileSystemsControllers::SonikFileStreamController_UTF16MODE;
			if(ptmp == nullptr || ptmp == 0)
			{
				return false;
			};

			getfo_.ResetPointer(ptmp);

			break;

		case FOTYPE::SonikFO_UTF8:
			ptmp = new(std::nothrow) SonikLibFileSystemsControllers::SonikFileStreamController_UTF8MODE;
			if(ptmp == nullptr || ptmp == 0)
			{
				return false;
			};

			getfo_.ResetPointer(ptmp);

			break;

		default:

			return false;
		};

		return true;
	};


	//c:指定したフォルダにあるファイル数を取得します。
	unsigned long GetDirectoryInFileCount(const char* Dir_Path)
	{
		unsigned long cnt = 0;

#if (WINVER >= 0x0600)
		//Windows処理
#ifdef _WIN64
		bool redirections_ = false;
		void* oldval = nullptr;
		redirections_ = Wow64DisableWow64FsRedirection(&oldval);

#endif

		HANDLE handle_;
		WIN32_FIND_DATA fdata;

		handle_ = FindFirstFile(Dir_Path, &fdata);
		if(handle_ == INVALID_HANDLE_VALUE)
		{
			return 0xFFFFFFFF;
		};


		while( FindNextFile(handle_, &fdata) )
		{
			++cnt;
		};

		FindClose(handle_);

#ifdef _WIN64
		if(redirections_)
		{
			Wow64RevertWow64FsRedirection(oldval);
		};

#endif


#elif __linux__

#endif

		return cnt;
	};

	//c:指定したフォルダにあるファイル名を列挙します。
	bool GetDirectoryInFileNameEnumeration(const char* Dir_Path, const char* SearchFileName, SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& retEnums)
	{
		SonikLib::SonikString namestr;
#if (WINVER >= 0x0600)
		//Windows処理
#ifdef _WIN64
		bool redirections_ = false;
		void* oldval = nullptr;
		redirections_ = Wow64DisableWow64FsRedirection(&oldval);

#endif

		HANDLE handle_;
		WIN32_FIND_DATA fdata;

		namestr = Dir_Path;
		namestr += SearchFileName;

		handle_ = FindFirstFile(namestr.c_str(), &fdata);
		if(handle_ == INVALID_HANDLE_VALUE)
		{
			return false;
		};

		namestr = fdata.cFileName;
		retEnums.EnQueue(namestr);

		while( FindNextFile(handle_, &fdata) )
		{
			namestr = fdata.cFileName;
			retEnums.EnQueue(namestr);

		};

		FindClose(handle_);


#ifdef _WIN64
		if(redirections_)
		{
			Wow64RevertWow64FsRedirection(oldval);
		};

#endif


#elif __linux__

#endif


		return true;
	};


};


