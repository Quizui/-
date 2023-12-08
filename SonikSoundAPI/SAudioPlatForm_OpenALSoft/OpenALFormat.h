/*
 * OpenAlFormat.h
 *
 *  Created on: 2020/05/11
 *      Author: SONIC
 */

#ifndef OPENALFORMAT_H_
#define OPENALFORMAT_H_


//OpenALはバッファのとり方が独特な物なので、PCMデータをOpenAL流儀の形に保存しないといけない。

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "AL/efx-creative.h"
#include "AL/efx-presets.h"

#include "../../SonikCAS/SonikAtomicLock.h"

namespace OpenALFormat
{
	class OAL_PlayerFlagsContainer
	{
		//関数呼び出しコスト削減かつここでしか使わないため
		//とりあえず全公開
	public:
		OAL_PlayerFlagsContainer* prev;
		OAL_PlayerFlagsContainer* next;

		// 0xF0=TOP 0x0F=END
		uint32_t point;
		bool* flags;

	public:
		OAL_PlayerFlagsContainer(void)
		:prev(nullptr)
		,next(nullptr)
		,point(0x00)
		,flags(nullptr)
		{
			//no process
		};

		~OAL_PlayerFlagsContainer(void)
		{
			//no process;
		};
	};

	class OALFormat
	{
	private:
		unsigned long SamplingRate;
		unsigned short Channels;
		unsigned short Bits;
		unsigned short BlockBaundary;
		unsigned long PCMDataSize;

		char* WaveData;
		ALuint PCMDataBuffers;

		//Top End
//		OAL_PlayerFlagsContainer FlagsList[2];

		//BufferDeleteAction
		void(*BufferDelete)(ALsizei, ALuint*);

		SonikLib::S_CAS::SonikAtomicLock FlagsListControlLock;

	public:
		//Constructor
		OALFormat(void(*SetBufferDelFunc)(ALsizei, ALuint*) = nullptr)
		:SamplingRate(0)
		,Channels(0)
		,Bits(0)
		,BlockBaundary(0)
		,PCMDataSize(0)
		,WaveData(nullptr)
		,PCMDataBuffers(0)
		,BufferDelete(SetBufferDelFunc)
		{
			//TOP Point設定
//			FlagsList[0].point = 0xF0;
//			FlagsList[0].next = &FlagsList[1];

			//END Point設定
//			FlagsList[1].point = 0x0F;
//			FlagsList[1].prev = &FlagsList[0];

		};

		//Destructor
		~OALFormat(void)
		{
//			OAL_PlayerFlagsContainer* l_flg_del_obj = FlagsList[0].next;

//			FlagsListControlLock.lock();
//
//			OAL_PlayerFlagsContainer* l_flg_obj = FlagsList[0].next;
//			//END 以外なら継続
//			while(l_flg_obj->point != FlagsList[1].point)
//			{
//				//処理上常にTOPの次を削除していけばいいので、リンクをつなぎ直せば良い
//				(*l_flg_obj->flags) = false;
//				FlagsList[0].next = l_flg_obj->next;
//
//				delete l_flg_obj;
//				l_flg_obj = FlagsList[0].next;
//			};
//
//			FlagsListControlLock.Unlock();


			if( BufferDelete != nullptr )
			{
				if( PCMDataBuffers != 0 )
				{
					(*BufferDelete)(1, &PCMDataBuffers);
				};
			};
		};

		//サンプリングレートを設定します。
		void SetSamplingRate(unsigned long SetValue)
		{
			SamplingRate = SetValue;
		};

		//チャンネルを設定します。
		void SetChannels(unsigned short SetValue)
		{
			Channels = SetValue;
		};

		//１サンプルあたりのビット数を設定します。
		void SetBits(unsigned short SetValue)
		{
			Bits = SetValue;
		};

		//ブロック境界バイト数を設定します。
		void SetBlockBaundary(unsigned short SetValue)
		{
			BlockBaundary = SetValue;
		};

		//波形データの総サイズを設定します。
		void SetPCMDataSize(unsigned long SetValue)
		{
			PCMDataSize = SetValue;
		};

		//作成されたバッファを設定します。
		void SetPCMBuffer(ALuint SetBuffer)
		{
			PCMDataBuffers = SetBuffer;
		};

		//読み込まれたWaveDataの先頭ポインタを設定します。
		void SetWaveData(char* SetWaveData)
		{
			WaveData = SetWaveData;
		}

//		bool AddAudioPlayerFlags(bool* PlayerFlags, uintptr_t& Get_FlagsID)
//		{
//			FlagsListControlLock.lock();
//			OAL_PlayerFlagsContainer* l_flgobj = new(std::nothrow) OAL_PlayerFlagsContainer;
//			if( l_flgobj == nullptr )
//			{
//				FlagsListControlLock.Unlock();
//				return false;
//			};
//
//			//リストの繋ぎを修正
//			l_flgobj->flags = PlayerFlags;
//			FlagsList[1].prev->next = l_flgobj;
//			l_flgobj->prev = FlagsList[1].prev;
//
//			FlagsList[1].prev = l_flgobj;
//			l_flgobj->next = &FlagsList[1];
//
//			Get_FlagsID = reinterpret_cast<uintptr_t>(&(*l_flgobj));
//			FlagsListControlLock.Unlock();
//
//			return true;
//		};

//		bool RemoveAudioPlayerFlags(uintptr_t FlagsID)
//		{
//			FlagsListControlLock.lock();
//			//対象のオブジェクトを調べる
//			OAL_PlayerFlagsContainer* ListItems = FlagsList[0].next;
//			while(reinterpret_cast<uintptr_t>(ListItems) != FlagsID)
//			{
//				//ENDまで行ってしまった場合はロックを外してreturn false;
//				if( ListItems->point == FlagsList[1].point )
//				{
//					FlagsListControlLock.Unlock();
//					return false;
//				};
//
//				ListItems = ListItems->next;
//
//			};
//
//			//あった場合に通る
//			//リストをつなぎ直して削除
//			ListItems->prev->next = ListItems->next;
//			ListItems->next->prev = ListItems->prev;
//
//			delete ListItems;
//
//			FlagsListControlLock.Unlock();
//
//			return true;
//		};

		//設定されているサンプリングレートを取得します。
		unsigned long GetSamplingRate(void) const
		{
			return SamplingRate;
		};

		//設定されているチャンネルを取得します。
		unsigned short GetChannels(void) const
		{
			return Channels;
		};

		//設定されている１サンプルあたりのビット数を取得します。
		unsigned short GetBits(void) const
		{
			return Bits;
		};

		//設定されている１サンプルあたりのブロック境界を取得します。
		unsigned short GetBlockBaundary(void) const
		{
			return BlockBaundary;
		};

		//設定されている波形データの総サイズを取得します。
		unsigned long GetPCMDataSize(void) const
		{
			return PCMDataSize;
		};

		//設定されているバッファを取得します。
		ALuint GetPCMDataBuffers(void)
		{
			return PCMDataBuffers;
		};

		//設定されている波形データへの先頭ポインタを取得します。
		char* GetPCMWaveData(void)
		{
			return WaveData;
		}

	};

};


#endif /* OPENALFORMAT_H_ */
