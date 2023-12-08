/*
 * SonikStateMachineBase.h
 *
 *  Created on: 2016/01/22
 *      Author: SONIC_000
 */

#ifndef SONIKSTATEMACHINE_SONIKSTATEBASE_H_
#define SONIKSTATEMACHINE_SONIKSTATEBASE_H_

#include "..\\Function\\TemplateFuncDefinition.hpp"

typedef enum SONIKSTATE_SCENETYPE
{
	SSMSCENE_INITIALIZE = 0,
	SSMSCENE_UPDATE,
	SSMSCENE_TRANSITION,
	SSMSCENE_NONE,

}SSMSCENE;

typedef enum _SONIKSTATEMACHINE_RETRUNVALUE_
{
	SSMRet_UPDATELOOP = 0xD01,	//次のフレームでもUPDATEステージを行います。
	SSMRet_UPDATENEXT,			//次のフレームはTransitionステージに移行します。
	SSMRet_INITIALIZE_SUCCESS,	//INITIALIZEシーンが正常に終了したことを表します。
	SSMRet_TRANSITION_SUCCESS,	//TRANSITIONシーンが正常に終了したことを表します。
	SSMRet_ERROR,				//エラーが発生した祭に使用します。
	SSMRet_END,					//シーン終了を意味します。(すべてのマシーンの終了を意味します。)

}SSMRetVal;


namespace SonikStateLib
{
	class StateContext;
};

namespace SonikStateMachineBase
{

	class SonikStateBase
	{
	private:
		SSMSCENE SceneType_;

		SSMRetVal (SonikStateBase::*PlayFunc)(SonikStateLib::StateContext* pContext);
		void (SonikStateBase::*CheckFunc)(SSMRetVal& RetVal);

	private:
		void CheckInitialize(SSMRetVal& RetVal);
		void CheckUpdate(SSMRetVal& RetVal);

	protected:
		virtual SSMRetVal SceneInitialize(SonikStateLib::StateContext* pContext) =0;
		virtual SSMRetVal SceneUpdate(SonikStateLib::StateContext* pContext) =0;
		virtual SSMRetVal SceneTransition(SonikStateLib::StateContext* pContext) =0;

	public:
		SonikStateBase(void);
		virtual ~SonikStateBase(void);

		//次のExeCall を呼び出した時に実行されるシーンのIDを取得します。
		SSMSCENE GetNowScene(void);

		//シーンの進捗状況をInitializeの前までリセットします。
		void ResetScene(void);

		//シーンの進歩状況をUpdateまで進めます。
		void SceneSkipToUpdate(SonikStateLib::StateContext* pContext, SSMRetVal* pRet);

		//呼び出すごとに、そのシーンがエラーや終了判定以外であれば次のシーンに進みます。
		SSMSCENE ExeCall(SonikStateLib::StateContext* pContext, SSMRetVal* pRet =0);

	};

};


#endif /* SONIKSTATEMACHINE_SONIKSTATEBASE_H_ */
