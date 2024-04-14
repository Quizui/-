/*
 * SonikDefinitionString.h
 *
 *  Created on: 2024/01/21
 *      Author: SONIC
 */

//一つのstring型で取得する文字列の型を変更したいときに使います。
//それぞれのstringを直接同時にincludeしても型が違うので競合はしません。
//そのため、例えばUTF-8を基準にしたいが、一部ではsjisで取りたい等あっても普通に別々include可能ですし、
//それぞれのクラスはdefinition_str()関数以外は「まったく機能が一緒」です。
//そのため普通にMultiString型として使えもしますが、静的ライブラリ等ではリンカ時にエラーの元になるので
//静的ライブラリとしてコンパイルするソースコードは基本型のSonikString型を直接使用するほうが良いです。

#ifndef __SONIKSTRING_SONIKSTRING_DEFINITION_H__
#define __SONIKSTRING_SONIKSTRING_DEFINITION_H__

#if WCHAR_MAX > 0xffffU
//wchar_t = ４byteとして扱う
	#if defined(SONIKSTRING_USED_UTF8)
		#if defined(SONIKSTRING_USED_UTF16) || defined(SONIKSTRING_USED_WIDE)
			//default
			#include "./Neutral/SonikString_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikString_CHR32;
			};


		#else
			#include "./UTF8/SonikStringUTF8_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringUTF8_CHR32;
			};

		#endif

	#elif defined(SONIKSTRING_USED_UTF16)
		#if defined(SONIKSTRING_USED_UTF8) || defined(SONIKSTRING_USED_WIDE)
			#include "./Neutral/SonikString_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikString_CHR32;
			};

		#else
			#include "./UTF16/SonikStringUTF16_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringUTF16_CHR32;
			};

		#endif

	#elif defined(SONIKSTRING_USED_WIDE)
			#include "./WIDE/SonikStringWIDE_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringWIDE_CHR32;
			};

	#else
		#include "./Neutral/SonikString_CHR32.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikString_CHR32;
			};

	#endif

#else
//それ以外は2Byte============================================
	#if defined(SONIKSTRING_USED_UTF8)
		#if defined(SONIKSTRING_USED_UTF16) || defined(SONIKSTRING_USED_WIDE)
			//default
			#include "./Neutral/SonikString_CHR16.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikString_CHR16;
			};


		#else
			#include "./UTF8/SonikStringUTF8_CHR16.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringUTF8_CHR16;
			};

		#endif

	#elif defined(SONIKSTRING_USED_UTF16)
		#if defined(SONIKSTRING_USED_UTF8) || defined(SONIKSTRING_USED_WIDE)
			#include "./Neutral/SonikString_CHR16.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikString_CHR16;
			};

		#else
			#include "./UTF16/SonikStringUTF16_CHR16.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringUTF16_CHR16;
			};

		#endif

	#elif defined(SONIKSTRING_USED_WIDE)
			#include "./WIDE/SonikStringWIDE_CHR16.h"
			namespace SonikLib
			{
				using SonikString = SonikLib::SonikStringWIDE_CHR16;
			};

	#else
		#include "./Neutral/SonikString_CHR16.h"
			namespace SonikLib
			{
			using SonikString = SonikLib::SonikString_CHR16;
			};

	#endif

#endif


#endif /* __SONIKSTRING_SONIKSTRING_DEFINITION_H__ */
