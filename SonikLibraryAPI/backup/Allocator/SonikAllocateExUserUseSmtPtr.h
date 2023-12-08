/*
 * SonikAllocateExUserUseSmtPtr.h
 *
 *  Created on: 2015/12/31
 *      Author: Sonik
 */

#ifndef SonikALLOCATEEXUSERUSESMTPTR_H_
#define SonikALLOCATEEXUSERUSESMTPTR_H_

#include "SonikAllocateRawExUserUseObjectSmtPtr.h"
#include "..\\SonikCASLockUse.h"
#include <atomic>
#include <cstdarg>
#include <type_traits>
#include "SonikAllocateExUserUseSmtPtrBase.h"


namespace SonikLib
{

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
		SonikAllocSmtPtr(char* SetPtr, std::atomic<unsigned long>* Set_pCount, SonikLib::SonikAllocObjectPtr& SetObjSmtPtr, unsigned long Arrays)
		{
			GetPtr = SetPtr;
			pCount = Set_pCount;
			pObj = SetObjSmtPtr; //ここはムーブ禁止！
			ArrayCount_ = Arrays;
		};

		//copy constructor
		SonikAllocSmtPtr(const SonikAllocSmtPtr<GetType>& t_his)
		{

			const_cast<SonikAllocSmtPtr<GetType>&>(t_his).shortblock_.lock();

			unsigned long first_;	//befor increment atomic value
			unsigned long second_;	//after increment atomic value

			//first step
			//CopySource increment
			if( t_his.pCount != 0 )
			{
				first_ = t_his.pCount->load();
				second_ = first_ + 1;

				while( !t_his.pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ + 1;
				};
			};

			//second step
			//CopyDestination decrement
			if( pCount != 0 )
			{
				first_ = pCount->load();
				second_ = first_ - 1;

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
			};

			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			const_cast<SonikAllocSmtPtr<GetType>&>(t_his).shortblock_.Unlock();

		};

		//destructor
		~SonikAllocSmtPtr(void)
		{
			shortblock_.lock();

			if(pCount == 0)
			{
				shortblock_.Unlock();
				return;
			};

			unsigned long first_;	//befor increment atomic value
			unsigned long second_;	//after increment atomic value

			//CopyDestination decrement
			if( pCount != 0 )
			{
				first_ = pCount->load();
				second_ = first_ - 1;

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

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

			GetPtr = 0;
			pCount = 0;
			ArrayCount_ = 0;

			shortblock_.Unlock();
		};


		//operator = overload move semantics
		SonikAllocSmtPtr<GetType>& operator =(SonikAllocSmtPtr<GetType>&& MoveObj)
		{
			if( this == &MoveObj )
			{
				return (*this);
			};

			MoveObj.shortblock_.lock();
			shortblock_.lock();

			if( GetPtr != 0 )
			{
				unsigned long first_ = pCount->load();	//befor increment atomic value
				unsigned long second_ = first_ - 1;	//after increment atomic value

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

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

			GetPtr = static_cast<char*&&>(MoveObj.GetPtr);
			pCount = static_cast<std::atomic<unsigned long>*&&>(MoveObj.pCount);
			ArrayCount_ = static_cast<unsigned long&&>(MoveObj.ArrayCount_);
			pObj = static_cast<SonikLib::SonikAllocObjectPtr&&>(MoveObj.pObj);

			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			MoveObj.GetPtr = 0;
			MoveObj.pCount = 0;


			MoveObj.shortblock_.Unlock();
			shortblock_.Unlock();

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

			(*pBase).shortblock_.lock();
			shortblock_.lock();

			if( GetPtr != 0 )
			{
				unsigned long first_ = pCount->load();	//befor increment atomic value
				unsigned long second_ = first_ - 1;	//after increment atomic value

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

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

			GetPtr = static_cast<char*&&>((*pBase).GetPtr);
			pCount = static_cast<std::atomic<unsigned long>*&&>((*pBase).pCount);
			ArrayCount_ = static_cast<unsigned long&&>((*pBase).ArrayCount_);
			pObj = static_cast<SonikLib::SonikAllocObjectPtr&&>((*pBase).pObj);

			//ArrayCount_とかはいまのとこ条件判定では使わないので０初期化サボり。
			(*pBase).GetPtr = 0;
			(*pBase).pCount = 0;


			(*pBase).shortblock_.Unlock();
			shortblock_.Unlock();

			return (*this);
		};

		//operator = overload
		SonikAllocSmtPtr<GetType>& operator =(const SonikAllocSmtPtr<GetType>& t_his)
		{
			const_cast<SonikAllocSmtPtr<GetType>&>(t_his).shortblock_.lock();
			shortblock_.Unlock();

			if( this == (&t_his) )
			{
				return (*this);
			};

			unsigned long first_;	//befor increment atomic value
			unsigned long second_;	//after increment atomic value

			//first step
			//CopySource increment
			if( t_his.pCount != 0 )
			{
				first_ = t_his.pCount->load();
				second_ = first_ + 1;

				while( !t_his.pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ + 1;
				};
			};

			//second step
			//CopyDestination decrement
			if( pCount != 0 )
			{
				first_ = pCount->load();
				second_ = first_ - 1;

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
			};

			GetPtr = t_his.GetPtr;
			pCount = t_his.pCount;
			pObj = t_his.pObj;
			ArrayCount_ = t_his.ArrayCount_;

			const_cast<SonikAllocSmtPtr<GetType>&>(t_his).shortblock_.Unlock();
			shortblock_.Unlock();

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

			SonikAllocSmtPtr<GetType>* pBase = reinterpret_cast<SonikAllocSmtPtr<GetType>*>(&t_his);

			(*pBase).shortblock_.lock();
			shortblock_.lock();

			unsigned long first_;	//befor increment atomic value
			unsigned long second_;	//after increment atomic value

			//first step
			//CopySource increment
			if( (*pBase).pCount != 0 )
			{
				first_ = (*pBase).pCount->load();
				second_ = first_ + 1;

				while( !(*pBase).pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ + 1;
				};
			};

			//second step
			//CopyDestination decrement
			if( pCount != 0 )
			{
				first_ = pCount->load();
				second_ = first_ - 1;

				while( !pCount->compare_exchange_strong(first_, second_) )
				{
					second_ = first_ - 1;
				};

				if(second_ == 0)
				{
					unsigned long looped =0;

					do
					{
						reinterpret_cast<GetType*>( (GetPtr + (sizeof(GetType) * looped)) )->~GetType();

						++looped;
						--ArrayCount_;
					}while(ArrayCount_ != 0);

					pObj.pObj->FreeAlloc(GetPtr);
				};
			};

			GetPtr = (*pBase).GetPtr;
			pCount = (*pBase).pCount;
			pObj = (*pBase).pObj;
			ArrayCount_ = (*pBase).ArrayCount_;

			(*pBase).shortblock_.Unlock();
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
		//operator == overload unsigned long
		bool operator ==(unsigned long AddressVal)
		{
			return ( (reinterpret_cast<unsigned long>(GetPtr) == AddressVal) ? true:false );
		};

		//operator != overload
		bool operator !=(const SonikAllocSmtPtr<GetType>& t_his)
		{
			return ( (GetPtr != t_his.GetPtr) ? true:false );
		};
		//operator != overload unsigned long
		bool operator !=(unsigned long AddressVal)
		{
			return ( (reinterpret_cast<unsigned long>(GetPtr) != AddressVal) ? true:false );
		};

		//operator * overload
		GetType& operator *(void)
		{
			return (*reinterpret_cast<GetType*>(GetPtr));
		};

		//operator [] overload
		GetType& operator [](unsigned long index)
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


//	//アロケータへのスマートポインタ
//	class SonikAllocObjectSmtPtr
//	{
//	private:
//		SonikAllocPtr::SonikAllocExPtr SBMAllocExSmtPtr;
//
//	public:
//		//Default Constructor
//		SonikAllocObjectSmtPtr(void)
//		{
//			//no process;
//		};
//
//		//Constructor OverLoad
//		SonikAllocObjectSmtPtr(SonikAllocPtr::SonikAllocExPtr& SetAllocSmtPtr)
//		{
//			SBMAllocExSmtPtr = SetAllocSmtPtr;
//		};
//
//		//Copy Constructor
//		SonikAllocObjectSmtPtr(const SonikAllocObjectSmtPtr& t_his)
//		{
//			SBMAllocExSmtPtr = t_his.SBMAllocExSmtPtr;
//		};
//
//		//Destructor
//		~SonikAllocObjectSmtPtr(void)
//		{
//			SBMAllocExSmtPtr.~SonikAllocExPtr();
//		};
//
//		//Template GetAlloc
//		template <class AllocType>
//		bool GetAlloc(SonikAllocSmtPtr<AllocType>& GetSmtPtr, unsigned long ArrayCount =1)
//		{
//			void* pTmp = 0;
//			char* pCTmp = 0;
//			std::atomic<unsigned long>* pAtomicTmp = 0;
//			unsigned long looped = 0;
//			unsigned long tmparray_ = ArrayCount;
//
//			if( !SBMAllocExSmtPtr->GetAlloc(pTmp, pAtomicTmp, sizeof(AllocType), ArrayCount) )
//			{
//				return false;
//			};
//
//
//			pCTmp = reinterpret_cast<char*>(pTmp);
//			try
//			{
//				do
//				{
//					new( pCTmp + sizeof(AllocType) * looped ) AllocType;
//
//					++looped;
//					--tmparray_;
//				}while(tmparray_ != 0);
//
//			}catch(...)
//			{
//				SBMAllocExSmtPtr->FreeAlloc(pTmp);
//				return false;
//			};
//
//
//			SonikAllocSmtPtr<AllocType> TmpSmtPtr(pCTmp, pAtomicTmp, SBMAllocExSmtPtr, ArrayCount);
//
//			GetSmtPtr = TmpSmtPtr;
//
//			return true;
//		};
//
//		//operator = overload
//		SonikAllocObjectSmtPtr& operator =(const SonikAllocObjectSmtPtr& t_his)
//		{
//			if( this != &t_his )
//			{
//				SBMAllocExSmtPtr = t_his.SBMAllocExSmtPtr;
//			};
//
//			return (*this);
//		};
//		//operator = overload
//		SonikAllocObjectSmtPtr& operator =(SonikAllocObjectSmtPtr&& MoveObj)
//		{
//			if( this != &MoveObj )
//			{
//				SBMAllocExSmtPtr = static_cast<SonikAllocPtr::SonikAllocExPtr&&>(MoveObj.SBMAllocExSmtPtr);
//
//			};
//
//			return (*this);
//		};
//
//
//		//operator * overload
//		SonikAllocObjectSmtPtr& operator *(void)
//		{
//			return (*this);
//		};
//
//		//operator -> overload
//		SonikAllocObjectSmtPtr* operator ->(void)
//		{
//			return this;
//		};
//
//	};

};



#endif /* SonikALLOCATEEXUSERUSESMTPTR_H_ */
