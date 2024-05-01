/*
 * SonikRBTree.h
 *
 *  Created on: 2016/01/27
 *      Author: SONIK
 */

#ifndef SONIKBALANCEDTREE_RB_SONIKRBTREE_H_
#define SONIKBALANCEDTREE_RB_SONIKRBTREE_H_

#include <utility>
#include <stdint.h>
#include <new>

#include "SonikRB_LinerSerchOperator.hpp"
#include "SonikRBTreeNode.hpp"
#include "../SonikCAS/SonikAtomicLock.h"


//赤黒木
namespace SonikLib
{
	//本体
	template <class SetDataType>
	class SonikRBTree
	{
	private:
		typedef SonikLib_Node::SonikRBTreeNodeBase NodesBase;
		typedef SonikLib_Node::SonikRBTreeNode<SetDataType> Nodes;

	private:
		SonikRBTree(const SonikRBTree<SetDataType>& _copy_) =delete;
		SonikRBTree(SonikRBTree<SetDataType>&& _move_) = delete;
		SonikRBTree& operator =(const SonikRBTree<SetDataType>& _copy_) = delete;
		SonikRBTree& operator =(SonikRBTree<SetDataType>&& _move_) = delete;

		//アロケータへのスマートポインタ
		//SonikLib::SonikRawAllocObjectPtr AllocSmtPtr_;

		//フリーリスト
		NodesBase* m_FreeArea;

		//根のノードへのスマートポインタ
		NodesBase* RootNode;
		//線形走査のノードポインタ
		NodesBase* LinerTop;
		NodesBase* LinerEnd;

		//排他処理ロック
		SonikLib::S_CAS::SonikAtomicLock atmlock_;

	private:
		//回転基準軸を指定し、そこを基準に木を右回転させます。
		inline NodesBase* RightRotateTree(NodesBase* Node_)
		{
			NodesBase* LeftNode_;
			NodesBase* TopParentNode_;

			LeftNode_ = Node_->left_;
			TopParentNode_ = Node_->Parent;

			if( Node_->root_ )
			{
				LeftNode_->root_ = true;
				Node_->root_ = false;
				RootNode = LeftNode_;
			};

			Node_->Parent = LeftNode_;
			Node_->left_ = LeftNode_->right_;

			if(LeftNode_->right_ != 0)
			{
				LeftNode_->right_->Parent = Node_;
			};

			LeftNode_->Parent = TopParentNode_;
			LeftNode_->right_ = Node_;

			if( TopParentNode_ != 0 )
			{
				//				if( TopParentNode_->left_->NodeValue == Node_->NodeValue )
				//				{
				//					TopParentNode_->left_ = LeftNode_;
				//				}else
				//				{
				TopParentNode_->right_ = LeftNode_;
				//				}
			};

			LeftNode_->colors = Node_->colors;
			Node_->colors = ((~(Node_->colors)) & 0x01);

			return LeftNode_;
		};

		//回転基準軸を指定し、そこを基準に木を左回転させます。
		inline NodesBase* LeftRotateTree(NodesBase* Node_)
		{
			NodesBase* RightNode_;
			NodesBase* TopParentNode_;

			RightNode_ = Node_->right_;
			TopParentNode_ = Node_->Parent;

			if( Node_->root_ )
			{
				RightNode_->root_ = true;
				Node_->root_ = false;
				RootNode = RightNode_;
			};

			Node_->Parent = RightNode_;
			Node_->right_ = RightNode_->left_;

			if(RightNode_->left_ != 0)
			{
				RightNode_->left_->Parent = Node_;
			};

			RightNode_->Parent = TopParentNode_;
			RightNode_->left_ = Node_;


			if( TopParentNode_ != 0 )
			{
				if( TopParentNode_->left_->NodeValue == Node_->NodeValue )
				{
					TopParentNode_->left_ = RightNode_;
				}else
				{
					TopParentNode_->right_ = RightNode_;
				}
			};


			RightNode_->colors = Node_->colors;
			Node_->colors = ((~(Node_->colors)) & 0x01);

			return RightNode_;
		};

		inline void IsBarancedProcess(NodesBase*& Node_)
		{
			//ファーストパターンチェック
			if( Node_->Parent->right_ == 0 )
			{
				//祖父の右の子がいなければ、右回転を行う。
				Node_ = RightRotateTree(Node_->Parent);

				//回転後に祖父の左の子がいなければ、更に左回転を行う。
				if((!Node_->root_) && Node_->Parent->left_ == 0)
				{
					Node_ = LeftRotateTree(Node_->Parent);
				};

			}else
			{
				//祖父の右の子がいれば、祖父の両側の子の色を黒にし、祖父を赤にしてさらに上をチェック
				NodesBase* ControlNode = Node_->Parent;

				//左の子を見つけられなければ左回転を行う
				if(ControlNode->left_ == 0)
				{
					ControlNode = LeftRotateTree(ControlNode);
				}else
				{
					ControlNode->left_->colors = NodesBase::TreeBlack;
					ControlNode->right_->colors = NodesBase::TreeBlack;
				};

				if(ControlNode->root_)
				{
					//祖父がルートであれば即終了
					return;
				};

				ControlNode->colors = NodesBase::TreeRed;


				ControlNode = ControlNode->Parent;

				while(1)
				{
					if(ControlNode->colors == NodesBase::TreeBlack)
					{
						//黒なら終了
						break;
					};

					if( ControlNode->Parent->right_->colors == NodesBase::TreeRed )
					{
						//さらに上の兄弟が赤であれば、兄弟とも黒になってコンティニュー
						ControlNode->colors = NodesBase::TreeBlack;
						ControlNode->Parent->right_->colors = NodesBase::TreeBlack;

						ControlNode = ControlNode->Parent;

						if( ControlNode->root_ )
						{
							//ルートなら終了
							break;
						};

						ControlNode->colors = NodesBase::TreeRed;
						ControlNode = ControlNode->Parent;
						continue;
					};

					//左下が赤で兄弟の色が赤と黒だった場合
					if( ControlNode->left_->colors == NodesBase::TreeRed )
					{
						//右回転して終わり
						ControlNode = RightRotateTree(ControlNode->Parent);
						break;

					};

					//一つ上の条件で右下が赤だった場合
					if( ControlNode->right_->colors == NodesBase::TreeRed )
					{
						//左回転を行った後右回転を行い、終了
						ControlNode = LeftRotateTree(ControlNode);
						ControlNode = RightRotateTree(ControlNode->Parent);
						break;
					};
				};

			};

		};//end method;

		//内部検索用関数です。
		inline bool __INFIND__(unsigned long SearchVal, NodesBase*& GetObject)
		{
			NodesBase* tmpNode = RootNode;

			while(1)
			{
				if(tmpNode == 0)
				{
					//走査した結果NULLまで到達したらfalse返却
					return false;
				};

				if( tmpNode->NodeValue == SearchVal )
				{
					//同じ値が見つかったら検索結果を返す。
					break;
				};

				if( tmpNode->NodeValue > SearchVal )
				{
					//ノードより小さい値なら左へ
					tmpNode = tmpNode->left_;

				}else if( tmpNode->NodeValue < SearchVal )
				{
					//ノードより大きい値なら右へ
					tmpNode = tmpNode->right_;
				};
			};

			GetObject = tmpNode;
			return true;
		};


	public:
		SonikRBTree(uint32_t _SetCnt = 150)
		:m_FreeArea(nullptr)
		,RootNode(0)
		,LinerTop(0)
		,LinerEnd(0)
		{
			try
			{
//				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(AllocSmtPtr_, sizeof(Nodes) * 150) )
//				{
//					throw -1;
//				};

				//初回の一つはちゃちゃっと作る
				m_FreeArea = new Nodes;


				//個数分取得。(配列にはしない。)
				NodesBase* l_pGetPtr= m_FreeArea ;
				for(uint32_t  i=1; i < _SetCnt; ++i)
				{
					l_pGetPtr->Next = new Nodes;
					l_pGetPtr = l_pGetPtr->Next;
				};

			}catch(...)
			{
					NodesBase* l_pGetPtr = nullptr;
					while(m_FreeArea != nullptr)
					{
						l_pGetPtr = m_FreeArea;
						m_FreeArea = m_FreeArea->Next;

						delete l_pGetPtr;
					};


					throw;
				};
		};

		//ノードに子を追加します。
		inline bool Insert(SetDataType SetData, uint32_t SetPriority)
		{
			atmlock_.lock();
			Nodes* tmpPtr;
			NodesBase* PretmpNode;
			NodesBase* tmpNode;
			NodesBase** pDirectionInsert = 0;

			if(m_FreeArea == nullptr)
			{
				//もうフリー領域がないので追加確保
				m_FreeArea = new(std::nothrow) Nodes;
				if(m_FreeArea == nullptr)
				{
					atmlock_.unlock();
					return false;
				};
			};

			tmpPtr = m_FreeArea;
			m_FreeArea = m_FreeArea->Next;

			//挿入するオブジェクトの色は赤
			tmpPtr->m_data = SetData;
			tmpPtr->colors = NodesBase::TreeRed;
			tmpPtr->root_ = false;
			tmpPtr->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpPtr->m_data = SetData;
				tmpPtr->colors = NodesBase::TreeBlack;
				tmpPtr->root_ = true;
				tmpPtr->NodeValue = SetPriority;

				RootNode = tmpPtr;
				LinerTop = tmpPtr;
				LinerEnd = tmpPtr;

			}else
			{
				//初回以外なら葉、もしくは枝として設定
				//追加先を検索。
				tmpNode = RootNode;
				while(1)
				{
					if( tmpNode->NodeValue == SetPriority )
					{
						//同じ値が見つかったらアウト
						tmpPtr->m_data.~SetDataType();

						//Freeリストへ追加。
						if(m_FreeArea == nullptr)
						{
							m_FreeArea = tmpPtr;
						}else
						{
							m_FreeArea->Prev = tmpPtr;
							m_FreeArea->Prev->Next = m_FreeArea;
							m_FreeArea = m_FreeArea->Prev;
							m_FreeArea->Prev = nullptr;
						};

						atmlock_.unlock();
						return false;
					};

					if( tmpNode->NodeValue > SetPriority )
					{
						//ノードより小さい値なら左へ
						if( tmpNode->left_ == 0 )
						{
							//検索不可能なところまでいったらbreak
							if( tmpNode->Prev != 0 )
							{
								tmpPtr->Prev = tmpNode->Prev;
								tmpPtr->Next = tmpNode;
								tmpPtr->Prev->Next = tmpPtr;
								tmpPtr->Prev = tmpPtr;
							}else
							{
								tmpPtr->Next = tmpNode;
								tmpNode->Prev = tmpPtr;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpPtr;
							};

							pDirectionInsert = &tmpNode->left_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->left_;
						continue;

					}else if( tmpNode->NodeValue < SetPriority )
					{
						//ノードより大きい値なら右へ
						if( tmpNode->right_ == 0 )
						{
							//検索不可能なところまでいったらbreak;
							if( tmpNode->Next != 0 )
							{
								tmpPtr->Next = tmpNode->Next;
								tmpPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpPtr;
								tmpNode->Next = tmpPtr;
							}else
							{
								tmpPtr->Prev = tmpNode;
								tmpNode->Next = tmpPtr;
							};

							pDirectionInsert = &tmpNode->right_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->right_;
						continue;
					};
				};

				//検索完了したので挿入処理を行う。
				//ノード挿入
				(*pDirectionInsert) = std::move(tmpPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.unlock();
			return true;

		};

		//ノードに子を追加します。
		inline bool Insert(SetDataType* SetData, unsigned long SetPriority)
		{
			atmlock_.lock();
			Nodes* tmpPtr;
			NodesBase* PretmpNode;
			NodesBase* tmpNode;
			NodesBase** pDirectionInsert = 0;

//			if( !AllocSmtPtr_.GetAlloc(tmpSmtPtr) )
//			{
//				atmlock_.unlock();
//				return false;
//			};

			if(m_FreeArea == nullptr)
			{
				//もうフリー領域がないので追加確保
				m_FreeArea = new(std::nothrow) Nodes;
				if(m_FreeArea == nullptr)
				{
					atmlock_.unlock();
					return false;
				};
			};

			tmpPtr = m_FreeArea;
			m_FreeArea = m_FreeArea->Next;

			//挿入するオブジェクトの色は赤
			tmpPtr->m_data = SetData;
			tmpPtr->colors = NodesBase::TreeRed;
			tmpPtr->root_ = false;
			tmpPtr->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpPtr->m_data = SetData;
				tmpPtr->colors = NodesBase::TreeBlack;
				tmpPtr->root_ = true;
				tmpPtr->NodeValue = SetPriority;

				RootNode = tmpPtr;
				LinerTop = tmpPtr;
				LinerEnd = tmpPtr;

			}else
			{
				//初回以外なら葉、もしくは枝として設定
				//追加先を検索。
				tmpNode = RootNode;
				while(1)
				{
					if( tmpNode->NodeValue == SetPriority )
					{
						//同じ値が見つかったらアウト
						tmpPtr->m_data =0;

						//Freeリストへ追加。
						if(m_FreeArea == nullptr)
						{
							m_FreeArea = tmpPtr;
						}else
						{
							m_FreeArea->Prev = tmpPtr;
							m_FreeArea->Prev->Next = m_FreeArea;
							m_FreeArea = m_FreeArea->Prev;
							m_FreeArea->Prev = nullptr;
						};

						atmlock_.unlock();
						return false;
					};

					if( tmpNode->NodeValue > SetPriority )
					{
						//ノードより小さい値なら左へ
						if( tmpNode->left_ == 0 )
						{
							//検索不可能なところまでいったらbreak
							if( tmpNode->Prev != 0 )
							{
								tmpPtr->Prev = tmpNode->Prev;
								tmpPtr->Next = tmpNode;
								tmpNode->Prev->Next = tmpPtr;
								tmpNode->Prev = tmpPtr;
							}else
							{
								tmpPtr->Next = tmpNode;
								tmpNode->Prev = tmpPtr;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpPtr;
							};

							pDirectionInsert = &tmpNode->left_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->left_;
						continue;

					}else if( tmpNode->NodeValue < SetPriority )
					{
						//ノードより大きい値なら右へ
						if( tmpNode->right_ == 0 )
						{
							//検索不可能なところまでいったらbreak;
							if( tmpNode->Next != 0 )
							{
								tmpPtr->Next = tmpNode->Next;
								tmpPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpPtr;
								tmpNode->Next = tmpPtr;
							}else
							{
								tmpPtr->Prev = tmpNode;
								tmpNode->Next = tmpPtr;
							};

							pDirectionInsert = &tmpNode->right_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->right_;
						continue;
					};
				};

				//検索完了したので挿入処理を行う。
				//ノード挿入
				(*pDirectionInsert) = std::move(tmpPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.unlock();
			return true;

		};


		//ノードの最後尾に子を追加します。
		inline bool Insert(SetDataType SetData)
		{
			atmlock_.lock();
			Nodes* tmpPtr;
			NodesBase* PretmpNode;
			NodesBase* tmpNode;
			NodesBase** pDirectionInsert = 0;
			unsigned long SetPriority;

			if( LinerEnd == 0 )
			{
				SetPriority = 0;
			}else
			{
				if( LinerEnd->NodeValue == 0xFFFFFFFF )
				{
					//最後尾に追加したいが　識別番号の最大値が使われているため追加できない。
					atmlock_.unlock();
					return false;
				};

				SetPriority = LinerEnd->NodeValue + 1;
			};

//			if( !AllocSmtPtr_.GetAlloc(tmpSmtPtr) )
//			{
//				atmlock_.unlock();
//				return false;
//			};

			if(m_FreeArea == nullptr)
			{
				//もうフリー領域がないので追加確保
				m_FreeArea = new(std::nothrow) Nodes;
				if(m_FreeArea == nullptr)
				{
					atmlock_.unlock();
					return false;
				};
			};

			tmpPtr = m_FreeArea;
			m_FreeArea = m_FreeArea->Next;

			//挿入するオブジェクトの色は赤
			tmpPtr->m_data = SetData;
			tmpPtr->colors = NodesBase::TreeRed;
			tmpPtr->root_ = false;
			tmpPtr->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpPtr->m_data = SetData;
				tmpPtr->colors = NodesBase::TreeBlack;
				tmpPtr->root_ = true;
				tmpPtr->NodeValue = SetPriority;

				RootNode = tmpPtr;
				LinerTop = tmpPtr;
				LinerEnd = tmpPtr;

			}else
			{
				//初回以外なら葉、もしくは枝として設定
				//追加先を検索。
				tmpNode = RootNode;
				while(1)
				{
					if( tmpNode->NodeValue == SetPriority )
					{
						//同じ値が見つかったらアウト
						tmpPtr->m_data.~SetDataType();

						//Freeリストへ追加。
						if(m_FreeArea == nullptr)
						{
							m_FreeArea = tmpPtr;
						}else
						{
							m_FreeArea->Prev = tmpPtr;
							m_FreeArea->Prev->Next = m_FreeArea;
							m_FreeArea = m_FreeArea->Prev;
							m_FreeArea->Prev = nullptr;
						};

						atmlock_.unlock();
						return false;
					};

					if( tmpNode->NodeValue > SetPriority )
					{
						//ノードより小さい値なら左へ
						if( tmpNode->left_ == 0 )
						{
							//検索不可能なところまでいったらbreak
							if( tmpNode->Prev != 0 )
							{
								tmpPtr->Prev = tmpNode->Prev;
								tmpPtr->Next = tmpNode;
								tmpNode->Prev->Next = tmpPtr;
								tmpNode->Prev = tmpPtr;
							}else
							{
								tmpPtr->Next = tmpNode;
								tmpNode->Prev = tmpPtr;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpPtr;
							};

							pDirectionInsert = &tmpNode->left_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->left_;
						continue;

					}else if( tmpNode->NodeValue < SetPriority )
					{
						//ノードより大きい値なら右へ
						if( tmpNode->right_ == 0 )
						{
							//検索不可能なところまでいったらbreak;
							if( tmpNode->Next != 0 )
							{
								tmpPtr->Next = tmpNode->Next;
								tmpPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpPtr;
								tmpNode->Next = tmpPtr;
							}else
							{
								tmpPtr->Prev = tmpNode;
								tmpNode->Next = tmpPtr;
							};

							if( SetPriority > LinerEnd->NodeValue)
							{
								LinerEnd = tmpPtr;
							};

							pDirectionInsert = &tmpNode->right_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->right_;
						continue;
					};
				};

				//検索完了したので挿入処理を行う。
				//ノード挿入
				(*pDirectionInsert) = std::move(tmpPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.unlock();
			return true;

		};

		//ノードの最後尾に子を追加します。
		inline bool Insert(SetDataType* SetData)
		{
			atmlock_.lock();
			Nodes* tmpPtr;
			NodesBase* PretmpNode;
			NodesBase* tmpNode;
			NodesBase** pDirectionInsert = 0;
			unsigned long SetPriority;

			if( LinerEnd == 0 )
			{
				SetPriority = 0;
			}else
			{
				if( LinerEnd->NodeValue == 0xFFFFFFFF )
				{
					//最後尾に追加したいが　識別番号の最大値が使われているため追加できない。
					atmlock_.unlock();
					return false;
				};

				SetPriority = LinerEnd->NodeValue + 1;
			};

//			if( !AllocSmtPtr_.GetAlloc(tmpSmtPtr) )
//			{
//				atmlock_.unlock();
//				return false;
//			};

			if(m_FreeArea == nullptr)
			{
				//もうフリー領域がないので追加確保
				m_FreeArea = new(std::nothrow) Nodes;
				if(m_FreeArea == nullptr)
				{
					atmlock_.unlock();
					return false;
				};
			};

			tmpPtr = m_FreeArea;
			m_FreeArea = m_FreeArea->Next;

			//挿入するオブジェクトの色は赤
			tmpPtr ->m_data = SetData;
			tmpPtr ->colors = NodesBase::TreeRed;
			tmpPtr ->root_ = false;
			tmpPtr ->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpPtr ->m_data = SetData;
				tmpPtr ->colors = NodesBase::TreeBlack;
				tmpPtr ->root_ = true;
				tmpPtr ->NodeValue = SetPriority;

				RootNode = tmpPtr ;
				LinerTop = tmpPtr ;
				LinerEnd = tmpPtr ;

			}else
			{
				//初回以外なら葉、もしくは枝として設定
				//追加先を検索。
				tmpNode = RootNode;
				while(1)
				{
					if( tmpNode->NodeValue == SetPriority )
					{
						//同じ値が見つかったらアウト
						tmpPtr ->m_data = 0;

						//Freeリストへ追加。
						if(m_FreeArea == nullptr)
						{
							m_FreeArea = tmpPtr;
						}else
						{
							m_FreeArea->Prev = tmpPtr;
							m_FreeArea->Prev->Next = m_FreeArea;
							m_FreeArea = m_FreeArea->Prev;
							m_FreeArea->Prev = nullptr;
						};

						atmlock_.unlock();
						return false;
					};

					if( tmpNode->NodeValue > SetPriority )
					{
						//ノードより小さい値なら左へ
						if( tmpNode->left_ == 0 )
						{
							//検索不可能なところまでいったらbreak
							if( tmpNode->Prev != 0 )
							{
								tmpPtr ->Prev = tmpNode->Prev;
								tmpPtr ->Next = tmpNode;
								tmpNode->Prev->Next = tmpPtr ;
								tmpNode->Prev = tmpPtr ;
							}else
							{
								tmpPtr ->Next = tmpNode;
								tmpNode->Prev = tmpPtr ;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpPtr ;
							};

							pDirectionInsert = &tmpNode->left_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->left_;
						continue;

					}else if( tmpNode->NodeValue < SetPriority )
					{
						//ノードより大きい値なら右へ
						if( tmpNode->right_ == 0 )
						{
							//検索不可能なところまでいったらbreak;
							if( tmpNode->Next != 0 )
							{
								tmpPtr->Next = tmpNode->Next;
								tmpPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpPtr;
								tmpNode->Next = tmpPtr;
							}else
							{
								tmpPtr->Prev = tmpNode;
								tmpNode->Next = tmpPtr;
							};

							if( SetPriority > LinerEnd->NodeValue)
							{
								LinerEnd = tmpPtr;
							};

							pDirectionInsert = &tmpNode->right_;
							break;
						};

						//まだいけそうなら検索再開
						PretmpNode = tmpNode;
						tmpNode = tmpNode->right_;
						continue;
					};
				};

				//検索完了したので挿入処理を行う。
				//ノード挿入
				(*pDirectionInsert) = std::move(tmpPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.unlock();
			return true;

		};

		inline bool TreeFind(unsigned long SearchValue, SetDataType& GetData)
		{
			NodesBase* Get_;
			Nodes* UpcastObj_;

			if( !__INFIND__(SearchValue, Get_) )
			{
				return false;
			};

			UpcastObj_ = reinterpret_cast<Nodes*>(Get_);

			GetData = UpcastObj_->m_data;
			return true;
		};

		inline void Erase(unsigned long EraseValue)
		{
			NodesBase* Get_;
			NodesBase* tmp_;
			Nodes* UpcastObj_;
			Nodes* UpcastObj_tmp;

			if( !__INFIND__(EraseValue, Get_) )
			{
				return;
			};

			//削除対象の要素で本ツリー最後の要素であった場合はそれを削除して即終了
			if( (Get_->root_) && (Get_->right_ == 0) && (Get_->left_ == 0) )
			{
				//				RootNode.~SonikAllocSmtPtr();
				//				LinerTop.~SonikAllocSmtPtr();
				//				LinerEnd.~SonikAllocSmtPtr();
				//				Get_.~SonikAllocSmtPtr();

				RootNode = 0;
				LinerTop = 0;
				LinerEnd = 0;

				//AllocSmtPtr_->FreeAlloc(Get_);

				//Freeリストへ追加。
				if(m_FreeArea == nullptr)
				{
					m_FreeArea = Get_;
				}else
				{
					m_FreeArea->Prev = Get_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};

				return;
			};

			if(Get_->colors == NodesBase::TreeRed)
			{
				//削除されるノード（自ノード)が赤の場合
				//普通に２分探索木同様に削除を行う。
				//自ノードが末端であればそのまま削除！
				if( (Get_->left_ == 0) && (Get_->right_ == 0) )
				{
					if( Get_->Parent->left_ == Get_ )
					{
						//自分は親の左の子である。
						Get_->Parent->left_ = 0;

					}else
					{
						//自分は親の右の子である。
						Get_->Parent->right_ = 0;
					};

					//線形削除
					if( Get_->Next != 0 )
					{
						//Get_->Next->Prev = 0;
						Get_->Next->Prev = Get_->Prev;
					};
					if( Get_->Prev != 0 )
					{
						//Get_->Prev->Next->~SonikRBTreeNodeBase();
						Get_->Prev->Next = Get_->Next;
					};

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//要素本体の削除
					//Get_->~SonikRBTreeNodeBase();
					//AllocSmtPtr_->FreeAlloc(Get_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = Get_;
					}else
					{
						m_FreeArea->Prev = Get_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					//関数終了
					return;
				};

				//自ノードが末端以外の時。
				//自分の右に子があるかないかをチェック。ここまで来てたらどっちかの要素がある。
				if( Get_->right_ != 0 )
				{
					//自分の右に子がいる。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);


					if(tmp_->right_ != 0)
					{
						//削除身代わり対象の更に右に子を持っていた場合は左回転を行う。
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Next != 0 )
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};

					//Prevは保証されている。
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->right_->~SonikAllocSmtPtr();
						tmp_->Parent->right_ = 0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->left_->~SonikAllocSmtPtr();
						tmp_->Parent->left_ = 0;

					};

				}else
				{
					//自分の左に子がいる。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					if(tmp_->left_ != 0)
					{
						//削除身代わり対象の更に左に子を持っていた場合は右回転を行う。
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Prev != 0 )
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};

					//Nextは保証されている。
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

				};

				//値書き換え
				UpcastObj_->m_data = UpcastObj_tmp->m_data;
				UpcastObj_->colors = UpcastObj_tmp->colors;
				UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;

				//AllocSmtPtr_->FreeAlloc(tmp_);

				//Freeリストへ追加。
				if(m_FreeArea == nullptr)
				{
					m_FreeArea = tmp_;
				}else
				{
					m_FreeArea->Prev = tmp_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};

				//終了
				return;

			}else
			{
				//削除されるノード（自ノード)が黒の場合

				unsigned long pattern_ = 100;
				bool patternmatchEnd = false;

				//末端以外ならば、どちらにあるかをチェック
				if( Get_->right_ != 0 )
				{
					//右の子を持っている。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に右に子がいれば、左回転
					if(tmp_->right_ != 0)
					{
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Next != 0)
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};


					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					}else
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->right_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->right_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->right_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に左回転させる。
							LeftRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->right_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->right_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は左削除の右ツリー操作なので、右回転)に回転させる。
							RightRotateTree(Get_->Parent->right_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->right_->right_->colors = NodesBase::TreeRed;
							Get_->Parent->right_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							LeftRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->right_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;


				}else
				{
					//右の子を持っていない。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に左に子がいれば、左回転
					if(tmp_->left_ != 0)
					{
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Prev != 0)
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->left_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->left_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->left_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に右回転させる。
							RightRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->left_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->left_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は右削除の左ツリー操作なので、左回転)に回転させる。
							LeftRotateTree(Get_->Parent->left_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->left_->left_->colors = NodesBase::TreeRed;
							Get_->Parent->left_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							RightRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->left_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;
				};//end else if;
			};//end else if;
		};//end faunction;

		inline void Erase(unsigned long EraseValue, SonikLib::SonikLinerOperator_RBTree<SetDataType>* EraseOperator)
		{
			NodesBase* Get_;
			NodesBase* tmp_;
			Nodes* UpcastObj_;
			Nodes* UpcastObj_tmp;

			if( !__INFIND__(EraseValue, Get_) )
			{
				return;
			};

			//削除対象の要素で本ツリー最後の要素であった場合はそれを削除して即終了
			if( (Get_->root_) && (Get_->right_ == 0) && (Get_->left_ == 0) )
			{
				//				RootNode.~SonikAllocSmtPtr();
				//				LinerTop.~SonikAllocSmtPtr();
				//				LinerEnd.~SonikAllocSmtPtr();
				//				Get_.~SonikAllocSmtPtr();

				RootNode = 0;
				LinerTop = 0;
				LinerEnd = 0;
				//AllocSmtPtr_->FreeAlloc(Get_);

				//Freeリストへ追加。
				if(m_FreeArea == nullptr)
				{
					m_FreeArea = Get_;
				}else
				{
					m_FreeArea->Prev = Get_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};

				return;
			};

			if(Get_->colors == NodesBase::TreeRed)
			{
				//削除されるノード（自ノード)が赤の場合
				//普通に２分探索木同様に削除を行う。
				//自ノードが末端であればそのまま削除！
				if( (Get_->left_ == 0) && (Get_->right_ == 0) )
				{
					if( Get_->Parent->left_ == Get_ )
					{
						//自分は親の左の子である。
						Get_->Parent->left_ = 0;

					}else
					{
						//自分は親の右の子である。
						Get_->Parent->right_ = 0;
					};

					//線形削除
					if( Get_->Next != 0 )
					{
						//Get_->Next->Prev = 0;
						Get_->Next->Prev = Get_->Prev;
					};
					if( Get_->Prev != 0 )
					{
						//Get_->Prev->Next->~SonikRBTreeNodeBase();
						Get_->Prev->Next = Get_->Next;
					};

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//要素本体の削除
					//Get_->~SonikRBTreeNodeBase();
					//AllocSmtPtr_->FreeAlloc(Get_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = Get_;
					}else
					{
						m_FreeArea->Prev = Get_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					//関数終了
					return;
				};

				//自ノードが末端以外の時。
				//自分の右に子があるかないかをチェック。ここまで来てたらどっちかの要素がある。
				if( Get_->right_ != 0 )
				{
					//自分の右に子がいる。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);


					if(tmp_->right_ != 0)
					{
						//削除身代わり対象の更に右に子を持っていた場合は左回転を行う。
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Next != 0 )
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};

					//Prevは保証されている。
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->right_->~SonikAllocSmtPtr();
						tmp_->Parent->right_ = 0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->left_->~SonikAllocSmtPtr();
						tmp_->Parent->left_ = 0;

					};

				}else
				{
					//自分の左に子がいる。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					if(tmp_->left_ != 0)
					{
						//削除身代わり対象の更に左に子を持っていた場合は右回転を行う。
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Prev != 0 )
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};

					//Nextは保証されている。
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

				};

				//Eraseポイント更新
				if( EraseOperator->pNodes_ == tmp_ )
				{
					(*EraseOperator).pNodes_ = reinterpret_cast<NodesBase*>(UpcastObj_);
				};

				//値書き換え
				UpcastObj_->m_data = UpcastObj_tmp->m_data;
				UpcastObj_->colors = UpcastObj_tmp->colors;
				UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;

				//AllocSmtPtr_->FreeAlloc(tmp_);

				//Freeリストへ追加。
				if(m_FreeArea == nullptr)
				{
					m_FreeArea = tmp_;
				}else
				{
					m_FreeArea->Prev = tmp_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};


				//終了
				return;

			}else
			{
				//削除されるノード（自ノード)が黒の場合

				unsigned long pattern_ = 100;
				bool patternmatchEnd = false;

				//末端以外ならば、どちらにあるかをチェック
				if( Get_->right_ != 0 )
				{
					//右の子を持っている。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に右に子がいれば、左回転
					if(tmp_->right_ != 0)
					{
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Next != 0)
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};


					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					}else
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					};

					//Eraseポイント更新
					if( (*EraseOperator).pNodes_ == tmp_ )
					{
						(*EraseOperator).pNodes_ = reinterpret_cast<NodesBase*>(UpcastObj_);
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->right_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->right_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->right_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に左回転させる。
							LeftRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->right_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->right_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は左削除の右ツリー操作なので、右回転)に回転させる。
							RightRotateTree(Get_->Parent->right_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->right_->right_->colors = NodesBase::TreeRed;
							Get_->Parent->right_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							LeftRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->right_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;


				}else
				{
					//右の子を持っていない。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に左に子がいれば、左回転
					if(tmp_->left_ != 0)
					{
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Prev != 0)
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

					//Eraseポイント更新
					if( (*EraseOperator).pNodes_ == tmp_ )
					{
						(*EraseOperator).pNodes_ = reinterpret_cast<NodesBase*>(UpcastObj_);
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->left_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->left_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->left_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に右回転させる。
							RightRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->left_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->left_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は右削除の左ツリー操作なので、左回転)に回転させる。
							LeftRotateTree(Get_->Parent->left_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->left_->left_->colors = NodesBase::TreeRed;
							Get_->Parent->left_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							RightRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->left_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;
				};//end else if;
			};//end else if;
		};//end faunction;

		inline void Erase(SonikLib::SonikLinerOperator_RBTree<SetDataType>* EraseOperator)
		{
			NodesBase* Get_;
			NodesBase* tmp_;
			Nodes* UpcastObj_;
			Nodes* UpcastObj_tmp;

			if( EraseOperator == 0 )
			{
				return;
			};

			if( EraseOperator->pNodes_ == 0 )
			{
				return;
			};

			if( !__INFIND__(EraseOperator->pNodes_->NodeValue, Get_) )
			{
				return;
			};

			//			EraseOperator->NextMove();

			//削除対象の要素で本ツリー最後の要素であった場合はそれを削除して即終了
			if( (Get_->root_) && (Get_->right_ == 0) && (Get_->left_ == 0) )
			{
				//				RootNode.~SonikAllocSmtPtr();
				//				LinerTop.~SonikAllocSmtPtr();
				//				LinerEnd.~SonikAllocSmtPtr();
				//				Get_.~SonikAllocSmtPtr();

				RootNode = 0;
				LinerTop = 0;
				LinerEnd = 0;
				//AllocSmtPtr_->FreeAlloc(Get_);

				//Freeリストへ追加。
				if(m_FreeArea == nullptr)
				{
					m_FreeArea = Get_;
				}else
				{
					m_FreeArea->Prev = Get_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};

				EraseOperator->pNodes_ = 0;

				return;
			};

			if(Get_->colors == NodesBase::TreeRed)
			{
				//削除されるノード（自ノード)が赤の場合
				//普通に２分探索木同様に削除を行う。
				//自ノードが末端であればそのまま削除！
				if( (Get_->left_ == 0) && (Get_->right_ == 0) )
				{
					if( Get_->Parent->left_ == Get_ )
					{
						//自分は親の左の子である。
						Get_->Parent->left_ = 0;

					}else
					{
						//自分は親の右の子である。
						Get_->Parent->right_ = 0;
					};

					//線形削除
					if( Get_->Next != 0 )
					{
						//Get_->Next->Prev = 0;
						Get_->Next->Prev = Get_->Prev;

					};
					if( Get_->Prev != 0 )
					{
						//Get_->Prev->Next->~SonikRBTreeNodeBase();
						Get_->Prev->Next = Get_->Next;
					};

					if(LinerTop == Get_)
					{
						LinerTop = Get_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = Get_->Prev;
					};

					//削除する前に移動しておく。
					EraseOperator->pNodes_ = Get_->Next;

					//要素本体の削除
					//Get_->~SonikRBTreeNodeBase();
					//AllocSmtPtr_->FreeAlloc(Get_);

					//Freeリストへ追加。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = Get_;
					}else
					{
						m_FreeArea->Prev = Get_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					//関数終了
					return;
				};

				//自ノードが末端以外の時。
				//自分の右に子があるかないかをチェック。ここまで来てたらどっちかの要素がある。
				if( Get_->right_ != 0 )
				{
					//自分の右に子がいる。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);


					if(tmp_->right_ != 0)
					{
						//削除身代わり対象の更に右に子を持っていた場合は左回転を行う。
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Next != 0 )
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};

					//Prevは保証されている。
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->right_->~SonikAllocSmtPtr();
						tmp_->Parent->right_ = 0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->left_->~SonikAllocSmtPtr();
						tmp_->Parent->left_ = 0;

					};

				}else
				{
					//自分の左に子がいる。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					if(tmp_->left_ != 0)
					{
						//削除身代わり対象の更に左に子を持っていた場合は右回転を行う。
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if( tmp_->Prev != 0 )
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};

					//Nextは保証されている。
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーからの除去
					//除去身代わり対象の親が自ノードのパターンと、自ノード以外のパターンがある。
					if( tmp_->Parent == Get_ )
					{
						//親が自ノードの場合
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//親が自ノード以外の場合
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

				};

				//値書き換え
				UpcastObj_->m_data = UpcastObj_tmp->m_data;
				UpcastObj_->colors = UpcastObj_tmp->colors;
				UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
				//AllocSmtPtr_->FreeAlloc(tmp_);

				if(m_FreeArea == nullptr)
				{
					m_FreeArea = tmp_;
				}else
				{
					m_FreeArea->Prev = tmp_;
					m_FreeArea->Prev->Next = m_FreeArea;
					m_FreeArea = m_FreeArea->Prev;
					m_FreeArea->Prev = nullptr;
				};

				//終了
				return;

			}else
			{
				//削除されるノード（自ノード)が黒の場合

				unsigned long pattern_ = 100;
				bool patternmatchEnd = false;

				//末端以外ならば、どちらにあるかをチェック
				if( Get_->right_ != 0 )
				{
					//右の子を持っている。
					tmp_ = Get_->Next;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に右に子がいれば、左回転
					if(tmp_->right_ != 0)
					{
						LeftRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Next != 0)
					{
						//tmp_->Next->Prev.~SonikAllocSmtPtr();
						tmp_->Next->Prev = tmp_->Prev;
					};
					//tmp_->Prev->Next.~SonikAllocSmtPtr();
					tmp_->Prev->Next = tmp_->Next;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};


					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					}else
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//フリーリストへ戻す。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->right_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->right_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->right_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->right_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に左回転させる。
							LeftRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->right_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->right_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は左削除の右ツリー操作なので、右回転)に回転させる。
							RightRotateTree(Get_->Parent->right_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->right_->right_->colors = NodesBase::TreeRed;
							Get_->Parent->right_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							LeftRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->right_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;


				}else
				{
					//右の子を持っていない。
					tmp_ = Get_->Prev;
					//アップキャストしておく。
					//Get_.PtrUpCast(UpcastObj_);
					//tmp_.PtrUpCast(UpcastObj_tmp);
					UpcastObj_ = reinterpret_cast<Nodes*>(Get_);
					UpcastObj_tmp = reinterpret_cast<Nodes*>(tmp_);

					//更に左に子がいれば、左回転
					if(tmp_->left_ != 0)
					{
						RightRotateTree(tmp_);
					};

					//線形リストから除去
					if(tmp_->Prev != 0)
					{
						//tmp_->Prev->Next.~SonikAllocSmtPtr();
						tmp_->Prev->Next = tmp_->Next;
					};
					//tmp_->Next->Prev.~SonikAllocSmtPtr();
					tmp_->Next->Prev = tmp_->Prev;

					if(LinerTop == tmp_)
					{
						LinerTop = tmp_->Next;
					}else if(LinerEnd == tmp_)
					{
						LinerEnd = tmp_->Prev;
					};

					//ツリーから除去
					if(tmp_->Parent == Get_)
					{
						//tmp_->Parent->left_.~SonikAllocSmtPtr();
						tmp_->Parent->left_ =0;
					}else
					{
						//tmp_->Parent->right_.~SonikAllocSmtPtr();
						tmp_->Parent->right_ =0;
					};

					//データ置き換え
					UpcastObj_->m_data = UpcastObj_tmp->m_data;
					UpcastObj_->colors = UpcastObj_tmp->colors;
					UpcastObj_->NodeValue = UpcastObj_tmp->NodeValue;
					//AllocSmtPtr_->FreeAlloc(tmp_);

					//フリーリストへ戻す。
					if(m_FreeArea == nullptr)
					{
						m_FreeArea = tmp_;
					}else
					{
						m_FreeArea->Prev = tmp_;
						m_FreeArea->Prev->Next = m_FreeArea;
						m_FreeArea = m_FreeArea->Prev;
						m_FreeArea->Prev = nullptr;
					};

					while( !patternmatchEnd )
					{
						if( Get_->colors == NodesBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == NodesBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->left_->colors == NodesBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == NodesBase::TreeBlack) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == NodesBase::TreeRed) && (Get_->Parent->left_->GetLeftColor() == NodesBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == NodesBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->left_->GetLeftColor() == NodesBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->left_->GetRightColor() == NodesBase::TreeRed )
						{
							pattern_ = 6;

						};


						//パターンマッチケース
						switch(pattern_)
						{
						case 0:
							//削除指定ノードが赤or黒、 入れ替え子ノードが削除指定ノードの色とは逆の色のパターン
							//データの置き換えは終わっているので、
							//黒にチェンジして終了
							Get_->colors = NodesBase::TreeBlack;

							patternmatchEnd = true;
							break;

						case 1:
							//削除指定ノードが根の場合、何もせずに終了
							patternmatchEnd = true;

							break;

						case 2:
							//兄弟が赤の場合
							//親を中心に右回転させる。
							RightRotateTree(Get_->Parent);

							//新しい親の下の状況により更に分岐
							Get_ = Get_->Parent;
							break;

						case 3:
							//兄弟が黒で、兄弟の親及び、子が黒の場合
							//兄弟を赤に変える
							Get_->Parent->left_->colors = NodesBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = NodesBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->left_->colors = NodesBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は右削除の左ツリー操作なので、左回転)に回転させる。
							LeftRotateTree(Get_->Parent->left_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->left_->left_->colors = NodesBase::TreeRed;
							Get_->Parent->left_->colors = NodesBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							RightRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->left_->colors = NodesBase::TreeBlack;

							//終了
							patternmatchEnd = true;
							break;

						default:
							patternmatchEnd = true;
							break;
						};

						if( patternmatchEnd )
						{
							break;
						};

					};//end whilw;
				};//end else if;
			};//end else if;
		};//end faunction;


		//リニアサーチ用のオブジェクトを取得します。
		inline SonikLib::SonikLinerOperator_RBTree<SetDataType> GetOpe_LinerBegin(void)
		{
			SonikLib::SonikLinerOperator_RBTree<SetDataType> ope_;

			ope_.pNodes_ = LinerTop;

			return ope_;
		};

		//リニアサーチ用のオブジェクトを取得します。
		inline SonikLib::SonikLinerOperator_RBTree<SetDataType> GetOpe_LinerEnd(void)
		{
			SonikLib::SonikLinerOperator_RBTree<SetDataType> ope_;

			ope_.pNodes_ = LinerEnd;

			return ope_;
		};

	};//end class;

};//end namespace SonikLib



#endif /* SONIKBALANCEDTREE_RB_SONIKRBTREE_H_ */
