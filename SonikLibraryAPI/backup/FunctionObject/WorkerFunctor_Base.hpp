#ifndef WORKER_FUNCTOR_RCOKYLIBRARY_
#define WORKER_FUNCTOR_RCOKYLIBRARY_

#ifdef _DEBUG
//デバッグ時のみファイル出力する。
#include <fstream>
#endif

namespace SonikLib
{
	//関数ポインタを同じ型で扱うためのベースクラスです
	//戻り値取得機能は保有していません。
	//戻り値を取得しようとすると、templateが必要になります。
	//すると継承元の汎用性が損なわれるため、戻り値は機能として実装していません。
	//どうしてもほしい場合は参照を使用し、関数ポインタとして実行するメソッドで代入処理を組み込んでください。
	class FunctionSystem_Base
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

		FunctionSystem_Base* next_;
		FunctionSystem_Base* prev_;


#ifdef _DEBUG
		//デバッグ時のみファイルに出力する。
		std::ofstream ofs;
		char str[256];

#endif

	public:
		//コンストラクタ
		FunctionSystem_Base(void)
		:MethodStatus(false)
		{
		next_ = 0;
		prev_ = 0;
		MethodPriority = 0;

		Destroy_ = false;

#ifdef _DEBUG
		ofs.open("PriorityCheck.txt", std::ios::app);

#endif
		};

		virtual ~FunctionSystem_Base(void)
		{
		};

		//自分の次へのポインタの設定と取得
		FunctionSystem_Base*& Get_NextBase(void)
		{

			return next_;
		};
		void Set_NextBase(FunctionSystem_Base* SetPointer_)
		{
			next_ = SetPointer_;

		};

		//自分の前へのポインタの設定と取得
		FunctionSystem_Base*& Get_PrevBase(void)
		{

			return prev_;
		};
		void Set_PrevBase(FunctionSystem_Base* SetPointer_)
		{

			prev_ = SetPointer_;
		};

		//メソッドステータスの取得
		const bool& Get_MethodStatus(void)
		{

			return MethodStatus;
		};

		//メソッドステータスの状態をオフにします。
		void Set_MethodStatusOff(void)
		{
			MethodStatus = false;
		};


		//メソッドプライオリティの取得
		const unsigned long& Get_MethodPriority(void)
		{
			return MethodPriority;

		};

		//メソッドプライオリティの変更
		void Set_MethodPriority(unsigned long SetPriority)
		{

			MethodPriority = SetPriority;
		};

		//保持オブジェクトの破棄フラグ
		void Set_DestroyObjectFlag(bool SetValue)
		{
			Destroy_ = SetValue;

		};

		const bool& Get_DestroyObjectFlag(void)
		{
			return Destroy_;
		}

		virtual void Run(void) =0;
	};


	//どうしても戻り値がほしいとき用のテンプレートベースクラスです。
	//どうしてもほしいとき用なので組み込みには不向きです。
	//ただし、同じ型を戻り値として受け取る場合は大いに利用できるかもしれません。
	template<class Rtype>
	class FunctionSystemTemplate_Base
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		FunctionSystemTemplate_Base<Rtype>* next_;
		FunctionSystemTemplate_Base<Rtype>* prev_;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

#ifdef _DEBUG
		//デバッグ時のみファイルに出力する。
		std::ofstream ofs;
		char str[256];

#endif

	public:
		//コンストラクタ
		FunctionSystemTemplate_Base(void)
		:MethodStatus(false)
		{
		next_ = 0;
		prev_ = 0;
		MethodPriority = 0;

		Destroy_ = false;

#ifdef _DEBUG
		ofs.open("PriorityCheck.txt", std::ios::app);

#endif
		};

		//デストラクタ
		virtual ~FunctionSystemTemplate_Base(void)
		{
			//処理なし。
		};

		//自分の次へのポインタの設定と取得
		FunctionSystemTemplate_Base<Rtype>*& Get_NextBase(void)
		{

			return next_;
		};
		void Set_NextBase(FunctionSystemTemplate_Base<Rtype>* SetPointer_)
		{
			next_ = SetPointer_;

		};

		//自分の前へのポインタの設定と取得
		FunctionSystemTemplate_Base<Rtype>*& Get_PrevBase(void)
		{

			return prev_;
		};
		void Set_PrevBase(FunctionSystemTemplate_Base<Rtype>* SetPointer_)
		{

			prev_ = SetPointer_;
		};

		//メソッドステータスの取得
		const bool& Get_MethodStatus(void)
		{

			return MethodStatus;
		};

		//メソッドステータスの変更
		void Set_MethodStatus(bool SetFlag)
		{

			MethodStatus = SetFlag;
		};


		//メソッドプライオリティの取得
		const unsigned long& Get_MethodPriority(void)
		{
			return MethodPriority;

		};

		//メソッドプライオリティの変更
		void Set_MethodPriority(unsigned long SetPriority)
		{

			MethodPriority = SetPriority;
		};

		//保持オブジェクトの破棄フラグ
		void Set_DestriyObjectFlag(const bool& SetValue)
		{
			Destroy_ = SetValue;

		};

		virtual Rtype Run(void) =0;
	};



};//end namespace


#endif //WORKER_FUNCTOR_SONICREATIVE_
