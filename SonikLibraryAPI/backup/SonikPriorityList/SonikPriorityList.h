/*
 * SonikPriorityList.h
 *
 *  Created on: 2016/03/15
 *      Author: SONIC_000
 */

#ifndef SONIKPRIORITYLIST_SONIKPRIORITYLIST_H_
#define SONIKPRIORITYLIST_SONIKPRIORITYLIST_H_

#include "..\\SonikAllocateUse.h"
#include "..\\SonikCASLockUse.h"
#include "SonikPriorityListNode.h"
#include "SonikPriorityListLinearSearch.h"

#include "..\\SonikLoggerUse.h"
//#include <sstream>
#include <string>

namespace SonikList
{
	template <class ListType>
	class SonikPriorityList
	{
	private:
		SonikLib::SonikRawAllocObjectPtr AllocPtr;

		//Linear Start Point
		SonikListNode::SonikListNodeBase* LinearTop;
		//Linear End Point
		SonikListNode::SonikListNodeBase* LinearEnd;

		unsigned long ItemCount;

		bool Inserted_;

		SonikCAS::SonikAtomicLock lock_;

	private:
		//プライベートソート関数 StartとEndを含む範囲内を挿入ソートします。
		//引数1及び、2の位置は置き換わります。
		void __InsertSort__(SonikListNode::SonikListNodeBase** pStart, SonikListNode::SonikListNodeBase** pEnd)
		{
			if( pStart == 0 || pEnd == 0 )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart) == 0 || (*pEnd) == 0 )
			{
				//ソートの必要が無い。
				return;
			};

			if( pStart == pEnd )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart) == (*pEnd) )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart)->Next == (*pEnd) )
			{
				//ソートの必要が無い。
				return;
			};

			SonikListNode::SonikPriorityListNode<ListType>* pChangePoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart)->Next);
			SonikListNode::SonikPriorityListNode<ListType>* pLinearPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart));
			SonikListNode::SonikPriorityListNode<ListType>* NextPoint = 0;
			register unsigned long ChagePointVal = pChangePoint->Priority;

			//交換対象を見つける
			while(1)
			{

				//線形ポインタとpChangeポインタが等しいなら差し込む場所が無いということになる。
				if(pChangePoint == pLinearPoint)
				{
					//現在調査していたChangeポインタが最終要素であればbreak;
					if(pChangePoint == (*pEnd))
					{
						break;
					};

					//差し込む場所がなければ、変更せず、次の要素をチェック
					pChangePoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pChangePoint->Next);
					//次の要素の値をレジスタに保存。
					ChagePointVal = pChangePoint->Priority;

					//線形ポインタをトップに戻す。
					pLinearPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart));

					//コンティニュー
					continue;
				};

				//pChangePoint以下であれば、線形ポインタを進めてコンティニュー
				if(ChagePointVal >= pLinearPoint->Priority)
				{
					pLinearPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLinearPoint->Next);
					continue;

				}else
				{
					//pCahngePointより大きければ、現在の線形ポイント位置の前に挿入する。
					//pChangeポイントが最終要素であれば、pEnd位置を一つ前にずらして、繋がりを切断する。
					if(pChangePoint == (*pEnd))
					{
						//一つ前の要素を設定
						(*pEnd) = pChangePoint->Prev;

						//Next値をコピー
						(*pEnd)->Next = pChangePoint->Next;
						//繋がりを切断。
						pChangePoint->Prev = 0;

						//breakフラグとしてNextPointをNULLにする。
						NextPoint = 0;

					}else
					{
						//最終要素以外であれば自分の左右の要素の繋がりを切断する。
						//先頭要素と置き換わることはあるが、自身が先頭要素を指すことはない。
						//切断する前に、次のChangeポインタ位置を取得しておく。
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pChangePoint->Next);

						//左の繋がりを切断、自分の右の要素と繋げる
						pChangePoint->Prev->Next = pChangePoint->Next;
						//右の繋がりを切断
						pChangePoint->Next->Prev = pChangePoint->Prev;

						pChangePoint->Prev = 0;
						pChangePoint->Next = 0;

					};

					//線形ポインタ位置が先頭要素であれば、pStartの要素をChange要素に変更する。
					if(pLinearPoint == (*pStart))
					{
						//先頭要素として設定
						(*pStart) = pChangePoint;

						//線形ポイント位置の左に挿入する。
						pLinearPoint->Prev = pChangePoint;
						//線形ポイント位置と繋がる。
						pChangePoint->Next = pLinearPoint;

					}else
					{
						//先頭要素以外であれば、線形ポイント位置の左の要素として挿入する。
						//線形ポイントの左の要素の繋がりをChangeポイントと繋げる。
						pLinearPoint->Prev->Next = pChangePoint;
						//Changeポイントの左の要素に繋げる
						pChangePoint->Prev = pLinearPoint->Prev;
						//線形ポイントの左の位置にChangeポイントを繋げる。
						pLinearPoint->Prev = pChangePoint;
						//ChangePointの右の位置に線形ポイントを繋げる。
						pChangePoint->Next = pLinearPoint;
					};

					//比較対象要素がなければ終了
					if(NextPoint == 0)
					{
						break;
					};

					//スタート位置と検索位置の設定
					pChangePoint = NextPoint;
					pLinearPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart));

					ChagePointVal = pChangePoint->Priority;

				}; //end else

			};//end while

		}; //end fanction

		//プライベートソート関数 StartとEndを含む範囲内をマージソートします。
		//引数1及び、2の位置は置き換わります。
		//引数３には要素数を指定します。
		void __MargeSort__(SonikListNode::SonikListNodeBase** pStart, SonikListNode::SonikListNodeBase** pEnd, unsigned long NodeListSize)
		{
			if( pStart == 0 || pEnd == 0 )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart) == 0 || (*pEnd) == 0 )
			{
				//ソートの必要が無い。
				return;
			};

			if( pStart == pEnd )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart) == (*pEnd) )
			{
				//ソートの必要が無い。
				return;
			};

			if( (*pStart)->Next == (*pEnd) )
			{
				//ソートの必要が無い。
				return;
			};

			//NodeListSizeが50より下なら挿入ソートして終了
			if(NodeListSize <= 50)
			{
				__InsertSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&(*pStart)), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&(*pEnd)));
				return;
			};

			register unsigned long SplitCount = NodeListSize / 50;
			if( NodeListSize - (50 * SplitCount) > 0 )
			{
				++SplitCount;
			};

			SonikListNode::SonikPriorityListNode<ListType>** InsartSortArray =0;
			try
			{
				InsartSortArray = new SonikListNode::SonikPriorityListNode<ListType>*[SplitCount];
			}catch(std::bad_alloc& e)
			{
				throw;
			};

			SonikListNode::SonikPriorityListNode<ListType>* pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart));
			SonikListNode::SonikPriorityListNode<ListType>* pRight = 0;
			SonikListNode::SonikPriorityListNode<ListType>* NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>((*pStart));
			register unsigned long lopi;
			register bool InsartEnd = false;

			SplitCount = 0;

			//要素数50個ずつ挿入ソートをかける(50個ずつなのは、挿入ソートの効率がいいのは５０個までだから。)
			while(1)
			{
				//ループ展開
				for(lopi = 49; lopi > 0; lopi -= 7)
				{
					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 1;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 2;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 3;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 4;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 5;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 6;
						break;
					};

					NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

					if( (*pEnd) == NextPoint )
					{
						InsartEnd = true;
						lopi -= 7;
						break;
					};

				};

				//挿入ソートの実行
				pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);
				__InsertSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pLeft), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&NextPoint));

				//ソート結果を配列に保存
				InsartSortArray[SplitCount] = pLeft;
				++SplitCount;

				//挿入ソート後のソート要素同士は、ソート数単位でリンクを切っておく。
				NextPoint->Next = 0;
				pRight->Prev = 0;

				//次の要素がなければ挿入ソート工程終了
				if(InsartEnd)
				{
					break;
				};

				//要素があれば次の要素へ
				NextPoint = pRight;
				pLeft = pRight;
			};

			//常に配列番号0番を軸にして、マージしていきます。
			lopi = 1;
			pLeft = InsartSortArray[0];
			pRight = InsartSortArray[lopi];
			NextPoint = 0;
			InsartEnd = false;

			while(1)
			{
				//左の要素と右の要素の比較のうち、小さい方を採用する。
				//等しい場合は、左の要素を採用する。
				if(pLeft->Priority < pRight->Priority)
				{
					//左の要素が小さいので、左の要素を採用
					//初回であれば、そのまま代入
					if(NextPoint == 0)
					{
						NextPoint = pLeft;
						InsartSortArray[0] = NextPoint;
					}else
					{
						//初回以外であれば次の要素に設定
						NextPoint->Next = pLeft;
						NextPoint->Next->Prev = NextPoint;
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					if(pLeft != 0)
					{
						pLeft->Prev->Next = 0;
						pLeft->Prev = 0;
					};

				}else if( pRight->Priority < pLeft->Priority)
				{
					//右の要素が小さいので、右の要素を採用
					//初回であれば、そのまま代入
					if(NextPoint == 0)
					{
						NextPoint = pRight;
						InsartSortArray[0] = NextPoint;
					}else
					{
						//初回以外であれば次の要素に設定
						NextPoint->Next = pRight;
						NextPoint->Next->Prev = NextPoint;
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);
					};

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
					if(pRight != 0)
					{
						pRight->Prev->Next = 0;
						pRight->Prev = 0;
					};

				}else if(pLeft->Priority == pRight->Priority)
				{
					//等しい時は左を採用
					//初回であれば、そのまま代入
					if(NextPoint == 0)
					{
						NextPoint = pLeft;
						InsartSortArray[0] = NextPoint;
					}else
					{
						//初回以外であれば次の要素に設定
						NextPoint->Next = pLeft;
						NextPoint->Next->Prev = NextPoint;
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					if(pLeft != 0)
					{
						pLeft->Prev->Next = 0;
						pLeft->Prev = 0;
					};

				};//end else if

				if(pLeft == 0)
				{
					//左の要素がなくなった場合、現在の右の要素を左要素として扱う。
					//右要素は一つすすめる。
					pLeft = pRight;
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);

					//左の要素として扱う右の要素のNextは0を設定しておく(隣接するとポインタがいろいろと競合してしまうので)
					pLeft->Next = 0;
					//右の要素を進めた際に右の要素がなくなれば、最後の要素だったということなので、挿入して終了
					if(pRight == 0)
					{
						NextPoint->Next = pLeft;
						NextPoint->Next->Prev = NextPoint;
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

						InsartEnd = true;
					};
				}else if( pRight == 0 )
				{
					//右の要素がなくなった場合、左の次の要素を右の要素として扱う。
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					//設定後の左の要素のNextは0を設定しておく(隣接するとポインタがいろいろと競合してしまうので)
					pLeft->Next = 0;
					//左の要素のNextがなかった場合は、最後の要素なのでそのまま挿入して終了
					if(pRight == 0)
					{
						NextPoint->Next = pLeft;
						NextPoint->Next->Prev = NextPoint;
						NextPoint = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(NextPoint->Next);

						InsartEnd = true;
					};
				};

				if(InsartEnd)
				{

					++lopi;

					if(lopi == SplitCount)
					{
						break;
					};

					pLeft = InsartSortArray[0];
					pRight = InsartSortArray[lopi];
					NextPoint = 0;

					InsartEnd = false;
				};

			};//end while

			(*pStart) = InsartSortArray[0];
			(*pEnd) = NextPoint;

			delete[] InsartSortArray;
		};

		bool __pivselect__(SonikListNode::SonikListNodeBase* pStart, SonikListNode::SonikListNodeBase* pEnd, unsigned long& _Get_)
		{
			SonikListNode::SonikPriorityListNode<ListType>* pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pStart);
			SonikListNode::SonikPriorityListNode<ListType>* pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
			register unsigned long Pivot_ = 0xFFFFFFFF;
			register unsigned long LeftPriority = pLeft->Priority;

			_Get_ = Pivot_;
			while(pRight != pEnd)
			{
				if(LeftPriority != pRight->Priority)
				{
					(LeftPriority < pRight->Priority) ? Pivot_ = pRight->Priority : Pivot_ = LeftPriority;

					break;
				};

				pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
			};

			if(Pivot_ == 0xFFFFFFFF)
			{
				//ソートの必要がない。
				return true;
			};

			_Get_ = Pivot_;
			return false;
		};

		void __QuickSort__(void)
		{
			if( (ItemCount -1) < 2 )
			{
				//ソートの必要性なし。
				return;
			}

			register unsigned long PivotVal = 0;

			//基準値決め。
			if(__pivselect__(LinearTop, LinearEnd->Prev, PivotVal))
			{
				//ソートの必要がない。
				return;
			};

			register unsigned long SplitCount = (ItemCount -1) / 50;
			SonikListNode::S_Inner_PListQSortNode* PointArray =0;

			if( (ItemCount -1) - (50 * SplitCount) > 0 )
			{
				++SplitCount;
			};

			try
			{
				PointArray = new SonikListNode::S_Inner_PListQSortNode[SplitCount];
			}catch(std::bad_alloc& e)
			{
				throw;
			};


			//基準値を元にクイックソート
			register unsigned long LeftCount = 1;
			register unsigned long RightCount = (ItemCount -1);
			register unsigned long UpdateCount = 1;

			SonikListNode::SonikPriorityListNode<ListType>* pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(LinearTop);
			SonikListNode::SonikPriorityListNode<ListType>* pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(LinearEnd->Prev);
			SonikListNode::SonikListNodeBase pSwapVal;
			SonikListNode::SonikListNodeBase* pUpdateTop = 0;
			register bool SwapEnd = false;

			SplitCount = 0;

			//初回スワップ
			while(1)
			{
				//左から交換対象を検索
				while(1)
				{
					//ピボット値より大きいか、等しいなら交換対象としてカウント
					if(PivotVal <= pLeft->Priority)
					{
						break;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					++LeftCount;
				};//end left while

				//右から交換対象を検索
				while(1)
				{
					//ピボット値より小さい場合、交換対象としてカウント
					if(pRight->Priority < PivotVal)
					{
						break;
					};

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
					--RightCount;
				};//end right while

				//見つかったポイントが交差地点かどうかをチェックする。
				//条件のいずれかに当てはまれば、終了
				if(LeftCount > RightCount)
				{
					//完全に交差していたら両要素を下げます。
					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
					--LeftCount;
					++RightCount;

					SwapEnd = true;

				}else if(LeftCount == RightCount)
				{
					//同じポイントを指していた場合、左を優先的に下げるが、
					//左が一番左側にあれば右を下げる。
					if(pLeft->Prev != 0)
					{
						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
						--LeftCount;
					}else
					{
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
						++RightCount;
					};

					SwapEnd = true;
				};

				//終了フラグが立っていればbreak;
				if(SwapEnd)
				{
					//分割ポイントを保存
					PointArray[SplitCount].Point = pRight;
					PointArray[SplitCount].PosNum = RightCount;
					SwapEnd = false;
					break;
				};

				//スワップ
				//隣り合っていた場合と、離れていた場合の処理
				if(pLeft->Next == pRight && pRight->Prev == pLeft)
				{
					//スワップ要素が隣り合っていた場合。
					pLeft->Next = pRight->Next;
					pRight->Prev = pLeft->Prev;

					pLeft->Prev = pRight;
					pRight->Next = pLeft;

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);

					if(pLeft->Prev != 0)
					{
						pLeft->Prev->Next = pLeft;
					};

					if(pRight->Next != 0)
					{
						pRight->Next->Prev = pRight;
					};

				}else
				{
					//スワップ要素が離れていた場合。
					pSwapVal.Next = pLeft->Next;
					pSwapVal.Prev = pLeft->Prev;

					pLeft->Next = pRight->Next;
					pLeft->Prev = pRight->Prev;

					pRight->Next = pSwapVal.Next;
					pRight->Prev = pSwapVal.Prev;

					pSwapVal.Next = pLeft;
					pSwapVal.Prev = pRight;

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Prev);
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Next);

					if(pLeft->Prev != 0)
					{
						pLeft->Prev->Next = pLeft;
					};
					pLeft->Next->Prev = pLeft;

					if(pRight->Next != 0)
					{
						pRight->Next->Prev = pRight;
					};
					pRight->Prev->Next = pRight;
				};

				if(LinearTop == pRight)
				{
					LinearTop = pLeft;
				};

				if(LinearEnd == pLeft)
				{
					LinearEnd = pRight;
				};

				pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
				pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
				++LeftCount;
				--RightCount;

			};//end while


			//初回の基準位置を元に左を更にソートしていく。
			//左半分のソート
			SonikListNode::SonikListNodeBase* pSort_Prev = 0;
			SonikListNode::SonikListNodeBase* pSort_Next = 0;
			bool NextEnd = false;

			pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(LinearTop);
			LeftCount = 1;

			pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
			RightCount = PointArray[SplitCount].PosNum -1;

			UpdateCount = LeftCount;
			pUpdateTop = pLeft;

			while(1)
			{
				if(NextEnd)
				{
					break;
				};

				if((RightCount - LeftCount) <= 50)
				{
					if(SplitCount == 0)
					{
						NextEnd = true;
					};

					//インサートソート
					pSort_Prev = pLeft->Prev;
					pSort_Next = pRight->Next;
					__InsertSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pLeft), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pRight));

					pLeft->Prev = pSort_Prev;
					pRight->Next = pSort_Next;

					//ソート終了後、つなげ直す。
					if(pSort_Prev != 0)
					{
						pSort_Prev->Next = pLeft;
					}else
					{
						//Prevが何もないなら、LinearTopだったということなので、Top値を更新。
						LinearTop = pLeft;
					};

					pSort_Next->Prev = pRight;

					//繋げ直したら、アップデート値を更新。
					pUpdateTop = PointArray[SplitCount].Point;
					UpdateCount = PointArray[SplitCount].PosNum;

					if(SplitCount != 0)
					{
						--SplitCount;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
					LeftCount = UpdateCount;

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
					RightCount = PointArray[SplitCount].PosNum -1;

					continue;

				}else if((RightCount - LeftCount) <= 50000)
				{
					if(SplitCount == 0)
					{
						NextEnd = true;
					};

					//マージソート
					pSort_Prev = pLeft->Prev;
					pSort_Next = pRight->Next;
					__MargeSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pLeft), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pRight), (RightCount - LeftCount));

					pLeft->Prev = pSort_Prev;
					pRight->Next = pSort_Next;

					//ソート終了後、つなげ直す。
					if(pSort_Prev != 0)
					{
						pSort_Prev->Next = pLeft;
					}else
					{
						//Prevが何もないなら、LinearTopだったということなので、Top値を更新。
						LinearTop = pLeft;
					};

					pSort_Next->Prev = pRight;

					//繋げ直したら、アップデート値を更新。
					pUpdateTop = PointArray[SplitCount].Point;
					UpdateCount = PointArray[SplitCount].PosNum;

					if(SplitCount != 0)
					{
						--SplitCount;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
					LeftCount = UpdateCount;

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
					RightCount = PointArray[SplitCount].PosNum -1;

					continue;
				};

				//基準値決め。
				if(__pivselect__(pLeft, pRight, PivotVal))
				{
					//ソートの必要がない。
					return;
				};

				while(1)
				{

					//左から交換対象を検索
					while(1)
					{
						//ピボット値より大きいか、等しいなら交換対象としてカウント
						if(PivotVal <= pLeft->Priority)
						{
							break;
						};

						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
						++LeftCount;
					};//end left while

					//右から交換対象を検索
					while(1)
					{
						//ピボット値より小さい場合、交換対象としてカウント
						if(pRight->Priority < PivotVal)
						{
							break;
						};

						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
						--RightCount;
					};//end right while

					//見つかったポイントが交差地点かどうかをチェックする。
					//条件のいずれかに当てはまれば、終了
					if(LeftCount > RightCount)
					{
						//完全に交差していたら両要素を下げます。
						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
						--LeftCount;
						++RightCount;

						SwapEnd = true;

					}else if(LeftCount == RightCount)
					{
						//同じポイントを指していた場合、左を優先的に下げるが、
						//左が一番左側にあれば右を下げる。
						if(pLeft->Prev != 0)
						{
							pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
							--LeftCount;
						}else
						{
							pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
							++RightCount;
						};

						SwapEnd = true;
					};

					//終了フラグが立っていればbreak;
					if(SwapEnd)
					{
						//分割ポイントを保存
						++SplitCount;
						PointArray[SplitCount].Point = pRight;
						PointArray[SplitCount].PosNum = RightCount;
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
						--RightCount;
						SwapEnd = false;
						break;
					};

					//スワップ
					//隣り合っていた場合と、離れていた場合の処理
					if(pLeft->Next == pRight && pRight->Prev == pLeft)
					{
						//スワップ要素が隣り合っていた場合。
						pLeft->Next = pRight->Next;
						pRight->Prev = pLeft->Prev;

						pLeft->Prev = pRight;
						pRight->Next = pLeft;

						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);

						if(pLeft->Prev != 0)
						{
							pLeft->Prev->Next = pLeft;
						};

						if(pRight->Next != 0)
						{
							pRight->Next->Prev = pRight;
						};
						pRight->Prev->Next = pRight;

					}else
					{
						//スワップ要素が離れていた場合。
						pSwapVal.Next = pLeft->Next;
						pSwapVal.Prev = pLeft->Prev;

						pLeft->Next = pRight->Next;
						pLeft->Prev = pRight->Prev;

						pRight->Next = pSwapVal.Next;
						pRight->Prev = pSwapVal.Prev;

						pSwapVal.Next = pLeft;
						pSwapVal.Prev = pRight;

						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Prev);
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Next);

						if(pLeft->Prev != 0)
						{
							pLeft->Prev->Next = pLeft;
						}
						pLeft->Next->Prev = pLeft;

						if(pRight->Next != 0)
						{
							pRight->Next->Prev = pRight;
						};
						pRight->Prev->Next = pRight;
					};

					if(pUpdateTop == pRight)
					{
						pUpdateTop = pLeft;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
					++LeftCount;
					--RightCount;

				};//end while

				if( pUpdateTop->Prev == 0 )
				{
					LinearTop = pUpdateTop;
				};

				pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
				LeftCount = UpdateCount;

			};//end while


			//初回の基準位置を元に右を更にソートしていく。
			//右半分のソート
			pSort_Prev = 0;
			pSort_Next = 0;
			NextEnd = false;

			pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point);
			LeftCount = PointArray[SplitCount].PosNum;

			PointArray[SplitCount].Point = LinearEnd;
			PointArray[SplitCount].PosNum = (ItemCount -1);

			pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
			RightCount = PointArray[SplitCount].PosNum -1;

			UpdateCount = LeftCount;
			pUpdateTop = pLeft;

			while(1)
			{
				if(NextEnd)
				{
					break;
				};

				if((RightCount - LeftCount) <= 50)
				{
					if(SplitCount == 0)
					{
						NextEnd = true;
					};

					//インサートソート
					pSort_Prev = pLeft->Prev;
					pSort_Next = pRight->Next;
					__InsertSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pLeft), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pRight));

					pLeft->Prev = pSort_Prev;
					pRight->Next = pSort_Next;

					//ソート終了後、つなげ直す。
					if(pSort_Prev != 0)
					{
						pSort_Prev->Next = pLeft;
					}else
					{
						//Prevが何もないなら、LinearTopだったということなので、Top値を更新。
						LinearTop = pLeft;
					};

					pSort_Next->Prev = pRight;

					//繋げ直したら、アップデート値を更新。
					pUpdateTop = PointArray[SplitCount].Point;
					UpdateCount = PointArray[SplitCount].PosNum;

					if(SplitCount != 0)
					{
						--SplitCount;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
					LeftCount = UpdateCount;

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
					RightCount = PointArray[SplitCount].PosNum -1;

					continue;

				}else if((RightCount - LeftCount) <= 50000)
				{
					if(SplitCount == 0)
					{
						NextEnd = true;
					};

					//マージソート
					pSort_Prev = pLeft->Prev;
					pSort_Next = pRight->Next;
					__MargeSort__(reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pLeft), reinterpret_cast<SonikListNode::SonikListNodeBase**>(&pRight), (RightCount - LeftCount));

					pLeft->Prev = pSort_Prev;
					pRight->Next = pSort_Next;

					//ソート終了後、つなげ直す。
					if(pSort_Prev != 0)
					{
						pSort_Prev->Next = pLeft;
					}else
					{
						//Prevが何もないなら、LinearTopだったということなので、Top値を更新。
						LinearTop = pLeft;
					};

					pSort_Next->Prev = pRight;

					//繋げ直したら、アップデート値を更新。
					pUpdateTop = PointArray[SplitCount].Point;
					UpdateCount = PointArray[SplitCount].PosNum;

					if(SplitCount != 0)
					{
						--SplitCount;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
					LeftCount = UpdateCount;

					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(PointArray[SplitCount].Point->Prev);
					RightCount = PointArray[SplitCount].PosNum -1;

					continue;
				};

				//基準値決め。
				if(__pivselect__(pLeft, pRight, PivotVal))
				{
					//ソートの必要がない。
					return;
				};

				while(1)
				{

					//左から交換対象を検索
					while(1)
					{
						//ピボット値より大きいか、等しいなら交換対象としてカウント
						if(PivotVal <= pLeft->Priority)
						{
							break;
						};

						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
						++LeftCount;
					};//end left while

					//右から交換対象を検索
					while(1)
					{
						//ピボット値より小さい場合、交換対象としてカウント
						if(pRight->Priority < PivotVal)
						{
							break;
						};

						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
						--RightCount;
					};//end right while

					//見つかったポイントが交差地点かどうかをチェックする。
					//条件のいずれかに当てはまれば、終了
					if(LeftCount > RightCount)
					{
						//完全に交差していたら両要素を下げます。
						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
						--LeftCount;
						++RightCount;

						SwapEnd = true;

					}else if(LeftCount == RightCount)
					{
						//同じポイントを指していた場合、左を優先的に下げるが、
						//左が一番左側にあれば右を下げる。
						if(pLeft->Prev != 0)
						{
							pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);
							--LeftCount;
						}else
						{
							pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
							++RightCount;
						};

						SwapEnd = true;
					};

					//終了フラグが立っていればbreak;
					if(SwapEnd)
					{
						//分割ポイントを保存
						++SplitCount;
						PointArray[SplitCount].Point = pRight;
						PointArray[SplitCount].PosNum = RightCount;
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
						--RightCount;
						SwapEnd = false;
						break;
					};

					//スワップ
					//隣り合っていた場合と、離れていた場合の処理
					if(pLeft->Next == pRight && pRight->Prev == pLeft)
					{
						//スワップ要素が隣り合っていた場合。
						pLeft->Next = pRight->Next;
						pRight->Prev = pLeft->Prev;

						pLeft->Prev = pRight;
						pRight->Next = pLeft;

						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Next);
						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Prev);

						if(pLeft->Prev != 0)
						{
							pLeft->Prev->Next = pLeft;
						};

						if(pRight->Next != 0)
						{
							pRight->Next->Prev = pRight;
						};
						pRight->Prev->Next = pRight;

					}else
					{
						//スワップ要素が離れていた場合。
						pSwapVal.Next = pLeft->Next;
						pSwapVal.Prev = pLeft->Prev;

						pLeft->Next = pRight->Next;
						pLeft->Prev = pRight->Prev;

						pRight->Next = pSwapVal.Next;
						pRight->Prev = pSwapVal.Prev;

						pSwapVal.Next = pLeft;
						pSwapVal.Prev = pRight;

						pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Prev);
						pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pSwapVal.Next);

						if(pLeft->Prev != 0)
						{
							pLeft->Prev->Next = pLeft;
						}
						pLeft->Next->Prev = pLeft;

						if(pRight->Next != 0)
						{
							pRight->Next->Prev = pRight;
						};
						pRight->Prev->Next = pRight;
					};

					if(pUpdateTop == pRight)
					{
						pUpdateTop = pLeft;
					};

					pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pLeft->Next);
					pRight = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pRight->Prev);
					++LeftCount;
					--RightCount;

				};//end while

				if( pUpdateTop->Prev == 0 )
				{
					LinearTop = pUpdateTop;
				};

				pLeft = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(pUpdateTop);
				LeftCount = UpdateCount;

			};//end while

			delete[] PointArray;
		};

		void __HybridSort__(void)
		{
			lock_.lock();

			SonikListNode::SonikListNodeBase* pTop = LinearTop;
			SonikListNode::SonikListNodeBase* pLast = LinearEnd->Prev;

			if(ItemCount <= 2)
			{
				//ソートの必要がない。
				return;
			};

			if( (ItemCount - 1) <= 50 )
			{
				__InsertSort__(&pTop, &pLast);
				LinearTop = pTop;
				pLast->Next = LinearEnd;
				LinearEnd->Prev = pLast;

			}else if( (ItemCount -1) <= 50000 )
			{
				__MargeSort__(&pTop, &pLast, (ItemCount -1));
				LinearTop = pTop;
				pLast->Next = LinearEnd;
				LinearEnd->Prev = pLast;

			}else
			{
				__QuickSort__();
			};

			//==============DEBUG==============
			//InsertSortCheck
//			__InsertSort__(&pTop, &pLast);
//			LinearTop = pTop;
//			LinearEnd->Prev = pLast;
//			pLast->Next = LinearEnd;

			//MargeSortCheck
//			__MargeSort__(&pTop, &pLast, (ItemCount -1));
//			LinearTop = pTop;
//			LinearEnd->Prev = pLast;
//			pLast->Next = LinearEnd;

			//QuickSortCheck
//			__QuickSort__();

			lock_.Unlock();

			Inserted_ = false;

		};


	public:
		SonikPriorityList(unsigned long SetItemNum = 100)
		:LinearTop(0)
		,LinearEnd(0)
		,Inserted_(false)
		,ItemCount(0)
		{
			try
			{
				if( !SonikLibCall::CreateSonikMemoryAllocaorRaw(AllocPtr, ((sizeof(SonikListNode::SonikPriorityListNode<ListType>) + 24) * (SetItemNum +1)) ) )
				{
					throw std::bad_alloc();
				};

				SonikListNode::SonikPriorityListNode<ListType>* Node_;
				if( !AllocPtr->GetAlloc<SonikListNode::SonikPriorityListNode<ListType>>(Node_) )
				{
					AllocPtr->~SonikRawAllocObjectPtr();
					throw std::bad_alloc();
				};

				LinearTop = Node_;
				LinearEnd = Node_;

			}catch(std::bad_alloc& e)
			{
				throw;
			};

			++ItemCount;
		};

		~SonikPriorityList(void)
		{
			//no process;
		};

		//Add
		bool AddPush(ListType& SetItem, unsigned long ItemPriority = 0)
		{
			if(ItemPriority == 0xFFFFFFFF)
			{
				return false;
			};

			SonikListNode::SonikListNodeBase* pTmp = 0;
			SonikListNode::SonikPriorityListNode<ListType>* pPrev = 0;
			SonikListNode::SonikPriorityListNode<ListType>* pGetPtr = 0;

			//新しいモノが番兵になるスタイル。
			if( !AllocPtr->GetAlloc( pGetPtr ) )
			{
				return false;
			};

			lock_.lock();

			pPrev = reinterpret_cast<SonikListNode::SonikPriorityListNode<ListType>*>(LinearEnd);
			LinearEnd = pGetPtr;
			pPrev->Next = pGetPtr;
			LinearEnd->Prev = reinterpret_cast<SonikListNode::SonikListNodeBase*>(pPrev);

			++ItemCount;

			lock_.Unlock();

			pPrev->m_data = SetItem;
			pPrev->Priority = ItemPriority;
			pPrev->Sentinel_ = false;

			Inserted_ = true;

			return true;
		};

		SonikLib::SonikLinerOperator_PriorityList<ListType> GetOperator(void)
		{
			__HybridSort__();

			SonikLib::SonikLinerOperator_PriorityList<ListType> ope_;

			ope_.pNodes_ = LinearTop;

			return ope_;
		};

	};


};


#endif /* SONIKPRIORITYLIST_SONIKPRIORITYLIST_H_ */
