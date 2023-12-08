/*
 * SonikPriorityListNode.h
 *
 *  Created on: 2016/03/15
 *      Author: SONIC_000
 */

#ifndef SONIKPRIORITYLIST_SONIKPRIORITYLISTNODE_H_
#define SONIKPRIORITYLIST_SONIKPRIORITYLISTNODE_H_

namespace SonikLib
{
	template <class ListType>
	class SonikLinerOperator_PriorityList;
};

namespace SonikList
{
	template <class ListType>
	class SonikPriorityList;
};

namespace SonikListNode
{
	class SonikListNodeBase
	{
		template <class ListType>
		friend class SonikLib::SonikLinerOperator_PriorityList;

		template <class ListType>
		friend class SonikList::SonikPriorityList;


	protected:
		SonikListNodeBase* Next;
		SonikListNodeBase* Prev;

	public:
		SonikListNodeBase(void)
		:Next(0)
		,Prev(0)
		{

		};

		virtual ~SonikListNodeBase(void)
		{
			//no process;
		};

	};

	template <class NodeType>
	class SonikPriorityListNode : public SonikListNodeBase
	{
		template <class ListType>
		friend class SonikLib::SonikLinerOperator_PriorityList;

		template <class ListType>
		friend class SonikList::SonikPriorityList;

	private:
		NodeType m_data;

		unsigned long Priority;

		//番兵フラグ
		bool Sentinel_;

	public:
		SonikPriorityListNode(void)
		:Priority(0xFFFFFFFF)
		,Sentinel_(true)
		{

		};

		~SonikPriorityListNode(void)
		{

		};

	};

	class S_Inner_PListQSortNode
	{
	public:
		SonikListNodeBase* Point;
		unsigned long PosNum;
	};

};



#endif /* SONIKPRIORITYLIST_SONIKPRIORITYLISTNODE_H_ */
