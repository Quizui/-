/*
 * ALSorceBox.h
 *
 *  Created on: 2020/05/13
 *      Author: SONIC
 */

#ifndef ALSORCEBOX_H_
#define ALSORCEBOX_H_

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include "AL/efx.h"
#include "AL/efx-creative.h"
#include "AL/efx-presets.h"


namespace OAL_SourceBox
{
	class SourceBox
	{
	public:
		ALuint m_Source;

		SourceBox* m_next;
		SourceBox* m_prev;

		SourceBox(void)
		:m_Source(0)
		,m_next(nullptr)
		,m_prev(nullptr)
		{
			//no process
		};

		~SourceBox(void)
		{
			//no process
		};

	};

}



#endif /* ALSORCEBOX_H_ */
