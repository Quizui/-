/*
 * SonikState.h
 *
 *  Created on: 2016/01/24
 *      Author: SONIC_000
 */

#ifndef SONIKSTATEMACHINE_SONIKSTATE_H_
#define SONIKSTATEMACHINE_SONIKSTATE_H_

#include "SonikStateBase.h"


namespace SonikStateLib
{
	//継承してオーバーライドしてください。
	class StateContext
	{
	public:
		StateContext(void)
		{
			//no process;
		};

		~StateContext(void)
		{
			//no process
		};
	};


};

namespace SonikStateLib
{
	//継承してオーバーライドしてください。
	class SonikState : public SonikStateMachineBase::SonikStateBase
	{
	protected:
		unsigned long UniqueCount_;

	protected:
		virtual SSMRetVal SceneInitialize(StateContext* pContext) =0;

		virtual SSMRetVal SceneUpdate(StateContext* pContext) =0;

		virtual SSMRetVal SceneTransition(StateContext* pContext) =0;
	};

};





//namespace SonikStateMachineBase
//{
//	template <class ContextType>
//	class StateFactoryModule
//	{
//	private:
//		std::map<std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase<ContextType>>> StateMap;
//		SonikLib::SonikAllocObjectPtr AllocSmtPtr;
//
//		bool init_;
//	private:
//		StateFactoryModule(void)
//		:init_(false)
//		{
//			//no process;
//		};
//
//		StateFactoryModule(const StateFactoryModule& t_his)
//		:init_(false)
//		{
//			//no process;
//		};
//
//		StateFactoryModule(StateFactoryModule&& t_his)
//		:init_(false)
//		{
//			//no process;
//		};
//
//		~StateFactoryModule(void)
//		{
//			//no process;
//		};
//
//		//初期化
//		bool Initialize(unsigned long SetCount)
//		{
//			return SonikLibCall::CreateSonikMemoryAllocaor(AllocSmtPtr, sizeof(SonikStateLib::SonikState<ContextType>) * SetCount);
//		};
//
//		bool GetState(std::string StateName, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase<ContextType>>& GetState_)
//		{
//			std::map<std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase<ContextType>>>::iterator it_;
//
//			it_ = StateMap.find(StateName);
//			if( it_ != StateMap.end() )
//			{
//				GetState_ = it_.second;
//			}
//
//			SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase<ContextType>> pAlloc;
//			if( !AllocSmtPtr->GetAlloc(pAlloc) )
//			{
//				return false;
//			};
//
//			if( !StateMap.insert( std::map<std::string, SonikLib::SonikAllocSmtPtr<SonikStateMachineBase::SonikStateBase<ContextType>>>::value_type(StateName, pAlloc) ).second )
//			{
//				return false;
//			};
//
//			GetState_ = pAlloc;
//			return true;
//		};
//
//
//	};
//
//};


#endif /* SONIKSTATEMACHINE_SONIKSTATE_H_ */
