/*
 * AudioSmartPointer.h
 *
 *  Created on: 2017/10/10
 *      Author: SONIC
 */

#ifndef SMARTPOINTER_AUDIOFORMATSMARTPOINTER_H_
#define SMARTPOINTER_AUDIOFORMATSMARTPOINTER_H_


namespace SonikAudioFormatPointer
{
	template <class PointerType>
	class SonikAudioFormatSmtPtr
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
		explicit SonikAudioFormatSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		SonikAudioFormatSmtPtr(const SonikAudioFormatSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~SonikAudioFormatSmtPtr(void)
		{
			Release();

		};

		SonikAudioFormatSmtPtr& operator =(const SonikAudioFormatSmtPtr<PointerType>& SmtPtr)
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

		bool operator ==(const SonikAudioFormatSmtPtr<PointerType>& SmtPtr)
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

		template <class Cast_Type>
		const Cast_Type* CastAccess(void)
		{
			return reinterpret_cast<Cast_Type*>(m_Pointer);
		};

		bool isPointerNull(void)
		{
			if(m_Pointer == nullptr)
			{
				return true;
			};

			return false;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};


	};


};




#endif /* SMARTPOINTER_AUDIOSMARTPOINTER_H_ */
