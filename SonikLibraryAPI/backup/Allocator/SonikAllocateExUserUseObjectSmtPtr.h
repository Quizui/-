/*
 * SonikAllocateExUserUseObjectSmtPtr.h
 *
 *  Created on: 2016/01/07
 *      Author: Sonik
 */

#ifndef ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_
#define ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_

#include "..\\SonikCASLockUse.h"
#include <atomic>
#include <utility>

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

	class SonikAllocObjectPtr
	{
		template <class GetType>
		friend class SonikAllocSmtPtr;

	private:
		SonikBTMA::SonikBaundaryTagAllocateEx_Base* pObj;
		void (__cdecl *pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*);
		std::atomic<unsigned long>* Counter;
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
		SonikAllocObjectPtr(SonikBTMA::SonikBaundaryTagAllocateEx* SetAllocPointer, void (__cdecl *Set_pFunc)(SonikBTMA::SonikBaundaryTagAllocateEx_Base*), std::atomic<unsigned long>* SetCountObj)
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
			unsigned long first_;
			unsigned long second_;

			const_cast<SonikAllocObjectPtr&>(t_his).shortblock_.lock();

			//先にコピー元の参照カウントをインクリメント
			if( t_his.Counter != 0 )
			{
				first_ = t_his.Counter->load();
				second_ = first_ + 1;

				while( !t_his.Counter->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ + 1;
				};
			};


//			//コピー先（自分)のカウンタがあればデクリメントをする。0になれば開放
//			if( Counter != 0 )
//			{
//				first_ = Counter->load();
//				second_ = first_ - 1;
//
//				while( !Counter->compare_exchange_strong(first_, second_) )
//				{
//					second_ = first_ - 1;
//				};
//
//				if( second_ == 0 )
//				{
//					(*pFunc)(pObj);
//				};
//			}

			//３つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;

			const_cast<SonikAllocObjectPtr&>(t_his).shortblock_.Unlock();

		};

		//destructor (memo: マルチスレッド時、代入演算子とかぶるかもしれないので一応ブロックしておく)
		~SonikAllocObjectPtr(void)
		{
			shortblock_.lock();

			if(Counter == 0)
			{
				shortblock_.Unlock();
				return;
			};

			unsigned long first_ = Counter->load();
			unsigned long second_ = first_ -1;

			while( (*Counter).compare_exchange_strong(first_, second_) )
			{
				second_ = first_ - 1;
			};

			if( second_ == 0 )
			{
				(*pFunc)(pObj);
			};

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = 0;
			pFunc = 0;
			Counter = 0;

			shortblock_.Unlock();

		};

		//operator = OverLoad(Move Semantics)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(SonikAllocObjectPtr&& MoveObj)
		{
			MoveObj.shortblock_.lock();
			shortblock_.lock();

			if( this == &MoveObj )
			{
				return (*this);
			};

			if(Counter != 0)
			{
				unsigned long first_ = Counter->load();
				unsigned long second_ = first_ -1;

				while( (*Counter).compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if( second_ == 0 )
				{
					(*pFunc)(pObj);
				};
			};

			pObj = static_cast<SonikBTMA::SonikBaundaryTagAllocateEx_Base*&&>(MoveObj.pObj);
			pFunc = std::move(MoveObj.pFunc);
			Counter = static_cast<std::atomic<unsigned long>*&&>(MoveObj.Counter);

			MoveObj.pObj = 0;
			MoveObj.pFunc = 0;
			MoveObj.Counter = 0;


			MoveObj.shortblock_.Unlock();
			shortblock_.Unlock();

			return (*this);
		};

		//operator = OverLoad(Copy)
		// (memo: デストラクタとかと同時実行される恐れがあるのでブロックしておく。)
		SonikAllocObjectPtr& operator =(const SonikAllocObjectPtr& t_his)
		{
			if( this == (&t_his) )
			{
				return (*this);
			};

			const_cast<SonikAllocObjectPtr&>(t_his).shortblock_.lock();
			shortblock_.lock();


			unsigned long first_;
			unsigned long second_;

			//先にコピー元の参照カウントをインクリメント
			if( t_his.Counter != 0 )
			{
				first_ = t_his.Counter->load();
				second_ = first_ + 1;

				while( !t_his.Counter->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ + 1;
				};
			};

			//コピー先（自分)のカウンタがあればデクリメントをする。0になれば開放
			if( Counter != 0 )
			{
				first_ = Counter->load();
				second_ = first_ - 1;

				while( !Counter->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if( second_ == 0 )
				{
					(*pFunc)(pObj);
				};
			}

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			pObj = t_his.pObj;
			pFunc = t_his.pFunc;
			Counter = t_his.Counter;


			const_cast<SonikAllocObjectPtr&>(t_his).shortblock_.Unlock();
			shortblock_.Unlock();

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
		bool GetAllocArray(SonikAllocSmtPtr<AllocType>& GetSmtPtr, unsigned long ArrayCount, ConstructorArg... Arg)
		{
			void* pTmp = 0;
			char* pCTmp = 0;
			std::atomic<unsigned long>* pAtomicTmp = 0;
			unsigned long looped = 0;
			unsigned long tmparray_ = ArrayCount;

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
			std::atomic<unsigned long>* pAtomicTmp = 0;
			unsigned long looped = 0;
			unsigned long tmparray_ = 1; //配列数省略の場合は一つしか作らない。

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


};//end namespace


#endif /* ALLOCATOR_SONIKALLOCATEEXUSERUSEOBJECTSMTPTR_H_ */
