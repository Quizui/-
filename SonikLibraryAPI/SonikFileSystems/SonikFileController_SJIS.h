/*
 * SonikFileController_SJIS.h
 *
 *  Created on: 2018/11/20
 *      Author: SONIK
 */

#ifndef SONIKFILECONTROLLER_SJIS_H_
#define SONIKFILECONTROLLER_SJIS_H_

#include "SonikFileController.h"

namespace SonikLibFileSystemsControllers
{
#ifdef __SONIK_I686__

	class SonikFileStreamController_SJISMODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_SJISMODE(void);
		//デストラクタ
		~SonikFileStreamController_SJISMODE(void);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。
		bool ReadText_CHR(int8_t* buffer, uint32_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, uint32_t GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint32_t GetRowCnt =1);

	};

#elif defined(__SONIK_x86_64__)
	class SonikFileStreamController_SJISMODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_SJISMODE(void);
		//デストラクタ
		~SonikFileStreamController_SJISMODE(void);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。
		bool ReadText_CHR(int8_t* buffer, uint64_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, uint64_t GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint64_t GetRowCnt =1);

	};

#endif

};




#endif /* SONIKFILECONTROLLER_SJIS_H_ */
