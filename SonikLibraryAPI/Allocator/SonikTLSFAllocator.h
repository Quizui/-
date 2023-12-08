/*
 * SonikTLSFAllocator.h
 *
 *  Created on: 2023/11/18
 *      Author: owner
 */

#ifndef ALLOCATOR_SONIKTLSFALLOCATOR_H_
#define ALLOCATOR_SONIKTLSFALLOCATOR_H_

#include <stdint.h>

namespace SonikLib
{
	namespace Allocator
	{
		class SonikTLSFAllocator
		{
		private:
			uint64_t m_AllocatorSize; //アロケータが確保しているサイズ。
			uint8_t m_SplitLevel; // アロケータ内のTLSFによる分割レベル。


		public:


		};



	}; //end namespace  Allocator

}; //end namespace SonikLib



#endif /* ALLOCATOR_SONIKTLSFALLOCATOR_H_ */
