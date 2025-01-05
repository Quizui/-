
#ifndef WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_
#define WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_

#include "FunctionObjectSystemInterface.hpp"
#include "../SmartPointer/SonikSmartPointer.hpp"

//引数を10個まで取れるテンプレートクラスを定義します。
//それぞれクラスのメンバ関数を登録する場合において、ポインタのポインタ型は指定できません。
//指定しようとした場合は型不一致のコンパイルエラーが出ます。
//インスタンス作成時のテンプレートのTypeに対して、オブジェクトのポインタ型は指定できません。
//同じく指定しようとした場合は型不一致のコンパイルエラーが出ます。

//戻り値があるものについてはベースクラスは FunctionObjectSystemInterface となっています
//継承元がテンプレートクラスであるため、一括して扱うことはできません。
//ただし、戻り値の型が同一の場合は一括で扱うことが可能です。構文例は下記の通り
//FunctionSystemTemplate_Base<int>* 等... <型名>はたとえポインタであっても必要です。

//戻り値が無いものについてはベースクラスは FunctionObjectSystemTemplateInterface となっています。
//継承元は非テンプレートであるため、型は同一の物として一括で扱うことが可能です。

//基本的にインターフェースが提供するのはメソッドを実行する。という機能だけになります。

//Typeがvoid型の特殊化引数については、グローバル関数用の実装となります。
//ベースクラスは戻り値があるもの、無いもので上記二つと一緒です。
//いずれのクラスもローカル変数として生成し、スレッドに渡されてほしくないため、
//NEW関数を経由しての作成を強制しています。

namespace __UF_SLIB_FUNCTION_PARAMOBJECT_FU__ //名前横のUF FU は特に意味はない。ユニーク名前でアクセスしづらいようにしたかっただけ。
{
	//パラメータのセッターを下記の形でコールしたい場合に使う構造
	//object<index>(setvalue);
	template <std::size_t Ind, class SetType>
	class UF_PARAMSETTER;

	template <class Types>
	class UF_PARAMSETTER<0, Types>
	{
	public:
		static void UF_FUNC_CHANGED_SETTER(Types& _changed_, Types&& _value_)
		{
			_changed_ = std::forward<Types>(_value_);
		}
	};

};


namespace SonikLib
{
	//テンプレート再実装を試みる
	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	//▶　クラスメンバ関数オブジェクト　 ◀
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	//引数 10個==================================================================
	template <class Cls_T, class arg_T1 = void, class arg_T2 = void, class arg_T3 = void, class arg_T4 = void, class arg_T5 = void, class arg_T6 = void, class arg_T7 = void, class arg_T8 = void, class arg_T9 = void, class arg_T10 = void>
	class FunctionObject_ClsMember : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9, arg_T10);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;
		arg_T9 m_arg9;
		arg_T10 m_arg10;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_, arg_T9 _argval9_, arg_T10 _argval10_)
		:m_arg1(_argval1_)
		,m_arg2(_argval2_)
		,m_arg3(_argval3_)
		,m_arg4(_argval4_)
		,m_arg5(_argval5_)
		,m_arg6(_argval6_)
		,m_arg7(_argval7_)
		,m_arg8(_argval8_)
		,m_arg9(_argval9_)
		,m_arg10(_argval10_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };
		template<>
		inline auto& __In__GetArgument<8>(void) { return m_arg9; };
		template<>
		inline auto& __In__GetArgument<9>(void) { return m_arg10; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			//FuncRetType == voidの場合は戻り値void関数として展開
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, arg_T10 Val10_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9, arg_T10>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object	= _SetObj_;
			lp->m_p_mfunc	= _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, arg_T10 Val10_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9, arg_T10>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  9個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7, class arg_T8, class arg_T9>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;
		arg_T9 m_arg9;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_, arg_T9 _argval9_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
			, m_arg8(_argval8_)
			, m_arg9(_argval9_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };
		template<>
		inline auto& __In__GetArgument<8>(void) { return m_arg9; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  8個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7, class arg_T8>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
			, m_arg8(_argval8_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  7個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  6個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  5個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4, arg_T5>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  4個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3, class arg_T4>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3, arg_T4);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3, arg_T4>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  3個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2, class arg_T3>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2, arg_T3);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2, m_arg3);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2, arg_T3>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  2個==================================================================
	template <class Cls_T, class arg_T1, class arg_T2>
	class FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1, arg_T2);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_, arg_T2 _argval2_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };


	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1, m_arg2);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1, arg_T2>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  1個==================================================================
	template <class Cls_T, class arg_T1>
	class FunctionObject_ClsMember<Cls_T, arg_T1> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)(arg_T1);
	private:
		arg_T1 m_arg1;

		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(arg_T1 _argval1_)
			:m_arg1(_argval1_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)(m_arg1);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_)
			: lp = new(std::nothrow) CreateClsType(Val1_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, arg_T1 Val1_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T, arg_T1>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_)
			: lp = new(std::nothrow) CreateClsType(Val1_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};

	//引数  0個==================================================================
	template <class Cls_T>
	class FunctionObject_ClsMember<Cls_T> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (Cls_T::*)();

	private:
		SonikLib::SharedSmtPtr<Cls_T> m_object;
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_ClsMember(void)
		{
			//no process
		};

	public:
		//デストラクタ
		inline ~FunctionObject_ClsMember(void)
		{
			if (this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Cls_T* _dymmy = nullptr;
				m_object.DestroyOwner();
			};
		};

		//関数実行Run
		inline void Run(void)
		{
			if (m_object.IsNullptr())
			{
				return;
			};

			(m_object->*m_p_mfunc)();
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(スマートポインタ指定
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(SonikLib::SharedSmtPtr<Cls_T> _SetObj_, FUNCNAMEDEF _set_func_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType()
				: lp = new(std::nothrow) CreateClsType();

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = _SetObj_;
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

		//クリエイタ(Rawポインタ指定)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(Cls_T* _SetObj_, FUNCNAMEDEF _set_func_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_ClsMember<Cls_T>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			if (_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return RetSmtPtrType();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType()
				: lp = new(std::nothrow) CreateClsType();

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_object = SonikLib::SharedSmtPtr<Cls_T*>(_SetObj_);
			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};
	};


	//▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼
	//▶　  グローバル関数オブジェクト　 ◀
	//▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
	//引数 10個==================================================================
	template <class arg_T1 = void, class arg_T2 = void, class arg_T3 = void, class arg_T4 = void, class arg_T5 = void, class arg_T6 = void, class arg_T7 = void, class arg_T8 = void, class arg_T9 = void, class arg_T10 = void>
	class FunctionObject_Global : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9, arg_T10);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;
		arg_T9 m_arg9;
		arg_T10 m_arg10;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_, arg_T9 _argval9_, arg_T10 _argval10_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
			, m_arg8(_argval8_)
			, m_arg9(_argval9_)
			, m_arg10(_argval10_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };
		template<>
		inline auto& __In__GetArgument<8>(void) { return m_arg9; };
		template<>
		inline auto& __In__GetArgument<9>(void) { return m_arg10; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9, m_arg10);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, arg_T10 Val10_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9, arg_T10>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  9個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7, class arg_T8, class arg_T9>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;
		arg_T9 m_arg9;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_, arg_T9 _argval9_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
			, m_arg8(_argval8_)
			, m_arg9(_argval9_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };
		template<>
		inline auto& __In__GetArgument<8>(void) { return m_arg9; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8, m_arg9);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, arg_T9 Val9_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8, arg_T9>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  8個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7, class arg_T8>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;
		arg_T8 m_arg8;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_, arg_T8 _argval8_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
			, m_arg8(_argval8_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };
		template<>
		inline auto& __In__GetArgument<7>(void) { return m_arg8; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7, m_arg8);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, arg_T8 Val8_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7, arg_T8>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  7個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6, class arg_T7>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;
		arg_T7 m_arg7;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_, arg_T7 _argval7_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
			, m_arg7(_argval7_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };
		template<>
		inline auto& __In__GetArgument<6>(void) { return m_arg7; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, arg_T7 Val7_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6, arg_T7>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  6個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5, class arg_T6>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;
		arg_T6 m_arg6;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_, arg_T6 _argval6_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
			, m_arg6(_argval6_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };
		template<>
		inline auto& __In__GetArgument<5>(void) { return m_arg6; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, arg_T6 Val6_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5, arg_T6>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  5個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4, class arg_T5>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4, arg_T5);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;
		arg_T5 m_arg5;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_, arg_T5 _argval5_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
			, m_arg5(_argval5_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };
		template<>
		inline auto& __In__GetArgument<4>(void) { return m_arg5; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, arg_T5 Val5_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4, arg_T5>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_, Val5_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  4個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3, class arg_T4>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3, arg_T4);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;
		arg_T4 m_arg4;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_, arg_T4 _argval4_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
			, m_arg4(_argval4_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };
		template<>
		inline auto& __In__GetArgument<3>(void) { return m_arg4; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3, m_arg4);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, arg_T4 Val4_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3, arg_T4>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_, Val4_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_, Val4_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  3個==================================================================
	template <class arg_T1, class arg_T2, class arg_T3>
	class FunctionObject_Global<arg_T1, arg_T2, arg_T3> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2, arg_T3);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;
		arg_T3 m_arg3;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_, arg_T3 _argval3_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
			, m_arg3(_argval3_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };
		template<>
		inline auto& __In__GetArgument<2>(void) { return m_arg3; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2, m_arg3);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, arg_T3 Val3_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2, arg_T3>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_, Val3_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_, Val3_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  2個==================================================================
	template <class arg_T1, class arg_T2>
	class FunctionObject_Global<arg_T1, arg_T2> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1, arg_T2);
	private:
		arg_T1 m_arg1;
		arg_T2 m_arg2;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_, arg_T2 _argval2_)
			:m_arg1(_argval1_)
			, m_arg2(_argval2_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };
		template<>
		inline auto& __In__GetArgument<1>(void) { return m_arg2; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1, m_arg2);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, arg_T2 Val2_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1, arg_T2>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_, Val2_)
				: lp = new(std::nothrow) CreateClsType(Val1_, Val2_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  1個==================================================================
	template <class arg_T1>
	class FunctionObject_Global<arg_T1> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(arg_T1);
	private:
		arg_T1 m_arg1;

		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(arg_T1 _argval1_)
			:m_arg1(_argval1_)
		{
			//no process
		};

	private:
		//セッタで使う関数群（実質indexテンプレートゲッタ)
		template <size_t Ind>
		inline auto& __In__GetArgument(void) { return; };

		template<>
		inline auto& __In__GetArgument<0>(void) { return m_arg1; };

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//セッター
		template <std::size_t Ind, class SetType>
		inline void SetParam(SetType&& _param_)
		{
			if constexpr (Ind >= 10)
			{
				return;
			};

			__UF_SLIB_FUNCTION_PARAMOBJECT_FU__::UF_PARAMSETTER<Ind, SetType>::UF_FUNC_CHANGED_SETTER(__In__GetArgument<Ind>(), std::forward<SetType>(_param_));
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)(m_arg1);
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, arg_T1 Val1_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<arg_T1>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType(Val1_)
				: lp = new(std::nothrow) CreateClsType(Val1_);

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

	//引数  0個==================================================================
	template <>
	class FunctionObject_Global<void> : public SonikFunctionObjectDefines::FunctionObjectSystemInterface
	{
		//コンストラクタ継承 using
		using SonikFunctionObjectDefines::FunctionObjectSystemInterface::FunctionObjectSystemInterface;

		//名前長いので短く！
		using FUNCNAMEDEF = void (*)(void);
	private:
		FUNCNAMEDEF m_p_mfunc;

	private:
		//コンストラクタ
		inline FunctionObject_Global(void)
		{
			//no process
		};

	public:
		//デストラクタ
		inline ~FunctionObject_Global(void)
		{
			//グローバル関数はメンバ関数と違ってオブジェクトは必要ないのでそのまま何もしない。
		};

		//関数実行Run
		inline void Run(void)
		{
			(*m_p_mfunc)();
			this->MethodStatus = true;

			return;
		};

		//クリエイタ(クラスオブジェクトが無いため、スマートポインタ版とRaw版に分ける必要がない。)
		static inline SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> New(FUNCNAMEDEF _set_func_, void* _allocate_ = nullptr)
		{
			using CreateClsType = SonikLib::FunctionObject_Global<void>;
			using RetSmtPtrType = SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface>;
			CreateClsType* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
				? lp = new(_allocate_) CreateClsType()
				: lp = new(std::nothrow) CreateClsType();

			if (lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return RetSmtPtrType();
			};

			lp->m_p_mfunc = _set_func_;

			RetSmtPtrType ret_sp;
			RetSmtPtrType::SmartPointerCreate(reinterpret_cast<SonikLib::SonikFOSInterface*>(lp), ret_sp);

			return ret_sp;
		};

	};

};

#endif