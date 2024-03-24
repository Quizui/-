/*
 * PlayStateEnums.h
 *
 *  Created on: 2023/07/16
 *      Author: owner
 */

#ifndef PLAYSTATEENUMS_H_
#define PLAYSTATEENUMS_H_

//外部に公開しないEnums
//指定させたいなら公開しても良き、でも種類ごとに関数作る予定。
namespace SonikAudioEnum
{
	enum class PlayStateID
	{
		PS_Play = 0x00,
		PS_Stop = 0x01,
		PS_SUSPEND = 0x02,


	};


}



#endif /* PLAYSTATEENUMS_H_ */
