#ifndef WORKER_FUNCTOR_SONIKLIBRARY_
#define WORKER_FUNCTOR_SONIKLIBRARY_

//前方宣言
namespace SonikFunctionObjectDefines
{
class FunctionObjectSystemInterface;
template<class Rtype>
class FunctionObjectSystemTemplateInterface;
};

//using
namespace SonikLib
{
	using SonikFOSInterface = SonikFunctionObjectDefines::FunctionObjectSystemInterface;
	template <class Rtype>
	using SonikFOSTemplateInterface = SonikFunctionObjectDefines::FunctionObjectSystemTemplateInterface<Rtype>;

};



namespace SonikFunctionObjectDefines
{
	//関数ポインタを同じ型で扱うためのベースクラスです
	//戻り値がある関数は指定できまてん。
	class FunctionObjectSystemInterface
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

		FunctionObjectSystemInterface* next_;
		FunctionObjectSystemInterface* prev_;

	public:
		//コンストラクタ
		FunctionObjectSystemInterface(void)
		:MethodStatus(false)
		,MethodPriority(0)
		,Destroy_(false)
		,next_(nullptr)
		,prev_(nullptr)
		{
			//member value initialize only
		};

		virtual ~FunctionObjectSystemInterface(void)
		{
		};

		//自分の次へのポインタの設定と取得
		FunctionObjectSystemInterface*& Get_NextBase(void)
		{

			return next_;
		};
		void Set_NextBase(FunctionObjectSystemInterface* SetPointer_)
		{
			next_ = SetPointer_;

		};

		//自分の前へのポインタの設定と取得
		FunctionObjectSystemInterface*& Get_PrevBase(void)
		{

			return prev_;
		};
		void Set_PrevBase(FunctionObjectSystemInterface* SetPointer_)
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

        virtual unsigned int GetCreateSize(void) =0;
        virtual void CreateCopy(void* AllocateArea) =0;

		virtual void Run(void) =0;
	};


	//どうしても戻り値がほしいとき用のテンプレートベースクラスを作成してみた。
	template<class Rtype>
	class FunctionObjectSystemTemplateInterface
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		FunctionObjectSystemTemplateInterface<Rtype>* next_;
		FunctionObjectSystemTemplateInterface<Rtype>* prev_;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

	public:
		//コンストラクタ
		FunctionObjectSystemTemplateInterface(void)
		:MethodStatus(false)
		,MethodPriority(0)
		,next_(nullptr)
		,prev_(nullptr)
		,Destroy_(false)
		{
			//member value initialize only
		};

		//デストラクタ
		virtual ~FunctionObjectSystemTemplateInterface(void)
		{
			//処理なし。
		};

		//自分の次へのポインタの設定と取得
		FunctionObjectSystemTemplateInterface<Rtype>*& Get_NextBase(void)
		{

			return next_;
		};
		void Set_NextBase(FunctionObjectSystemTemplateInterface<Rtype>* SetPointer_)
		{
			next_ = SetPointer_;

		};

		//自分の前へのポインタの設定と取得
		FunctionObjectSystemTemplateInterface<Rtype>*& Get_PrevBase(void)
		{

			return prev_;
		};
		void Set_PrevBase(FunctionObjectSystemTemplateInterface<Rtype>* SetPointer_)
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

        virtual unsigned int GetCreateSize(void) =0;
        virtual void CreateCopy(void* AllocateArea) =0;

		virtual Rtype Run(void) =0;
	};

};//end namespace


#endif //WORKER_FUNCTOR_SONICREATIVE_
