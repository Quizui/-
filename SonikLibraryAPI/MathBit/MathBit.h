#ifndef MATH_BIT_COMMON_HEADER_
#define MATH_BIT_COMMON_HEADER_

#include <cstdint>

namespace SonikMathBit
{
	uint8_t OnBitCountFor8bit(uint8_t BitValue);

	uint8_t OnBitCountFor16bit(uint16_t BitValue);

	uint8_t OnBitCountFor32bit(uint32_t BitValue);

	uint8_t OnBitCountFor64bit(uint64_t BitValue);

	uint8_t GetMSBFor8bit(uint8_t BitValue);

	uint8_t GetMSBFor16bit(uint16_t BitValue);

	uint8_t GetMSBFor32bit(uint32_t BitValue);

	uint8_t GetMSBFor64bit(uint64_t BitValue);

	uint8_t GetLSBFor8bit(uint32_t BitValue);

	uint8_t GetLSBFor16bit(uint32_t BitValue);

	uint8_t GetLSBFor32bit(uint32_t BitValue);

	uint8_t GetLSBFor64bit(uint64_t BitValue);

	uint8_t BitSwapFor8bit(uint8_t BitValue);

	uint16_t BitSwapFor16bit(uint16_t BitValue);

	uint32_t BitSwapFor32bit(uint32_t BitValue);

	uint64_t BitSwapFor64bit(uint64_t BitValue);

};

#endif
