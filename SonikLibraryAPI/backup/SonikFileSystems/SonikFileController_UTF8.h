/*
 * SonikFileController_UTF8.h
 *
 *  Created on: 2018/11/20
 *      Author: USER
 */

#ifndef SONIKFILECONTROLLER_UTF8_H_
#define SONIKFILECONTROLLER_UTF8_H_


#include "../SonikFileSystems/SonikFileController.h"

namespace SonikLibFileSystemsControllers
{
	class SonikFileStreamController_UTF8MODE : public SonikFileStreamController
	{
	public:
		//コンストラクタ
		SonikFileStreamController_UTF8MODE(void);
		//デストラクタ
		~SonikFileStreamController_UTF8MODE(void);

		//FileOpen
		bool OpenFile(const char* OpenFilePathStr, SonikLibFileSystems::OpenMode mode);


		//(テキストモード専用)指定した文字数分TEXTを読み込みます。（最大char * 3倍 の容量が必要になります。)
		bool ReadText_CHR(char* buffer, uint32_t ReadSize);
		//(テキストモード専用)指定された行数分TEXTを読み込みます。(改行は削除されます。)
		bool ReadText_Line(SonikLib::SonikString& LineStr, unsigned long GetRowCnt = 1);
		//指定された行数分TEXTを読み込みます。改行は削除され、改行で分割されたQueueとして取得します。
		bool ReadText_LineQueue(SonikQueue::SonikAtomicQueue<SonikLib::SonikString>& LineStrQueue, unsigned long GetRowCnt =1);
	};

};




#endif /* SONIKFILECONTROLLER_UTF8_H_ */
