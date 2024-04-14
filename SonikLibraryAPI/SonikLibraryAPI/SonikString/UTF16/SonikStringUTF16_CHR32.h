/*
 * SonikString.h
 *
 *  Created on: 2016/01/10
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef __SONIKLIB_SONIKSTRING_UTF16_CHR32_H__
#define __SONIKLIB_SONIKSTRING_UTF16_CHR32_H__

#include "../SonikStringLocaleEnmus.h"

//前方宣言===================================
namespace SonikLib
{
	namespace Container
	{
		template <class T>
		class SonikVariableArrayContainer;
	};
};
//=========================================


namespace SonikLib
{
	class SonikStringUTF16_CHR32
	{
		friend bool operator<(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
		friend bool operator>(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
		friend bool operator<=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
		friend bool operator>=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);

	private:
		class SonikStringUTF16_CHR32_pImpl;
		SonikStringUTF16_CHR32_pImpl* pImpl;

	public:
		SonikStringUTF16_CHR32(SonikLibStringConvert::SonikLibConvertLocale _setlocale_ = SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
		SonikStringUTF16_CHR32(const SonikStringUTF16_CHR32& t_his);
		SonikStringUTF16_CHR32(const char* SetStr);
		SonikStringUTF16_CHR32(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16_CHR32(const char16_t* SetStr);
		SonikStringUTF16_CHR32(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16_CHR32(const wchar_t* SetStr);
		SonikStringUTF16_CHR32(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16_CHR32(const int8_t* SetStr);
		SonikStringUTF16_CHR32(const int8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);

		~SonikStringUTF16_CHR32(void);

		//ロケールを設定します。
		bool SetStringLocale(SonikLibStringConvert::SonikLibConvertLocale _setlocale_);

		//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
		const char* str_c(void);
		//wchar_t形式に変換して取得します。(バッファタイプも書き換わります。)
		const wchar_t* str_wchar(void);
		//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
		const char16_t* str_utf16(void);
		//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
		const int8_t* str_utf8(void);

		//define切り替えのstrゲット
		const char16_t* definition_str(void);

		//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_c(char* dstBuffer = nullptr);
		//wchar_t形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_wcstr(wchar_t* dstBuffer = nullptr);
		//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_utf16(char16_t* dstBuffer = nullptr);
		//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
		//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
		uint64_t GetCpy_str_utf8(char* dstBuffer = nullptr);

		//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
		uint64_t Count_Byte_NotNull(void);
		//c:文字列数を取得します。（Null終端文字をカウントに含まない)
		uint64_t Count_Str_NotNull(void);

		//文字列中の全角英数字を半角英数字に変換します。
		bool ConvertFWANtoHWAN(void);
		//文字列中の全角カナを半角カナに変換します。
		bool ConvertFWKNtoHWKN(void);

		//c: 指定位置の文字を削除します。
		void EraseChar(uint64_t ChrPoint);
		//c: 指定の開始位置から指定された文字数を削除します。
		void EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint);

		//指定したAsciiコードをデリミタとしてSplitを行います。
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF16_CHR32>& Container);

		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikStringUTF16_CHR32& operator =(const SonikStringUTF16_CHR32& t_his);
		SonikStringUTF16_CHR32& operator =(SonikStringUTF16_CHR32&& Move) noexcept;
		SonikStringUTF16_CHR32& operator =(const char* Str);
		SonikStringUTF16_CHR32& operator =(const char16_t* w_Str);
		SonikStringUTF16_CHR32& operator =(const wchar_t* w_Str);
		SonikStringUTF16_CHR32& operator =(const int8_t* utf8_Str);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16_CHR32& operator +=(const SonikStringUTF16_CHR32& t_his);
		SonikStringUTF16_CHR32& operator +=(const char* Str);
		SonikStringUTF16_CHR32& operator +=(const char16_t* w_Str);
		SonikStringUTF16_CHR32& operator +=(const wchar_t* w_Str);
		SonikStringUTF16_CHR32& operator +=(const int8_t* utf8_Str);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16_CHR32 operator +(const SonikStringUTF16_CHR32& t_his);
		SonikStringUTF16_CHR32 operator +(const char* Str);
		SonikStringUTF16_CHR32 operator +(const char16_t* w_Str);
		SonikStringUTF16_CHR32 operator +(const wchar_t* w_Str);
		SonikStringUTF16_CHR32 operator +(const int8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikStringUTF16_CHR32& t_his);
		bool operator ==(const char* Str);
		bool operator ==(const char16_t* w_Str);
		bool operator ==(const wchar_t* w_Str);
		bool operator ==(const int8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikStringUTF16_CHR32& t_his);
		bool operator !=(const char* Str);
		bool operator !=(const char16_t* w_Str);
		bool operator !=(const wchar_t* w_Str);
		bool operator !=(const int8_t* utf8_Str);

	};

	//c:比較演算子
	bool operator<(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
	bool operator>(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
	bool operator<=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
	bool operator>=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val);
};

#endif /* __SONIKLIB_SONIKSTRING_UTF16_CHR32_H__ */