/*
 * SonikFileController_UTF16.h
 *
 *  Created on: 2018/11/20
 *      Author: SONIK
 */

#ifndef SONIKFILECONTROLLER_UTF16_H_
#define SONIKFILECONTROLLER_UTF16_H_

#include "SonikFileController.h"

namespace SonikLibFileSystemsControllers
{
#ifdef __SONIK_I686__
	class SonikFileStreamController_UTF16MODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_UTF16MODE(void);
		//デストラクタ
		~SonikFileStreamController_UTF16MODE(void);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。（wchar_t型に変換されるのでcharの配列サイズは2倍確保してください)
		bool ReadText_CHR(int8_t* buffer, uint32_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, uint32_t GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint32_t GetRowCnt =1);

	};

#elif defined(__SONIK_x86_64__)
	class SonikFileStreamController_UTF16MODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_UTF16MODE(void);
		//デストラクタ
		~SonikFileStreamController_UTF16MODE(void);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。（wchar_t型に変換されるのでcharの配列サイズは2倍確保してください)
		bool ReadText_CHR(int8_t* buffer, uint64_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, uint64_t GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, uint64_t GetRowCnt =1);

	};
#endif

};




#endif /* SONIKFILECONTROLLER_UTF16_H_ */
