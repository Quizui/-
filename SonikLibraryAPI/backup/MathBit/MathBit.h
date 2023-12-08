#ifndef MATH_BIT_COMMON_HEADER_
#define MATH_BIT_COMMON_HEADER_


namespace SonikMathBit
{
	unsigned char OnBitCountFor8bit(unsigned char BitValue);

	unsigned char OnBitCountFor16bit(unsigned short BitValue);

	unsigned char OnBitCountFor32bit(unsigned long BitValue);

	unsigned char OnBitCountFor64bit(unsigned long long BitValue);

	unsigned char GetMSBFor8bit(unsigned char BitValue);

	unsigned char GetMSBFor16bit(unsigned short BitValue);

	unsigned char GetMSBFor32bit(unsigned long BitValue);

	unsigned char GetMSBFor64bit(unsigned long long BitValue);

	unsigned char GetLSBFor8bit(unsigned long BitValue);

	unsigned char GetLSBFor16bit(unsigned long BitValue);

	unsigned char GetLSBFor32bit(unsigned long BitValue);

	unsigned char GetLSBFor64bit(unsigned long long BitValue);

	unsigned char BitSwapFor8bit(unsigned char BitValue);

	unsigned short BitSwapFor16bit(unsigned short BitValue);

	unsigned long BitSwapFor32bit(unsigned long BitValue);

	unsigned long long BitSwapFor64bit(unsigned long long BitValue);

};

#endif
