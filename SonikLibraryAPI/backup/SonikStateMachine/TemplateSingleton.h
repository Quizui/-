/*
 * TemplateSingleton.h
 *
 *  Created on: 2016/01/24
 *      Author: SONIC_000
 */

#ifndef TEMPLATESINGLETON_H_
#define TEMPLATESINGLETON_H_

#include "..\\SonikAllocateUse.h"
#include "..\\SonikCASLockUse.h"

namespace SonikTmplateSingleton
{
	template <class SingletonCls>
	class TemplateSingleton
	{
	private:
		static SonikLib::SonikAtomicLock singleton_atm_lock_;

	private:
		//コピーコンストラクタの禁止
		TemplateSingleton(const TemplateSingleton& t_his)
		{
			//no process;
		};
		//代入演算子の禁止
		void operator =(const TemplateSingleton& t_his)
		{
			//no process;
		};

	protected:
		//継承先以外のコール禁止
		TemplateSingleton(void)
		{
			//no process;
		};
		//継承先以外のコール禁止
		virtual ~TemplateSingleton(void)
		{
			//no process;
		};

	public:
		static SingletonCls& Instance(void)
		{
			singleton_atm_lock_.lock();
			static SingletonCls instCls_;

			singleton_atm_lock_.Unlock();

			return instCls_;
		};
	};

	template <class SingletonCls>
	SonikLib::SonikAtomicLock TemplateSingleton<SingletonCls>::singleton_atm_lock_;


};


#endif /* TEMPLATESINGLETON_H_ */
