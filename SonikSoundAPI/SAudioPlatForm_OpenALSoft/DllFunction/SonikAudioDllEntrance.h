/*
 * SonikAudioDllEntrance.h
 *
 *  Created on: 2017/11/10
 *      Author: SONIC
 */

#ifndef DLLENTRANCE_SONIKAUDIODLLENTRANCE_H_
#define DLLENTRANCE_SONIKAUDIODLLENTRANCE_H_

#include "SonikAudioDll_Definition.h"
#include <stdint.h>

namespace SonikAudioPlatForm
{
	class SonikPlatformAudioInterface;
};

extern "C"
{
	SONIKAUDIOEXPORTDLL
	bool PlatFormInitialize(char* DllPath, uint32_t SetBit, uint32_t SetSampling, uint32_t SetCh, uint32_t SetBufferCnt, SonikAudioPlatForm::SonikPlatformAudioInterface*& _GetAudioInterface_);
	SONIKAUDIOEXPORTDLL
	void PlatFormDelete(void);
};

#endif /* DLLENTRANCE_SONIKAUDIODLLENTRANCE_H_ */
