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

#ifndef SONIKSTRING_SONIKDEFINITIONSTRING_H_
#define SONIKSTRING_SONIKDEFINITIONSTRING_H_

#if defined(SONIKSTRING_USED_UTF8)
	#if defined(SONIKSTRING_USED_UTF16) || defined(SONIKSTRING_USED_WIDE)
		//default
		#include "SonikString.h"
		namespace SonikLib
		{
			using MultiString = SonikLib::SonikString;
		};

	#else
		#include "./UTF8/SonikString_UTF8.h"
		namespace SonikLib
		{
			using MultiString = SonikLib::SonikString_UTF8;
		};

	#endif

#elif defined(SONIKSTRING_USED_UTF16)
	#if defined(SONIKSTRING_USED_UTF8) || defined(SONIKSTRING_USED_WIDE)
		#include "SonikString.h"
		namespace SonikLib
		{
			using MultiString = SonikLib::SonikString;
		};

	#else
		#include "./UTF16/SonikString_UTF16.h"
		namespace SonikLib
		{
			using MultiString = SonikLib::SonikString_UTF16;
		};

	#endif

#elif defined(SONIKSTRING_USED_WIDE)
		#include "./WIDE/SonikString_WIDE.h"
		namespace SonikLib
		{
			using MultiString = SonikLib::SonikString_WIDE;
		};

#else
	#include "SonikString.h"
	namespace SonikLib
	{
		using MultiString = SonikLib::SonikString;
	};

#endif

#endif /* SONIKSTRING_SONIKDEFINITIONSTRING_H_ */
