/*
 * Enums.h
 *
 *  Created on: 2020/06/05
 *      Author: SONIC
 */

#ifndef SONIKAUDIO_OPENAL_SOURCE_STATE_ENUMS_H_
#define SONIKAUDIO_OPENAL_SOURCE_STATE_ENUMS_H_

namespace OpenALAudioEnum
{
	enum class OalFuncID
	{
		FuncID_SourcePlay = 0x00,
		FuncID_SourceStop,
		FuncID_SourcePause,
		FuncID_SourceRewind,
		FuncID_SourceDelete,
		FUNCID_SourceFloat,
		FUNCID_alSourcefv,

	};

}



#endif /* SONIKAUDIO_OPENAL_SOURCE_STATE_ENUMS_H_ */
