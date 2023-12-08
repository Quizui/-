/*
 * SonikStringConvert.h
 *
 *  Created on: 2016/01/08
 *      Author: SONIK
 *  TEXTFORMAT: UTF-8
 */

#ifndef SONIKString_SonikStringCONVERT_H_
#define SONIKString_SonikStringCONVERT_H_

//#include "..\\SonikCASLockUse.h"

enum SonikLibConvertType
{
	SCHTYPE_SJIS = 0,
	SCHTYPE_UTF8,
	SCHTYPE_BOMUTF8,
	SCHTYPE_UTF16,
	SCHTYPE_UNKNOWN,
	SCHTYPE_NULLTEXT,
};

namespace SonikLibStringConvert
{

	//文字列のタイプが、SJISかUTF-8かを判別します。
	//完全な判別は不可能（らしい）なので可能性の範囲でチェックされた結果を返却します。
	//ASCIIはSJISとして結果を返却します。
	//UTF-16 は返却値としては返りません。
	SonikLibConvertType CheckConvertType(const char* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されているバイト数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	unsigned long GetStringLengthByte(const char* pCheckSrc);

	//unicode(UTF-16)文字の文字列バイト数を返却します。
	unsigned long GetStringLengthByte(const wchar_t* pCheckSrc);

	//unicode(UTF-32)文字の文字列バイト数を返却します。
	//ただのループ。
	unsigned long GetStringLengthByte(const long* pCheckSrc);

	//文字列のタイプをチェックし、その文字列で使用されている文字数を返却します。
	//文字列のタイプチェックは可能性の範囲のチェックとなります。
	//SJIS, UTF-8のみに対応。
	unsigned long GetStringCount(const char* pCheckSrc);

	//SJIS, UTF-8のみに対応。
	//第２引数に指定したタイプで強制的にカウントを行います。(SJIS混じりUTF8の対処)
	unsigned long GetStringCount(const char* pCheckSrc, SonikLibConvertType CountStrType);

	//unicode(UTF-16)文字の文字数を返却します。
	unsigned long GetStringCount(const wchar_t* pCheckSrc);

	//unicode(UTF-32)文字の文字数を返却します。
	unsigned long GetStringCount(const long* pCheckSrc);

	//UTF-8をUNICODE(UTF-32)に変換します。
	bool ConvertUTF8ToUTF32(char* pSrc, long* pDest, unsigned long* DestBufferSize);

	//UNICODE(UTF-32)をUTF-8に変換します。
	bool ConvertUTF32ToUTF8(long* pSrc, char* pDest, unsigned long* DestBufferSize);

	//UNICODE(UTF-32)をUNICODE(UTF-16)に変換します。
	bool ConvertUTF32ToUTF16(long* pSrc, wchar_t* pDest, unsigned long* DestBufferSize);

	//UNICODE(UTF16)をUNICODE(UTF-32)に変換します。
	bool ConvertUTF16ToUTF32(wchar_t* pSrc, long* pDest, unsigned long* DestBufferSize);

	//UTF8をUNICODE(UTF-16)に変換します。
	bool ConvertUTF8ToUTF16(char* pSrc, wchar_t* pDest, unsigned long* DestBufferSize);

	//UNICODE(UTF-16)をUTF8に変換します。
	bool ConvertUTF16ToUTF8(wchar_t* pSrc, char* pDest, unsigned long* DestBufferSize);


	//マルチバイト文字列をUTF8文字列に変換します。
	//第１引数の文字列は、可能性の判定として、SJIS判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertMBSToUTF8(char* pSrc, char* pDest, unsigned long* DestBufferSize);

	//UTF8文字列をマルチバイト文字列に変換します。
	//第１引数の文字列は、可能性の判定として、UTF8判定であれば処理を行います。
	//第１引数の文字列に対して、Null終端がない場合の動作は、strlenと同様にバッファオーバーランを起こします。
	bool ConvertUTF8ToMBS(char* pSrc, char* pDest, unsigned long* DestBufferSize);

	//マルチバイト文字列をUTF16文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertMBStoUTF16(char* pSrc, wchar_t* pDest, unsigned long* DestBufferSize);

	//UTF16文字列をマルチバイト文字列に変換します。
	//内部ではmbstowcs_s関数を使用しますが、一時領域を確保し、コピーして処理を行うため、コピー元領域、コピー先領域が重なっていても正常にコピーされます。
	bool ConvertUTF16toMBS(wchar_t* pSrc, char* pDest, unsigned long* DestBufferSize);

};


#endif /* SONIKString_SonikStringCONVERT_H_ */
