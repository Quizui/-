/*
 * SonikAudioDll_Definition.h
 *
 *  Created on: 2016/05/05
 *      Author: SONIC_000
 */

#ifndef DLLCALL_SONIKAUDIODLL_DEFINITION_H_
#define DLLCALL_SONIKAUDIODLL_DEFINITION_H_


#ifdef __SONIK_DLL_OUTPUT_DEFINE__

#define SONIKAUDIOEXPORTDLL __declspec(dllexport)

#else

#define SONIKAUDIOEXPORTDLL

#endif


#endif /* DLLCALL_SONIKAUDIODLL_DEFINITION_H_ */
