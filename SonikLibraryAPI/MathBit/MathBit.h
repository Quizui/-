#ifndef MATH_BIT_COMMON_HEADER_
#define MATH_BIT_COMMON_HEADER_

#include <cstdint>

namespace SonikMathBit
{
    //立っているビットの数をカウントします。
	uint16_t OnBitCountFor8bit(uint8_t BitValue);
	uint16_t OnBitCountFor16bit(uint16_t BitValue);
	uint16_t OnBitCountFor32bit(uint32_t BitValue);
	uint16_t OnBitCountFor64bit(uint64_t BitValue);

    //立っているビット中一番最上位のビットの位置を取得します。(0~カウント)
	int16_t GetMSBFor8bit(uint8_t BitValue);
	int16_t GetMSBFor16bit(uint16_t BitValue);
	int16_t GetMSBFor32bit(uint32_t BitValue);
	int16_t GetMSBFor64bit(uint64_t BitValue);

    //立っていないビット中一番最上位のビットの位置を取得します。(0~カウント)
    int16_t GetZEROMSBFor8bit(uint8_t BitValue);
    int16_t GetZEROMSBFor16bit(uint16_t BitValue);
    int16_t GetZEROMSBFor32bit(uint32_t BitValue);
    int16_t GetZEROMSBFor64bit(uint64_t BitValue);

    //立っているビット中一番最下位のビットの位置を取得します。(0~カウント)
	int16_t GetLSBFor8bit(uint32_t BitValue);
	int16_t GetLSBFor16bit(uint32_t BitValue);
	int16_t GetLSBFor32bit(uint32_t BitValue);
	int16_t GetLSBFor64bit(uint64_t BitValue);

    //立っていないビット中一番最下位のビットの位置を取得します。(0~カウント)
    int16_t GetZEROLSBFor8bit(uint8_t BitValue);
    int16_t GetZEROLSBFor16bit(uint16_t BitValue);
    int16_t GetZEROLSBFor32bit(uint32_t BitValue);
    int16_t GetZEROLSBFor64bit(uint64_t BitValue);

    //ビットを反転させます。
	uint8_t BitSwapFor8bit(uint8_t BitValue);
	uint16_t BitSwapFor16bit(uint16_t BitValue);
	uint32_t BitSwapFor32bit(uint32_t BitValue);
	uint64_t BitSwapFor64bit(uint64_t BitValue);

    //エンディアン変換を行います。
    void EndianConvertFor2Byte(char* _data_, uint64_t _datasize_);
    void EndianConvertFor4Byte(char* _data_, uint64_t _datasize_);
    void EndianConvertFor8Byte(char* _data_, uint64_t _datasize_);
};

#endif
