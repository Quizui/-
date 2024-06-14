/*
 * PlayStateEnums.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYSTATEENUMS_H_
#define PLAYSTATEENUMS_H_

#include <stdint.h>

//外部に公開しないEnums
//指定させたいなら公開しても良き、でも種類ごとに関数作る予定。
namespace SonikAudioEnum
{
	enum PlayStateID : uint32_t
	{
		PS_Play = 0x00,
		PS_Stop = 0x01,
		PS_SUSPEND = 0x02,

	};

	enum PlayEffectID : uint32_t
	{
		EF_DISTANCE = 1, //Distanceによる減衰を適用します。0x01(1bit目)
		EF_PANNING	= 2, //Panningによる減衰を適用します。 0x02(2bit目)

		EF_BITMAX = EF_DISTANCE | EF_PANNING, //エフェクトのビットON最大値。
		EF_CNT = 2, //エフェクトの種類数
	};

}



#endif /* PLAYSTATEENUMS_H_ */
