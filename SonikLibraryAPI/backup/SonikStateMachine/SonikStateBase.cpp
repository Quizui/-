/*
 * SonikStateBase.cpp
 *
 *  Created on: 2016/01/25
 *      Author: SONIC_000
 */

#include "SonikStateBase.h"
#include "SonikState.h"

namespace SonikStateMachineBase
{

	SonikStateBase::SonikStateBase(void)
	:SceneType_(SSMSCENE_INITIALIZE)
	,PlayFunc(&SonikStateBase::SceneInitialize)
	,CheckFunc(&SonikStateBase::CheckInitialize)
	{
		//no process
	};

	SonikStateBase::~SonikStateBase(void)
	{
		//no process
	};

	SSMSCENE SonikStateBase::GetNowScene(void)
	{
		return SceneType_;
	};

	void SonikStateBase::CheckInitialize(SSMRetVal& RetVal)
	{
		if(RetVal != SSMRet_INITIALIZE_SUCCESS)
		{
			PlayFunc = 0;
		};

		PlayFunc = &SonikStateBase::SceneUpdate;
		CheckFunc = &SonikStateBase::CheckUpdate;
		SceneType_ = SSMSCENE_UPDATE;
	};

	void SonikStateBase::CheckUpdate(SSMRetVal& RetVal)
	{
		if(RetVal == SSMRet_ERROR && RetVal == SSMRet_END)
		{
			PlayFunc = 0;
		}else if(RetVal == SSMRet_UPDATENEXT)
		{
			PlayFunc = &SonikStateBase::SceneTransition;
			SceneType_ = SSMSCENE_TRANSITION;
			CheckFunc = 0;
		};
	};

	//シーンの進捗状況をInitializeの前までリセットします。
	void SonikStateBase::ResetScene(void)
	{
		SceneType_	= SSMSCENE_INITIALIZE;
		PlayFunc	= &SonikStateBase::SceneInitialize;
		CheckFunc	= &SonikStateBase::CheckInitialize;

	};

	//シーンの進歩状況をUpdateまで進めます。
	void SonikStateBase::SceneSkipToUpdate(SonikStateLib::StateContext* pContext, SSMRetVal* pRet)
	{
		ResetScene();

		ExeCall(pContext, pRet);

	};

	SSMSCENE SonikStateBase::ExeCall(SonikStateLib::StateContext* pContext, SSMRetVal* pRet)
	{
		SSMRetVal ret_;

		if(PlayFunc == 0)
		{
			if( pRet != 0 )
			{
				(*pRet) = SSMRet_ERROR;
			};
			return SceneType_;
		};

		ret_ = (this->*PlayFunc)(pContext);

		if(	CheckFunc != 0 )
		{
			(this->*CheckFunc)(ret_);
		};

		if( pRet != 0 )
		{
			(*pRet) = ret_;
		};

		return SceneType_;
	};
};
