/*
 * SonikAllocateExUserUseObjectSmtPtr.h
 *
 *  Created on: 2016/01/07
 *      Author: SONIK
 */

#ifndef ALLOCATOR_SONIKRAWALLOCATEEXUSERUSEOBJECTSMTPTR_H_
#define ALLOCATOR_SONIKRAWALLOCATEEXUSERUSEOBJECTSMTPTR_H_

#include "..\\SonikCASUse.h"
#include <utility>
#include <new>
#include "SonikBaundaryTagAllocateExBase.h"

namespace SonikBTMA
{
	class SonikBaundaryTagAllocateEx;
};

namespace SonikLib
{
#ifdef __SONIK_I686__

	class SonikRawAllocObjectPtr
	{
		template <class GetType>
		friend class SonikAllocSmtPtr;

	private:
		SonikBTMA::SonikBaundaryTagAllocateEx_Base* pObj;
		void (__cdecl *pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*);
		std::atomic<uint32_t>* Counter;
//		SonikLib::SonikAtomicLock shortblock_;

	public:
		//default constructor
		SonikRawAllocObjectPtr(void)
		:pObj(0)
		,pFunc(0)
		,Counter(0)
		{
			try
			{
				Counter = new std::atomic<uint32_t>;
			}catch(std::bad_alloc&)
			{
				throw;
			}

			Counter->store(1);
		};

		//constructor OverLoad
		SonikRawAllocObjectPtr(SonikBTMA::SonikBaundaryTagAllocateEx* SetAllocPointer, void (__cdecl *Set_pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*), std::atomic<uint32_t>* SetCountObj)
		{
			pObj = reinterpret_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*>( SetAllocPointer );
			pFunc = Set_pFunc;
			Counter = SetCountObj;

			//Addref
			uint32_t TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};
		};

		//CopyConstructor
		SonikRawAllocObjectPtr(const SonikRawAllocObjectPtr& t_his)
		:pFunc(0)
		,Counter(0)
		{
			//３つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			//Addref
			uint32_t TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

		};

		//destructor (memo: マルチスレッド時、代入演算子とかぶるかもしれないので一応ブロックしておく)
		~SonikRawAllocObjectPtr(void)
		{
			//moveされていれば何もしない。
			if(Counter == 0)
			{
				return;
			};

			//Release
			uint32_t TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				if( pFunc != 0 )
				{
					(*pFunc)(pObj);
				};

				delete Counter;
			};

		};

		//operator = OverLoad(Move Semantics)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikRawAllocObjectPtr& operator =(SonikRawAllocObjectPtr&& MoveObj)
		{
			if( this == &MoveObj )
			{
				return (*this);
			};

			//Release
			uint32_t TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				if( pFunc != 0 )
				{
					(*pFunc)(pObj);
				};

				delete Counter;
			};

			pObj = static_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*&&>(MoveObj.pObj);
			pFunc = std::move(MoveObj.pFunc);
			Counter = static_cast<std::atomic<uint32_t>*&&>(MoveObj.Counter);

			MoveObj.pObj = 0;
			MoveObj.pFunc = 0;
			MoveObj.Counter = 0;

			//AddRef
			TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

			return (*this);
		};

		//operator = OverLoad(Copy)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikRawAllocObjectPtr& operator =(const SonikRawAllocObjectPtr& t_his)
		{
			if( this == (&t_his) )
			{
				return (*this);
			};

			//Release
			uint32_t TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				if( pFunc != 0 )
				{
					(*pFunc)(pObj);
				};

				delete Counter;
			};

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			//Addref
			TmpCnt = Counter->load(std::memory_order::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

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

		SonikRawAllocObjectPtr& operator *(void)
		{
			return (*this);
		};

		SonikRawAllocObjectPtr* operator ->(void)
		{
			return this;
		};


		//Template GetAlloc Array Version
		template <class AllocType, class... ConstructorArg>
		bool GetAllocArray(AllocType*& GetPtr, uint32_t ArrayCount, ConstructorArg... Arg)
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

			GetPtr = reinterpret_cast<AllocType*>(pTmp);

			return true;
		};

		//Template GetAlloc
		template <class AllocType, class... ConstructorArg>
		bool GetAlloc(AllocType*& GetPtr, ConstructorArg... Arg)
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


			GetPtr = reinterpret_cast<AllocType*>(pTmp);

			return true;
		};

		//FreeAlloc
		template <class FreeType>
		void FreeAlloc(FreeType*& pFree)
		{
			if(pFree == 0 )
			{
				return;
			};

			//Destructor Call
			pFree->~FreeType();

			pObj->FreeAlloc(pFree);
		};

		//FreeAlloc Array Version
		template <class FreeType>
		void FreeAlloc(FreeType*& pFree, uint32_t FreeArrayCount)
		{
			if(pFree == 0 || FreeArrayCount == 0)
			{
				return;
			};

			uint32_t tmparray_ = FreeArrayCount;
			FreeType* pControl = pFree;

			do
			{
				pControl->~FreeType();
				pControl += sizeof(FreeType);

				--tmparray_;
			}while(tmparray_ != 0);

			pObj->FreeAlloc(pFree);
		};


	};


#elif defined(__SONIK_x86_64__)

	class SonikRawAllocObjectPtr
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
		SonikRawAllocObjectPtr(void)
		:pObj(0)
		,pFunc(0)
		,Counter(0)
		{

		};

		//constructor OverLoad
		SonikRawAllocObjectPtr(SonikBTMA::SonikBaundaryTagAllocateEx* SetAllocPointer, void (__cdecl *Set_pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*), std::atomic<uint64_t>* SetCountObj)
		{
			pObj = reinterpret_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*>( SetAllocPointer );
			pFunc = Set_pFunc;
			Counter = SetCountObj;

			//Addref
			uint64_t TmpCnt = Counter->load(std::memory_order_acquire);
			while( !Counter->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};
		};

		//CopyConstructor
		SonikRawAllocObjectPtr(const SonikRawAllocObjectPtr& t_his)
		:pFunc(0)
		,Counter(0)
		{
//			//コピーコンストラクタなので自分自身はロックする必要がない。
//			//相手側が別スレッドで、デストラクタやムーブ代入がコールされ、参照先が無効になる可能性があるのでロック。
//			t_his.shortblock_.lock();

			//ロック後無効か有効化チェック。
			if( t_his.Counter == 0 )
			{
//				//カウンタが無効なので何もしない。
//				t_his.shortblock_.Unlock();
				return;
			};

			//ポインタが生きているようなので、値をコピー
			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			//AddRef(カウントアップ)
			//一応ビジーループ
			uint64_t first_ = Counter->load(std::memory_order_acquire);
			while( Counter->compare_exchange_strong(first_, first_ +1) )
			{
				//busy loop
			};

//			t_his.shortblock_.Unlock();

		};

		//destructor (memo: マルチスレッド時、代入演算子とかぶるかもしれないので一応ブロックしておく)
		~SonikRawAllocObjectPtr(void)
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
		SonikRawAllocObjectPtr& operator =(SonikRawAllocObjectPtr&& MoveObj)
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
			//Release
			if( Counter != 0 )
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
			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			MoveObj.pObj = 0;
			MoveObj.Counter = 0;

			//アンロック
			shortblock_.Unlock();
			MoveObj.shortblock_.Unlock();

			return (*this);
		};

		//operator = OverLoad(Copy)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikRawAllocObjectPtr& operator =(const SonikRawAllocObjectPtr& t_his)
		{
			//コピー元とコピー先が同一なら何もしない。
			if( this == (&t_his) )
			{
				return (*this);
			};

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
			//4つくらいならmemcpyとかよりこっちのほうが速そう
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

		SonikRawAllocObjectPtr& operator *(void)
		{
			return (*this);
		};

		SonikRawAllocObjectPtr* operator ->(void)
		{
			return this;
		};


		//Template GetAlloc Array Version
		template <class AllocType, class... ConstructorArg>
		bool GetAllocArray(AllocType*& GetPtr, uint64_t ArrayCount, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			int8_t* pCTmp = 0;
			std::atomic<uint64_t>* pAtomicTmp = 0;
			uint64_t looped = 0;
			uint64_t tmparray_ = ArrayCount;

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

			GetPtr = reinterpret_cast<AllocType*>(pTmp);

			return true;
		};

		//Template GetAlloc
		template <class AllocType, class... ConstructorArg>
		bool GetAlloc(AllocType*& GetPtr, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			int8_t* pCTmp = 0;
			std::atomic<uint64_t>* pAtomicTmp = 0;
			uint64_t looped = 0;
			uint64_t tmparray_ = 1; //配列数省略の場合は一つしか作らない。

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


			GetPtr = reinterpret_cast<AllocType*>(pTmp);

			return true;
		};

		//FreeAlloc
		template <class FreeType>
		void FreeAlloc(FreeType*& pFree)
		{
			if(pFree == 0 )
			{
				return;
			};

			//Destructor Call
			pFree->~FreeType();

			pObj->FreeAlloc(pFree);
		};

		//FreeAlloc Array Version
		template <class FreeType>
		void FreeAlloc(FreeType*& pFree, uint64_t FreeArrayCount)
		{
			if(pFree == 0 || FreeArrayCount == 0)
			{
				return;
			};

			uint64_t tmparray_ = FreeArrayCount;
			FreeType* pControl = pFree;

			do
			{
				pControl->~FreeType();
				pControl += sizeof(FreeType);

				--tmparray_;
			}while(tmparray_ != 0);

			pObj->FreeAlloc(pFree);
		};


	};

#endif

};//end namespace


#endif /* ALLOCATOR_SONIKRAWALLOCATEEXUSERUSEOBJECTSMTPTR_H_ */
