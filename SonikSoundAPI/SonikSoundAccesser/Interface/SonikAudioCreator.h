/*
 * SonikAudioCreator.h
 *
 *  Created on: 2020/04/24
 *      Author: SONIC
 */

#ifndef SONIKAUDIOCREATOR_H_
#define SONIKAUDIOCREATOR_H_

#include "../../../SonikCAS/SonikAtomicLock.h"
#include "../SAudioAccesserTypedef.h"
#include "../AudioSmartPointer.h"

//Singleton Class
namespace SonikAudio
{
	class SonikAudioCreator
	{
	private:
		SonikLib::S_CAS::SonikAtomicLock _lock;
		SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudio::SonikAudioInterface> _interface;

	private:
		//Constructor
		SonikAudioCreator(void);
		//Copy Constructor
		SonikAudioCreator(const SonikAudioCreator& t_his);
		//override operator equal
		SonikAudioCreator& operator =(const SonikAudioCreator& t_his);

	public:
		//Destrucotr
		~SonikAudioCreator(void);

		static SonikAudioCreator& Instance(void);

		bool CreatAudioInterface(char* DllPath, unsigned long SetBit, unsigned long SetSampling, unsigned long SetCh, SonikAudio::SAudioInterface& RefGetInterface);

		void DeleteAudioInterface(void);

	};


}




#endif /* SONIKAUDIOCREATOR_H_ */
