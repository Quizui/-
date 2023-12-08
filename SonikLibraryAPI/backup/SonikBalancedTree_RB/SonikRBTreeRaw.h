/*
 * SonikRBTree.h
 *
 *  Created on: 2016/01/27
 *      Author: SONIC_000
 */

#ifndef SONIKBALANCEDTREE_RB_SONIKRBTREERAW_H_
#define SONIKBALANCEDTREE_RB_SONIKRBTREERAW_H_

#include "..\\SonikAllocateUse.h"
#include "..\\SonikCASLockUse.h"
#include "SonikRBTreeNodeRaw.h"
#include "SonikRB_RawLinerSerchOperator.h"
#include <utility>

//赤黒木
namespace SonikBalanceTree
{

	//本体
	template <class SetDataType>
	class SonikRBTreeRaw
	{
	private:
	typedef SonikRBTreeNodeRaw<SetDataType> Nodes;

	private:
		//アロケータへのスマートポインタ
		SonikLib::SonikRawAllocObjectPtr AllocSmtPtr_;

		//根のノードへのスマートポインタ
		SonikRBTreeNodeBaseRaw* RootNode;
		//線形走査のノードポインタ
		SonikRBTreeNodeBaseRaw* LinerTop;
		SonikRBTreeNodeBaseRaw* LinerEnd;

		//排他処理ロック
		SonikCAS::SonikAtomicLock atmlock_;

	private:
		//回転基準軸を指定し、そこを基準に木を右回転させます。
		SonikRBTreeNodeBaseRaw* RightRotateTree(SonikRBTreeNodeBaseRaw* Node_)
		{
			SonikRBTreeNodeBaseRaw* LeftNode_;
			SonikRBTreeNodeBaseRaw* TopParentNode_;

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
				if( TopParentNode_->left_->NodeValue == Node_->NodeValue )
				{
					TopParentNode_->left_ = LeftNode_;
				}else
				{
					TopParentNode_->right_ = LeftNode_;
				}
			};

			LeftNode_->colors = Node_->colors;
			Node_->colors = ((~(Node_->colors)) & 0x01);

			return LeftNode_;
		};

		//回転基準軸を指定し、そこを基準に木を左回転させます。
		SonikRBTreeNodeBaseRaw* LeftRotateTree(SonikRBTreeNodeBaseRaw* Node_)
		{
			SonikRBTreeNodeBaseRaw* RightNode_;
			SonikRBTreeNodeBaseRaw* TopParentNode_;

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

		void IsBarancedProcess(SonikRBTreeNodeBaseRaw*& Node_)
		{
			//ファーストパターンチェック
			if( Node_->Parent->right_ == 0 )
			{
				//祖父の右の子がいなければ、右回転を行う。
				Node_ = RightRotateTree(Node_->Parent);
			}else
			{
				//祖父の右の子がいれば、祖父の両側の子の色を黒にし、祖父を赤にしてさらに上をチェック
				SonikRBTreeNodeBaseRaw* ControlNode = Node_->Parent;

				//左の子を見つけられなければ左回転を行う
				if(ControlNode->left_ == 0)
				{
					ControlNode = LeftRotateTree(ControlNode);
				}else
				{
					ControlNode->left_->colors = SonikRBTreeNodeBase::TreeBlack;
					ControlNode->right_->colors = SonikRBTreeNodeBase::TreeBlack;
				};

				if(ControlNode->root_)
				{
					//祖父がルートであれば即終了
					return;
				};

				ControlNode->colors = SonikRBTreeNodeBase::TreeRed;


				ControlNode = ControlNode->Parent;

				while(1)
				{
					if(ControlNode->colors == SonikRBTreeNodeBase::TreeBlack)
					{
						//黒なら終了
						break;
					};

					if( ControlNode->Parent->right_->colors == SonikRBTreeNodeBase::TreeRed )
					{
						//さらに上の兄弟が赤であれば、兄弟とも黒になってコンティニュー
						ControlNode->colors = SonikRBTreeNodeBase::TreeBlack;
						ControlNode->Parent->right_->colors = SonikRBTreeNodeBase::TreeBlack;

						ControlNode = ControlNode->Parent;

						if( ControlNode->root_ )
						{
							//ルートなら終了
							break;
						};

						ControlNode->colors = SonikRBTreeNodeBase::TreeRed;
						ControlNode = ControlNode->Parent;
						continue;
					};

					//左下が赤で兄弟の色が赤と黒だった場合
					if( ControlNode->left_->colors == SonikRBTreeNodeBase::TreeRed )
					{
						//右回転して終わり
						ControlNode = RightRotateTree(ControlNode->Parent);
						break;

					};

					//一つ上の条件で右下が赤だった場合
					if( ControlNode->right_->colors == SonikRBTreeNodeBase::TreeRed )
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
		bool __INFIND__(unsigned long SearchVal, SonikRBTreeNodeBaseRaw*& GetObject)
		{
			SonikRBTreeNodeBaseRaw* tmpNode = RootNode;

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
		SonikRBTreeRaw(void)
		:RootNode(0)
		,LinerTop(0)
		,LinerEnd(0)
		{
			try
			{
				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(AllocSmtPtr_, sizeof(Nodes) * 150) )
				{
					throw -1;
				};

			}catch(...)
			{
				throw;
			};
		};

		SonikRBTreeRaw(unsigned long SetSize_)
		:RootNode(0)
		,LinerTop(0)
		,LinerEnd(0)
		{
			try
			{
				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(AllocSmtPtr_, SetSize_ * 150) )
				{
					throw -1;
				};

			}catch(...)
			{
				throw;
			};
		};

		//ノードに子を追加します。
		bool Insert(SetDataType SetData, unsigned long SetPriority)
		{
			atmlock_.lock();
			Nodes* tmpSmtPtr;
			SonikRBTreeNodeBaseRaw* PretmpNode;
			SonikRBTreeNodeBaseRaw* tmpNode;
			SonikRBTreeNodeBaseRaw** pDirectionInsert = 0;

			if( !AllocSmtPtr_.GetAlloc(tmpSmtPtr) )
			{
				return false;
			};

			//挿入するオブジェクトの色は赤
			tmpSmtPtr->m_data = SetData;
			tmpSmtPtr->colors = SonikRBTreeNodeBase::TreeRed;
			tmpSmtPtr->root_ = false;
			tmpSmtPtr->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpSmtPtr->m_data = SetData;
				tmpSmtPtr->colors = SonikRBTreeNodeBase::TreeBlack;
				tmpSmtPtr->root_ = true;
				tmpSmtPtr->NodeValue = SetPriority;

				RootNode = tmpSmtPtr;
				LinerTop = tmpSmtPtr;
				LinerEnd = tmpSmtPtr;

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
								tmpSmtPtr->Prev = tmpNode->Prev;
								tmpSmtPtr->Next = tmpNode;
								tmpNode->Prev->Next = tmpSmtPtr;
								tmpNode->Prev = tmpSmtPtr;
							}else
							{
								tmpSmtPtr->Next = tmpNode;
								tmpNode->Prev = tmpSmtPtr;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpSmtPtr;
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
								tmpSmtPtr->Next = tmpNode->Next;
								tmpSmtPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpSmtPtr;
								tmpNode->Next = tmpSmtPtr;
							}else
							{
								tmpSmtPtr->Prev = tmpNode;
								tmpNode->Next = tmpSmtPtr;
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
				(*pDirectionInsert) = std::move(tmpSmtPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.Unlock();
			return true;

		};

		//ノードの最後尾に子を追加します。
		bool Insert(SetDataType SetData)
		{
			atmlock_.lock();
			Nodes* tmpSmtPtr;
			SonikRBTreeNodeBaseRaw* PretmpNode;
			SonikRBTreeNodeBaseRaw* tmpNode;
			SonikRBTreeNodeBaseRaw** pDirectionInsert = 0;
			unsigned long SetPriority;

			if( LinerEnd == 0 )
			{
				SetPriority = 0;
			}else
			{
				if( LinerEnd->NodeValue == 0xFFFFFFFF )
				{
					//最後尾に追加したいが　識別番号の最大値が使われているため追加できない。
					return false;
				};

				SetPriority = LinerEnd->NodeValue + 1;
			};

			if( !AllocSmtPtr_.GetAlloc(tmpSmtPtr) )
			{
				return false;
			};

			//挿入するオブジェクトの色は赤
			tmpSmtPtr->m_data = SetData;
			tmpSmtPtr->colors = SonikRBTreeNodeBase::TreeRed;
			tmpSmtPtr->root_ = false;
			tmpSmtPtr->NodeValue = SetPriority;


			//初回なら根として設定
			if(RootNode == 0)
			{
				tmpSmtPtr->m_data = SetData;
				tmpSmtPtr->colors = SonikRBTreeNodeBase::TreeBlack;
				tmpSmtPtr->root_ = true;
				tmpSmtPtr->NodeValue = SetPriority;

				RootNode = tmpSmtPtr;
				LinerTop = tmpSmtPtr;
				LinerEnd = tmpSmtPtr;

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
								tmpSmtPtr->Prev = tmpNode->Prev;
								tmpSmtPtr->Next = tmpNode;
								tmpNode->Prev->Next = tmpSmtPtr;
								tmpNode->Prev = tmpSmtPtr;
							}else
							{
								tmpSmtPtr->Next = tmpNode;
								tmpNode->Prev = tmpSmtPtr;
							};

							if( SetPriority < LinerTop->NodeValue)
							{
								LinerTop = tmpSmtPtr;
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
								tmpSmtPtr->Next = tmpNode->Next;
								tmpSmtPtr->Prev = tmpNode;
								tmpNode->Next->Prev = tmpSmtPtr;
								tmpNode->Next = tmpSmtPtr;
							}else
							{
								tmpSmtPtr->Prev = tmpNode;
								tmpNode->Next = tmpSmtPtr;
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
				(*pDirectionInsert) = std::move(tmpSmtPtr);
				(*pDirectionInsert)->Parent = tmpNode;

				//挿入箇所ノードがルートノード以外であれば処理をする。
				if(!tmpNode->root_)
				{
					IsBarancedProcess(tmpNode);
				};

			};

			atmlock_.Unlock();
			return true;

		};

		bool TreeFind(unsigned long SearchValue, SetDataType& GetData)
		{
			SonikRBTreeNodeBaseRaw* Get_;
			Nodes* UpcastObj_;

			if( !__INFIND__(SearchValue, Get_) )
			{
				return false;
			};

			UpcastObj_ = reinterpret_cast<Nodes*>(Get_);

			GetData = UpcastObj_->m_data;
			return true;
		};

		void Erase(unsigned long EraseValue)
		{
			SonikRBTreeNodeBaseRaw* Get_;
			SonikRBTreeNodeBaseRaw* tmp_;
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
				AllocSmtPtr_->FreeAlloc(Get_);

				return;
			};

			if(Get_->colors == SonikRBTreeNodeBase::TreeRed)
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
					AllocSmtPtr_->FreeAlloc(Get_);

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

				AllocSmtPtr_->FreeAlloc(tmp_);

				//終了
				return;

			}else
			{
				//削除されるノード（自ノード)が黒の場合

				unsigned long pattern_ = 100;
				bool patternmatchEnd = false;
				bool SecondPattern = false;

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
					AllocSmtPtr_->FreeAlloc(tmp_);

					while( !patternmatchEnd )
					{
						if( Get_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == SonikRBTreeNodeBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->right_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeRed) && (Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeRed )
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
							Get_->colors = SonikRBTreeNodeBase::TreeBlack;

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
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = SonikRBTreeNodeBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は左削除の右ツリー操作なので、右回転)に回転させる。
							RightRotateTree(Get_->Parent->right_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->right_->right_->colors = SonikRBTreeNodeBase::TreeRed;
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							LeftRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->right_->colors = SonikRBTreeNodeBase::TreeBlack;

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
					AllocSmtPtr_->FreeAlloc(tmp_);

					while( !patternmatchEnd )
					{
						if( Get_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == SonikRBTreeNodeBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->left_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeRed) && (Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeRed )
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
							Get_->colors = SonikRBTreeNodeBase::TreeBlack;

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
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = SonikRBTreeNodeBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は右削除の左ツリー操作なので、左回転)に回転させる。
							LeftRotateTree(Get_->Parent->left_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->left_->left_->colors = SonikRBTreeNodeBase::TreeRed;
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							RightRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->left_->colors = SonikRBTreeNodeBase::TreeBlack;

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

		void Erase(SonikLib::SonikLinerOperator<SetDataType>* EraseOperator)
		{
			SonikRBTreeNodeBaseRaw* Get_;
			SonikRBTreeNodeBaseRaw* tmp_;
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
				AllocSmtPtr_->FreeAlloc(Get_);
				EraseOperator->pNodes_ = 0;

				return;
			};

			if(Get_->colors == SonikRBTreeNodeBase::TreeRed)
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
					AllocSmtPtr_->FreeAlloc(Get_);

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

				AllocSmtPtr_->FreeAlloc(tmp_);

				//終了
				return;

			}else
			{
				//削除されるノード（自ノード)が黒の場合

				unsigned long pattern_ = 100;
				bool patternmatchEnd = false;
				bool SecondPattern = false;

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
					AllocSmtPtr_->FreeAlloc(tmp_);

					while( !patternmatchEnd )
					{
						if( Get_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == SonikRBTreeNodeBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->right_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeRed) && (Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->right_->GetLeftColor() == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->right_->GetRightColor() == SonikRBTreeNodeBase::TreeRed )
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
							Get_->colors = SonikRBTreeNodeBase::TreeBlack;

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
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = SonikRBTreeNodeBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は左削除の右ツリー操作なので、右回転)に回転させる。
							RightRotateTree(Get_->Parent->right_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->right_->right_->colors = SonikRBTreeNodeBase::TreeRed;
							Get_->Parent->right_->colors = SonikRBTreeNodeBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							LeftRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->right_->colors = SonikRBTreeNodeBase::TreeBlack;

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
					AllocSmtPtr_->FreeAlloc(tmp_);

					while( !patternmatchEnd )
					{
						if( Get_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 0;

						}else if( Get_->colors == SonikRBTreeNodeBase::TreeBlack && Get_->root_ )
						{
							pattern_ = 1;

						}else if( Get_->Parent->left_->colors == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 2;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 3;

						}else if( (Get_->Parent->colors == SonikRBTreeNodeBase::TreeRed) && (Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeBlack) && (Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeBlack) )
						{
							pattern_ = 4;

						}else if( Get_->Parent->left_->GetLeftColor() == SonikRBTreeNodeBase::TreeRed )
						{
							pattern_ = 5;

						}else if( Get_->Parent->left_->GetRightColor() == SonikRBTreeNodeBase::TreeRed )
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
							Get_->colors = SonikRBTreeNodeBase::TreeBlack;

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
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeRed;
							//親を新たな判断基準とする。
							Get_ = Get_->Parent;

							//ケース再判断
							break;

						case 4:
							//兄弟が黒で、兄弟の親が赤、子が黒の場合
							//親を黒に変更
							Get_->Parent->colors = SonikRBTreeNodeBase::TreeBlack;
							//兄弟を赤に変更
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeRed;

							//終了
							patternmatchEnd = true;
							break;

						case 5:
							//兄弟の子のうち、内側の子が赤の場合
							//兄弟を中心に外側(ここの処理は右削除の左ツリー操作なので、左回転)に回転させる。
							LeftRotateTree(Get_->Parent->left_);

							//元兄弟の色を赤に、新兄弟の色を黒に変更
							Get_->Parent->left_->left_->colors = SonikRBTreeNodeBase::TreeRed;
							Get_->Parent->left_->colors = SonikRBTreeNodeBase::TreeBlack;

							//再判断
							break;

						case 6:
							//兄弟の子のうち、外側の子が赤の場合
							//親を中心に削除指定ノード側に回転
							RightRotateTree(Get_->Parent);

							//外側の子を黒にする。
							Get_->Parent->Parent->left_->colors = SonikRBTreeNodeBase::TreeBlack;

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
		SonikLib::SonikLinerOperator<SetDataType> GetOpe_LinerBegin(void)
		{
			SonikLib::SonikLinerOperator<SetDataType> ope_;

			ope_.pNodes_ = LinerTop;

			return ope_;
		};

		//リニアサーチ用のオブジェクトを取得します。
		SonikLib::SonikLinerOperator<SetDataType> GetOpe_LinerEnd(void)
		{
			SonikLib::SonikLinerOperator<SetDataType> ope_;

			ope_.pNodes_ = LinerEnd;

			return ope_;
		};

	};//end class;


};//end namespace



#endif /* SONIKBALANCEDTREE_RB_SONIKRBTREE_H_ */
