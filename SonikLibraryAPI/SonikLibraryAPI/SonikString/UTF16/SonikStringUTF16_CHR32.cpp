/*
 * SonikString_x64.cpp
 *
 *  Created on: 2019/02/10
 *      Author: SONIK
 */

#include <new>
#include <algorithm>
#include <string>
#include <locale.h>
#include <stdint.h>
#include "../../SonikCAS/SonikAtomicLock.h"
#include "../../MathBit/MathBit.h"
#include "../SonikStringConvert.h"
#include "../../Container/RangedForContainer.hpp"
#include "SonikStringUTF16_CHR32.h"

namespace SonikLib
{
	//UTF8, UTF16, SJISが扱えるstringクラスです。
	//c:処理自体はスレッドセーフですが、文字列をgetした後にバッファを書き換えられる恐れがあります。
	class SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl
	{
	private:
		//c:文字列領域
		int8_t* Stringval_;

		//文字コンバートに使う基準ロケール
		char* m_locale;

		//c:格納している最大文字数
		uint64_t MaxLength_;

		//c:現在の文字列のタイプ
		SonikLibConvertType CType;
		//c:文字列領域のサイズ
		uint64_t buffer_;
		//c:マルチスレッドブロック
		SonikLib::S_CAS::SonikAtomicLock string_atm_lock;
		//c:マルチスレッドブロック（オペレータ)
		SonikLib::S_CAS::SonikAtomicLock string_operator_lock;

	private:
		//c:内部用リサイズ関数です。
		bool ReAlloc(uint64_t ReSize);

		//c:現在のバッファタイプを指定のバッファタイプに変更します。
		//c:変更の際に、バッファに対して変換作業が行われます。
		//c:変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
		//SCHTYPE_UNKNOWNを指定した場合は、必ずfalseとなります。
		bool SetCharacterType(SonikLibConvertType SetType);

	public:
		//c:コンストラクタ
		SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		//c:コンストラクタオーバーロード
		SonikStringUTF16_CHR32_pImpl(const char* SetStr);
		SonikStringUTF16_CHR32_pImpl(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		//c:コンストラクタオーバーロード
		SonikStringUTF16_CHR32_pImpl(const char16_t* SetStr);
		SonikStringUTF16_CHR32_pImpl(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		//c:コンストラクタオーバーロード
		SonikStringUTF16_CHR32_pImpl(const wchar_t* SetStr);
		SonikStringUTF16_CHR32_pImpl(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);
		//コンストラクタオーバーロード
		SonikStringUTF16_CHR32_pImpl(const int8_t* SetStr);
		SonikStringUTF16_CHR32_pImpl(const int8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_);

		//c:コピーコンストラクタ
		SonikStringUTF16_CHR32_pImpl(const SonikStringUTF16_CHR32_pImpl& t_his);

		//c:デストラクタ
		~SonikStringUTF16_CHR32_pImpl(void);

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

		//c: 文字列中の全角英数字を半角英数字に変換します。
		bool ConvertFWANtoHWAN(void);
		//c: 文字列中の全角カナを半角カナに変換します。
		bool ConvertFWKNtoHWKN(void);

		//c: 指定位置の文字を削除します。
		void EraseChar(uint64_t ChrPoint);
		//c: 指定の開始位置から指定された文字数を削除します。
		void EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint);

		//c: 指定したAsciiコードをデリミタとしてSplitを行います。
		bool SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF16_CHR32>& Container);

		//c: 各入力フォーマットから現在のバッファに変換して代入します。
		SonikStringUTF16_CHR32_pImpl& operator =(const SonikStringUTF16_CHR32_pImpl& t_his);
		SonikStringUTF16_CHR32_pImpl& operator =(SonikStringUTF16_CHR32_pImpl&& Move) noexcept;
		SonikStringUTF16_CHR32_pImpl& operator =(const char* Str);
		SonikStringUTF16_CHR32_pImpl& operator =(const char16_t* w_Str);
		SonikStringUTF16_CHR32_pImpl& operator =(const wchar_t* w_Str);
		SonikStringUTF16_CHR32_pImpl& operator =(const int8_t* utf8_Str);


		//c: 各入力フォーマットから現在のバッファに変換して結合します。
		//c: コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16_CHR32_pImpl& operator +=(const SonikStringUTF16_CHR32_pImpl& t_his);
		SonikStringUTF16_CHR32_pImpl& operator +=(const char* Str);
		SonikStringUTF16_CHR32_pImpl& operator +=(const char16_t* w_Str);
		SonikStringUTF16_CHR32_pImpl& operator +=(const wchar_t* w_Str);
		SonikStringUTF16_CHR32_pImpl& operator +=(const int8_t* utf8_Str);

		//c: 現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//c: コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikStringUTF16_CHR32_pImpl operator +(const SonikStringUTF16_CHR32_pImpl& t_his);
		SonikStringUTF16_CHR32_pImpl operator +(const char* Str);
		SonikStringUTF16_CHR32_pImpl operator +(const char16_t* w_Str);
		SonikStringUTF16_CHR32_pImpl operator +(const wchar_t* w_Str);
		SonikStringUTF16_CHR32_pImpl operator +(const int8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 一致の場合true 不一致の場合 falseを返却します。
		bool operator ==(const SonikStringUTF16_CHR32_pImpl& t_his) ;
		bool operator ==(const char* Str);
		bool operator ==(const char16_t* w_Str);
		bool operator ==(const wchar_t* w_Str);
		bool operator ==(const int8_t* utf8_Str);

		//c: 文字列同士を比較します。(strcmp)
		//c: 不一致の場合true　一致の場合 falseを返却します。
		bool operator !=(const SonikStringUTF16_CHR32_pImpl& t_his);
		bool operator !=(const char* Str);
		bool operator !=(const char16_t* w_Str);
		bool operator !=(const wchar_t* w_Str);
		bool operator !=(const int8_t* utf8_Str);

		//c:比較演算子
		bool Greater(const char* CompareArg2val);
		bool Less(const char* CompareArg2val);
		bool GreaterEqual(const char* CompareArg2val);
		bool LessEqual(const char* CompareArg2val);

	};


	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_NULLTEXT)
	,buffer_(100)
	{
		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
			if(  l_size == 0)
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, _setlocale_);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;

		};

		std::fill_n(Stringval_, buffer_, 0);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const char* SetStr)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_NULLTEXT)
	,buffer_(100)
	{
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(SetStr);

		//NULL文字文追加(+1)して格納
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(SetStr) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			if(  l_size == 0 )
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;

		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		CType = tmpType;
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_NULLTEXT)
	,buffer_(100)
	{
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(SetStr);

		//NULL文字文追加(+1)して格納
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(SetStr) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
			if(  l_size == 0)
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, _setlocale_);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;

		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		CType = tmpType;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const char16_t* SetStr)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF16)
	,buffer_(100)
	{
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(SetStr) + 2; //Null文字分 shortサイズ分追加。

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			if(  l_size == 0 )
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF16)
	,buffer_(100)
	{
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(SetStr) + 2; //Null文字分 shortサイズ分追加。

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
			if(  l_size == 0)
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, _setlocale_);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const wchar_t* SetStr)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF32)
	,buffer_(100)
	{
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char32_t*>(SetStr)) + 4; //Null文字分 longサイズ分追加。

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			if(  l_size == 0 )
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char32_t*>(Stringval_));
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF32)
	,buffer_(100)
	{
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char32_t*>(SetStr)) + 4; //Null文字分 longサイズ分追加。

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
			if(  l_size == 0)
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, _setlocale_);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char32_t*>(Stringval_));
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const int8_t* SetStr)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF16)
	,buffer_(100)
	{
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(SetStr));

		//NULL文字文追加(+1)して格納
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(SetStr)) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			if(  l_size == 0 )
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		CType = tmpType;
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const int8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF16)
	,buffer_(100)
	{
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(SetStr));

		//NULL文字文追加(+1)して格納
		uint64_t SrcByte = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(SetStr)) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			uint32_t l_size = 0;
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
			if(  l_size == 0)
			{
				throw std::bad_alloc();
			};

			m_locale = new char[l_size];
			SonikLibStringConvert::ConvertLocaleCharacter(l_size, m_locale, _setlocale_);

			Stringval_ = new int8_t[buffer_];
		}catch(std::bad_alloc&)
		{
			delete[] m_locale;
			delete[] Stringval_;
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, SrcByte);
		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		CType = tmpType;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SonikStringUTF16_CHR32_pImpl(const SonikStringUTF16_CHR32_pImpl& t_his)
	:Stringval_(nullptr)
	,m_locale(nullptr)
	,MaxLength_(0)
	,CType(SCHTYPE_UTF16)
	,buffer_(100)
{
		uint32_t localesize = strlen(t_his.m_locale);
		try
		{
			m_locale = new char[localesize];
			Stringval_ = new int8_t[t_his.buffer_];
		}catch(std::bad_alloc& e)
		{
			delete m_locale;
			delete[] Stringval_;
			throw std::bad_alloc(e);
		};

		buffer_ = t_his.buffer_;
		CType = t_his.CType;
		MaxLength_ = t_his.MaxLength_;

		memcpy_s(m_locale, localesize, t_his.m_locale, localesize);
		memcpy_s(Stringval_, buffer_, t_his.Stringval_, buffer_);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::~SonikStringUTF16_CHR32_pImpl(void)
	{
		if(m_locale != 0)
		{
			delete[] m_locale;
		};
		if(Stringval_ != 0)
		{
			delete[] Stringval_;
		};
	};

	//現在のバッファタイプを指定のバッファタイプに変更します。
	//変更の際に、バッファに対して変換作業が行われます。
	//変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SetCharacterType(SonikLibConvertType SetType)
	{
		string_atm_lock.lock();

		uint64_t convSize_ = 0;
//		unsigned long bufsize_ = SonikLibStringConvert::GetStringLength(reinterpret_cast<char*>(Stringval_));
		switch(CType)
		{
		case SCHTYPE_SJIS:
			//SJIS から SetType へ各変換
			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//SJISへの変換は行わない。行う必要がない
				string_atm_lock.unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16への変換
				SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), nullptr, &convSize_, m_locale);

				if( convSize_ > buffer_ )
				{
					if( !this->ReAlloc( convSize_ ) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char16_t*>(Stringval_), nullptr, m_locale) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//SJISからUTF8への変換を行う。
				SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), nullptr, &convSize_, m_locale);

				if( convSize_ > buffer_ )
				{
					if( !this->ReAlloc( convSize_ ) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), nullptr, m_locale) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定
				break;
			};

			break;

		case SCHTYPE_UTF16:
			//UTF16  から SetType へ各変換
			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//UTF16からSJISへの変換
				SonikLibStringConvert::ConvertUTF16toMBS(reinterpret_cast<char16_t*>(Stringval_), nullptr, &convSize_, m_locale);

//				if( (convSize_ & 0x01) == 1 )
//				{
//					++convSize_;
//				};

				if( convSize_ > buffer_ )
				{
					if( !this->ReAlloc(convSize_) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				//convSize_ = buffer_ << 1; // x * 2 = x << 1
				if( !SonikLibStringConvert::ConvertUTF16toMBS(reinterpret_cast<char16_t*>(Stringval_), reinterpret_cast<char*>(Stringval_), nullptr, m_locale) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16 から UTF16への変換は行わない。行う必要がない。

				string_atm_lock.unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//UTF16 から UTF8への変換
				SonikLibStringConvert::ConvertUTF16ToUTF8(reinterpret_cast<char16_t*>(Stringval_), nullptr, &convSize_);

//				if( (convSize_ & 0x01) == 1 )
//				{
//					++convSize_;
//				};

				if( convSize_  > buffer_ )
				{
					if( !this->ReAlloc(convSize_) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF16ToUTF8(reinterpret_cast<char16_t*>(Stringval_), reinterpret_cast<char*>(Stringval_), nullptr) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;

				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				string_atm_lock.unlock();
				break;
			};

			break;

		case SCHTYPE_UTF8:

			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//UTF8からSJISへの変換
				SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), nullptr, &convSize_, m_locale);

//				if( (convSize_ & 0x01) == 1 )
//				{
//					++convSize_;
//				};

				if( convSize_ > buffer_ )
				{
					if( !this->ReAlloc(convSize_) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), nullptr, m_locale) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF8からUTF16へ変換
				SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), nullptr, &convSize_);

				if( convSize_ > buffer_ )
				{
					if( !this->ReAlloc(convSize_) )
					{
						string_atm_lock.unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char16_t*>(Stringval_), nullptr) )
				{
					string_atm_lock.unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.unlock();
				return true;

				break;

			case SCHTYPE_UTF8:
				//UTF8からUTF8へ変換は行わない。行う必要がない。

				string_atm_lock.unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				break;
			};

			break;

		case SCHTYPE_NULLTEXT:

			CType = SetType;
			string_atm_lock.unlock();
			break;

		default:
			//SCHTYPE_UNKNOWN判定

			break;
		};

		string_atm_lock.unlock();
		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::ReAlloc(uint64_t ReArraySize)
	{
		int8_t* pTmp = 0;

		pTmp = new(std::nothrow) int8_t[ReArraySize];
		if(pTmp == nullptr)
		{
			return false;
		};

		std::fill_n(pTmp, ReArraySize, 0);

		memcpy_s(pTmp, ReArraySize, Stringval_, buffer_);

		delete[] Stringval_;
		Stringval_ = pTmp;
		buffer_ = ReArraySize;

		return true;
	};

	//ロケールを設定します。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SetStringLocale(SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{

		string_atm_lock.lock();

		uint32_t  l_size = 0;
		SonikLibStringConvert::ConvertLocaleCharacter(l_size, nullptr, _setlocale_);
		if( l_size == 0 )
		{
			string_atm_lock.unlock();
			return false;
		};

		char* tmpbuffer = nullptr;
		try
		{
			tmpbuffer = new char[l_size];

		}catch(std::bad_alloc&)
		{
			string_atm_lock.unlock();
			return false;
		};

		 SonikLibStringConvert::ConvertLocaleCharacter(l_size, tmpbuffer, _setlocale_);

		 delete[] m_locale;
		 m_locale = tmpbuffer;

		string_atm_lock.unlock();
		return true;
	};

	const char* SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::str_c(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return "";
		};

		if( !this->SetCharacterType(SCHTYPE_SJIS) )
		{
			return "";
		};

		return reinterpret_cast<char*>(Stringval_);

	};

	//wchar_t形式に変換して取得します。(バッファタイプも書き換わります。)
	const wchar_t* SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::str_wchar(void)
	{
		if( CType == SCHTYPE_UNKNOWN )
		{
			return u"";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF32) )
		{
			return u"";
		};

		return reinterpret_cast<wchar_t*>(Stringval_);
	};

	const char16_t* SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::str_utf16(void)
	{
		if( CType == SCHTYPE_UNKNOWN )
		{
			return u"";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF16) )
		{
			return u"";
		};

		return reinterpret_cast<char16_t*>(Stringval_);

	};

	const int8_t* SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::str_utf8(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return reinterpret_cast<const int8_t*>("");
		};

		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return reinterpret_cast<const int8_t*>("");
		};

		return Stringval_;
	};

	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::GetCpy_str_c(char* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_SJIS)
		{
			//UNKNOWN以外　かつ SJIS以外ならSJISへ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_SJIS) )
			{
				return 0;
			};
		};

		//NULL文字分追加 (+1)して格納
		uint64_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_))  + 1;

		if(dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::GetCpy_str_wcstr(wchar_t* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_UTF32)
		{
			//UNKNOWN以外　かつ UTF16以外ならUTF16へ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_UTF32) )
			{
				return 0;
			};
		};

		//NULL文字分追加(wide = +2) して格納
		uint64_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char32_t*>(Stringval_)) + 4;

		if(dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::GetCpy_str_utf16(char16_t* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_UTF16)
		{
			//UNKNOWN以外　かつ UTF16以外ならUTF16へ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_UTF16) )
			{
				return 0;
			};
		};

		//NULL文字分追加(wide = +2) して格納
		uint64_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_)) + 2;

		if(dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::GetCpy_str_utf8(char* dstBuffer)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return 0;
		};

		if(CType != SCHTYPE_UTF8)
		{
			//UNKNOWN以外　かつ UTF8以外ならUTF8へ変換してカウントチェック
			if( !this->SetCharacterType(SCHTYPE_UTF8) )
			{
				return 0;
			};
		};

		//NULL文字分追加 (+1)して格納
		uint64_t cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_)) + 1;

		if(dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::Count_Byte_NotNull(void)
	{
		return SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
	};

	//c:文字列数を取得します。（Null終端文字をカウントに含まない)
	uint64_t SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::Count_Str_NotNull(void)
	{
		return MaxLength_;
	};

	//文字列中の全角英数字を半角英数字に変換します。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::ConvertFWANtoHWAN(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return false;
		};

		//全角半角変換はUTF-8しか作ってないのでUTF-8に一度変換する。
		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return false;
		};

		string_atm_lock.lock();
		//全角半角変換
		uint64_t Size = 0;
		//サイズ取得
		SonikLibStringConvert::ConvertUTF8FWCToHWCForAN(reinterpret_cast<char*>(Stringval_), nullptr, Size);
		//領域取得
		if( Size & 0x01 )
		{
			++Size;
		};

		int8_t* tmp_Str = new(std::nothrow) int8_t[Size];
		if( tmp_Str == nullptr )
		{
			string_atm_lock.unlock();
			return false;
		};

		//本番
		if( !SonikLibStringConvert::ConvertUTF8FWCToHWCForAN(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(tmp_Str), Size) )
		{
			string_atm_lock.unlock();
			return false;
		};

		delete Stringval_;
		Stringval_ = tmp_Str;

		if( buffer_ < Size )
		{
			buffer_ = Size;
		};

		string_atm_lock.unlock();
		return true;
	};

	//文字列中の全角カナを半角カナに変換します。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::ConvertFWKNtoHWKN(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return false;
		};

		//全角半角変換はUTF-8しか作ってないのでUTF-8に一度変換する。
		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return false;
		};

		string_atm_lock.lock();
		//全角半角変換
		uint64_t Size = 0;
		//サイズ取得
		SonikLibStringConvert::ConvertUTF8FWCToHWCForKANA(reinterpret_cast<char*>(Stringval_), nullptr, Size);
		//領域取得
		if( Size & 0x01 )
		{
			++Size;
		};

		int8_t* tmp_Str = new(std::nothrow) int8_t[Size];
		if( tmp_Str == nullptr )
		{
			string_atm_lock.unlock();
			return false;
		};

		//本番
		if( !SonikLibStringConvert::ConvertUTF8FWCToHWCForKANA(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(tmp_Str), Size) )
		{
			string_atm_lock.unlock();
			return false;
		};

		delete Stringval_;
		Stringval_ = reinterpret_cast<int8_t*>(tmp_Str);

		if( buffer_ < Size )
		{
			buffer_ = Size;
		};

		string_atm_lock.unlock();

		return true;
	};

	//c: 指定位置の文字を削除します。
	void SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::EraseChar(uint64_t ChrPoint)
	{
		this->str_utf8();

		if( SonikLibStringControl::StringPointEraser(reinterpret_cast<char*>(Stringval_), ChrPoint, 1, MaxLength_) )
		{
			MaxLength_ -= 1;
		};

	};

	//c: 指定の開始位置から指定された文字数を削除します。
	void SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint)
	{
		this->str_utf8();

		if( SonikLibStringControl::StringPointEraser(reinterpret_cast<char*>(Stringval_), ChrStartPoint, ChrEndPoint, MaxLength_) )
		{
			MaxLength_ -= ChrEndPoint;
		};
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF16_CHR32>& Container)
	{
		this->str_utf8();

		uint64_t bitcnt = 0;
		unsigned char swapbit = 0;
		uint8_t* pTmpstr = reinterpret_cast<uint8_t*>(Stringval_);
		uint8_t* pTmpstr_St = pTmpstr;
		SonikLib::SonikStringUTF16_CHR32 PushStr;
		while( (*pTmpstr) != 0x00 )
		{
			swapbit = SonikMathBit::BitSwapFor8bit((*pTmpstr));

			bitcnt =  ~(swapbit);

			bitcnt |= (bitcnt << 1);
			bitcnt |= (bitcnt << 2);
			bitcnt |= (bitcnt << 4);
			bitcnt |= (bitcnt << 8);
			bitcnt |= (bitcnt << 16);
			bitcnt |= (bitcnt << 32);

			bitcnt = (bitcnt & 0x5555555555555555) + ( (bitcnt >> 1) & 0x5555555555555555 );
			bitcnt = (bitcnt & 0x3333333333333333) + ( (bitcnt >> 2) & 0x3333333333333333 );
			bitcnt = (bitcnt & 0x0F0F0F0F0F0F0F0F) + ( (bitcnt >> 4) & 0x0F0F0F0F0F0F0F0F );
			bitcnt = (bitcnt & 0x00FF00FF00FF00FF) + ( (bitcnt >> 8) & 0x00FF00FF00FF00FF );
			bitcnt = (bitcnt & 0x0000FFFF0000FFFF) + ( (bitcnt >> 16) & 0x0000FFFF0000FFFF );

			bitcnt = (bitcnt & 0x00000000FFFFFFFF) + ( (bitcnt >> 32) & 0x00000000FFFFFFFF);
			bitcnt = (64 - bitcnt);

			if( bitcnt == 0 )
			{
				++bitcnt;
			};

			if( (*pTmpstr) == delim )
			{
				(*pTmpstr) = 0;
				PushStr = reinterpret_cast<char*>(pTmpstr_St);
				if( !Container.PushBack(PushStr) )
				{
					(*pTmpstr) = delim;
					return false;
				};

				(*pTmpstr) = delim;
				pTmpstr_St = pTmpstr;
				++pTmpstr_St;
			};

			pTmpstr += bitcnt;

		};

		PushStr = reinterpret_cast<char*>(pTmpstr_St);
		if( !Container.PushBack(PushStr) )
		{
			return false;
		};

		return true;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(const SonikStringUTF16_CHR32_pImpl& t_his)
	{

		if( this == &t_his )
		{
			return (*this);
		};

		int8_t* tmpbuffer = nullptr;
		try
		{
			tmpbuffer = new int8_t[ t_his.buffer_];

		}catch(std::bad_alloc&)
		{
			throw;
		};

		if( Stringval_ != 0 )
		{
			delete[] Stringval_;
		};

		Stringval_ = tmpbuffer;

		buffer_ = t_his.buffer_;
		CType = t_his.CType;
		MaxLength_ = t_his.MaxLength_;

		memcpy(Stringval_, t_his.Stringval_, buffer_);

		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(SonikStringUTF16_CHR32_pImpl&& Move) noexcept
	{
		if( this == &Move )
		{
			return (*this);
		};

		if( Stringval_ != 0 )
		{
			delete[] Stringval_;

		};

		buffer_ = std::move(Move.buffer_);
		CType = std::move(Move.CType);
		Stringval_ = std::move(Move.Stringval_);
		MaxLength_ = std::move(Move.MaxLength_);

		Move.CType = SonikLibConvertType::SCHTYPE_UNKNOWN;
		Move.Stringval_ = nullptr;
		Move.buffer_ = 0;

		return (*this);

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(const char* Str)
	{
		if(Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		uint64_t Size_ = SonikLibStringConvert::GetStringLengthByte(Str);
		if(buffer_ < (Size_ + 1))
		{
			//null終端分追加
			if(!this->ReAlloc( Size_ +1 ))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		std::fill_n(Stringval_, buffer_, 0);
		if( strcmp(Str, "") == 0 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.unlock();
			return (*this);
		};

		CType = SonikLibStringConvert::CheckConvertType(Str);

		memcpy_s(Stringval_, buffer_ , Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(const char16_t* w_Str)
	{
		if(w_Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		uint64_t Size_ = SonikLibStringConvert::GetStringLengthByte(w_Str) + 2;
		if(buffer_ < Size_)
		{
			//null終端分追加
			if(!this->ReAlloc( Size_ ))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		std::fill_n(Stringval_, buffer_, 0);
		if( (*w_Str) == 0x00 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.unlock();
			return (*this);
		};

		CType = SCHTYPE_UTF16;

		memcpy_s(Stringval_, buffer_, w_Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(const wchar_t* w_Str)
	{
		if(w_Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		uint64_t Size_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char32_t*>(w_Str)) + 4;
		if(buffer_ < Size_)
		{
			//null終端分追加
			if(!this->ReAlloc( Size_ ))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		std::fill_n(Stringval_, buffer_, 0);
		if( (*w_Str) == 0x00 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.unlock();
			return (*this);
		};

		CType = SCHTYPE_UTF16;

		memcpy_s(Stringval_, buffer_, w_Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char32_t*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator =(const int8_t* utf8_Str)
	{
		if(utf8_Str == nullptr )
		{
			return (*this);
		};

		string_operator_lock.lock();

		uint64_t Size_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(utf8_Str));
		if(buffer_ < (Size_ + 1))
		{
			//null終端分追加
			if(!this->ReAlloc( Size_ +1 ))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		std::fill_n(Stringval_, buffer_, 0);
		if( strcmp(reinterpret_cast<const char*>(utf8_Str), "") == 0 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.unlock();
			return (*this);
		};

		CType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(utf8_Str));

		memcpy_s(Stringval_, buffer_ , utf8_Str, Size_);

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +=(const SonikStringUTF16_CHR32_pImpl& t_his)
	{
		string_operator_lock.lock();

		if( t_his.CType == SCHTYPE_NULLTEXT || t_his.CType == SCHTYPE_UNKNOWN )
		{
			//c:結合を行わない
			string_operator_lock.unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != t_his.CType )
		{
			SetCharacterType(t_his.CType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint64_t CopySize_;
		uint64_t bufuse_;
		uint32_t sizeofsize_ = 0;
		if(t_his.CType == SCHTYPE_UTF16)
		{
			// >> 1 = x/2
			CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));
			bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));

			if( buffer_ < (CopySize_ + bufuse_ ))
			{
				if(!this->ReAlloc((CopySize_ + bufuse_) + 2))
				{
					string_operator_lock.unlock();
					throw std::bad_alloc();
				};
			};

			sizeofsize_ = 2;

		}else
		{

			CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
			bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

			if( buffer_ < (CopySize_ + bufuse_) + 1 )
			{
				if(!this->ReAlloc((CopySize_ + bufuse_) + 1))
				{
					string_operator_lock.unlock();
					throw std::bad_alloc();
				};
			};

			sizeofsize_ = 1;

		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + sizeofsize_), t_his.Stringval_, CopySize_);
		Stringval_[bufuse_ + CopySize_] = 0;

		if( CType == SCHTYPE_UTF16 )
		{
			MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));
		}else
		{
			MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		};

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +=(const char* Str)
	{
		string_operator_lock.lock();

		if(Str == nullptr)
		{
			string_operator_lock.unlock();
			return (*this);
		}

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(Str);

		if(tmpType == SCHTYPE_UTF16)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_operator_lock.unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint64_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(Str);
		uint64_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		if( (CopySize_ + bufuse_) + 1 > buffer_ )
		{
			if(!this->ReAlloc( (CopySize_ + bufuse_) + 1))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1) , Str, CopySize_ );

		//utf8の残骸が後ろに残っている可能性があるので、0を直接埋め込む
		Stringval_[bufuse_ + CopySize_] = 0;

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +=(const char16_t* w_Str)
	{
		string_operator_lock.lock();

		if(w_Str == nullptr)
		{
			string_operator_lock.unlock();
			return (*this);
		}

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。(ここではUTF16確定になる)
		if( CType != SCHTYPE_UTF16)
		{
			SetCharacterType(SCHTYPE_UTF16);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint64_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(w_Str);
		uint64_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));

		if( (CopySize_ + bufuse_) + 2 > buffer_ )
		{
			if(!this->ReAlloc( (CopySize_ + bufuse_) + 2))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 2), w_Str, CopySize_);
		Stringval_[bufuse_ + CopySize_] = 0;

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char16_t*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +=(const wchar_t* w_Str)
	{
		string_operator_lock.lock();

		if(w_Str == nullptr)
		{
			string_operator_lock.unlock();
			return (*this);
		}

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。(ここではUTF16確定になる)
		if( CType != SCHTYPE_UTF32 )
		{
			SetCharacterType(SCHTYPE_UTF32);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint64_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char32_t*>(w_Str));
		uint64_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char32_t*>(Stringval_));

		if( (CopySize_ + bufuse_) + 2 > buffer_ )
		{
			if(!this->ReAlloc( (CopySize_ + bufuse_) + 4))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 4), w_Str, CopySize_);
		Stringval_[bufuse_ + CopySize_] = 0;

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char32_t*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl& SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +=(const int8_t* utf8_Str)
	{
		string_operator_lock.lock();

		if(utf8_Str == nullptr)
		{
			string_operator_lock.unlock();
			return (*this);
		}

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(utf8_Str));

		if(tmpType == SCHTYPE_UTF16)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_operator_lock.unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		uint64_t CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(utf8_Str));
		uint64_t bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		if( (CopySize_ + bufuse_) + 1 > buffer_ )
		{
			if(!this->ReAlloc( (CopySize_ + bufuse_) + 1))
			{
				string_operator_lock.unlock();
				throw std::bad_alloc();
			};
		};

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1) , utf8_Str, CopySize_ );

		//utf8の残骸が後ろに残っている可能性があるので、0を直接埋め込む
		Stringval_[bufuse_ + CopySize_] = 0;

		MaxLength_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

		string_operator_lock.unlock();
		return (*this);

	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +(const SonikStringUTF16_CHR32_pImpl& t_his)
	{
		SonikStringUTF16_CHR32_pImpl tmpStr = (*this);

		tmpStr += t_his;

		return tmpStr;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +(const char* Str)
	{
		SonikStringUTF16_CHR32_pImpl tmpStr = (*this);

		tmpStr += Str;

		return tmpStr;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +(const char16_t* w_Str)
	{
		SonikStringUTF16_CHR32_pImpl tmpStr = (*this);

		tmpStr += w_Str;

		return tmpStr;

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +(const wchar_t* w_Str)
	{
		SonikStringUTF16_CHR32_pImpl tmpStr = (*this);

		tmpStr += w_Str;

		return tmpStr;
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator +(const int8_t* utf8_Str)
	{
		SonikStringUTF16_CHR32_pImpl tmpStr = (*this);

		tmpStr += utf8_Str;

		return tmpStr;
	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 一致の場合true 不一致の場合 falseを返却します。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator ==(const SonikStringUTF16_CHR32_pImpl& t_his)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != t_his.CType )
		{
			if( !SetCharacterType(t_his.CType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = 0;
		uint64_t targetuse_ = 0;
		if( CType == SCHTYPE_UTF16 )
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));

		}else
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		};

		//c: サイズが一緒なら次の精査へ
		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( (*(Stringval_ + i)) != (*((t_his.Stringval_) + 1)) )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator ==(const char* Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(Str);

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(Str);

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator ==(const char16_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(w_Str);

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator ==(const wchar_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char16_t*>(w_Str));

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator ==(const int8_t* utf8_Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(utf8_Str));

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return false;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(utf8_Str));

		if( myuse_ != targetuse_ )
		{
			return false;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != utf8_Str[i] )
			{
				return false;
			};

		};

		//c: 全部越えたら一致と判定
		return true;
	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 不一致の場合true　一致の場合 falseを返却します。
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator !=(const SonikStringUTF16_CHR32_pImpl& t_his)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != t_his.CType )
		{
			if( !SetCharacterType(t_his.CType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = 0;
		uint64_t targetuse_ = 0;
		if( CType == SCHTYPE_UTF16 )
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(t_his.Stringval_));

		}else
		{
			myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
			targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		};

		//c: サイズが一緒なら次の精査へ
		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != t_his.Stringval_[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator !=(const char* Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(Str);

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(Str);

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator !=(const char16_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(w_Str);

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator !=(const wchar_t* w_Str)
	{
		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != SCHTYPE_UTF16 )
		{
			if( !SetCharacterType(SCHTYPE_UTF16) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char16_t*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char16_t*>(w_Str));

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != w_Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::operator !=(const int8_t* utf8_Str)
	{
		SonikLibConvertType StrType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<const char*>(utf8_Str));

		//c: 文字タイプが違えば相手と同じ文字タイプに変換
		if( CType != StrType )
		{
			if( !SetCharacterType(StrType) )
			{
				//c: 変換ミスが発生したら不一致として返却
				return true;
			};
		};

		//c: 文字数が違えば違う文字列として判定(不一致)
		uint64_t myuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));
		uint64_t targetuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<const char*>(utf8_Str));

		if( myuse_ != targetuse_ )
		{
			return true;
		};

		//c: 文字数も一緒であればByte精査
		for(uint64_t i=0; i < myuse_; ++i)
		{
			if( Stringval_[i] != utf8_Str[i] )
			{
				return true;
			};

		};

		//c: 全部越えたら一致と判定
		return false;
	};

	//c:比較演算子
	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::Greater(const char* CompareArg2val)
	{
		if( strcmp(this->str_c(), CompareArg2val) < 0 )
		{
			return true;
		};

		return false;
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::Less(const char* CompareArg2val)
	{
		return this->Greater(CompareArg2val);
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::GreaterEqual(const char* CompareArg2val)
	{
		return !(this->Less(CompareArg2val));
	};

	bool SonikStringUTF16_CHR32::SonikStringUTF16_CHR32_pImpl::LessEqual(const char* CompareArg2val)
	{
		return !(this->Greater(CompareArg2val));
	};

//===========================================================
//
//				pImpl使用（外側)クラスの実装
//
//===========================================================

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(_setlocale_);
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const SonikStringUTF16_CHR32& t_his)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			(*pImpl) = (*(t_his.pImpl));
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};
	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const char* SetStr)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};

	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const char* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(_setlocale_);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const char16_t* SetStr)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const char16_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(_setlocale_);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const wchar_t* SetStr)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const wchar_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(_setlocale_);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};

	};

	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const int8_t* SetStr)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(SonikLibStringConvert::SonikLibConvertLocale::LC_JPN);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};
	};
	SonikStringUTF16_CHR32::SonikStringUTF16_CHR32(const int8_t* SetStr, SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		pImpl = nullptr;

		try
		{
			pImpl = new SonikStringUTF16_CHR32_pImpl(_setlocale_);
			(*pImpl) = SetStr;
		}catch(std::bad_alloc&)
		{
			delete pImpl;
			throw;
		};

	};

	SonikStringUTF16_CHR32::~SonikStringUTF16_CHR32(void)
	{
		if(pImpl != 0)
		{
			delete pImpl;
		};
	};

	//ロケールを設定します。
	bool SonikStringUTF16_CHR32::SetStringLocale(SonikLibStringConvert::SonikLibConvertLocale _setlocale_)
	{
		return pImpl->SetStringLocale(_setlocale_);
	};

	//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
	const char* SonikStringUTF16_CHR32::str_c(void)
	{
		return pImpl->str_c();
	};

	//wchar_t形式に変換して取得します。(バッファタイプも書き換わります。)
	const wchar_t* SonikStringUTF16_CHR32::str_wchar(void)
	{
		return pImpl->str_wchar();
	};

	//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
	const char16_t* SonikStringUTF16_CHR32::str_utf16(void)
	{
		return pImpl->str_utf16();
	};

	//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
	const int8_t* SonikStringUTF16_CHR32::str_utf8(void)
	{
		return pImpl->str_utf8();
	};

	//define切り替えのstrゲット
	const char16_t* SonikStringUTF16_CHR32::definition_str(void)
	{
		return pImpl->str_utf16();
	};

	//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint64_t SonikStringUTF16_CHR32::GetCpy_str_c(char* dstBuffer)
	{
		return pImpl->GetCpy_str_c(dstBuffer);
	};

	//wchar_t形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint64_t SonikStringUTF16_CHR32::GetCpy_str_wcstr(wchar_t* dstBuffer)
	{
		return pImpl->GetCpy_str_wcstr(dstBuffer);
	};

	//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint64_t SonikStringUTF16_CHR32::GetCpy_str_utf16(char16_t* dstBuffer)
	{
		return pImpl->GetCpy_str_utf16(dstBuffer);
	};

	//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	uint64_t SonikStringUTF16_CHR32::GetCpy_str_utf8(char* dstBuffer)
	{
		return pImpl->GetCpy_str_utf8(dstBuffer);
	};

	//c:文字列のByte数を取得します。（Null終端文字をカウントに含まない)
	uint64_t SonikStringUTF16_CHR32::Count_Byte_NotNull(void)
	{
		return pImpl->Count_Byte_NotNull();
	};

	//c:文字列数を取得します。（Null終端文字をカウントに含まない)
	uint64_t SonikStringUTF16_CHR32::Count_Str_NotNull(void)
	{
		return pImpl->Count_Str_NotNull();
	};

	//文字列中の全角英数字を半角英数字に変換します。
	bool SonikStringUTF16_CHR32::ConvertFWANtoHWAN(void)
	{
		return pImpl->ConvertFWANtoHWAN();
	};

	//文字列中の全角カナを半角カナに変換します。
	bool SonikStringUTF16_CHR32::ConvertFWKNtoHWKN(void)
	{
		return pImpl->ConvertFWKNtoHWKN();
	};

	//c: 指定位置の文字を削除します。
	void SonikStringUTF16_CHR32::EraseChar(uint64_t ChrPoint)
	{
		pImpl->EraseChar(ChrPoint);
	};

	//c: 指定の開始位置から指定された文字数を削除します。
	void SonikStringUTF16_CHR32::EraseStr(uint64_t ChrStartPoint, uint64_t ChrEndPoint)
	{
		pImpl->EraseStr(ChrStartPoint, ChrEndPoint);
	};

	//指定したAsciiコードをデリミタとしてSplitを行います。
	bool SonikStringUTF16_CHR32::SplitForUTF8(uint8_t delim, SonikLib::Container::SonikVariableArrayContainer<SonikLib::SonikStringUTF16_CHR32>& Container)
	{
		return pImpl->SplitForUTF8(delim, Container);
	};

	//各入力フォーマットから現在のバッファに変換して代入します。
	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(const SonikStringUTF16_CHR32& t_his)
	{
		(*pImpl) = (*(t_his.pImpl));

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(SonikStringUTF16_CHR32&& Move) noexcept
	{
		(*pImpl) = std::move( (*(Move.pImpl)) );

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(const char* Str)
	{
		(*pImpl) = Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(const char16_t* w_Str)
	{
		(*pImpl) = w_Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(const wchar_t* w_Str)
	{
		(*pImpl) = w_Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator =(const int8_t* utf8_Str)
	{
		(*pImpl) = utf8_Str;

		return (*this);
	};

	//各入力フォーマットから現在のバッファに変換して結合します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator +=(const SonikStringUTF16_CHR32& t_his)
	{
		(*pImpl) += (*(t_his.pImpl));

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator +=(const char* Str)
	{
		(*pImpl) += Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator +=(const char16_t* w_Str)
	{
		(*pImpl) += w_Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator +=(const wchar_t* w_Str)
	{
		(*pImpl) += w_Str;

		return (*this);
	};

	SonikStringUTF16_CHR32& SonikStringUTF16_CHR32::operator +=(const int8_t* utf8_Str)
	{
		(*pImpl) += utf8_Str;

		return (*this);
	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikStringUTF16_CHR32 SonikStringUTF16_CHR32::operator +(const SonikStringUTF16_CHR32& t_his)
	{
		SonikStringUTF16_CHR32 str_;

		(*(str_.pImpl)) = (*pImpl) + (*(t_his.pImpl));

		return str_;
	};

	SonikStringUTF16_CHR32 SonikStringUTF16_CHR32::operator +(const char* Str)
	{
		SonikStringUTF16_CHR32 str_;

		(*(str_.pImpl)) = (*pImpl) + Str;

		return str_;
	};

	SonikStringUTF16_CHR32 SonikStringUTF16_CHR32::operator +(const char16_t* w_Str)
	{
		SonikStringUTF16_CHR32 str_;

		(*(str_.pImpl)) = (*pImpl) + w_Str;

		return str_;
	};

	SonikStringUTF16_CHR32 SonikStringUTF16_CHR32::operator +(const wchar_t* w_Str)
	{
		SonikStringUTF16_CHR32 str_;

		(*(str_.pImpl)) = (*pImpl) + w_Str;

		return str_;
	};

	SonikStringUTF16_CHR32 SonikStringUTF16_CHR32::operator +(const int8_t* utf8_Str)
	{
		SonikStringUTF16_CHR32 str_;

		(*(str_.pImpl)) = (*pImpl) + utf8_Str;

		return str_;
	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 一致の場合true 不一致の場合 falseを返却します。
	bool SonikStringUTF16_CHR32::operator ==(const SonikStringUTF16_CHR32& t_his)
	{
		return (*pImpl) == (*t_his.pImpl);
	};

	bool SonikStringUTF16_CHR32::operator ==(const char* Str)
	{
		return (*pImpl) == Str;
	};

	bool SonikStringUTF16_CHR32::operator ==(const char16_t* w_Str)
	{
		return (*pImpl) == w_Str;
	};

	bool SonikStringUTF16_CHR32::operator ==(const wchar_t* w_Str)
	{
		return (*pImpl) == w_Str;
	};

	bool SonikStringUTF16_CHR32::operator ==(const int8_t* utf8_Str)
	{
		return (*pImpl) == utf8_Str;
	};

	//c: 文字列同士を比較します。(strcmp)
	//c: 不一致の場合true　一致の場合 falseを返却します。
	bool SonikStringUTF16_CHR32::operator !=(const SonikStringUTF16_CHR32& t_his)
	{
		return (*pImpl) != (*t_his.pImpl);
	};

	bool SonikStringUTF16_CHR32::operator !=(const char* Str)
	{
		return (*pImpl) != Str;
	};

	bool SonikStringUTF16_CHR32::operator !=(const char16_t* w_Str)
	{
		return (*pImpl) != w_Str;
	};

	bool SonikStringUTF16_CHR32::operator !=(const wchar_t* w_Str)
	{
		return (*pImpl) != w_Str;
	};

	bool SonikStringUTF16_CHR32::operator !=(const int8_t* utf8_Str)
	{
		return (*pImpl) != utf8_Str;
	};

	bool operator <(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val)
	{
		return CompareArg1val.pImpl->Greater(CompareArg2val.pImpl->str_c());
	};

	bool operator >(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val)
	{
		return CompareArg1val.pImpl->Less(CompareArg2val.pImpl->str_c());
	};

	bool operator <=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val)
	{
		return CompareArg1val.pImpl->GreaterEqual(CompareArg2val.pImpl->str_c());
	};

	bool operator >=(const SonikStringUTF16_CHR32& CompareArg1val, const SonikStringUTF16_CHR32& CompareArg2val)
	{
		return CompareArg1val.pImpl->LessEqual(CompareArg2val.pImpl->str_c());
	};

};
