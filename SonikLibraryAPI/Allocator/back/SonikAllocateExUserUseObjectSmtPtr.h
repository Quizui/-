/*
 * SonikAllocateExUserUseObjectSmtPtr.h
 *
 *  Created on: 2016/01/07
 *      Author: SONIK
 */

#ifndef ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_
#define ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_

#include "..\\SonikCASUse.h"
#include <utility>
#include <cstdint>
#include "SonikBaundaryTagAllocateExBase.h"

namespace SonikBTMA
{
	class SonikBaundaryTagAllocateEx;
};

namespace SonikLib
{
	//前方宣言=========================
	template <class GetType>
	class SonikAllocSmtPtr;

	//=================================
#ifdef __SONIK_I686__
//32bit definition
	class SonikAllocObjectPtr
	{
		template <class GetType>
		friend class SonikAllocSmtPtr;

	private:
		SonikBTMA::SonikBaundaryTagAllocateEx_Base* pObj;
		void (__cdecl *pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*);
		std::atomic<uint32_t>* Counter;
		SonikLib::SonikAtomicLock shortblock_;

	public:
		//default constructor
		SonikAllocObjectPtr(void)
		:pObj(0)
		,pFunc(0)
		,Counter(0)
		{

		};

		//constructor OverLoad
		SonikAllocObjectPtr(SonikBTMA::SonikBaundaryTagAllocateEx* SetAllocPointer, void (__cdecl *Set_pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*), std::atomic<uint32_t>* SetCountObj)
		{
			pObj = reinterpret_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*>( SetAllocPointer );
			pFunc = Set_pFunc;
			Counter = SetCountObj;
		};

		//CopyConstructor (memo: おそらくマルチスレッド時は自身をブロックする必要はない。)
		SonikAllocObjectPtr(const SonikAllocObjectPtr& t_his)
		:pFunc(0)
		,Counter(0)
		{
			//コピーコンストラクタなので自分自身はロックする必要がない。
//			t_his.shortblock_.lock();

			//ロック後無効か有効化チェック。
			if( t_his.Counter == 0 )
			{
				//カウンタが無効なので何もしない。
//				t_his.shortblock_.Unlock();
				return;
			};

			//一応ビジーループ
			uint32_t first_ = t_his.Counter->load(std::memory_order::memory_order_acquire);
			while( !t_his.Counter->compare_exchange_strong(first_, first_+1, std::memory_order::memory_order_acq_rel) )
			{
				//busy loop
			};

			//カウントアップしたのでロックを解除してそのまま
//			t_his.shortblock_.Unlock();

			//３つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

		};

		//destructor (memo: マルチスレッド時、代入演算子とかぶるかもしれないので一応ブロックしておく)
		~SonikAllocObjectPtr(void)
		{
			//デストラクタと同時の他の代入処理が走っている可能性が無きにしもあらず（参照渡し先などでのコピー操作)
			//なので操作前にロック
			shortblock_.lock();

			//自身がムーヴされていてポインタが無効になっているかもしれない。
			if( Counter == 0 )
			{
				//無効なのでロック解除して終了
				shortblock_.Unlock();
				return;
			}

			//カウンタが生きているのでRelease(カウントダウン）
			//一応ビジーループ
			uint32_t first_ = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(first_, first_-1, std::memory_order::memory_order_acq_rel) )
			{
				//busy loop
			};

			//カウンタが０なら、オブジェクの開放メソッドのコール
			if( first_ -1 == 0 )
			{
				(*pFunc)(pObj);
			};

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = 0;
			pFunc = 0;
			Counter = 0;

			//すべての処理が終了後、アンロック
			shortblock_.Unlock();

		};

		//operator = OverLoad(Move Semantics)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(SonikAllocObjectPtr&& MoveObj)
		{
			//相手も自分もブロックをかける。
			MoveObj.shortblock_.lock();
			shortblock_.lock();

			if( this == &MoveObj )
			{
				//コピー元とコピー先が同一なら何もせずアンロック
				shortblock_.Unlock();
				MoveObj.shortblock_.Unlock();
				return (*this);
			};

			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			if(Counter != 0)
			{
				//一応ビジーループ
				uint32_t first_ = Counter->load(std::memory_order::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_ -1, std::memory_order::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					(*pFunc)(pObj);
				};
			};

			//Move
			pObj = static_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*&&>(MoveObj.pObj);
			pFunc = std::move(MoveObj.pFunc);
			Counter = static_cast<std::atomic<uint32_t>*&&>(MoveObj.Counter);

			//相手側にセット
			MoveObj.pObj = 0;
			MoveObj.pFunc = 0;
			MoveObj.Counter = 0;

			//Unlock
			shortblock_.Unlock();
			MoveObj.shortblock_.Unlock();

			return (*this);
		};

		//operator = OverLoad(Copy)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(const SonikAllocObjectPtr& t_his)
		{
			//相手も自分もブロックをかける。
//			t_his.shortblock_.lock();
			shortblock_.lock();

			if( this == (&t_his) )
			{
				//コピー元とコピー先が同一なら何もせずアンロック
				shortblock_.Unlock();
//				t_his.shortblock_.Unlock();
				return (*this);
			};

			uint32_t first_ = 0;
			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			if( Counter != 0 )
			{
				//一応ビジーループ
				first_ = Counter->load(std::memory_order::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_ -1, std::memory_order::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					(*pFunc)(pObj);
				};
			};

			//コピー元の情報を取得し、カウントアップする。
			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			//カウンタが生きているか？
			if( Counter != 0 )
			{
				//生きているご様子なのでカウントアップ
				//一応ビジーループ
				first_ = Counter->load(std::memory_order::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_+1, std::memory_order::memory_order_acq_rel) )
				{
					//busy loop
				};
			};

			//Unlock
			shortblock_.Unlock();
//			t_his.shortblock_.Unlock();

			return (*this);
		};

		bool NullPtrCheck(void)
		{
			if( pObj == 0 )
			{
				return true;
			};

			return false;
		};

		SonikAllocObjectPtr& operator *(void)
		{
			return (*this);
		};

		SonikAllocObjectPtr* operator ->(void)
		{
			return this;
		};


		//Template GetAlloc Array Version
		template <class AllocType, class... ConstructorArg>
		bool GetAllocArray(SonikAllocSmtPtr<AllocType>& GetSmtPtr, uint32_t ArrayCount, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			int8_t* pCTmp = 0;
			std::atomic<uint32_t>* pAtomicTmp = 0;
			uint32_t looped = 0;
			uint32_t tmparray_ = ArrayCount;

			if( !pObj->GetAlloc(pTmp, pAtomicTmp, sizeof(AllocType), ArrayCount) )
			{
				return false;
			};


			pCTmp = reinterpret_cast<int8_t*>(pTmp);
			try
			{

				//コンストラクタ引数あり。
				do
				{
					new( pCTmp + sizeof(AllocType) * looped ) AllocType(Arg...);

					++looped;
					--tmparray_;
				}while(tmparray_ != 0);

			}catch(...)
			{
				pObj->FreeAlloc(pTmp);
				return false;
			};


			SonikAllocSmtPtr<AllocType> TmpSmtPtr(pCTmp, pAtomicTmp, (*this), ArrayCount);

			GetSmtPtr = static_cast< SonikAllocSmtPtr<AllocType>&& >(TmpSmtPtr);

			return true;
		};

		//Template GetAlloc
		template <class AllocType, class... ConstructorArg>
		bool GetAlloc(SonikAllocSmtPtr<AllocType>& GetSmtPtr, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			int8_t* pCTmp = 0;
			std::atomic<uint32_t>* pAtomicTmp = 0;
			uint32_t looped = 0;
			uint32_t tmparray_ = 1; //配列数省略の場合は一つしか作らない。

			if( !pObj->GetAlloc(pTmp, pAtomicTmp, sizeof(AllocType), 1) )
			{
				return false;
			};


			pCTmp = reinterpret_cast<int8_t*>(pTmp);
			try
			{

				//コンストラクタ引数あり。
				do
				{
					new( pCTmp + sizeof(AllocType) * looped ) AllocType(Arg...);

					++looped;
					--tmparray_;
				}while(tmparray_ != 0);

			}catch(...)
			{
				pObj->FreeAlloc(pTmp);
				return false;
			};


			SonikAllocSmtPtr<AllocType> TmpSmtPtr(pCTmp, pAtomicTmp, (*this), 1);

			GetSmtPtr = static_cast< SonikAllocSmtPtr<AllocType>&& >(TmpSmtPtr);

			return true;
		};

	};

#elif defined(__SONIK_x86_64__)
//64bit definition
	class SonikAllocObjectPtr
	{
		template <class GetType>
		friend class SonikAllocSmtPtr;

	private:
		SonikBTMA::SonikBaundaryTagAllocateEx_Base* pObj;
		void (__cdecl *pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*);
		std::atomic<uint64_t>* Counter;
		SonikLib::SonikAtomicLock shortblock_;

	public:
		//default constructor
		SonikAllocObjectPtr(void)
		:pObj(0)
		,pFunc(0)
		,Counter(0)
		{

		};

		//constructor OverLoad
		SonikAllocObjectPtr(SonikBTMA::SonikBaundaryTagAllocateEx* SetAllocPointer, void (__cdecl *Set_pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*), std::atomic<uint64_t>* SetCountObj)
		{
			pObj = reinterpret_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*>( SetAllocPointer );
			pFunc = Set_pFunc;
			Counter = SetCountObj;
		};

		//CopyConstructor (memo: おそらくマルチスレッド時は自身をブロックする必要はない。)
		SonikAllocObjectPtr(const SonikAllocObjectPtr& t_his)
		:pFunc(0)
		,Counter(0)
		{
//			//コピーコンストラクタなので自分自身はロックする必要がない。
//			//相手側が別スレッドで、デストラクタやムーブ代入がコールされ、参照先が無効になる可能性があるのでロック。
//			t_his.shortblock_.lock();

			//ロック後無効か有効化チェック。
			if( t_his.Counter == 0 )
			{
				//カウンタが無効なので何もしない。
//				t_his.shortblock_.Unlock();
				return;
			};

			//一応ビジーループ
			uint64_t first_ = t_his.Counter->load(std::memory_order_acquire);
			while( !t_his.Counter->compare_exchange_strong(first_, first_+1, std::memory_order_acq_rel) )
			{
				//busy loop
			};

//			//カウントアップしたのでロックを解除してそのまま
//			t_his.shortblock_.Unlock();

			//３つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

		};

		//destructor (memo: マルチスレッド時、代入演算子とかぶるかもしれないので一応ブロックしておく)
		~SonikAllocObjectPtr(void)
		{
			//デストラクタと同時の他の代入処理が走っている可能性が無きにしもあらず（参照渡し先などでのコピー操作)
			//なので操作前にロック
			shortblock_.lock();

			//自身がムーヴされていてポインタが無効になっているかもしれない。
			if( Counter == 0 )
			{
				//無効なのでロック解除して終了
				shortblock_.Unlock();
				return;
			};

			//カウンタが生きているのでRelease(カウントダウン）
			//一応ビジーループ
			uint64_t first_ = Counter->load(std::memory_order_acquire);
			while( !Counter->compare_exchange_strong(first_, first_-1, std::memory_order_acq_rel) )
			{
				//busy loop
			};

			//カウンタが０なら、オブジェクの開放メソッドのコール
			if( first_ -1 == 0 )
			{
				(*pFunc)(pObj);
			};

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = 0;
			pFunc = 0;
			Counter = 0;

			//すべての処理が終了後、アンロック
			shortblock_.Unlock();

		};

		//operator = OverLoad(Move Semantics)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(SonikAllocObjectPtr&& MoveObj)
		{
			//コピー元とコピー先が同一なら何もしない。
			if( this == &MoveObj )
			{
				return (*this);
			};

			//相手も自分もブロックをかける。
			MoveObj.shortblock_.lock();
			shortblock_.lock();

			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			if(Counter != 0)
			{
				//一応ビジーループ
				uint64_t first_ = Counter->load(std::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					(*pFunc)(pObj);
				};
			};

			//Move
			pObj = static_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*&&>(MoveObj.pObj);
			pFunc = std::move(MoveObj.pFunc);
			Counter = static_cast<std::atomic<uint64_t>*&&>(MoveObj.Counter);

			//相手側にセット
			MoveObj.pObj = 0;
			MoveObj.pFunc = 0;
			MoveObj.Counter = 0;

			//Unlock
			shortblock_.Unlock();
			MoveObj.shortblock_.Unlock();

			return (*this);
		};

		//operator = OverLoad(Copy)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(const SonikAllocObjectPtr& t_his)
		{
			//コピー元とコピー先が同一なら何もしない。
			if( this == (&t_his) )
			{
				return (*this);
			};

//			//相手も自分もブロックをかける。
//			t_his.shortblock_.lock();
			shortblock_.lock();


			uint64_t first_ = 0;
			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			if( Counter != 0 )
			{
				//一応ビジーループ
				first_ = Counter->load(std::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					(*pFunc)(pObj);
				};
			};

			//コピー元の情報を取得し、カウントアップする。
			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			//カウンタが生きているか？
			if( Counter != 0 )
			{
				//生きているご様子なのでカウントアップ
				//一応ビジーループ
				first_ = Counter->load(std::memory_order_acquire);
				while( !Counter->compare_exchange_strong(first_, first_+1, std::memory_order_acq_rel) )
				{
					//busy loop
				};
			};

			//Unlock
			shortblock_.Unlock();
//			t_his.shortblock_.Unlock();

			return (*this);
		};

		bool NullPtrCheck(void)
		{
			if( pObj == 0 )
			{
				return true;
			};

			return false;
		};

		SonikAllocObjectPtr& operator *(void)
		{
			return (*this);
		};

		SonikAllocObjectPtr* operator ->(void)
		{
			return this;
		};


		//Template GetAlloc Array Version
		template <class AllocType, class... ConstructorArg>
		bool GetAllocArray(SonikAllocSmtPtr<AllocType>& GetSmtPtr, uint64_t ArrayCount, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			char* pCTmp = 0;
			std::atomic<uint64_t>* pAtomicTmp = 0;
			uint64_t looped = 0;
			uint64_t tmparray_ = ArrayCount;

			if( !pObj->GetAlloc(pTmp, pAtomicTmp, sizeof(AllocType), ArrayCount) )
			{
				return false;
			};


			pCTmp = reinterpret_cast<char*>(pTmp);
			try
			{

				//コンストラクタ引数あり。
				do
				{
					new( pCTmp + sizeof(AllocType) * looped ) AllocType(Arg...);

					++looped;
					--tmparray_;
				}while(tmparray_ != 0);

			}catch(...)
			{
				pObj->FreeAlloc(pTmp);
				return false;
			};


			SonikAllocSmtPtr<AllocType> TmpSmtPtr(pCTmp, pAtomicTmp, (*this), ArrayCount);

			GetSmtPtr = static_cast< SonikAllocSmtPtr<AllocType>&& >(TmpSmtPtr);

			return true;
		};

		//Template GetAlloc
		template <class AllocType, class... ConstructorArg>
		bool GetAlloc(SonikAllocSmtPtr<AllocType>& GetSmtPtr, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			char* pCTmp = 0;
			std::atomic<uint64_t>* pAtomicTmp = 0;
			uint64_t looped = 0;
			uint64_t tmparray_ = 1; //配列数省略の場合は一つしか作らない。

			if( !pObj->GetAlloc(pTmp, pAtomicTmp, sizeof(AllocType), 1) )
			{
				return false;
			};


			pCTmp = reinterpret_cast<char*>(pTmp);
			try
			{

				//コンストラクタ引数あり。
				do
				{
					new( pCTmp + sizeof(AllocType) * looped ) AllocType(Arg...);

					++looped;
					--tmparray_;
				}while(tmparray_ != 0);

			}catch(...)
			{
				pObj->FreeAlloc(pTmp);
				return false;
			};


			SonikAllocSmtPtr<AllocType> TmpSmtPtr(pCTmp, pAtomicTmp, (*this), 1);

			GetSmtPtr = static_cast< SonikAllocSmtPtr<AllocType>&& >(TmpSmtPtr);

			return true;
		};

	};

#endif

};//end namespace


#endif /* ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_ */
