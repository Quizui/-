/*
 * SonikFileController_SJIS.h
 *
 *  Created on: 2018/11/20
 *      Author: USER
 */

#ifndef SONIKFILECONTROLLER_SJIS_H_
#define SONIKFILECONTROLLER_SJIS_H_

#include "../SonikFileSystems/SonikFileController.h"

namespace SonikLibFileSystemsControllers
{
	class SonikFileStreamController_SJISMODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_SJISMODE(void);
		//デストラクタ
		~SonikFileStreamController_SJISMODE(void);

		//(テキストモード専用)指定した文字数分TEXTを読み込みます。
		bool ReadText_CHR(char* buffer, uint32_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, unsigned long GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, unsigned long GetRowCnt =1);

	};

};




#endif /* SONIKFILECONTROLLER_SJIS_H_ */
