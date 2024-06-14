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
	class SonikAudioControlData
	{
	protected:
		SonikAudio::SAudioFormat m_AudioData;			//オーディオデータへのスマートポインタ
		char* mp_ControlData;							//操作用ポインタ
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
		virtual ~SonikAudioControlData(void);
		//その他デフォルト(コピーコンストラクタ等)

		//コントロールオーディオのポインタを先頭ポインタへ移動します。
		void TopResetAudioControlPointer(void);

		//現在のコントロールポインタの位置が終端かどうかを確認します。
		bool Get_EndPointer(void);

		//コントロールオーディオポインタのゲット
		char** GetAudioControlPointer(void);

		//音量(ボリューム)のセット
		void SetVolume(float SetValue);

		//繰り返し(リピート)フラグのセット
		void SetRepeat(bool SetValue);

		//オーディオステータスのセット
		void SetAudioState(SonikAudioEnum::PlayStateID SetValue);

		//データ自身のマスター音量(ボリューム)のゲット
		const float* GetVolume(void);

		//繰り返し(リピート)フラグのゲット
		bool GetRepeat(void);

		//Waveデータの全体サイズを取得します。
		uint32_t GetAllWaveDataSize(void);

		//ステータスのゲット
		SonikAudioEnum::PlayStateID GetPlayState(void);

		//Unique IDの取得(マップに登録する時や登録したものを検索するのに使います。
		uint64_t Get_UniqueID(void);

		//データが最終的にミキシングしてほしいボリューム値を取得
		virtual void GetMixingVolume(double&, double&) = 0;

	};

};



#endif /* PLAYER_SONIKAUDIOPLAYER_CONTROLDATA_H_ */
