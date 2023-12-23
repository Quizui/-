#ifndef WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_
#define WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_

#include "WorkerFunctor_Base.hpp"

//引数を10個まで取れるテンプレートクラスを定義します。

//戻り値があるものについてはベースクラスは FunctionSystemTemplate_Base となっています
//継承元がテンプレートクラスであるため、一括して扱うことはできません。
//ただし、戻り値の型が同一の場合は一括で扱うことが可能です。構文例は下記の通り
//FunctionSystemTemplate_Base<int>* 等... <型名>はたとえポインタであっても必要です。

//戻り値が無いものについてはベースクラスは FunctionSystem_Base となっています。
//継承元は非テンプレートであるため、型は同一の物として一括で扱うことが可能です。
//この実装は戻り値を受け取れない代わりのケースバイケース実装となります。
//このベースクラスを使用してどうしても戻り値がほしい場合は関数ポインタに指定するメソッドの引数で、参照等を使用してください。
//構文例は下記の通りです。
//FunctionSystemTemplate_Base* このポインタには子を代入できます。
//ただし、基本的にインターフェースが提供するのはメソッドを実行する。という機能だけになります。

//Typeがvoid型の特殊化引数については、グローバル関数用の実装となります。
//ベースクラスは戻り値があるもの、無いもので上記二つと一緒です。


namespace SonikLib
{
	//戻り値有り、引数10
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	public:
		Members_10_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;
			Arg10Val = Val10_;

		};

		~Members_10_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val, this->Arg10Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
			if( (*object_) == NULL )
			{

				return 0;
			};
#else
			if( (*object_) == 0 )
			{

				return 0;
			};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			this->MethodStatus = true;

			return ret;

		};

	};
	//戻り値無し、引数10(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	public:
		Members_10_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;
			Arg10Val = Val10_;

		};

		~Members_10_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};

		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val, this->Arg10Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline void Run(void)
		{
#ifdef NULL
				if( (*object_) == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数10 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);
	public:
		Members_10_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;
			Arg10Val = Val10_;

		};

		~Members_10_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_10_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_10_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val, this->Arg10Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数10 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	public:
		Members_10_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;
			Arg10Val = Val10_;

		};

		~Members_10_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_10_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_10_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val, this->Arg10Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数9
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	public:
		Members_9_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;

			object_ = 0;

		};

		~Members_9_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数9(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	public:
		Members_9_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;

			object_ = 0;

		};

		~Members_9_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};

		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) )
		{
			p_mfunc_ = set_func;

		};

                void SetObject( Type* SetObject )
                {
                        object_ = SetObject;
                };

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( (*object_) == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数9 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	public:
		Members_9_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;

		};

		~Members_9_FuncRG(void)
		{
			//no process;
		}

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_9_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_9_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数9 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	public:
		Members_9_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;
			Arg9Val  = Val9_;

		};

		~Members_9_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_9_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_9_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val, this->Arg9Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline virtual void Run(void)
		{

			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);

		};

	};

	//戻り値有り、引数8
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	public:
		Members_8_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;

		};

		~Members_8_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};


		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数8 (自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	public:
		Members_8_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;

		};

		~Members_8_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};

		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline void Run(void)
		{
#ifdef NULL
				if( (*object_) == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数8 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	public:
		Members_8_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;

		};

		~Members_8_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_8_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_8_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数8 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	public:
		Members_8_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;
			Arg8Val  = Val8_;

		};

		~Members_8_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_8_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_8_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val, this->Arg8Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };


		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数7
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	public:
		Members_7_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;

			object_ = 0;

		};

		~Members_7_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数7 (自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	public:
		Members_7_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;

		};

		~Members_7_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( (*object_) == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数7 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	public:
		Members_7_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;

		};

		~Members_7_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_7_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_7_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数7 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	public:
		Members_7_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
			Arg7Val  = Val7_;

		};

		~Members_7_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_7_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_7_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val, this->Arg7Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数6
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	public:
		Members_6_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;

		};

		~Members_6_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数6(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	public:
		Members_6_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;
		};

		~Members_6_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( (*object_) == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数6 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	public:
		Members_6_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;

		};

		~Members_6_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_6_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_6_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数6 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	public:
		Members_6_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
			Arg6Val  = Val6_;

		};

		~Members_6_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_6_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_6_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val, this->Arg6Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数5
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	public:
		Members_5_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;
		};

		~Members_5_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数5(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	public:
		Members_5_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;

			object_ = 0;

		};

		~Members_5_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};

		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数5 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	public:
		Members_5_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;

		};

		~Members_5_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_5_FuncRG<Rtype,Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_5_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数5 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	public:
		Members_5_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;
			Arg5Val  = Val5_;

		};

		~Members_5_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_5_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_5_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val, this->Arg5Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };


		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数4
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	public:
		Members_4_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;

		};

		~Members_4_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };


		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数4(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	public:
		Members_4_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;

		};

		~Members_4_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数4 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	public:
		Members_4_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;

		};

		~Members_4_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_4_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_4_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数4 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	public:
		Members_4_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;
			Arg4Val  = Val4_;

		};

		~Members_4_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_4_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_4_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val, this->Arg4Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数3
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	public:
		Members_3_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;

		};

		~Members_3_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = ((*object_)->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数3(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	public:
		Members_3_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;

		};

		~Members_3_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数3 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	public:
		Members_3_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;

		};

		~Members_3_FuncRG(void)
		{
			//no process;
		}

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_3_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_3_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数3 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	public:
		Members_3_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;
			Arg3Val  = Val3_;

		};

		~Members_3_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_3_FuncG<Arg1_Val, Arg2_Val, Arg3_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_3_FuncG<Arg1_Val, Arg2_Val, Arg3_Val>(this->Arg1Val, this->Arg2Val, this->Arg3Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{

			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数2
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val>
	class Members_2_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val);

	public:
		Members_2_FuncR(Arg1_Val Val1_, Arg2_Val Val2_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;

		};

		~Members_2_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val, Arg2_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>(this->Arg1Val, this->Arg2Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( object_ == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数2(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val>
	class Members_2_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val);

	public:
		Members_2_Func(Arg1_Val Val1_, Arg2_Val Val2_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;

			object_ = 0;

		};

		~Members_2_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val, Arg2_Val) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_2_Func<Type, Arg1_Val, Arg2_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_2_Func<Type, Arg1_Val, Arg2_Val>(this->Arg1Val, this->Arg2Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			(object_->*p_mfunc_)(Arg1Val, Arg2Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数2 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val>
	class Members_2_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val);

	public:
		Members_2_FuncRG(void)
		:p_mfunc_(0)
		{
			//no process;
		};

		Members_2_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;

		};

		~Members_2_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val, Arg2_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_2_FuncRG<Rtype, Arg1_Val, Arg2_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_2_FuncRG<Rtype, Arg1_Val, Arg2_Val>(this->Arg1Val, this->Arg2Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数2 グローバル用
	template<class Arg1_Val, class Arg2_Val>
	class Members_2_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val);

	public:
		Members_2_FuncG(Arg1_Val Val1_, Arg2_Val Val2_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
			Arg2Val  = Val2_;

		};

		~Members_2_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(Arg1_Val, Arg2_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_2_FuncG<Arg1_Val, Arg2_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_2_FuncG<Arg1_Val, Arg2_Val>(this->Arg1Val, this->Arg2Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数1
	template<class Rtype, class Type, class Arg1_Val>
	class Members_1_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;

		Type* object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val);

	public:
		Members_1_FuncR(void)
		:object_(0)
		,p_mfunc_(0)
		{
			//no process;
		};

		Members_1_FuncR(Arg1_Val Val1_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;

		};

		~Members_1_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetArgument(Arg1_Val SetArg1_)
		{
			Arg1Val = SetArg1_;
		};

		void SetFunc( Rtype (Type::*set_func)(Arg1_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_1_FuncR<Rtype, Type, Arg1_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_1_FuncR<Rtype, Type, Arg1_Val>(this->Arg1Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( object_ == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = (object_->*p_mfunc_)(Arg1Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数1(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val>
	class Members_1_Func : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;

		Type* object_;
		void (Type::*p_mfunc_)(Arg1_Val);

	public:
		Members_1_Func(void)
		:object_(0)
		,p_mfunc_(0)
		{
			//no process;
		};

		Members_1_Func(Arg1_Val Val1_)
		:object_(0)
		,p_mfunc_(0)
		{
			Arg1Val  = Val1_;

		};

		~Members_1_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetArgument(Arg1_Val SetArg1_)
		{
			Arg1Val = SetArg1_;
		};

		void SetFunc( void (Type::*set_func)(Arg1_Val) )
		{
			p_mfunc_ = set_func;

		};

                void SetObject( Type* SetObject )
                {
                        object_ = SetObject;
                };

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_1_Func<Type, Arg1_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_1_Func<Type, Arg1_Val>(this->Arg1Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			(object_->*p_mfunc_)(Arg1Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数1 グローバル用
	template<class Rtype, class Arg1_Val>
	class Members_1_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;

		Rtype (*p_mfunc_)(Arg1_Val);

	public:
		Members_1_FuncRG(void)
		:p_mfunc_(0)
		{
			//処理無し。
		};

		Members_1_FuncRG(Arg1_Val Val1_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;
		};

		~Members_1_FuncRG(void)
		{
			//no process;
		};

		void SetArgument(Arg1_Val SetArg1_)
		{
			Arg1Val = SetArg1_;
		};

		void SetFunc( Rtype (*set_func)(Arg1_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_1_FuncRG<Rtype, Arg1_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_1_FuncRG<Rtype, Arg1_Val>(this->Arg1Val);

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数1 グローバル用
	template<class Arg1_Val>
	class Members_1_FuncG : public FunctionSystem_Base
	{
	private:
		Arg1_Val  Arg1Val;

		void (*p_mfunc_)(Arg1_Val);

	public:
		Members_1_FuncG(void)
		:p_mfunc_(0)
		{
			//no process;
		};

		Members_1_FuncG(Arg1_Val Val1_)
		:p_mfunc_(0)
		{
			Arg1Val  = Val1_;

		};

		~Members_1_FuncG(void)
		{
			//no process;
		};

		void SetArgument(Arg1_Val SetArg1_)
		{
			Arg1Val = SetArg1_;
		};

		void SetFunc( void (*set_func)(Arg1_Val) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_1_FuncG<Arg1_Val>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_1_FuncG<Arg1_Val>(this->Arg1Val);

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{

			(*p_mfunc_)(Arg1Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数0
	template<class Rtype, class Type>
	class Members_0_FuncR : public FunctionSystemTemplate_Base<Rtype>
	{
	private:

		Type* object_;
		Rtype(Type::*p_mfunc_)(void);

	public:
		Members_0_FuncR(void)
		:object_(0)
		,p_mfunc_(0)
		{
			//処理なし
		};

		~Members_0_FuncR(void)
		{
			if( object_ != 0)
			{
				if(FunctionSystemTemplate_Base<Rtype>::Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( Rtype (Type::*set_func)(void) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_0_FuncR<Rtype, Type>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_0_FuncR<Rtype, Type>();

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline Rtype Run(void)
		{
			Rtype ret;
#ifdef NULL
				if( (*object_) == NULL )
				{

					return 0;
				};
#else
				if( (*object_) == 0 )
				{

					return 0;
				};

#endif

			ret = (object_->*p_mfunc_)();
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数0(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type>
	class Members_0_Func : public FunctionSystem_Base
	{
	private:

		Type* object_;
		void (Type::*p_mfunc_)(void);

	public:
		Members_0_Func(void)
		:object_(0)
		,p_mfunc_(0)
		{
			//処理なし
		};

		~Members_0_Func(void)
		{
			if( object_ != 0)
			{
				if(Destroy_)
				{
					delete object_;

				};

			};
		};

		void SetFunc( void (Type::*set_func)(void) )
		{
			p_mfunc_ = set_func;

		};

		void SetObject( Type* SetObject )
		{
			object_ = SetObject;
		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_0_Func<Type>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_0_Func<Type>();

                    pTmp->SetFunc(this->p_mfunc_);
                    pTmp->SetObject(this->object_);

                };

		inline void Run(void)
		{
#ifdef NULL
				if( object_ == NULL )
				{

					return;
				};
#else
				if( (*object_) == 0 )
				{

					return;
				};

#endif

			((object_)->*p_mfunc_)();
			MethodStatus = true;
		};

	};
	//戻り値有り、引数0 グローバル用
	template<class Rtype>
	class Members_0_FuncRG : public FunctionSystemTemplate_Base<Rtype>
	{
	private:

		Rtype (*p_mfunc_)(void);

	public:
		Members_0_FuncRG(void)
		:p_mfunc_(0)
		{
			//処理無し
		};

		~Members_0_FuncRG(void)
		{
			//no process;
		};

		void SetFunc( Rtype (*set_func)(void) )
		{
			p_mfunc_ = set_func;

		};

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_0_FuncRG<Rtype>* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_0_FuncRG<Rtype>();

                    pTmp->SetFunc(this->p_mfunc_);
                };

		inline Rtype Run(void)
		{

			return (*p_mfunc_)();
		};

	};
	//戻り値無し、引数0 グローバル用
	class Members_0_FuncG : public FunctionSystem_Base
	{
	private:

		void (*p_mfunc_)(void);

	public:
		Members_0_FuncG(void)
		:p_mfunc_(0)
		{
			//処理無し
		};

		~Members_0_FuncG(void)
		{
			//no process;
		};

		void SetFunc( void (*set_func)(void) )
		{
			p_mfunc_ = set_func;

		}

                unsigned int GetCreateSize(void)
                {
                    return sizeof((*this));
                };

                void CreateCopy(void* AllocateArea)
                {
                    Members_0_FuncG* pTmp = nullptr;

                    pTmp = new(AllocateArea) Members_0_FuncG();

                    pTmp->SetFunc(this->p_mfunc_);

                };

		inline void Run(void)
		{

			(*p_mfunc_)();
			MethodStatus = true;
		};

	};



};


#endif
