#ifndef SONIKBAUNDARYBLOCK_H_
#define SONIKBAUNDARYBLOCK_H_

#include <cstddef>
#include <cstdint>
#include <atomic>
#include <new>

namespace SonikBTMA
{
	class AllocImpl;
	class SonikBaundaryTagAllocateEx;
};

namespace SonikInnerPtr
{
	//内部完結するポインタクラスです。
	class BTMAInnerPtr;
};

namespace SonikBTMAFreeBlock
{
	class FreeBlockManager;
};

namespace SonikBaundaryBlock
{
#ifdef __SONIK_I686__
	//前置ブロッククラス
	class SonikBaundaryPre
	{
		friend class SonikBTMA::AllocImpl;
		friend class SonikBTMA::SonikBaundaryTagAllocateEx;
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		unsigned long UseUserMemorySize;		//使用領域のみのサイズ
		bool Flag;								//領域使用フラグ
		std::atomic<uint32_t> RefCounter;	//参照カウンタ
		SonikBaundaryPre* freelist_next;		//フリーリストに登録された時に使うポインタ
		SonikBaundaryPre* freelist_prev;

	private:
		//コピーコンストラクタの禁止
		SonikBaundaryPre(SonikBaundaryPre& t_his);

		//代入演算子。クラス代入の禁止
		SonikBaundaryPre& operator =(SonikBaundaryPre& t_his);

	public:
		//コンストラクタ
		SonikBaundaryPre(void);

		//デストラクタ
		~SonikBaundaryPre(void);

		//placement new
		void* operator new(std::size_t size, void* ptr);

		//placement delete
		void operator delete(void* ptr_new, void* heepPtr);
		//placement delete(default)
		void operator delete(void* ptr);


		//後置タグ先頭アドレス値までのバイト数を取得します。
		unsigned long GetGoPostTagSize(void);

		//前置タグ及び、後置タグを除いた、使用中領域のサイズを取得します。
		unsigned long GetUseMemorySize(void);

		//前置タグ、後置タグ、使用中領域のすべての合計サイズを取得します。
		unsigned long GetAllDataSize(void);

		//領域使用中かどうかのフラグを取得します。
		bool GetUsedFlag(void);

		//後置タグ、前置タグを除いた、使用領域のサイズを設定します。
		//引数1: 使用領域サイズを指定します。
		void SetUseUserMemorySize(uint32_t SetSize);

		//領域使用中かどうかのフラグを設定します。
		//引数1: 使用中であればtrue, 使用中でなければfalse を設定します。
		void SetUseFlag(bool SetFlag);

	};

	//��u�^�O�N���X�B
	class SonikBaundaryPost
	{
		friend class SonikBTMA::AllocImpl;
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		//�O�u�^�O�N���X�ւ̃|�C���^
		SonikBaundaryPre* PrePointer;

	private:
		//�R�s�[�R���X�g���N�^�B�R�s�[�̋֎~
		SonikBaundaryPost(SonikBaundaryPost& t_his);
		//������Z�q�I�[�o�[���[�h�B����ƃR�s�[�̋֎~
		SonikBaundaryPost& operator = (SonikBaundaryPost& t_his);

	public:
		//�R���X�g���N�^
		SonikBaundaryPost(void);

		//�f�X�g���N�^
		~SonikBaundaryPost(void);

		//placement new
		void* operator new(std::size_t size, void* ptr);

		//placement delete
		void operator delete(void* ptr_new, void* heepPtr);
		//�f�t�H���gdelete �̃I�[�o�[���[�h�B���ꂪ�Ȃ��ƌx���Ƃ�VC�œf����邻���ȁB
		void operator delete(void* ptr);

		//���݂̈ʒu����O�u�^�O�̃|�C���^���擾����B
		SonikBaundaryPre* GetGoPreTagPtr(void);

		//�O�u�^�O�ւ̃|�C���^���Z�b�g���܂��B
		void SetPrePointer(SonikBaundaryPre* SetPointer);

	};
#elif defined(__SONIK_x86_64__)
	//前置ブロッククラス
	class SonikBaundaryPre
	{
		friend class SonikBTMA::AllocImpl;
		friend class SonikBTMA::SonikBaundaryTagAllocateEx;
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		uint64_t UseUserMemorySize;		//使用領域のみのサイズ
		bool Flag;								//領域使用フラグ
		std::atomic<uint64_t> RefCounter;	//参照カウンタ
		SonikBaundaryPre* freelist_next;		//フリーリストに登録された時に使うポインタ
		SonikBaundaryPre* freelist_prev;

	private:
		//コピーコンストラクタの禁止
		SonikBaundaryPre(SonikBaundaryPre& t_his);

		//代入演算子。クラス代入の禁止
		SonikBaundaryPre& operator =(SonikBaundaryPre& t_his);

	public:
		//コンストラクタ
		SonikBaundaryPre(void);

		//デストラクタ
		~SonikBaundaryPre(void);

		//placement new
        void* operator new(size_t size, void* ptr);

		//placement delete
		void operator delete(void* ptr_new, void* heepPtr);
		//placement delete(default)
		void operator delete(void* ptr);


		//後置タグ先頭アドレス値までのバイト数を取得します。
		uint64_t GetGoPostTagSize(void);

		//前置タグ及び、後置タグを除いた、使用中領域のサイズを取得します。
		uint64_t GetUseMemorySize(void);

		//前置タグ、後置タグ、使用中領域のすべての合計サイズを取得します。
		uint64_t GetAllDataSize(void);

		//領域使用中かどうかのフラグを取得します。
		bool GetUsedFlag(void);

		//後置タグ、前置タグを除いた、使用領域のサイズを設定します。
		//引数1: 使用領域サイズを指定します。
		void SetUseUserMemorySize(uint64_t SetSize);

		//領域使用中かどうかのフラグを設定します。
		//引数1: 使用中であればtrue, 使用中でなければfalse を設定します。
		void SetUseFlag(bool SetFlag);

	};

	//��u�^�O�N���X�B
	class SonikBaundaryPost
	{
		friend class SonikBTMA::AllocImpl;
		friend class SonikBTMAFreeBlock::FreeBlockManager;
	private:
		//�O�u�^�O�N���X�ւ̃|�C���^
		SonikBaundaryPre* PrePointer;

	private:
		//�R�s�[�R���X�g���N�^�B�R�s�[�̋֎~
		SonikBaundaryPost(SonikBaundaryPost& t_his);
		//������Z�q�I�[�o�[���[�h�B����ƃR�s�[�̋֎~
		SonikBaundaryPost& operator = (SonikBaundaryPost& t_his);

	public:
		//�R���X�g���N�^
		SonikBaundaryPost(void);

		//�f�X�g���N�^
		~SonikBaundaryPost(void);

		//placement new
		void* operator new(std::size_t size, void* ptr);

		//placement delete
		void operator delete(void* ptr_new, void* heepPtr);
		//�f�t�H���gdelete �̃I�[�o�[���[�h�B���ꂪ�Ȃ��ƌx���Ƃ�VC�œf����邻���ȁB
		void operator delete(void* ptr);

		//���݂̈ʒu����O�u�^�O�̃|�C���^���擾����B
		SonikBaundaryPre* GetGoPreTagPtr(void);

		//�O�u�^�O�ւ̃|�C���^���Z�b�g���܂��B
		void SetPrePointer(SonikBaundaryPre* SetPointer);

	};
#endif

}

#endif /* SONIKBAUNDARYBLOCK_H_ */
