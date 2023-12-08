/*
 * SonikFileSystems.h
 *
 *  Created on: 2018/11/14
 *      Author: SONIK
 */

#ifndef SONIKFILESYSTEMS_H_
#define SONIKFILESYSTEMS_H_

#include "../Container/SonikAtomicQueue.hpp"
#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../SonikString/SonikString.h"

namespace SonikLibFileSystemsControllers
{

	class SonikFileStreamController;
};


namespace SonikLibFileSystems
{
	typedef SonikLib::NormalSmtPtr<SonikLibFileSystemsControllers::SonikFileStreamController> SonikFileController;

	enum class FOTYPE
	{
		SONIKFO_SJIS = 0x01,
		SONIKFO_UTF16,
		SONIKFO_UTF8
	};

	//指定したフォーマットでファイルを操作オブジェクトを生成します。
	bool CreateFileObject(SonikFileController& getfo_, const char* FilePath, FOTYPE CreateType);

	//c:指定したフォルダにあるファイル数を取得します。
	unsigned long GetDirectoryInFileCount(const char* Dir_Path, const char* FileName = nullptr);

	//c:指定したフォルダにあるファイル名を列挙します。
	bool GetDirectoryInFileNameEnumeration(const char* Dir_Path, const char* SearchFileName, SonikLib::SonikAtomicQueue<SonikLib::SonikString>& retEnums);

};



#endif /* SONIKFILESYSTEMS_H_ */
