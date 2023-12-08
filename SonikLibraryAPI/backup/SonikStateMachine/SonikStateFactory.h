/*
 * SonikStateMachine.h
 *
 *  Created on: 2016/01/23
 *      Author: SONIC_000
 */

#ifndef SONIKSTATEMACHINE_SONIKSTATEFACTORY_H_
#define SONIKSTATEMACHINE_SONIKSTATEFACTORY_H_

#include "..\\SonikAllocateUse.h"
#include "..\\SonikCASLockUse.h"
#include <map>

#include "TemplateSingleton.h"
#include "SonikState.h"

namespace SonikLib
{
	class SonikStateFactory : public SonikTmplateSingleton::TemplateSingleton<SonikStateFactory>
	{
	//本クラスからの作成を許可
	friend class SonikTmplateSingleton::TemplateSingleton<SonikStateFactory>;

	private:
		std::map< std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase> > statemap_;
		SonikLib::SonikAllocObjectPtr AllocSmtPtr;

	public:
		SonikStateFactory(void);

		bool InitStateFactory(unsigned long BiggestStateSize, unsigned long StateCount);

		template <class StateType = SonikStateLib::SonikState>
		bool GetState(std::string StateName, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase>& GetState_)
		{
			if( AllocSmtPtr.NullPtrCheck() )
			{
				return false;
			};

			if( std::is_base_of<SonikStateLib::SonikState, StateType>::value == false )
			{
				return false;
			};

			std::map< std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase> >::iterator it;

			it = statemap_.find(StateName);
			if( it != statemap_.end() )
			{
				GetState_ = it->second;
				return true;
			};

			SonikLib::SonikAllocSmtPtr<StateType> TmpState_;
			if( !AllocSmtPtr->GetAlloc<StateType>(TmpState_) )
			{
				return false;
			};

			GetState_ = TmpState_;

			if( !statemap_.insert( std::map< std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase> >::value_type(StateName, GetState_) ).second )
			{
				GetState_.~SonikAllocSmtPtr();
				return false;
			};

			return true;
		};

	};

};






#endif /* SONIKSTATEMACHINE_SONIKSTATEFACTORY_H_ */
