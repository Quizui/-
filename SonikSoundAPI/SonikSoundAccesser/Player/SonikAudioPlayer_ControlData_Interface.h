/*
 * SonikAudioPlayer_ControlData_Interface.h
 *
 *  Created on: 2023/10/17
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_INTERFACE_H_
#define PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_INTERFACE_H_

#include <stdint.h>
#include "../PlayStateEnums.h"

//外部公開するインターフェースを定義します。
//オーディオデータ本体の操作インターフェース。

//継承先の定義、実装は下記。
//・SonikAudioPlayer_ControlData.h

//前方宣言
namespace SonikMathDataBox
{
	class Sonik3DPoint;
};

namespace SonikAudioDataInterface
{
	//プレイヤー側に渡す用のクラス。
	class SADInterface_PlayerSide
	{
	private:
		//メンバー変数なし。

	public:
		//コンストラクタとデストラクタは一応定義。
		//コンストラクタ
		SADInterface_PlayerSide(void)
		{
			//no porcess;
		};
		//デストラクタ
		virtual ~SADInterface_PlayerSide(void)
		{
			//no process;
		};

		//ポジションのゲット
		virtual double GetPositionX(void) =0;
		virtual double GetPositionY(void) =0;
		virtual double GetPositionZ(void) =0;
		virtual void GetPositionAll(double& x, double& y, double& z) =0;
		virtual SonikMathDataBox::Sonik3DPoint& GetPositionAll(void) =0;
		virtual void GetPositionXY(double& x, double& y) =0;
		virtual void GetPositionXZ(double& x, double& z) =0;
		virtual void GetPositionYZ(double& y, double& z) =0;

		//方向(Directionのゲット
		virtual double GetDirectionX(void) =0;
		virtual double GetDirectionY(void) =0;
		virtual double GetDirectionZ(void) =0;
		virtual void GetDirectionAll(double& x, double& y, double& z) =0;
		virtual SonikMathDataBox::Sonik3DPoint& GetDirectionAll(void) =0;
		virtual void GetDirectionXY(double& x, double& y) =0;
		virtual void GetDirectionXZ(double& x, double& z) =0;
		virtual void GetDirectionYZ(double& y, double& z) =0;

		//音量(ボリューム)のゲット
		virtual const float* GetVolume(void) =0;

		//繰り返し(リピート)フラグのゲット
		virtual bool GetRepeat(void) =0;

		//ステータスのゲット
		virtual SonikAudioEnum::PlayStateID GetPlayState(void) =0;

		//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
		virtual uint64_t Get_UniqueID(void) =0;

	};

};

#endif /* PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_INTERFACE_H_ */
