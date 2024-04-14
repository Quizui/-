/*
 * SonikFileController.h
 *
 *  Created on: 2018/11/16
 *      Author: SONIK
 */

#ifndef SONIKFILECONTROLLER_H_
#define SONIKFILECONTROLLER_H_

#include "../SonikString/SonikString.h"
#include "../SonikCAS/SonikAtomicLock.h"
#include "../SmartPointer/SonikSmartPointer.hpp"

#include <stdint.h>

//前方宣言============================
namespace SonikLib
{
	template<class QueueType>
	class SonikAtomicQueue;

	namespace FileSystemControllers
	{
		class SonikFileStreamController;
	};
};

struct _iobuf;
typedef _iobuf FILE;

//====================================

namespace SonikLib
{
	using SFileSystemController = SonikLib::SharedSmtPtr<SonikLib::FileSystemControllers::SonikFileStreamController>;

	namespace FileSystem
	{
		//エンディアン対策で16進数から実数値に変更。コメントに16進数記載
		enum class OpenMode : uint32_t
		{
			//UNKNOWN
			OPEN_UNKNOWN					= 0,	//0x00000000 -> unknow 特殊。不定の証

			//TEXT OPEN
			OPEN_TXT_READ					= 114,			//0x00000072 -> "r" 読み込み専用(Read Only) エラー + 新規作成不可
			OPEN_TXT_WRITE					= 119,			//0x00000077 -> "w" 書き込み専用(Write Only)	 内容を消去 + 新規作成可
			OPEN_TXT_WRITEADD			= 97,			//0x00000061 -> "a" 追加書き込み専用(AddWrite Only) 内容の最後に追記 + 新規作成可
			OPEN_TXT_READWRITE			= 11122,		//0x00002B72 -> "r+" 読み書き(Read And Write) エラー + 新規作成不可
			OPEN_TXT_WRITEREAD			= 11127,		//0x00002B77 -> "w+" 書き読み(Write And Read) 内容を消去 + 新規作成可
			OPEN_TXT_READADDWRITE	= 11105,		//0x00002B61 -> "a+" 読み込みと追加書き込み(Read And AddWrite) 内容の最後に追記 + 新規作成可

			//Binary OPEN
			OPEN_BIN_READ					= 25202,		//0x00006272 -> "rb" 読み込み専用(Read Only) エラー + 新規作成不可
			OPEN_BIN_WRITE					= 25207,		//0x00006277 -> "wb" 書き込み専用(Write Only)	 内容を消去 + 新規作成可
			OPEN_BIN_WRITEADD			= 25185,		//0x00006261 -> "ab" 追加書き込み専用(AddWrite Only) 内容の最後に追記 + 新規作成可
			OPEN_BIN_READWRITE			= 2843250,	//0x002B6272 -> "rb+" 読み書き(Read And Write) エラー + 新規作成不可
			OPEN_BIN_WRITEREAD			= 2843255,	//0x002B6277 -> "wb+" 書き読み(Write And Read) 内容を消去 + 新規作成可
			OPEN_BIN_READADDWRITE	= 2843233,	//0x002B6261 -> "ab+" 読み込みと追加書き込み(Read And AddWrite) 内容の最後に追記 + 新規作成可

		}; // end enum class

	}; //end namespace FileSystem

    namespace FileSystemControllers
    {
    	class SonikFileSystemController
		{
			private:
    			FILE* m_file;
    			FileSystem::OpenMode m_openmode;
    			SonikLib::SonikString m_filepath;
    			SonikLib::S_CAS::SonikAtomicLock m_lock;

			private:
    			//コピー禁止&ムーブ禁止
    			SonikFileSystemController(const SonikFileSystemController _copy_) = delete;
    			SonikFileSystemController(SonikFileSystemController&& _move_) = delete;
    			SonikFileSystemController& operator =(const SonikFileSystemController& _copy_) = delete;
    			SonikFileSystemController& operator =(SonikFileSystemController& _move_) = delete;

    			//コンストラクタ
    			SonikFileSystemController(void);

			public:
    			//デストラクタ
    			~SonikFileSystemController(void);
    			//クリエイタ
    			static bool CreateFileController(SFileSystemController& _out_);

    			//FileOpen
    			bool OpenFile(SonikLib::SonikString _filepath_, FileSystem::OpenMode _mode_);
    			//FileClose
    			void CloseFile(void);

    			//現在のファイルサイズの取得
    			uint64_t GetFileSize(void);

    			//シーク位置を最初に移動します。
    			void SeekPointSet_Top(void);
    			//シーク位置を最後に移動します。
    			void SeekPointSet_End(void);
    			//現在ンお読み込みシーク位置から指定バイト数分移動します。
    			void SeekPointSet_Point(uint64_t _offset_);
    			//現在のシーク位置を取得します。
    			uint64_t SeekPointGet(void);

    			//指定したサイズ文読み込みます。
    			void Read(char* _buffer_, uint64_t _size_);
    			//バイナリデータ書き込み用 4バイト配列をreinterpretで渡している場合はblocksizeはsizeof(uint32_t)等...。
    			void Write(char* _writevalue_, uint32_t _writesize_, uint32_t _writeblocksize_);

    			//SonikStringの吐き出し方法で分けています。
    			//テキストモードでオープンした状態だとファイル内の文字のエンコーディングがUTF-8に代わるといったことはありません。
    			//バイナリで、追記以外...つまりすべての文字を再出力..となった場合は変換されるかもしれません。
    			void Write_char(SonikLib::SonikString& _writevalue_);
    			void Write_UTF8(SonikLib::SonikString& _writevalue_);
    			void Write_UTF16(SonikLib::SonikString& _writevalue_);

    			//テキストモード専用　指定された行数文TEXTを読み込みます。
    			void ReadText_Line(SonikLib::SonikString& _str_, uint64_t GetRowCnt =1);
    			//テキストモード専用　指定された行数文TEXTを読み込ます。改行は削除され、改行で分割されたQueueとして取得します。
    			void ReadText_LineQueue(SonikLib::SonikAtomicQueue<SonikString>& _GetLineQueue_, uint64_t GetRowCnt =1);
		};

    }; //end namespace FileSystemController

}; //end namespace SonikLib

#endif /* SONIKFILECONTROLLER_H_ */
