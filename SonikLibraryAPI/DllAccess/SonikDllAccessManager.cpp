/*
 * SonikDllAccessManager_x64.cpp
 *
 *  Created on: 2019/02/16
 *      Author: SONIK
 */

#include <map>

#include "SonikDllAccessManager.h"
#include "SonikDllLoader.h"

namespace SonikLib
{

#if defined(_WIN32) || defined(_WIN64)

	//ClassImplement
	class SonikDllHandleManager::DllObjectImple : public SonikDllOptions::SonikDllObject
	{
	private:
		SONIK_DLL_ACCESS_MANAGER_POINTER m_handle;

	public:
		//Constructor
		DllObjectImple(SONIK_DLL_ACCESS_MANAGER_POINTER SetHandle)
		:m_handle(SetHandle)
		 {
			//no process
		 };

		//Destructor
		~DllObjectImple(void)
		{
			if( m_handle != 0 )
			{
				SonikLibLoderFree(m_handle);
			};
		};

		//PureFunctions
		uintptr_t GetDllProcAddress(const char* ProcName)
		{
			SonikLib::SonikString str;
			str = ProcName;

			return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(m_handle, str.str_c()));
		};

		uintptr_t GetDllProcAddress(const char16_t* ProcName)
		{
			SonikLib::SonikString str;
			str = ProcName;

			return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(m_handle, str.str_c()));
		}

		uintptr_t GetDllProcAddress(const wchar_t* ProcName)
		{
			SonikLib::SonikString str;
			str = ProcName;

			return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(m_handle, str.str_c()));
		}

	};
	//constructor
	SonikDllHandleManager::SonikDllHandleManager(void)
	{
		//no process;
	};

	//Destructor
	SonikDllHandleManager::~SonikDllHandleManager(void)
	{
		maptype::iterator _it = DllHandleList.begin();

		while( _it != DllHandleList.end() )
		{
			SonikLibLoderFree(_it->second);
			_it = DllHandleList.erase(_it);
		};

	};

	bool SonikDllHandleManager::DllGetLoad(const char* _DllPath_, SDllHandle& _GetDllObject)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString dll_str;

		m_lock.lock();

		dll_str = _DllPath_;

		handles_ = SonikLibLoder(dll_str.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		DllObjectImple* l_imple = new(std::nothrow) DllObjectImple(handles_);
		if( l_imple == 0 )
		{
			m_lock.unlock();
			return false;
		};

		if(!SDllHandle::SmartPointerCreate(l_imple, _GetDllObject))
		{
			delete l_imple;
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	bool SonikDllHandleManager::DllGetLoad(const char16_t* _DllPath_, SDllHandle& _GetDllObject)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString dll_str;

		m_lock.lock();

		dll_str = _DllPath_;

		handles_ = SonikLibLoder(dll_str.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		DllObjectImple* l_imple = new(std::nothrow) DllObjectImple(handles_);
		if( l_imple == 0 )
		{
			m_lock.unlock();
			return false;
		};

		if(!SDllHandle::SmartPointerCreate(l_imple, _GetDllObject))
		{
			delete l_imple;
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	bool SonikDllHandleManager::DllGetLoad(const wchar_t* _DllPath_, SDllHandle& _GetDllObject)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString dll_str;

		m_lock.lock();

		dll_str = _DllPath_;

		handles_ = SonikLibLoder(dll_str.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		DllObjectImple* l_imple = new(std::nothrow) DllObjectImple(handles_);
		if( l_imple == 0 )
		{
			m_lock.unlock();
			return false;
		};

		if(!SDllHandle::SmartPointerCreate(l_imple, _GetDllObject))
		{
			delete l_imple;
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	bool SonikDllHandleManager::DllLoad(const char* _DllPath_, const char* SetFind_DllName, const char* RegisterName)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString findstr;

		findstr = RegisterName;
		if( DllHandleList.find(findstr.str_c()) != DllHandleList.end() )
		{
			return true;
		};

		m_lock.lock();

		findstr = _DllPath_;

		handles_ = SonikLibLoder(findstr.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		findstr = RegisterName;
		if( DllHandleList.insert( maptype::value_type(findstr, handles_) ).second )
		{
			SonikLibLoderFree(handles_);
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	bool SonikDllHandleManager::DllLoad(const char16_t* _DllPath_, const char16_t* SetFind_DllName, const char16_t* RegisterName)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString findstr;

		findstr = RegisterName;
		if( DllHandleList.find(findstr.str_c()) != DllHandleList.end() )
		{
			return true;
		};

		m_lock.lock();

		findstr = _DllPath_;

		handles_ = SonikLibLoder(findstr.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		findstr = RegisterName;
		if( DllHandleList.insert( maptype::value_type(findstr, handles_) ).second )
		{
			SonikLibLoderFree(handles_);
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	bool SonikDllHandleManager::DllLoad(const wchar_t* _DllPath_, const wchar_t* SetFind_DllName, const wchar_t* RegisterName)
	{
		SONIK_DLL_ACCESS_MANAGER_POINTER handles_;
		SonikLib::SonikString findstr;

		findstr = RegisterName;
		if( DllHandleList.find(findstr.str_c()) != DllHandleList.end() )
		{
			return true;
		};

		m_lock.lock();

		findstr = _DllPath_;

		handles_ = SonikLibLoder(findstr.str_c(), SonikDllLoader::LibLoderFlag::LOAD_DEFAULT);
		if(handles_ == 0)
		{
			m_lock.unlock();
			return false;
		};

		findstr = RegisterName;
		if( DllHandleList.insert( maptype::value_type(findstr, handles_) ).second )
		{
			SonikLibLoderFree(handles_);
			m_lock.unlock();
			return false;
		};

		m_lock.unlock();
		return true;
	};

	void SonikDllHandleManager::FreeDll(const char* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.str_c());
		if( it == DllHandleList.end() )
		{
			return;
		};

		m_lock.lock();

		if( !SonikLibLoderFree(it->second) )
		{
			m_lock.unlock();
			return;
		};

		DllHandleList.erase(it);

		m_lock.unlock();
		return;
	};

	void SonikDllHandleManager::FreeDll(const char16_t* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.str_c());
		if( it == DllHandleList.end() )
		{
			return;
		};

		m_lock.lock();

		if( !SonikLibLoderFree(it->second) )
		{
			m_lock.unlock();
			return;
		};

		DllHandleList.erase(it);

		m_lock.unlock();
		return;
	};

	void SonikDllHandleManager::FreeDll(const wchar_t* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.str_c());
		if( it == DllHandleList.end() )
		{
			return;
		};

		m_lock.lock();

		if( !SonikLibLoderFree(it->second) )
		{
			m_lock.unlock();
			return;
		};

		DllHandleList.erase(it);

		m_lock.unlock();
		return;
	};

	uintptr_t SonikDllHandleManager::GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char* ProcName)
	{
		SonikLib::SonikString str;
		str = ProcName;

		return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(dllhandle, str.str_c()));
	};

	uintptr_t SonikDllHandleManager::GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const char16_t* ProcName)
	{
		SonikLib::SonikString str;
		str = ProcName;

		return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(dllhandle, str.str_c()));
	};

	uintptr_t SonikDllHandleManager::GetDllProcAddress(SONIK_DLL_ACCESS_MANAGER_POINTER dllhandle, const wchar_t* ProcName)
	{
		SonikLib::SonikString str;
		str = ProcName;

		return reinterpret_cast<uintptr_t>(SonikLibLoderProcAddress(dllhandle, str.str_c()));
	};

	SONIK_DLL_ACCESS_MANAGER_POINTER SonikDllHandleManager::GetHandle(const char* FindDllName)
	{
		maptype::iterator it;

		it = DllHandleList.find(FindDllName);
		if( it == DllHandleList.end() )
		{
			return 0;
		};

		return it->second;
	};

	SONIK_DLL_ACCESS_MANAGER_POINTER SonikDllHandleManager::GetHandle(char16_t* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.str_c());
		if( it == DllHandleList.end() )
		{
			return 0;
		};

		return it->second;
	};

	SONIK_DLL_ACCESS_MANAGER_POINTER SonikDllHandleManager::GetHandle(wchar_t* FindDllName)
	{
		maptype::iterator it;
		SonikLib::SonikString findstr;

		findstr = FindDllName;
		it = DllHandleList.find(findstr.str_c());
		if( it == DllHandleList.end() )
		{
			return 0;
		};

		return it->second;
	};

#elif defined(__linux__)

#endif

};
