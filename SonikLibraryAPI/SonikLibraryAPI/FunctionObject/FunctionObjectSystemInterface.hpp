#ifndef WORKER_FUNCTOR_SONIKLIBRARY_
#define WORKER_FUNCTOR_SONIKLIBRARY_

#include "../SmartPointer/SonikSmartPointer.hpp"

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
	//Weak 及び Strong のnext はSonikLibのWorkerThread内で意味を持ちます。
	//それぞれ、Weak は次のタスク実行の前にスレッドをリスタートします。(関数と関数の間にスレッドの終了等の余地を設けます)
	//Strong はスレッドをリスタートせず、その場でStrong_nextに設定されているrunをコールします。(関数と関数の間にスレッド終了等の余地を設けません)
	class FunctionObjectSystemInterface
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

		//弱い依存の単方向next
		SonikLib::SharedSmtPtr<FunctionObjectSystemInterface> weak_next;
		//強い依存の単方向next
		SonikLib::SharedSmtPtr<FunctionObjectSystemInterface> strong_next;

	public:
		//コンストラクタ
		FunctionObjectSystemInterface(void)
		:MethodStatus(false)
		,MethodPriority(0)
		,Destroy_(false)
		{
			//member value initialize only
		};

		virtual ~FunctionObjectSystemInterface(void)
		{
		};

		//弱い依存でnextのタスクを設定します。
		bool SetNext_Weak(FunctionObjectSystemInterface* _SetSmtPtr_)
		{
			return weak_next.ResetPointer(_SetSmtPtr_);
		};

		bool SetNext_Weak(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>& _SetSmtPtr_)
		{
			weak_next = _SetSmtPtr_;
			return true;
		};

		bool SetNext_Weak(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>&& _SetSmtPtr_)
		{
			weak_next = _SetSmtPtr_;
			return true;
		};

		//強い依存でnextのタスクを設定します。
		bool SetNext_Strong(FunctionObjectSystemInterface* _SetSmtPtr_)
		{
			return strong_next.ResetPointer(_SetSmtPtr_);
		};

		bool SetNext_Strong(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>& _SetSmtPtr_)
		{
			strong_next = _SetSmtPtr_;
			return true;
		};

		bool SetNext_Strong(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>&& _SetSmtPtr_)
		{
			strong_next = _SetSmtPtr_;
			return true;
		};

		//弱い依存のnextタスクを取得します。
		//nextタスクがない場合、falseを返却します。
		bool GetNext_weak(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>& _getSmtPtr_)
		{
			if(weak_next.IsNullptr())
			{
				return false;
			};

			_getSmtPtr_ = weak_next;
			return true;
		};

		//強い依存のnextタスクを取得します。
		//nextタスクがない場合、falseを返却します。
		bool GetNext_strong(SonikLib::SharedSmtPtr<FunctionObjectSystemInterface>& _getSmtPtr_)
		{
			if(strong_next.IsNullptr())
			{
				return false;
			};

			_getSmtPtr_ = strong_next;
			return true;
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


	//どうしても戻り値がほしいとき用のテンプレートベースクラスを作成してみた。
	template<class Rtype>
	class FunctionObjectSystemTemplateInterface
	{
	protected:
		//メソッドステータス
		bool MethodStatus;

		//メソッドプライオリティ
		unsigned long MethodPriority;

		//保持したオブジェクトを破棄するかどうかのフラグ
		bool Destroy_;

		//弱い依存の単方向next
		SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>> weak_next;
		//強い依存の単方向next
		SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>> strong_next;

	public:
		//コンストラクタ
		FunctionObjectSystemTemplateInterface(void)
		:MethodStatus(false)
		,MethodPriority(0)
		,Destroy_(false)
		{
			//member value initialize only
		};

		//デストラクタ
		virtual ~FunctionObjectSystemTemplateInterface(void)
		{
			//処理なし。
		};

		//弱い依存でnextのタスクを設定します。
		bool SetNext_Weak(FunctionObjectSystemTemplateInterface<Rtype>* _SetSmtPtr_)
		{
			return weak_next.ResetPointer(_SetSmtPtr_);
		};

		bool SetNext_Weak(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>& _SetSmtPtr_)
		{
			weak_next = _SetSmtPtr_;
			return true;
		};

		bool SetNext_Weak(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>&& _SetSmtPtr_)
		{
			weak_next = _SetSmtPtr_;
			return true;
		};

		//強い依存でnextのタスクを設定します。
		bool SetNext_Strong(FunctionObjectSystemTemplateInterface<Rtype>* _SetSmtPtr_)
		{
			return strong_next.ResetPointer(_SetSmtPtr_);
		};

		bool SetNext_Strong(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>& _SetSmtPtr_)
		{
			strong_next = _SetSmtPtr_;
			return true;
		};

		bool SetNext_Strong(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>&& _SetSmtPtr_)
		{
			strong_next = _SetSmtPtr_;
			return true;
		};

		//弱い依存のnextタスクを取得します。
		//nextタスクがない場合、falseを返却します。
		bool GetNext_weak(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>& _getSmtPtr_)
		{
			if(weak_next.IsNullptr())
			{
				return false;
			};

			_getSmtPtr_ = weak_next;
			return true;
		};

		//強い依存のnextタスクを取得します。
		//nextタスクがない場合、falseを返却します。
		bool GetNext_strong(SonikLib::SharedSmtPtr<FunctionObjectSystemTemplateInterface<Rtype>>& _getSmtPtr_)
		{
			if(strong_next.IsNullptr())
			{
				return false;
			};

			_getSmtPtr_ = strong_next;
			return true;
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
