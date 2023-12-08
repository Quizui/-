/*
 * SonikString.h
 *
 *  Created on: 2016/01/10
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef SONIKLIBSTRING_H_
#define SONIKLIBSTRING_H_

#include "SonikStringConvert.h"


namespace SonikLib
{

	class SonikString
	{
	private:
		class SonikString_pImpl;
		SonikString_pImpl* pImpl;

	public:
		SonikString(void);
		SonikString(const SonikString& t_his);
		SonikString(SonikString&& Move);

		~SonikString(void);

		//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* c_str(void);
		//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
		const wchar_t* c_wcstr(void);
		//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* utf8_str(void);

		//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		unsigned long GetCpy_c_str(char* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		unsigned long GetCpy_c_wcstr(wchar_t* dstBuffer = nullptr);
		//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		unsigned long GetCpy_utf8_str(char* dstBuffer = nullptr);

		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikString& operator =(const SonikString& t_his);
		SonikString& operator =(SonikString&& Move);
		SonikString& operator =(const char* Str);
		SonikString& operator =(const wchar_t* w_Str);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString& operator +=(const SonikString& t_his);
		SonikString& operator +=(const char* Str);
		SonikString& operator +=(const wchar_t* w_Str);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString operator +(const SonikString& t_his);
		SonikString operator +(const char* Str);
		SonikString operator +(const wchar_t* w_Str);

	};

};



#endif /* SONIKLIBSTRING_H_ */
