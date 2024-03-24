/*
 * SonikAudioPlayer_ControlData.h
 *
 *  Created on: 2023/10/16
 *      Author: owner
 */

#ifndef PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_
#define PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_

#include <stdint.h>
#include "../../../SonikCAS/SonikAtomicLock.h"
#include "SonikAudioPlayer_ControlData_Interface.h"
#include "../PlayStateEnums.h"
#include "../../AudioLoadTypedef.h"
#include "../SAudioAccesserTypedef.h"


namespace SonikMathDataBox
{
	class Sonik3DPoint;
};



namespace SonikAudioData
{

	//大本のクラス。
	class SonikAudioControlData : public SonikAudioDataInterface::SADInterface_PlayerSide
	{
	private:
		SonikAudio::SAudioFormat m_AudioData;			//オーディオデータへのスマートポインタ
		char* mp_ControlData;							//操作用ポインタ
		SonikMathDataBox::Sonik3DPoint* m_3dpos;		//3D座標
		SonikMathDataBox::Sonik3DPoint* m_3ddir;		//3D方向
		float m_volume;									//オーディオの音量
		bool m_repeat;									//オーディオのリピートフラグ
		SonikAudioEnum::PlayStateID m_AudioState;		//オーディオのステータス(プレイ、ストップ等)
		uintptr_t m_uniqueid;							//メインインターフェースで管理される番号です。（自信のアドレス値をIDとして使います。)

		//CASLock
		SonikLib::S_CAS::SonikAtomicLock AudioStateLock;
		SonikLib::S_CAS::SonikAtomicLock RepeatFlgLock;


	public:
		//コンストラクタ
		SonikAudioControlData(SonikAudio::SAudioFormat SetAudioPointer);
		//デストラクタ
		~SonikAudioControlData(void);
		//その他デフォルト(コピーコンストラクタ等)

		//コントロールオーディオのポインタを先頭ポインタへ移動します。
		void TopResetAudioControlPointer(void);

		//現在のコントロールポインタの位置が終端かどうかを確認します。
		bool Get_EndPointer(void);

		//コントロールオーディオポインタのゲット
		char** GetAudioControlPointer(void);

		//ポジションのセット
		void SetPositionX(double SetValue);
		void SetPositionY(double SetValue);
		void SetPositionZ(double SetValue);
		void SetPositionAll(double x, double y, double z);
		void SetPositionXY(double x, double y);
		void SetPositionXZ(double x, double z);
		void SetPositionYZ(double y, double z);

		//別のポジションへのポインタとつなぎ、位置を一緒に動かしたいときに使います。
		//内部の個別ポジションに戻したい場合はnullptrを指定します。
		void SetPositonConnectX(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositonConnectY(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositonConnectZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositionConnectAll(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositonConnectXY(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositonConnectXZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);
		void SetPositonConnectYZ(SonikMathDataBox::Sonik3DPoint* _3dpos_);

		//方向のセット
		void SetDirectionX(double SetValue);
		void SetDirectionY(double SetValue);
		void SetDirectionZ(double SetValue);
		void SetDirectionAll(double x, double y, double z);
		void SetDirectionXY(double x, double y);
		void SetDirectionXZ(double x, double z);
		void SetDirectionYZ(double y, double z);

		//別の方向へのポインタとつなぎ、位置を一緒に動かしたいときに使います。
		//内部の個別ポジションに戻したい場合はnullptrを指定します。
		void SetDirectionConnectX(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectY(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectAll(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectXY(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectXZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);
		void SetDirectionConnectYZ(SonikMathDataBox::Sonik3DPoint* _3ddir_);


		//音量(ボリューム)のセット
		void SetVolume(float SetValue);

		//繰り返し(リピート)フラグのセット
		void SetRepeat(bool SetValue);

		//オーディオステータスのセット
		void SetAudioState(SonikAudioEnum::PlayStateID SetValue);

		//継承元の純粋仮想関数の実装====================================
		//ポジションのゲット
		double GetPositionX(void);
		double GetPositionY(void);
		double GetPositionZ(void);
		void GetPositionAll(double& x, double& y, double& z);
		SonikMathDataBox::Sonik3DPoint& GetPositionAll(void);
		void GetPositionXY(double& x, double& y);
		void GetPositionXZ(double& x, double& z);
		void GetPositionYZ(double& y, double& z);

		//方向(Directionのゲット
		double GetDirectionX(void);
		double GetDirectionY(void);
		double GetDirectionZ(void);
		void GetDirectionAll(double& x, double& y, double& z);
		SonikMathDataBox::Sonik3DPoint& GetDirectionAll(void);
		void GetDirectionXY(double& x, double& y);
		void GetDirectionXZ(double& x, double& z);
		void GetDirectionYZ(double& y, double& z);


		//音量(ボリューム)のゲット
		const float* GetVolume(void);

		//繰り返し(リピート)フラグのゲット
		bool GetRepeat(void);

		//Waveデータの全体サイズを取得します。
		uint32_t GetAllWaveDataSize(void);

		//ステータスのゲット
		SonikAudioEnum::PlayStateID GetPlayState(void);

		//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
		uint64_t Get_UniqueID(void);

	};

};



#endif /* PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_ */
