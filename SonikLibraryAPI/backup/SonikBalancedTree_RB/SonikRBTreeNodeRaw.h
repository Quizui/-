/*
 * SonikRBTreeNodeRaw.h
 *
 *  Created on: 2016/03/12
 *      Author: SONIC_000
 */

#ifndef SONIKBALANCEDTREE_RB_SONIKRBTREENODERAW_H_
#define SONIKBALANCEDTREE_RB_SONIKRBTREENODERAW_H_

//前方宣言
namespace SonikLib
{
	template <class TreeType>
	class SonikLinerOperator_RBTree;
};

namespace SonikBalanceTree
{
	//前方宣言
	template <class SetDataType>
	class SonikRBTreeRaw;

	//ノードベース
	class SonikRBTreeNodeBaseRaw
	{
		template <class SetDataType>
		friend class SonikRBTreeRaw;

		template <class TreeType>
		friend class SonikLib::SonikLinerOperator_RBTree;

	public:
		//色 列挙
		typedef enum _S_TREE_COLOR
		{
			TreeBlack = 0,
			TreeRed,
		}SonikTreeColor;

	protected:
		//本ノードの色
		unsigned long colors;
		//根であるか？
		bool root_;
		//ノードの値
		unsigned long NodeValue;

		//線形操作用の相互ノードポインタ
		SonikRBTreeNodeBaseRaw* Next;
		SonikRBTreeNodeBaseRaw* Prev;

		//自分の前ノード
		SonikRBTreeNodeBaseRaw* Parent;
		//左の子ノード
		SonikRBTreeNodeBaseRaw* left_;
		//右の子ノード
		SonikRBTreeNodeBaseRaw* right_;

	public:
		SonikRBTreeNodeBaseRaw(void)
	:colors(TreeBlack)
	,root_(false)
	,NodeValue(0)
	,Next(0)
	,Prev(0)
	,Parent(0)
	,left_(0)
	,right_(0)
	{

	};

		~SonikRBTreeNodeBaseRaw(void)
		{

		};

		SonikTreeColor GetLeftColor(void)
		{
			if( left_ != 0 )
			{
				return static_cast<SonikTreeColor>(left_->colors);
			};

			return TreeBlack;
		};

		SonikTreeColor GetRightColor(void)
		{
			if( right_ != 0 )
			{
				return static_cast<SonikTreeColor>(right_->colors);
			};

			return TreeBlack;
		};


	};

	//ノード本体
	template<class DataValueType>
	class SonikRBTreeNodeRaw : public SonikRBTreeNodeBaseRaw
	{
		template <class SetDataType>
		friend class SonikRBTreeRaw;

		template <class TreeType>
		friend class SonikLib::SonikLinerOperator_RBTree;

	private:
		//ノードが持っている外部入力データ
		DataValueType m_data;

	public:
		SonikRBTreeNodeRaw(void)
	{

	};

		~SonikRBTreeNodeRaw(void)
		{
		};

	};

};



#endif /* SONIKBALANCEDTREE_RB_SONIKRBTREENODERAW_H_ */
