/*
 * PlayerCDType.h
 *
 *  Created on: 2024/06/16
 *      Author: SONIC
 */

#ifndef OTHER_PLAYERCDTYPE_H_
#define OTHER_PLAYERCDTYPE_H_

#include <stdint.h>

namespace SonikAudioEnum
{
	enum PlayerCDType : uint32_t
	{
		PCDTYPE_BGM = 0,
		PCDTYPE_SE = 1,

		PCDTYPE_CNT,
	};

};


#endif /* OTHER_PLAYERCDTYPE_H_ */
