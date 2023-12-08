/*
 * SonikAllocateExUserUseSmtPtr.h
 *
 *  Created on: 2015/12/31
 *      Author: SONIK
 */

#ifndef SONIKALLOCATEEXUSERUSESMTPTR_H_
#define SONIKALLOCATEEXUSERUSESMTPTR_H_

#include "SonikAllocateExUserUseSmtPtrBase.h"
#include "SonikAllocateRawExUserUseObjectSmtPtr.h"
#include "..\\SonikCASUse.h"
#include <cstdarg>
#include <type_traits>


namespace SonikLib
{
#ifdef __SONIK_I686__
	//アロケータから取得した領域へのテンプレートスマートポインタ
	template <class GetType>
	class SonikAllocSmtPtr : public SonikAllocateSmtPtrBase::SonikAllocSmtPtr_Base
	{
	public:
		//default constructor
		SonikAllocSmtPtr(void)
		{
			//no process;
		};

		//constructor overload
		SonikAllocSmtPtr(int8_t* SetPtr, ::std::atomic<uint32_t>* Set_pCount, SonikAllocObjectPtr& SetObjSmtPtr, uint32_t Arrays)
		{
			GetPtr = SetPtr;
			pCount = Set_pCount;
			pObj = SetObjSmtPtr; //ここはムーブ禁止！
			ArrayCount_ = Arrays;
		};

		//copy constructor
		SonikAllocSmtPtr(const SonikAllocSmtPtr<GetType>& t_his)
		{

			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			//Addref
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

		};

		//destructor
		~SonikAllocSmtPtr(void)
		{
			//moveされていれば何もしない。
			if(pCount == 0)
			{
				return;
			};

			//Release
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};

			if( (TmpCnt -1) == 0 )
			{
				if( GetPtr != 0 )
				{
					uint64_t looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
					pObj.~SonikAllocObjectPtr();

				};

				delete pCount;
			};

			GetPtr = 0;
			pCount = 0;
			ArrayCount_ = 0;

		};


		//operator = overload move semantics
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<GetType>&& MoveObj)
		{
			if( this == &MoveObj )
			{
				return (*this);
			};

			//Release
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				uint32_t looped =0;

				do
				{
					reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

					++looped;
					--ArrayCount_;
				}while(ArrayCount_ != 0);

				pObj.pObj->FreeAlloc(GetPtr);

				delete pCount;
			};

			GetPtr = static_cast<int8_t*&&>(MoveObj.GetPtr);
			pCount = static_cast<::std::atomic<uint32_t>*&&>(MoveObj.pCount);
			ArrayCount_ = static_cast<uint32_t&&>(MoveObj.ArrayCount_);
			pObj = static_cast<SonikAllocObjectPtr&&>(MoveObj.pObj);

			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			MoveObj.GetPtr = 0;
			MoveObj.pCount = 0;


			//Addref
			TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

			return (*this);
		};

		//operator = overload move semantics overload
		template <class MoveType>
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<MoveType>&& MoveObj)
		{
			if( ::std::is_same<GetType, MoveType>::value == false )
			{
				if( ::std::is_base_of<GetType, MoveType>::value == false )
				{
					return (*this);
				};
			};

			if( reinterpret_cast<int8_t*>(this) == reinterpret_cast<int8_t*>(&MoveObj) )
			{
				return (*this);
			};

			SonikAllocSmtPtr<GetType>* pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&MoveObj);

			//Release
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				uint32_t looped =0;

				do
				{
					reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

					++looped;
					--ArrayCount_;
				}while(ArrayCount_ != 0);

				pObj.pObj->FreeAlloc(GetPtr);
				delete pCount;
			};

			GetPtr = static_cast<int8_t*&&>((*pBase).GetPtr);
			pCount = static_cast<::std::atomic<uint32_t>*&&>((*pBase).pCount);
			ArrayCount_ = static_cast<uint32_t&&>((*pBase).ArrayCount_);
			pObj = static_cast<SonikAllocObjectPtr&&>((*pBase).pObj);

			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			(*pBase).GetPtr = 0;
			(*pBase).pCount = 0;

			//Addref
			TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

			return (*this);
		};

		//operator = overload
		SonikAllocSmtPtr<GetType>& operator =(const SonikAllocSmtPtr<GetType>& t_his)
		{

			if( this == (&t_his) )
			{
				return (*this);
			};

			//Release
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};

			if( (TmpCnt -1) == 0 )
			{
				uint32_t looped =0;

				do
				{
					reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

					++looped;
					--ArrayCount_;
				}while(ArrayCount_ != 0);

				pObj.pObj->FreeAlloc(GetPtr);

			};

			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			//Addref
			TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

			return (*this);
		};

		//operator = overload
		template <class CpyType>
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<CpyType>& t_his)
		{
			if( ::std::is_same<GetType, CpyType>::value == false )
			{
				if( ::std::is_base_of<GetType, CpyType>::value == false )
				{
					return (*this);
				};
			};

			if( reinterpret_cast<int8_t*>(this) == reinterpret_cast<int8_t*>(&t_his) )
			{
				return (*this);
			};

			SonikAllocSmtPtr<GetType>* pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&t_his);

			if( this == (&t_his) )
			{
				return (*this);
			};

			//Release
			uint32_t TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( pCount->compare_exchange_strong(TmpCnt, TmpCnt-1) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				uint32_t looped =0;

				do
				{
					reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

					++looped;
					--ArrayCount_;
				}while(ArrayCount_ != 0);

				pObj.pObj->FreeAlloc(GetPtr);

			};

			GetPtr = (*pBase).GetPtr;
			pCount = (*pBase).pCount;
			pObj = (*pBase).pObj;
			ArrayCount_ = (*pBase).ArrayCount_;


			//Addref
			TmpCnt = pCount->load(std::memory_order::memory_order_acquire);
			while( !pCount->compare_exchange_strong(TmpCnt, TmpCnt+1) )
			{
				//no process
			};

			return (*this);
		};

		//Pointer Up Cast
		template <class UpCastType>
		bool PtrUpCast(SonikAllocSmtPtr<UpCastType>& GetSmtPtr)
		{
			if( ::std::is_base_of<GetType, UpCastType>::value == true )
			{
				SonikAllocSmtPtr<GetType>* pBase;
				pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&GetSmtPtr);

				(*pBase) = (*this);
				return true;
			};

			return false;

		};

		//operator == overload class
		bool operator ==(const SonikAllocSmtPtr<GetType>& t_his)
											{
			return ( (GetPtr == t_his.GetPtr) ? true:false );
											};
		//operator == overload unsigned long
		bool operator ==(uintptr_t AddressVal)
											{
			return ( (reinterpret_cast<uintptr_t>(GetPtr) == AddressVal) ? true:false );
											};

		//operator != overload
		bool operator !=(const SonikAllocSmtPtr<GetType>& t_his)
											{
			return ( (GetPtr != t_his.GetPtr) ? true:false );
											};
		//operator != overload unsigned long
		bool operator !=(uintptr_t AddressVal)
											{
			return ( (reinterpret_cast<uintptr_t>(GetPtr) != AddressVal) ? true:false );
											};

		//operator * overload
		GetType& operator *(void)
		{
			return (*reinterpret_cast<GetType*>(GetPtr));
		};

		//operator [] overload
		GetType& operator [](uint32_t index)
		{
			return (*reinterpret_cast<GetType*>( GetPtr + (sizeof(GetType) * index) ));
		};

		//operator -> overload
		GetType* operator ->(void)
		{
			GetType* ret_ = reinterpret_cast<GetType*>(GetPtr);
			return ret_;
		};

	};

#elif defined(__SONIK_x86_64__)
	//アロケータから取得した領域へのテンプレートスマートポインタ
	template <class GetType>
	class SonikAllocSmtPtr : public SonikAllocateSmtPtrBase::SonikAllocSmtPtr_Base
	{
	public:
		//default constructor
		SonikAllocSmtPtr(void)
		{
			//no process;
		};

		//constructor overload
		SonikAllocSmtPtr(char* SetPtr, std::atomic<uint64_t>* Set_pCount, SonikLib::SonikAllocObjectPtr& SetObjSmtPtr, uint64_t Arrays)
		{
			GetPtr = reinterpret_cast<int8_t*>(SetPtr);
			pCount = Set_pCount;
			pObj = SetObjSmtPtr; //ここはムーブ禁止！
			ArrayCount_ = Arrays;
		};

		//copy constructor
		SonikAllocSmtPtr(const SonikAllocSmtPtr<GetType>& t_his)
		{
//			//コピーコンストラクタなので自分自身はロックする必要がない。
//			//相手側が別スレッドで、デストラクタやムーブ代入がコールされ、参照先が無効になる可能性があるのでロック。
//			t_his.shortblock_.lock();

			//ロック後無効か有効化チェック。
			if( t_his.pCount == 0 )
			{
				//カウンタが無効なので何もしない。
//				t_his.shortblock_.Unlock();
				return;
			};

			//ポインタが生きているようなので、値をコピー
			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			//AddRef(カウントアップ)
			//一応ビジーループ
			uint64_t first_ = pCount->load(std::memory_order_acquire);
			while( pCount->compare_exchange_strong(first_, first_ +1) )
			{
				//busy loop
			};

//			t_his.shortblock_.Unlock();

		};

		//destructor
		~SonikAllocSmtPtr(void)
		{
			//デストラクタと同時の他の代入処理が走っている可能性が無きにしもあらず（参照渡し先などでのコピー操作)
			//なので操作前にロック
			shortblock_.lock();

			//自身がムーヴされていてポインタが無効になっているかもしれない。
			if( pCount == 0 )
			{
				//無効なのでロック解除して終了
				shortblock_.Unlock();
				return;
			};

			//カウンタが生きているのでRelease(カウントダウン）
			//一応ビジーループ
			uint64_t first_ = pCount->load(std::memory_order_acquire);
			while( !pCount->compare_exchange_strong(first_, first_-1, std::memory_order_acq_rel) )
			{
				//busy loop
			};

			//カウンタが０なら、オブジェクの開放メソッドのコール
			if( first_ -1 == 0 )
			{
				uint64_t looped =0;

				do
				{
					reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

					++looped;
					--ArrayCount_;
				}while(ArrayCount_ != 0);

				pObj.pObj->FreeAlloc(GetPtr);

				pObj.~SonikAllocObjectPtr();
			}

			//3つくらいならmemcpyとかよりこっちのほうが速そう
			shortblock_.Unlock();
			GetPtr = 0;
			pCount = 0;
			ArrayCount_ = 0;

			//すべての処理が終了後、アンロック
			shortblock_.Unlock();

		};


		//operator = overload move semantics
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<GetType>&& MoveObj)
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
			if( pCount != 0 )
			{
				//一応ビジーループ
				uint64_t first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					uint64_t looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
				pObj.~SonikAllocObjectPtr();
			};

			//Move
			GetPtr = static_cast<int8_t*&&>(MoveObj.GetPtr);
			pCount = static_cast<std::atomic<uint64_t>*&&>(MoveObj.pCount);
			ArrayCount_ = static_cast<uint64_t&&>(MoveObj.ArrayCount_);
			pObj = static_cast<SonikLib::SonikAllocObjectPtr&&>(MoveObj.pObj);

			//相手側にセット
			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			MoveObj.GetPtr = 0;
			MoveObj.pCount = 0;

			//アンロック
			shortblock_.Unlock();
			MoveObj.shortblock_.Unlock();

			return (*this);
		};

		//operator = overload move semantics overload
		template <class MoveType>
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<MoveType>&& MoveObj)
		{
			if( std::is_same<GetType, MoveType>::value == false )
			{
				if( std::is_base_of<GetType, MoveType>::value == false )
				{
					return (*this);
				};
			};

			if( reinterpret_cast<char*>(this) == reinterpret_cast<char*>(&MoveObj) )
			{
				return (*this);
			};

			SonikAllocSmtPtr<GetType>* pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&MoveObj);

			//相手も自分もブロックをかける。
			pBase->shortblock_.lock();
			shortblock_.lock();

			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			//Release
			if( pCount != 0 )
			{
				//一応ビジーループ
				uint64_t first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					uint64_t looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
				pObj.~SonikAllocObjectPtr();
			};

			//Move
			GetPtr = static_cast<int8_t*&&>(pBase->GetPtr);
			pCount = static_cast<std::atomic<uint64_t>*&&>(pBase->pCount);
			ArrayCount_ = static_cast<uint64_t&&>(pBase->ArrayCount_);
			pObj = static_cast<SonikLib::SonikAllocObjectPtr&&>(pBase->pObj);

			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			pBase->GetPtr = 0;
			pBase->pCount = 0;

			//MoveなのでAddref(カウントアップ)はしない。

			//Unlock
			shortblock_.Unlock();
			pBase->shortblock_.Unlock();

			return (*this);
		};

		//operator = overload
		SonikAllocSmtPtr<GetType>& operator =(const SonikAllocSmtPtr<GetType>& t_his)
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
			if( pCount != 0 )
			{
				//一応ビジーループ
				first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					uint64_t looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
			};

			//コピー元の情報を取得し、カウントアップする。
			//4つくらいならmemcpyとかよりこっちのほうが速そう
			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			//カウンタが生きているか？
			if( pCount != 0 )
			{
				//生きているご様子なのでカウントアップ
				//一応ビジーループ
				first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_+1, std::memory_order_acq_rel) )
				{
					//busy loop
				};
			};

			//Unlock
			shortblock_.Unlock();
//			t_his.shortblock_.Unlock();

			return (*this);
		};

		//operator = overload
		template <class CpyType>
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<CpyType>& t_his)
		{
			if( std::is_same<GetType, CpyType>::value == false )
			{
				if( std::is_base_of<GetType, CpyType>::value == false )
				{
					return (*this);
				};
			};

			if( reinterpret_cast<char*>(this) == reinterpret_cast<char*>(&t_his) )
			{
				return (*this);
			};

//			SonikAllocSmtPtr<GetType>* pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&t_his);

			t_his.shortblock_.lock();
			shortblock_.lock();

			uint64_t first_ = 0;
			//自分がカウンターを持っていたら、カウンターを一つカウントダウンする。
			if( pCount != 0 )
			{
				//一応ビジーループ
				first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_ -1, std::memory_order_acq_rel) )
				{
					//busy loop
				};

				if( first_ -1 == 0 )
				{
					//自身の管理オブジェクトを開放
					uint64_t looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
			};

			//コピー元の情報を取得し、カウントアップする。
			//4つくらいならmemcpyとかよりこっちのほうが速そう
			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			//カウンタが生きているか？
			if( pCount != 0 )
			{
				//生きているご様子なのでカウントアップ
				//一応ビジーループ
				first_ = pCount->load(std::memory_order_acquire);
				while( !pCount->compare_exchange_strong(first_, first_+1, std::memory_order_acq_rel) )
				{
					//busy loop
				};
			};

			t_his.shortblock_.Unlock();
			shortblock_.Unlock();

			return (*this);
		};

		//Pointer Up Cast
		template <class UpCastType>
		bool PtrUpCast(SonikAllocSmtPtr<UpCastType>& GetSmtPtr)
		{
			if( std::is_base_of<GetType, UpCastType>::value == true )
			{
				SonikAllocSmtPtr<GetType>* pBase;
				pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&GetSmtPtr);

				(*pBase) = (*this);
				return true;
			};

			return false;

		};

		//operator == overload class
		bool operator ==(const SonikAllocSmtPtr<GetType>& t_his)
		{
			return ( (GetPtr == t_his.GetPtr) ? true:false );
		};
		//operator == overload uint64_t
		bool operator ==(uint64_t AddressVal)
		{
			return ( (reinterpret_cast<uint64_t>(GetPtr) == AddressVal) ? true:false );
		};

		//operator != overload
		bool operator !=(const SonikAllocSmtPtr<GetType>& t_his)
		{
			return ( (GetPtr != t_his.GetPtr) ? true:false );
		};
		//operator != overload uint64_t
		bool operator !=(uint64_t AddressVal)
		{
			return ( (reinterpret_cast<uintptr_t>(GetPtr) != AddressVal) ? true:false );
		};

		//operator * overload
		GetType& operator *(void)
		{
			return (*reinterpret_cast<GetType*>(GetPtr));
		};

		//operator [] overload
		GetType& operator [](uint64_t index)
		{
			return (*reinterpret_cast<GetType*>( GetPtr + (sizeof(GetType) * index) ));
		};

		//operator -> overload
		GetType* operator ->(void)
		{
			GetType* ret_ = reinterpret_cast<GetType*>(GetPtr);
			return ret_;
		};

	};

#endif
};



#endif /* SONIKALLOCATEEXUSERUSESMTPTR_H_ */
