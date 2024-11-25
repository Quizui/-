/*
 * SonikStringUTF16.h
 *
 *  Created on: 2016/01/10
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef __SONIKLIB_SONIKSTRING_UTF16_H__
#define __SONIKLIB_SONIKSTRING_UTF16_H__

#include "../SonikStringBase.h"

//前方宣言===================================
namespace SonikLib
{
	namespace Container
	{
		template <class T>
		class SonikVariableArrayContainer;
	};

	class SonikString;
	class SonikStringWIDE;
	class SonikStringUTF8;
};
//=========================================


namespace SonikLib
{
	class SonikStringUTF16 : public BASED_STRINGCLASS_SONIKLIB::SonikStringBase
	{
		friend class SonikString;
		friend class SonikStringWIDE;
		friend class SonikStringUTF8;

	public:
		SonikStringUTF16(SonikLibStringConvert::SonikLibConvertLocale _setlocale_ = SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
		SonikStringUTF16(const SonikStringUTF16& t_his);
		SonikStringUTF16(const SonikString& t_his);
		SonikStringUTF16(const SonikStringWIDE& t_his);
		SonikStringUTF16(const SonikStringUTF8& t_his);
		SonikStringUTF16(const char* SetStr);
		SonikStringUTF16(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16(const char16_t* SetStr);
		SonikStringUTF16(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16(const wchar_t* SetStr);
		SonikStringUTF16(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		SonikStringUTF16(const utf8_t* SetStr);
		SonikStringUTF16(const utf8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const int8_t SetValue);
		SonikStringUTF16(const int8_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const uint8_t SetValue);
		SonikStringUTF16(const uint8_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const int16_t SetValue);
		SonikStringUTF16(const int16_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const uint16_t SetValue);
		SonikStringUTF16(const uint16_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const int32_t SetValue);
		SonikStringUTF16(const int32_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const uint32_t SetValue);
		SonikStringUTF16(const uint32_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const int64_t SetValue);
		SonikStringUTF16(const int64_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const uint64_t SetValue);
		SonikStringUTF16(const uint64_t SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const float SetValue);
		SonikStringUTF16(const float SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
        SonikStringUTF16(const double SetValue);
		SonikStringUTF16(const double SetValue, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);

		~SonikStringUTF16(void);

		//define切り替えのStrCopy
		const char16_t* definition_str(void);

		//define切り替えのStrCopy
		uint64_t GetCpy_str_definition(char16_t* dstBuffer = nullptr);

		//指定したAsciiコードをデリミタとしてSplitを行います。
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF16>& Container);
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikString>& Container);
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringWIDE>& Container);
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF8>& Container);

		//各入力フォーマットから現在のバッファに変換して代入します。
		SonikStringUTF16& operator =(const SonikStringUTF16& t_his);
		SonikStringUTF16& operator =(const SonikString& t_his);
		SonikStringUTF16& operator =(const SonikStringWIDE& t_his);
		SonikStringUTF16& operator =(const SonikStringUTF8& t_his);
		SonikStringUTF16& operator =(SonikStringUTF16&& Move) noexcept;
		SonikStringUTF16& operator =(SonikString&& Move) noexcept;
		SonikStringUTF16& operator =(SonikStringWIDE&& Move) noexcept;
		SonikStringUTF16& operator =(SonikStringUTF8&& Move) noexcept;

		SonikStringUTF16& operator =(const char* Str);
		SonikStringUTF16& operator =(const char16_t* w_Str);
		SonikStringUTF16& operator =(const wchar_t* w_Str);
		SonikStringUTF16& operator =(const utf8_t* utf8_Str);
        SonikStringUTF16& operator =(const int8_t SetValue);
        SonikStringUTF16& operator =(const uint8_t SetValue);
        SonikStringUTF16& operator =(const int16_t SetValue);
        SonikStringUTF16& operator =(const uint16_t SetValue);
        SonikStringUTF16& operator =(const int32_t SetValue);
        SonikStringUTF16& operator =(const uint32_t SetValue);
        SonikStringUTF16& operator =(const int64_t SetValue);
        SonikStringUTF16& operator =(const uint64_t SetValue);
        SonikStringUTF16& operator =(const float SetValue);
		SonikStringUTF16& operator =(const double SetValue);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16& operator +=(const SonikStringUTF16& t_his);
		SonikStringUTF16& operator +=(const SonikString& t_his);
		SonikStringUTF16& operator +=(const SonikStringWIDE& t_his);
		SonikStringUTF16& operator +=(const SonikStringUTF8& t_his);
		SonikStringUTF16& operator +=(const char* Str);
		SonikStringUTF16& operator +=(const char16_t* w_Str);
		SonikStringUTF16& operator +=(const wchar_t* w_Str);
		SonikStringUTF16& operator +=(const utf8_t* utf8_Str);
        SonikStringUTF16& operator +=(const int8_t SetValue);
        SonikStringUTF16& operator +=(const uint8_t SetValue);
        SonikStringUTF16& operator +=(const int16_t SetValue);
        SonikStringUTF16& operator +=(const uint16_t SetValue);
        SonikStringUTF16& operator +=(const int32_t SetValue);
        SonikStringUTF16& operator +=(const uint32_t SetValue);
        SonikStringUTF16& operator +=(const int64_t SetValue);
        SonikStringUTF16& operator +=(const uint64_t SetValue);
        SonikStringUTF16& operator +=(const float SetValue);
		SonikStringUTF16& operator +=(const double SetValue);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16 operator +(const SonikStringUTF16& t_his);
		SonikStringUTF16 operator +(const SonikString& t_his);
		SonikStringUTF16 operator +(const SonikStringWIDE& t_his);
		SonikStringUTF16 operator +(const SonikStringUTF8& t_his);
		SonikStringUTF16 operator +(const char* Str);
		SonikStringUTF16 operator +(const char16_t* w_Str);
		SonikStringUTF16 operator +(const wchar_t* w_Str);
		SonikStringUTF16 operator +(const utf8_t* utf8_Str);
        SonikStringUTF16 operator +(const int8_t SetValue);
        SonikStringUTF16 operator +(const uint8_t SetValue);
        SonikStringUTF16 operator +(const int16_t SetValue);
        SonikStringUTF16 operator +(const uint16_t SetValue);
        SonikStringUTF16 operator +(const int32_t SetValue);
        SonikStringUTF16 operator +(const uint32_t SetValue);
        SonikStringUTF16 operator +(const int64_t SetValue);
        SonikStringUTF16 operator +(const uint64_t SetValue);
        SonikStringUTF16 operator +(const float SetValue);
		SonikStringUTF16 operator +(const double SetValue);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikStringUTF16& t_his) const;
		bool operator ==(const SonikString& t_his) const;
		bool operator ==(const SonikStringWIDE& t_his) const;
		bool operator ==(const SonikStringUTF8& t_his) const;

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikStringUTF16& t_his) const;
		bool operator !=(const SonikString& t_his) const;
		bool operator !=(const SonikStringWIDE& t_his) const;
		bool operator !=(const SonikStringUTF8& t_his) const;

		//小なり
		bool operator <(const SonikStringUTF16& _Greater_) const;
		bool operator <(const SonikString& _Greater_) const;
		bool operator <(const SonikStringWIDE& _Greater_) const;
		bool operator <(const SonikStringUTF8& _Greater_) const;

		//大なり
		bool operator >(const SonikStringUTF16& _Less_) const;
		bool operator >(const SonikString& _Less_) const;
		bool operator >(const SonikStringWIDE& _Less_) const;
		bool operator >(const SonikStringUTF8& _Less_) const;

		//小なりイコール
		bool operator <=(const SonikStringUTF16& _GreaterEqual_) const;
		bool operator <=(const SonikString& _GreaterEqual_) const;
		bool operator <=(const SonikStringWIDE& _GreaterEqual_) const;
		bool operator <=(const SonikStringUTF8& _GreaterEqual_) const;

		//大なりイコール
		bool operator >=(const SonikStringUTF16& _LessEqual_) const;
		bool operator >=(const SonikString& _LessEqual_) const;
		bool operator >=(const SonikStringWIDE& _LessEqual_) const;
		bool operator >=(const SonikStringUTF8& _LessEqual_) const;

	};
	
};

#endif /* __SONIKLIB_SONIKSTRING_UTF16_H__ */
