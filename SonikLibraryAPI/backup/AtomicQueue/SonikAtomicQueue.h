/*
 * SonikAtomicQueue.h
 *
 *  Created on: 2015/09/22
 *      Author: SONIC
 */

#ifndef SONIKATOMICQUEUE_H_
#define SONIKATOMICQUEUE_H_

//#include <atomic>
//#include <new>
#include "..\\SonikAllocateUse.h"
#include "..\\SonikCASLockUse.h"

namespace sonik_WarksSystem
{
	class FunctionSystem_Base;

};

namespace SonikQueue
{
	template <class QueueType>
	class SonikAtomicQueue;

};

//前方宣言ここまで=================

namespace SonikAtomicNode
{

	template<class ClsType>
	class QueueNode
	{
		friend SonikQueue::SonikAtomicQueue<ClsType>;

		typedef SonikAtomicNode::QueueNode<ClsType> TypeNode;
	private:
		ClsType m_TemplateObject;
		bool SentinelFlag; //番兵フラグ

		TypeNode* Next;

	public:

		QueueNode(void)
		:SentinelFlag(true)
		,Next(0)
		{
		};

		~QueueNode(void)
		{

		};

		void SetNext(TypeNode* pSetNext)
		{
			Next = pSetNext;
		};

		TypeNode* GetNext(void)
		{
			return Next;
		};

		void SetSentinelFlag(bool Setflag)
		{
			SentinelFlag = Setflag;
		};

		const bool& GetSentinelFlag(void)
		{
			return SentinelFlag;
		};

		void SetClsTypeObject(ClsType&& SetItem)
		{
			m_TemplateObject = static_cast<ClsType&&>(SetItem);
		};
		ClsType GetClsTypeObject(void)
		{
			return m_TemplateObject;
		};

	};

};


namespace SonikQueue
{
	template<class QueueType>
	class SonikAtomicQueue
	{
		typedef SonikAtomicNode::QueueNode<QueueType> TypeNode;

	private:
		TypeNode* _first;
		TypeNode* _last;

		//普通にキューすると、最終の一つ手前に挿入等ができないので、最終要素リストとして以下を使う。
		TypeNode* endspot_first;
		TypeNode* endspot_last;

		//おおよそのキュー数(指定した数より使用できる数は少なくなります)
		unsigned long Queue_RoundCount;

		//ノード領域のためのアロケータクラスです。
		SonikLib::SonikRawAllocObjectPtr NodeAllocate;

		//アトミックブロッククラス。マルチスレッド対応にするための排他制御クラスです。
		SonikCAS::SonikAtomicLock shortblock;


	public:
		SonikAtomicQueue(void)
		:Queue_RoundCount(150)
//		,ShortBlock(false)
		{
			try
			{
				unsigned long SetSize = (sizeof(TypeNode) * Queue_RoundCount) + ((sizeof(SonikBaundaryBlock::SonikBaundaryPre) + sizeof(SonikBaundaryBlock::SonikBaundaryPost)) * Queue_RoundCount);
				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(NodeAllocate, SetSize) )
				{
					throw -1;
				};


				TypeNode* pTmpNode;
				TypeNode* pTmpNode_EndSpot;
				if( !NodeAllocate->GetAlloc(pTmpNode) )
				{
					throw -1;
				};

				if( !NodeAllocate->GetAlloc(pTmpNode_EndSpot) )
				{
					throw -1;
				};

				_first = pTmpNode;
				_last = pTmpNode;

				endspot_first = pTmpNode_EndSpot;
				endspot_last = pTmpNode_EndSpot;

			}catch(...)
			{
				throw -1;
			};

		};

		SonikAtomicQueue(unsigned long QueueItemMax)
		:Queue_RoundCount(QueueItemMax)
//		,ShortBlock(false)
		{
			try
			{

				unsigned long SetSize = (sizeof(TypeNode) * Queue_RoundCount) + ((sizeof(SonikBaundaryBlock::SonikBaundaryPre) + sizeof(SonikBaundaryBlock::SonikBaundaryPost)) * Queue_RoundCount);
				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(NodeAllocate, SetSize) )
				{
					throw -1;
				};


				TypeNode* pTmpNode;
				TypeNode* pTmpNode_EndSpot;
				if( !NodeAllocate->GetAlloc(pTmpNode) )
				{
					throw -1;
				};

				if( !NodeAllocate->GetAlloc(pTmpNode_EndSpot) )
				{
					throw -1;
				};


				_first = pTmpNode;
				_last = pTmpNode;

				endspot_first = pTmpNode_EndSpot;
				endspot_last = pTmpNode_EndSpot;

			}catch(...)
			{
				throw -1;
			};

		};


		~SonikAtomicQueue(void)
		{
			TypeNode* pTmp;

			while( !_first->SentinelFlag )
			{
				pTmp = static_cast< TypeNode*&& >(_first);
				_first = static_cast< TypeNode*&& >(pTmp->Next);

//				pTmp.~SonikAllocSmtPtr();
				NodeAllocate->FreeAlloc(pTmp);
			};

			while( !endspot_first->SentinelFlag )
			{
				pTmp = static_cast< TypeNode*&& >(_first);
				endspot_first = static_cast< TypeNode*&& >(pTmp->Next);

//				pTmp.~SonikAllocSmtPtr();
				NodeAllocate->FreeAlloc(pTmp);
			};

//			_first.~SonikAllocSmtPtr();
//			_last.~SonikAllocSmtPtr();

		};

		//書き込み(エンキュー)
		bool EnQueue(QueueType SetData, bool SetEndEnQueue =false)
		{
			TypeNode* pTmp;
			TypeNode* pPrev;
			TypeNode* pGetPtr;

			//新しいモノが番兵になるスタイル。
			if( !NodeAllocate->GetAlloc( pGetPtr ) )
			{
				return false;
			};

			if( !SetEndEnQueue )
			{
				shortblock.lock();

//				if(_last == pGetPtr)
//				{
//					NodeAllocate->GetAlloc( pGetPtr );
//				};

				pPrev = static_cast<TypeNode*&&>(_last);
				_last = pGetPtr;
				pPrev->Next = static_cast<TypeNode*&&>(pGetPtr);

				shortblock.Unlock();

				pPrev->m_TemplateObject = static_cast<QueueType&&>(SetData);
				pPrev->SentinelFlag = false;

			}else
			{
				shortblock.lock();

				pPrev = static_cast<TypeNode*&&>(endspot_last);
				endspot_last = pGetPtr;
				pPrev->Next = static_cast<TypeNode*&&>(pGetPtr);

				shortblock.Unlock();

				pPrev->m_TemplateObject = static_cast<QueueType&&>(SetData);
				pPrev->SentinelFlag = false;

			};

			return true;
		};

//		//書き込み(エンキュー)(MoveSemantics)
//		bool EnQueue(QueueType&& SetData)
//		{
//			SonikLib::SonikAllocSmtPtr<TypeNode> pTmp;
//			SonikLib::SonikAllocSmtPtr<TypeNode> pPrev;
//			SonikLib::SonikAllocSmtPtr<TypeNode> pGetPtr;
//
//			//新しいモノが番兵になるスタイル。
//			if( !NodeAllocate->GetAlloc( pGetPtr ) )
//			{
//				return false;
//			};
//
//
//			shortblock.lock();
//
//			pPrev = static_cast<SonikLib::SonikAllocSmtPtr<TypeNode>&&>(_last);
//			_last = pGetPtr;
//			pPrev->Next = static_cast<SonikLib::SonikAllocSmtPtr<TypeNode>&&>(pGetPtr);
//
//			shortblock.Unlock();
//
//			pPrev->m_TemplateObject = static_cast<QueueType&&>(SetData);
//			pPrev->SentinelFlag = false;
//
//			return true;
//		};


		//取得（デキュー)
		bool DeQueue(QueueType& GetValue)
		{
			TypeNode* pTmp;
			QueueType ret;

			shortblock.lock();

			if( _first->SentinelFlag && endspot_first->SentinelFlag )
			{
				shortblock.Unlock();
				return false;
			};

			if(!_first->SentinelFlag)
			{
				pTmp = static_cast<TypeNode*&&>(_first);
				_first = static_cast<TypeNode*&&>(pTmp->Next);

			}else
			{
				pTmp = static_cast<TypeNode*&&>(endspot_first);
				endspot_first = static_cast<TypeNode*&&>(pTmp->Next);

			};

			GetValue = static_cast<QueueType&&>(pTmp->m_TemplateObject);

			NodeAllocate->FreeAlloc(pTmp);

			shortblock.Unlock();

			return true;
		};

	};


};


#endif /* SONIKATOMICQUEUE_H_ */
