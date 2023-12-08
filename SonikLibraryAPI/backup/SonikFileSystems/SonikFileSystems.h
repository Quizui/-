/*
 * SonikFileSystems.h
 *
 *  Created on: 2018/11/14
 *      Author: USER
 */

#ifndef SONIKFILESYSTEMS_H_
#define SONIKFILESYSTEMS_H_

#include "../SonikContainerUse.h"
#include "../SonikStringUse.h"
#include "../SonikSmartPointerUse.h"

namespace SonikLibFileSystemsControllers
{

	class SonikFileStreamController;
};


namespace SonikLibFileSystems
{
	typedef SonikLib::NormalSmtPtr<SonikLibFileSystemsControllers::SonikFileStreamController> SonikFileController;

	enum class FOTYPE
	{
		SonikFO_SJIS = 0x01,
		SonikFO_UTF16,
		SonikFO_UTF8
	};

	//指定したフォーマットでファイルを操作オブジェクトを生成します。
	bool CreateFileObject(SonikFileController& getfo_, const char* FilePath, FOTYPE CreateType);

	//c:指定したフォルダにあるファイル数を取得します。
	unsigned long GetDirectoryInFileCount(const char* Dir_Path);

	//c:指定したフォルダにあるファイル名を列挙します。
	bool GetDirectoryInFileNameEnumeration(const char* Dir_Path, const char* SearchFileName, SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& retEnums);

};



#endif /* SONIKFILESYSTEMS_H_ */
