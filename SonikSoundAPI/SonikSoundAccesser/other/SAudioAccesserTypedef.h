/*
 * SAudioTypedef.h
 *
 *  Created on: 2020/06/07
 *      Author: SONIC
 */

#ifndef SAUDIO_ACCESSER_TYPEDEF_H_
#define SAUDIO_ACCESSER_TYPEDEF_H_

//#include "AudioFormat/AudioLoadTypedef.h"
#include "../../SmartPointer/SonikSmartPointer.hpp"

namespace SonikAudio
{
	class SonikAudioInterface;
};

namespace SonikAudio
{
	class SonikAudioPlayer;
};

namespace SonikAudio
{
	class SonikAudioListener;
};


namespace SonikAudio
{

	using SAudioInterface = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioInterface>;

	using SAudioPlayer = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioPlayer>;

	using SAudioListener = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioListener>;

};


#endif /* SAUDIOTYPEDEF_H_ */
