/*
 * SonikPriorityListLinearSearch.h
 *
 *  Created on: 2016/03/17
 *      Author: SONIC_000
 */

#ifndef SONIKPRIORITYLIST_SONIKPRIORITYLISTLINEARSEARCH_H_
#define SONIKPRIORITYLIST_SONIKPRIORITYLISTLINEARSEARCH_H_

#include "SonikPriorityListNode.h"

namespace SonikList
{
	template <class ListType>
	class SonikPriorityList;
};

namespace SonikLib
{
	template <class ListTmplateType>
	class SonikLinerOperator_PriorityList
	{
		template <class ListType>
		friend class SonikList::SonikPriorityList;

	private:
		//SonikBalanceTree::SonikRBTreeNodeRaw<TreeType>* pNodes_;
		SonikListNode::SonikListNodeBase* pNodes_;

	public:
		SonikLinerOperator_PriorityList(void)
		:pNodes_(0)
		{

		};

		~SonikLinerOperator_PriorityList(void)
		{

		};

		bool NullPtrCheck(void)
		{
			if( pNodes_ == 0 || reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF )
			{
				return true;
			};

			return false;
		}

		//現在のアクセスポインタを現在のポインタのNext値にします。
		bool NextMove(void)
		{
			pNodes_ = pNodes_->Next;
			if( reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF || pNodes_ == 0)
			{
				return false;
			};

			return true;
		};

		//現在のアクセスポインタを現在のポインタのPrev値にします。
		bool PrevMove(void)
		{
			pNodes_ = pNodes_->Prev;
			if(pNodes_ == 0)
			{
				return false;
			};

			return true;
		};

		//前置インクリメント オーバーロード
		//NextMove関数をコールするのと同義
		bool operator ++(void)
		{
			pNodes_ = pNodes_->Next;
			if( reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF || pNodes_ == 0)
			{
				return false;
			};

			return true;
		};
		//後置インクリメント オーバーロード
		//NextMove関数をコールするのと同義
		bool operator ++(int n)
		{
			pNodes_ = pNodes_->Next;
			if( reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF || pNodes_ == 0)
			{
				return false;
			};

			return true;
		};

		//前置デクリメント オーバーロード
		//PrevMove関数をコールするのと同義
		bool operator --(void)
		{
			pNodes_ = pNodes_->Prev;
			if(pNodes_ == 0)
			{
				return false;
			};

			return true;
		};
		//後置デクリメントオーバーロード
		//PrevMove関数をコールするのと同義
		bool operator --(int n)
		{
			pNodes_ = pNodes_->Prev;
			if(pNodes_ == 0)
			{
				return false;
			};

			return true;
		};

		//比較演算子オーバーロード
		bool operator ==(ListTmplateType& CompareObject)
		{
			if( pNodes_ == 0 || reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF)
			{
				return false;
			};

			if( reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->m_data == CompareObject )
			{
				return true;
			};

			return false;
		};

		bool operator !=(ListTmplateType& CompareObject)
		{
			if( pNodes_ == 0 || reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->Priority == 0xFFFFFFFF)
			{
				return false;
			};

			if( reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->m_data != CompareObject )
			{
				return true;
			};

			return false;
		};

		ListTmplateType GetOperatorValue(void)
		{
			return reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->m_data;
		};

		//現在のオブジェクトにアクセスします。
		ListTmplateType& operator ->(void)
		{
			return reinterpret_cast<SonikListNode::SonikPriorityListNode<ListTmplateType>*>(pNodes_)->m_data;
		};

	};

};



#endif /* SONIKPRIORITYLIST_SONIKPRIORITYLISTLINEARSEARCH_H_ */
