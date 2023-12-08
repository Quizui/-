/*
 * AudioSmartPointer.h
 *
 *  Created on: 2017/10/10
 *      Author: SONIC
 */

#ifndef SMARTPOINTER_SO_SMARTPOINTER_HPP_
#define SMARTPOINTER_SO_SMARTPOINTER_HPP_

namespace SonikLib
{
	template <class PointerType>
	class NormalSmtPtr
	{
	private:
		PointerType* m_Pointer;

		unsigned long* m_Count;

	private:
		void AddRef(void)
		{
			++(*m_Count);
		};

		void Release(void)
		{
			--(*m_Count);

			if( (*m_Count) == 0 )
			{
				delete m_Pointer;
				delete m_Count;

			};

		};

	public:

		//constructor
		explicit NormalSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		NormalSmtPtr(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~NormalSmtPtr(void)
		{
			Release();

		};

		NormalSmtPtr& operator =(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			//自身への代入は意味が無いので行わない。
			if( SmtPtr.m_Pointer == m_Pointer )
			{
				return (*this);
			};

			Release();

			m_Count = SmtPtr.m_Count;
			m_Pointer = SmtPtr.m_Pointer;

			AddRef();

			return (*this);
		};

		bool operator ==(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const unsigned long PtrVal)
		{
			if( m_Pointer == PtrVal )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = SetPointer;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};


};




#endif /* SMARTPOINTER_SO_SMARTPOINTER_HPP_ */
