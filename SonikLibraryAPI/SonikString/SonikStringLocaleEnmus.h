/*
 * SonikStringLocaleEnmus.h
 *
 *  Created on: 2024/04/07
 *      Author: SONIC
 */

#ifndef SONIKSTRING_SONIKSTRINGLOCALEENMUS_H_
#define SONIKSTRING_SONIKSTRINGLOCALEENMUS_H_

#include <stdint.h>

namespace SonikLibStringConvert
{
	//ロケール設定用定数
	enum class SonikLibConvertLocale: uint32_t
	{
		LC_DEFAULT_C,	//default C -> "C"
		LC_JPN,				//Japanese -> "ja_JP"
		LC_JPNUTF8,		//Japanese_UTF8 -> "jp_JP.UTF-8"
		LC_ENGUS,			//English_US -> "en_US"
		LC_ENGGB,			//English_GB -> "en_GB"
		LC_FRNCE,			//France -> "fr_FR"
		LC_GERMANY,		//GERMANY -> "de_DE" ※ドイツ
	};
};


#endif /* SONIKSTRING_SONIKSTRINGLOCALEENMUS_H_ */
