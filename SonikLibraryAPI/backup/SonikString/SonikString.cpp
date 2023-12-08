/*
 * SonikString.cpp
 *
 *  Created on: 2016/01/10
 *      Author: SONIC_000
 */

#include "SonikString.h"

#include <new>
#include <algorithm>
#include <cstring>
#include <locale.h>
#include "..//SonikCASLockUse.h"

namespace SonikLib
{

	//UTF8, UTF16, SJISが扱えるstringクラスです。
	//処理自体はスレッドセーフですが、文字列をgetした後にバッファを書き換えられる恐れがあります。
	class SonikString::SonikString_pImpl
	{
	private:
		//文字列領域
		wchar_t* Stringval_;
		//現在の文字列のタイプ
		SonikLibConvertType CType;
		//文字列領域のサイズ
		unsigned long buffer_;
		//マルチスレッドブロック
		SonikLib::SonikAtomicLock string_atm_lock;
		//マルチスレッドブロック（オペレータ)
		SonikLib::SonikAtomicLock string_operator_lock;

	private:
		//内部用リサイズ関数です。
		bool ReAlloc(unsigned long ReSize);

		//現在のバッファタイプを指定のバッファタイプに変更します。
		//変更の際に、バッファに対して変換作業が行われます。
		//変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
		//SCHTYPE_UNKNOWNを指定した場合は、必ずfalseとなります。
		bool SetCharacterType(SonikLibConvertType SetType);

	public:
		//コンストラクタ
		SonikString_pImpl(void);
		//コンストラクタオーバーロード
		SonikString_pImpl(const char* SetStr);
		//コンストラクタオーバーロード
		SonikString_pImpl(const wchar_t* SetStr);

		//コピーコンストラクタ
		SonikString_pImpl(const SonikString_pImpl& t_his);
		//ムーブコンストラクタ
		SonikString_pImpl(SonikString_pImpl&& Move);

		//デストラクタ
		~SonikString_pImpl(void);


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
		SonikString_pImpl& operator =(const SonikString_pImpl& t_his);
		SonikString_pImpl& operator =(SonikString_pImpl&& Move);
		SonikString_pImpl& operator =(const char* Str);
		SonikString_pImpl& operator =(const wchar_t* w_Str);

		//各入力フォーマットから現在のバッファに変換して結合します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_pImpl& operator +=(const SonikString_pImpl& t_his);
		SonikString_pImpl& operator +=(const char* Str);
		SonikString_pImpl& operator +=(const wchar_t* w_Str);

		//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
		//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
		SonikString_pImpl operator +(const SonikString_pImpl& t_his);
		SonikString_pImpl operator +(const char* Str);
		SonikString_pImpl operator +(const wchar_t* w_Str);

	};


	SonikString::SonikString_pImpl::SonikString_pImpl(void)
	{
		Stringval_ = 0;
		buffer_ = 50;
		CType = SCHTYPE_NULLTEXT;

		try
		{
			Stringval_ = new wchar_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);
	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const char* SetStr)
	{
		buffer_ = 50;
		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(SetStr);

		//NULL文字文追加(+1)して格納
		unsigned int SrcByte = SonikLibStringConvert::GetStringCount(SetStr) + 1;

		if( SrcByte > buffer_ )
		{
			buffer_ = SrcByte;
		};

		try
		{
			Stringval_ = new wchar_t[buffer_];
		}catch(std::bad_alloc& e)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		if( tmpType == SCHTYPE_UTF8 )
		{
			if( !SonikLibStringConvert::ConvertUTF8ToUTF16(const_cast<char*>(SetStr), Stringval_, &buffer_) )
			{
				throw std::bad_alloc();
			};

		}else if( tmpType == SCHTYPE_SJIS )
		{
			setlocale(LC_CTYPE, "jpn");
			if( mbstowcs_s(0, Stringval_, buffer_, SetStr, SrcByte) != 0 )
			{
				setlocale(LC_CTYPE, "");
				throw std::bad_alloc();
			};

			setlocale(LC_CTYPE, "");
		};

		CType = tmpType;

	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const wchar_t* SetStr)
	{
		buffer_ = 50;
		CType = SCHTYPE_UTF16;

		unsigned long SrcLen = SonikLibStringConvert::GetStringCount(SetStr);

		if(buffer_ < SrcLen)
		{
			buffer_ = SrcLen;
		};

		try
		{
			Stringval_ = new wchar_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		std::fill_n(Stringval_, buffer_, 0);

		memcpy(Stringval_, SetStr, buffer_);

	};

	SonikString::SonikString_pImpl::SonikString_pImpl(const SonikString_pImpl& t_his)
	{
		buffer_ = t_his.buffer_;
		CType = t_his.CType;

		try
		{
			Stringval_ = new wchar_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		memcpy(Stringval_, t_his.Stringval_, buffer_);

	};

	SonikString::SonikString_pImpl::SonikString_pImpl(SonikString_pImpl&& Move)
	{
		buffer_ = std::move(Move.buffer_);
		CType = std::move(Move.CType);
		Stringval_ = std::move(Move.Stringval_);

		Move.CType = SonikLibConvertType::SCHTYPE_UNKNOWN;
		Move.Stringval_ = nullptr;
		Move.buffer_ = 0;

	};

	SonikString::SonikString_pImpl::~SonikString_pImpl(void)
	{
		if(Stringval_ != 0)
		{
			delete[] Stringval_;
		};
	};

	//現在のバッファタイプを指定のバッファタイプに変更します。
	//変更の際に、バッファに対して変換作業が行われます。
	//変換の際に失敗した場合は、falseになり、タイプの切り替えと変換作業は行われません。
	bool SonikString::SonikString_pImpl::SetCharacterType(SonikLibConvertType SetType)
	{
		string_atm_lock.lock();

		unsigned int convSize_ = 0;
//		unsigned long bufsize_ = SonikLibStringConvert::GetStringLength(reinterpret_cast<char*>(Stringval_));
		switch(CType)
		{
		case SCHTYPE_SJIS:
			//SJIS から SetType へ各変換
			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//SJISへの変換は行わない。行う必要がない
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16への変換
//				mbstowcs_s(&convSize_, 0, 0, reinterpret_cast<char*>(Stringval_), bufsize_);
				SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), 0, reinterpret_cast<unsigned long*>(&convSize_));
				//convSize_ *= 2;

//				if( (convSize_ & 0x01) == 1 )
//				{
//					++convSize_;
//				};

				if( (convSize_ +1) > buffer_ )
				{
					if( !this->ReAlloc( (convSize_+1) ) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBStoUTF16(reinterpret_cast<char*>(Stringval_), Stringval_, &buffer_) )
				{
					string_atm_lock.Unlock();
					return false;
				};

//				if( mbstowcs_s(0, Stringval_, (convSize_ >> 1), reinterpret_cast<char*>(Stringval_), (convSize_ >> 1)) != 0 )
//				{
//					string_atm_lock.Unlock();
//					return false;
//				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//SJISからUTF8への変換を行う。
				SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), 0, reinterpret_cast<unsigned long*>(&convSize_));

//				if( (convSize_ & 0x01) == 1 )
//				{
//					--convSize_;
//				};

				if( (((convSize_ -1) >> 2) +1) > buffer_ ) // x / 4 = x >> 2
				{
					if( !this->ReAlloc(((convSize_ -1) >> 2) +1) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertMBSToUTF8(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), reinterpret_cast<unsigned long*>(&convSize_)) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
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
//				wcstombs_s(&convSize_, 0, 0, Stringval_, (bufsize_ * 2));
				SonikLibStringConvert::ConvertUTF16toMBS(Stringval_, 0, reinterpret_cast<unsigned long*>(&convSize_));

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_ << 1) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ << 1) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				//convSize_ = buffer_ << 1; // x * 2 = x << 1
				if( !SonikLibStringConvert::ConvertUTF16toMBS(Stringval_, reinterpret_cast<char*>(Stringval_), reinterpret_cast<unsigned long*>(&convSize_)) )
				{
					string_atm_lock.Unlock();
					return false;
				};

//				if( wcstombs_s(0, reinterpret_cast<char*>(Stringval_), convSize_, Stringval_, (bufsize_ * 2)) != 0 )
//				{
//					string_atm_lock.Unlock();
//					return false;
//				};
//
//				setlocale(LC_CTYPE, "");

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF16 から UTF16への変換は行わない。行う必要がない。

				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_UTF8:
				//UTF16 から UTF8への変換
				SonikLibStringConvert::ConvertUTF16ToUTF8(Stringval_, 0, reinterpret_cast<unsigned long*>(&convSize_));

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_ >> 2) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ >> 2) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF16ToUTF8(Stringval_, reinterpret_cast<char*>(Stringval_), reinterpret_cast<unsigned long*>(&convSize_)) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				string_atm_lock.Unlock();
				break;
			};

			break;

		case SCHTYPE_UTF8:

			switch(SetType)
			{
			case SCHTYPE_SJIS:
				//UTF8からSJISへの変換
				SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), 0, reinterpret_cast<unsigned long*>(&convSize_));

				if( (convSize_ & 0x01) == 1 )
				{
					++convSize_;
				};

				if( (convSize_ >> 1) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ >> 1) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

				if( !SonikLibStringConvert::ConvertUTF8ToMBS(reinterpret_cast<char*>(Stringval_), reinterpret_cast<char*>(Stringval_), reinterpret_cast<unsigned long*>(&convSize_)) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF16:
				//UTF8からUTF16へ変換
				SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), 0, reinterpret_cast<unsigned long*>(&convSize_));

//				if( (convSize_ & 0x01) == 1 )
//				{
//					++convSize_;
//				};
//				convSize_ <<= 1;

				if( (convSize_ >> 2) > buffer_ )
				{
					if( !this->ReAlloc(convSize_ >> 2) )
					{
						string_atm_lock.Unlock();
						return false;
					};

				};

//				convSize_ >>= 1;
				if( !SonikLibStringConvert::ConvertUTF8ToUTF16(reinterpret_cast<char*>(Stringval_), Stringval_, reinterpret_cast<unsigned long*>(&convSize_)) )
				{
					string_atm_lock.Unlock();
					return false;
				};

				CType = SetType;
				string_atm_lock.Unlock();
				return true;

				break;

			case SCHTYPE_UTF8:
				//UTF8からUTF8へ変換は行わない。行う必要がない。

				string_atm_lock.Unlock();
				return true;
				break;

			case SCHTYPE_NULLTEXT:

				CType = SetType;
				string_atm_lock.Unlock();
				break;

			default:
				//SCHTYPE_UNKNOWN判定

				break;
			};

			break;

		case SCHTYPE_NULLTEXT:

			CType = SetType;
			string_atm_lock.Unlock();
			break;

		default:
			//SCHTYPE_UNKNOWN判定

			break;
		};

		string_atm_lock.Unlock();
		return false;
	};

	bool SonikString::SonikString_pImpl::ReAlloc(unsigned long ReArraySize)
	{
		wchar_t* pTmp = 0;
		//コピー元なのでNULL文字は数えない。
//		unsigned long bufsize_ = SonikLibStringConvert::GetStringCount(Stringval_) + 1;
//
//		try
//		{
//			pTmp = new char[ReSize];
//		}catch(std::bad_alloc&)
//		{
//			return false;
//		};

		pTmp = new(std::nothrow) wchar_t[ReArraySize];

		std::fill_n(pTmp, ReArraySize, 0);

		memcpy_s(pTmp, ReArraySize << 1, Stringval_, buffer_ << 1);

		delete[] Stringval_;
		Stringval_ = pTmp;
		buffer_ = ReArraySize;

		return true;
	};

	const char* SonikString::SonikString_pImpl::c_str(void)
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

	const wchar_t* SonikString::SonikString_pImpl::c_wcstr(void)
	{
		if( CType == SCHTYPE_UNKNOWN )
		{
			return L"";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF16) )
		{
			return L"";
		};

		return Stringval_;

	};

	const char* SonikString::SonikString_pImpl::utf8_str(void)
	{
		if(CType == SCHTYPE_UNKNOWN)
		{
			return "";
		};

		if( !this->SetCharacterType(SCHTYPE_UTF8) )
		{
			return "";
		};

		return reinterpret_cast<char*>(Stringval_);
	};

	unsigned long SonikString::SonikString_pImpl::GetCpy_c_str(char* dstBuffer)
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
		unsigned long cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_))  + 1;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	unsigned long SonikString::SonikString_pImpl::GetCpy_c_wcstr(wchar_t* dstBuffer)
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
		unsigned long cpysize = SonikLibStringConvert::GetStringLengthByte(Stringval_) + 2;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	unsigned long SonikString::SonikString_pImpl::GetCpy_utf8_str(char* dstBuffer)
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
		unsigned long cpysize = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_)) + 1;

		if( dstBuffer == 0 || dstBuffer == nullptr )
		{
			//サイズ返却して終了
			return cpysize;
		};

		//dstコピー
		memcpy(dstBuffer, Stringval_, cpysize);

		return cpysize;
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const SonikString_pImpl& t_his)
	{
		buffer_ = t_his.buffer_;
		CType = t_his.CType;

		if( this == &t_his )
		{
			return (*this);
		};

		if( Stringval_ != 0 )
		{
			delete[] Stringval_;

		};

		try
		{
			Stringval_ = new wchar_t[buffer_];
		}catch(std::bad_alloc&)
		{
			throw;
		};

		memcpy(Stringval_, t_his.Stringval_, buffer_);

		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(SonikString_pImpl&& Move)
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

		Move.CType = SonikLibConvertType::SCHTYPE_UNKNOWN;
		Move.Stringval_ = nullptr;
		Move.buffer_ = 0;

		return (*this);

	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const char* Str)
	{
		if(Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		std::fill_n(Stringval_, buffer_, 0);
		if( strcmp(Str, "") == 0 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.Unlock();
			return (*this);
		};

		CType = SonikLibStringConvert::CheckConvertType(Str);
		unsigned long Size_ = SonikLibStringConvert::GetStringLengthByte(Str);
		unsigned long strcnt = SonikLibStringConvert::GetStringCount(Str);

//		if((Size_ & 0x01) == 1)
//		{
//			++Size_;
//
//			if(Size_ > (buffer_ << 1)) //x * 2 = x << 1
//			{
//				this->ReAlloc(Size_ + 1);
//			};
//
//			--Size_;
//		}else
//		{
//			if(Size_ > (buffer_ * 2)) //x * 2 = x << 1
//			{
//				this->ReAlloc(Size_ + 1);
//			};
//
//		};

		if(buffer_ < (strcnt + 1))
		{
			//null終端分追加
			this->ReAlloc(strcnt + 1);
		};

		memcpy_s(Stringval_, (buffer_ << 1) , Str, Size_);

		string_operator_lock.Unlock();
		return (*this);

	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator =(const wchar_t* w_Str)
	{
		if(w_Str == 0 )
		{
			return (*this);
		};

		string_operator_lock.lock();

		std::fill_n(Stringval_, buffer_, 0);
		if( (*w_Str) == 0x00 )
		{
			CType = SCHTYPE_NULLTEXT;
			string_operator_lock.Unlock();
			return (*this);
		};

		CType = SCHTYPE_UTF16;
		unsigned long Size_ = SonikLibStringConvert::GetStringCount(w_Str);

		if( (Size_ +1) > buffer_ )
		{
			this->ReAlloc(Size_ + 1);
		};

		memcpy_s(Stringval_, buffer_, w_Str, Size_);

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const SonikString_pImpl& t_his)
	{
		string_operator_lock.lock();

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != t_his.CType )
		{
			SetCharacterType(t_his.CType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		unsigned long CopySize_;
		unsigned long bufuse_;
		if(t_his.CType == SCHTYPE_UTF16)
		{
			// >> 1 = x/2
			CopySize_ = SonikLibStringConvert::GetStringLengthByte(t_his.Stringval_) >> 1;
			bufuse_ = SonikLibStringConvert::GetStringLengthByte(Stringval_) >> 1;

			if( buffer_ < (CopySize_ + bufuse_ ))
			{
				this->ReAlloc((CopySize_ + bufuse_) + 1);
			};


		}else
		{

			CopySize_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(t_his.Stringval_));
			bufuse_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_));

			if( buffer_ < (CopySize_ + bufuse_) + 1 )
			{
				this->ReAlloc((CopySize_ + bufuse_) + 1);
			};

		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(t_his.Stringval_));
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));


		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1), t_his.Stringval_, CopySize_);

		//最後に全部元の形に変換
//		SetCharacterType(CType);

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const char* Str)
	{
		string_operator_lock.lock();

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(Str);

		if(tmpType == SCHTYPE_UTF16)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_atm_lock.Unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		unsigned long CopySize_ = SonikLibStringConvert::GetStringCount(Str);
		if( tmpType == SCHTYPE_UTF8 )
		{
			CopySize_ <<= 1; //x*2
		};

		unsigned long bufuse_ = SonikLibStringConvert::GetStringCount(reinterpret_cast<char*>(Stringval_), CType);
		if( CType == SCHTYPE_UTF8 )
		{
			bufuse_ <<= 1; //x*2
		}

		if( (CopySize_ + bufuse_) > buffer_ )
		{
			this->ReAlloc( (CopySize_ + bufuse_) + 1);
		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(Str);
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(reinterpret_cast<char*>(Stringval_));

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1) , Str, CopySize_ );

		//最後に全部コピー元の形に変換
//		SetCharacterType(CType);

		string_operator_lock.Unlock();
		return (*this);
	};

	SonikString::SonikString_pImpl& SonikString::SonikString_pImpl::operator +=(const wchar_t* w_Str)
	{
		string_operator_lock.lock();

		SonikLibConvertType tmpType = SonikLibStringConvert::CheckConvertType(reinterpret_cast<char*>(const_cast<wchar_t*>(w_Str)));

		if(tmpType == SCHTYPE_UTF8 || tmpType == SCHTYPE_SJIS)
		{
			//reinterpret_castなどで変換して渡された場合に検出する可能性あり。
			string_operator_lock.Unlock();
			return (*this);
		};

		//コピー元とタイプが違えばコピー元に合わせて変換をかける。(ここではUTF16確定になる)
		if( CType != tmpType )
		{
			SetCharacterType(tmpType);
		};

		//カウントを行い、結合時にはみ出すようなら再確保
		unsigned long CopySize_ = SonikLibStringConvert::GetStringCount(w_Str);
		unsigned long bufuse_ = SonikLibStringConvert::GetStringCount(Stringval_);

		if( (CopySize_ + bufuse_) + 1 > buffer_ )
		{
			this->ReAlloc( (CopySize_ + bufuse_) + 1);
		};

		CopySize_ = SonikLibStringConvert::GetStringLengthByte(w_Str);
		bufuse_ = SonikLibStringConvert::GetStringLengthByte(Stringval_);

		memcpy_s(&(reinterpret_cast<char*>(Stringval_)[bufuse_]), (CopySize_ + 1), w_Str, CopySize_);

		//最後に全部コピー元の形に変換
//		SetCharacterType(CType);

		string_operator_lock.Unlock();
		return (*this);
	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const SonikString_pImpl& t_his)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += t_his;

		return tmpStr;
	};

	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const char* Str)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += Str;

		return tmpStr;
	};

	SonikString::SonikString_pImpl SonikString::SonikString_pImpl::operator +(const wchar_t* w_Str)
	{
		SonikString_pImpl tmpStr = (*this);

		tmpStr += w_Str;

		return tmpStr;

	};


//===========================================================
//
//				pImpl使用（外側)クラスの実装
//
//===========================================================

	SonikString::SonikString(void)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
		}catch(std::bad_alloc&)
		{
			throw;
		};

	};
	SonikString::SonikString(const SonikString& t_his)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = (*(t_his.pImpl));
		}catch(std::bad_alloc&)
		{
			throw;
		};
	};

	SonikString::SonikString(SonikString&& Move)
	{
		pImpl = 0;

		try
		{
			pImpl = new SonikString_pImpl;
			(*pImpl) = std::move( (*(Move.pImpl)) );
		}catch(std::bad_alloc&)
		{
			throw;
		};

	};

	SonikString::~SonikString(void)
	{
		if(pImpl != 0)
		{
			delete pImpl;
		};
	};

	//SJIS形式に変換して取得します。(バッファタイプも書き換わります。)
	const char* SonikString::c_str(void)
	{
		return pImpl->c_str();
	};

	//UTF16形式に変換して取得します。(バッファタイプも書き換わります。)
	const wchar_t* SonikString::c_wcstr(void)
	{
		return pImpl->c_wcstr();
	};

	//UTF8形式に変換して取得します。(バッファタイプも書き換わります。)
	const char* SonikString::utf8_str(void)
	{
		return pImpl->utf8_str();
	};

	//SJIS形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	unsigned long SonikString::GetCpy_c_str(char* dstBuffer)
	{
		return pImpl->GetCpy_c_str(dstBuffer);
	};

	//UTF16形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	unsigned long SonikString::GetCpy_c_wcstr(wchar_t* dstBuffer)
	{
		return pImpl->GetCpy_c_wcstr(dstBuffer);
	};

	//UTF8形式に変換して、バッファをdstBufferにコピーします。(バッファタイプも書き換わります。)
	//第１引数を省略してコールした場合はdstに必要なバッファサイズを取得することができます。(単位/1Byte)
	unsigned long SonikString::GetCpy_utf8_str(char* dstBuffer)
	{
		return pImpl->GetCpy_utf8_str(dstBuffer);
	};

	//各入力フォーマットから現在のバッファに変換して代入します。
	SonikString& SonikString::operator =(const SonikString& t_his)
	{
		(*pImpl) = (*(t_his.pImpl));

		return (*this);
	};

	SonikString& SonikString::operator =(SonikString&& Move)
	{
		(*pImpl) = std::move( (*(Move.pImpl)) );

		return (*this);
	};

	SonikString& SonikString::operator =(const char* Str)
	{
		(*pImpl) = Str;

		return (*this);
	};

	SonikString& SonikString::operator =(const wchar_t* w_Str)
	{
		(*pImpl) = w_Str;

		return (*this);
	};

	//各入力フォーマットから現在のバッファに変換して結合します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString& SonikString::operator +=(const SonikString& t_his)
	{
		(*pImpl) += (*(t_his.pImpl));

		return (*this);
	};

	SonikString& SonikString::operator +=(const char* Str)
	{
		(*pImpl) += Str;

		return (*this);
	};

	SonikString& SonikString::operator +=(const wchar_t* w_Str)
	{
		(*pImpl) += w_Str;

		return (*this);
	};

	//現在のバッファと入力バッファを結合し、別のオブジェクトとして返却します。
	//コピー元とコピー先が同じオブジェクトの場合、そのまま結合します。
	SonikString SonikString::operator +(const SonikString& t_his)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + (*(t_his.pImpl));

		return str_;
	};

	SonikString SonikString::operator +(const char* Str)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + Str;

		return str_;
	};

	SonikString SonikString::operator +(const wchar_t* w_Str)
	{
		SonikString str_;

		(*(str_.pImpl)) = (*pImpl) + w_Str;

		return str_;
	};




};


