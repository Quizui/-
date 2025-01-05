#pragma once

#ifndef __SONIKLIB_ALLOCATE_TRAITS_HEADER__
#define __SONIKLIB_ALLOCATE_TRAITS_HEADER__

#include <new>
#include <type_traits>

namespace SonikLib
{
	namespace SLibAllocEnums
	{
		enum class EnableRet
		{
			ENABLED_OK = 0,	//処理成功

			HEEPALLOCERR_CREATEFILED,	//アロケータクリエイトが失敗(アロケータオブジェクトの空作成(new)が失敗)
			HEEPALLOCERR_MAINBLOCK,		//メインブロックのヒープ領域獲得時にエラーが発生しました。
			HEEPALLOCERR_FREEBLOCK,		//フリーリスト管理用のヒープ領域獲得時にエラーが発生しました。
			HEEPALLOCERR_MTBLOCK,		//マルチスレッドブロックオブジェクトのヒープ領域獲得時にエラーが発生しました。
//			HEEPALLOCERR_REFCNT,		//参照カウンタオブジェクトのヒープ領域獲得時にエラーが発生しました。(2024-12-27 継承先をスマートポインタ形式にしたため不要とした。でも復活するかもしれないからコメントアウトで対処
			HEEPALLOCERR_OBJECTSMTPTR,	//最終スマートポインタ生成処理に失敗しました。(一応atomic<unsigned int>型の newを１回行います..)

			ENABLE_DEFAULT = 255,		//Enabled初期状態(生成関数が通されていない初期状態。)
		};
	};

	//アロケータインターフェース
	class SLibAllocateInterface
	{
	protected:
		SLibAllocEnums::EnableRet m_enabled_state;		//有効状態

	private:
		//自分のとこのポインタかチェックします。
		virtual int8_t __INNER_IS_ADDR__(void* _checkpointer_) 
		{
			return 0; //デフォルトの証
		};
		//配列サイズを確認します。
		virtual uint32_t __INNER_ARRAYSIZECHECK__(void* _checkpointer_)
		{
			return 0; //デフォルトの証
		};

	public:
		inline SLibAllocateInterface(void) noexcept
		:m_enabled_state(SLibAllocEnums::EnableRet::ENABLE_DEFAULT)
		{
			//no porcess;
		};

		//コピーコンストラクタ
		inline SLibAllocateInterface(const SLibAllocateInterface& _copy_) noexcept
		:m_enabled_state(SLibAllocEnums::EnableRet::ENABLE_DEFAULT)
		{
			//no process;
		};

		//ムーヴコンストラクタ
		inline SLibAllocateInterface(SLibAllocateInterface&& _move_) noexcept
		:m_enabled_state(SLibAllocEnums::EnableRet::ENABLE_DEFAULT)
		{
			//no process;
		};

		//デストラクタ
		inline virtual ~SLibAllocateInterface(void)
		{
			//no process
		};

		//operator = copy
		inline SLibAllocateInterface& operator =(const SLibAllocateInterface& _copy_) noexcept
		{
			return (*this);
		};

		//operator = move
		inline SLibAllocateInterface& operator =(SLibAllocateInterface& _move_) noexcept
		{
			return (*this);
		};

		//現在の有効状態を取得します。
		inline SLibAllocEnums::EnableRet GetNowEnabledState(void) noexcept
		{
			return m_enabled_state;
		};

		//対象のデストラクタをコールします。
		//管理管轄外のポインタが指定された場合で、カスタムアロケータの場合は継承先の動作によって変わります。
		template <class Type>
		void CallDestructor(Type* _Target_)
		{
			static_assert(!std::is_pointer_v<Type>, "Please Used NoPointerType | ポインタ型は許容していません。内部でType* とするため指定自体はオブジェクト型としてください。");

			_Target_->~Type();
		};
		
		template <class Type>
		void CallDestructor_Array(Type* _Target_Top_)
		{
			static_assert(!std::is_pointer_v<Type>, "Please Used NoPointerType | ポインタ型は許容していません。内部でType* とするため指定自体はオブジェクト型としてください。");

			if (__INNER_IS_ADDR__(_Target_Top_) != 1)
			{
				//-1は管轄外、0 はデフォルト new or new[] のため、memdel をコールするかユーザー自身でdelete[] してもらう。
				//そっちのほうがデストラクタ自動的にコールされるからいい。結局デフォルトのmemdel は::operator delete 呼ぶし、何なら２回デストラクタがコールされてしまうことになる。
				return;
			};

			//配列サイズのチェック
			uint32_t l_ar_size = __INNER_ARRAYSIZECHECK__(_Target_Top_);
			//Type* l_control = _Target_Top_;
			
			//回数分デストラクタをコール
			for (uint32_t i = 0; i < l_ar_size; ++i)
			{
				_Target_Top_[i]->~Type();
			}

			return;

		};

		virtual void* memal(size_t _size_) noexcept
		{
			return ::operator new(_size_, std::nothrow);
		};
		virtual void* memal_Exception(size_t _size_)//例外throw
		{
			return ::operator new(_size_);
		};

		virtual void* memalArray(size_t _size_, size_t _elem_) noexcept
		{
			return ::operator new[](_size_* _elem_, std::nothrow);
		};
		virtual void* memalArray_Exception(size_t _size_, size_t _elem_)//例外throw
		{
			return ::operator new[](_size_* _elem_);
		};

		virtual void memdel(void* _del_)
		{
			::operator delete(_del_);
		};

		virtual void memdelArray(void* _del_)
		{
			::operator delete[](_del_);
		};
	};

};

#endif //#define __SONIKLIB_ALLOCATE_TRAITS_HEADER__