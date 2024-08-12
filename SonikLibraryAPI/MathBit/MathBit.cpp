
#include "MathBit.h"

namespace SonikMathBit
{
    //立っているビットの数をカウントします。
	uint16_t OnBitCountFor8bit(uint8_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x55) + ( (BitValue >> 1) & 0x55 );
		BitValue = (BitValue & 0x33) + ( (BitValue >> 2) & 0x33 );

		return (BitValue & 0x0F) + ( (BitValue >> 4) & 0x0F );
	};
	uint16_t OnBitCountFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x5555) + ( (BitValue >> 1) & 0x5555 );
		BitValue = (BitValue & 0x3333) + ( (BitValue >> 2) & 0x3333 );
		BitValue = (BitValue & 0x0F0F) + ( (BitValue >> 4) & 0x0F0F );

		return (BitValue & 0x00FF) + ( (BitValue >> 8) & 0x00FF );
	};
    uint16_t OnBitCountFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x55555555) + ( (BitValue >> 1) & 0x55555555 );
		BitValue = (BitValue & 0x33333333) + ( (BitValue >> 2) & 0x33333333 );
		BitValue = (BitValue & 0x0F0F0F0F) + ( (BitValue >> 4) & 0x0F0F0F0F );
		BitValue = (BitValue & 0x00FF00FF) + ( (BitValue >> 8) & 0x00FF00FF );

		return (BitValue & 0x0000FFFF) + ( (BitValue >> 16) & 0x0000FFFF);
    };
    uint16_t OnBitCountFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return 0;
		};

		BitValue = (BitValue & 0x5555555555555555) + ( (BitValue >> 1) & 0x5555555555555555 );
		BitValue = (BitValue & 0x3333333333333333) + ( (BitValue >> 2) & 0x3333333333333333 );
		BitValue = (BitValue & 0x0F0F0F0F0F0F0F0F) + ( (BitValue >> 4) & 0x0F0F0F0F0F0F0F0F );
		BitValue = (BitValue & 0x00FF00FF00FF00FF) + ( (BitValue >> 8) & 0x00FF00FF00FF00FF );
		BitValue = (BitValue & 0x0000FFFF0000FFFF) + ( (BitValue >> 16) & 0x0000FFFF0000FFFF );

		return (BitValue & 0x00000000FFFFFFFF) + ( (BitValue >> 32) & 0x00000000FFFFFFFF);
	};


    //立っているビット中一番最上位のビットの位置を取得します。(0~カウント)
	int16_t GetMSBFor8bit(uint8_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);

		return OnBitCountFor8bit(BitValue) -1;
	};

    int16_t GetMSBFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);

		return OnBitCountFor16bit(BitValue) -1;
	};

    int16_t GetMSBFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);
		BitValue |= (BitValue >> 16);

		return OnBitCountFor32bit(BitValue) -1;
	};

    int16_t GetMSBFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue >> 1);
		BitValue |= (BitValue >> 2);
		BitValue |= (BitValue >> 4);
		BitValue |= (BitValue >> 8);
		BitValue |= (BitValue >> 16);
		BitValue |= (BitValue >> 32);

		return OnBitCountFor64bit(BitValue) -1;
	};


    //立っていないビット中一番最上位のビットの位置を取得します。(0~カウント)
    int16_t GetZEROMSBFor8bit(uint8_t BitValue)
    {
        if(BitValue == 0xFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        BitValue |= (BitValue >> 1);
        BitValue |= (BitValue >> 2);
        BitValue |= (BitValue >> 4);
        
        return OnBitCountFor8bit(BitValue) -1;
    };
    int16_t GetZEROMSBFor16bit(uint16_t BitValue)
    {
        if(BitValue == 0xFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        BitValue |= (BitValue >> 1);
        BitValue |= (BitValue >> 2);
        BitValue |= (BitValue >> 4);
        BitValue |= (BitValue >> 8);
        
        return OnBitCountFor16bit(BitValue) -1;
    };
    int16_t GetZEROMSBFor32bit(uint32_t BitValue)
    {
        if(BitValue == 0xFFFFFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        BitValue |= (BitValue >> 1);
        BitValue |= (BitValue >> 2);
        BitValue |= (BitValue >> 4);
        BitValue |= (BitValue >> 8);
        BitValue |= (BitValue >> 16);
        
        return OnBitCountFor32bit(BitValue) -1;
    };
    int16_t GetZEROMSBFor64bit(uint64_t BitValue)
    {
        if(BitValue == 0xFFFFFFFFFFFFFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        BitValue |= (BitValue >> 1);
        BitValue |= (BitValue >> 2);
        BitValue |= (BitValue >> 4);
        BitValue |= (BitValue >> 8);
        BitValue |= (BitValue >> 16);
        BitValue |= (BitValue >> 32);
        
        return OnBitCountFor64bit(BitValue) -1;
    };


    //立っているビット中一番最下位のビットの位置を取得します。(0~カウント)
	int16_t GetLSBFor8bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);

		return (8 - OnBitCountFor8bit(BitValue));

	};

    int16_t GetLSBFor16bit(uint16_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);

		return (16 - OnBitCountFor16bit(BitValue));

	};

    int16_t GetLSBFor32bit(uint32_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);
		BitValue |= (BitValue << 16);

		return (32 - OnBitCountFor32bit(BitValue));

	};

    int16_t GetLSBFor64bit(uint64_t BitValue)
	{
		if(BitValue == 0)
		{

			return -1;
		};

		BitValue |= (BitValue << 1);
		BitValue |= (BitValue << 2);
		BitValue |= (BitValue << 4);
		BitValue |= (BitValue << 8);
		BitValue |= (BitValue << 16);
		BitValue |= (BitValue << 32);

		return (64 - OnBitCountFor64bit(BitValue));

	};


    //立っていないビット中一番最下位のビットの位置を取得します。(0~カウント)
    int16_t GetZEROLSBFor8bit(uint8_t BitValue)
    {
        if(BitValue == 0xFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        
        BitValue |= (BitValue << 1);
        BitValue |= (BitValue << 2);
        BitValue |= (BitValue << 4);
        
        return 8 - OnBitCountFor8bit(BitValue);
    };
    int16_t GetZEROLSBFor16bit(uint16_t BitValue)
    {
        if(BitValue == 0xFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        
        BitValue |= (BitValue << 1);
        BitValue |= (BitValue << 2);
        BitValue |= (BitValue << 4);
        BitValue |= (BitValue << 8);
        
        return 16 - OnBitCountFor16bit(BitValue);
    };
    int16_t GetZEROLSBFor32bit(uint32_t BitValue)
    {
        if(BitValue == 0xFFFFFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        
        BitValue |= (BitValue << 1);
        BitValue |= (BitValue << 2);
        BitValue |= (BitValue << 4);
        BitValue |= (BitValue << 8);
        BitValue |= (BitValue << 16);
        
        return 32 - OnBitCountFor32bit(BitValue);
    };
    int16_t GetZEROLSBFor64bit(uint64_t BitValue)
    {
        if(BitValue == 0xFFFFFFFFFFFFFFFF)
        {
            return -1;
        };
        
        BitValue = ~BitValue;
        
        BitValue |= (BitValue << 1);
        BitValue |= (BitValue << 2);
        BitValue |= (BitValue << 4);
        BitValue |= (BitValue << 8);
        BitValue |= (BitValue << 16);
        BitValue |= (BitValue << 32);
        
        return 64 - OnBitCountFor64bit(BitValue);
    };


    //ビットを反転させます。
	uint8_t BitSwapFor8bit(uint8_t BitValue)
	{
		BitValue = ((BitValue & 0x55) << 1) | ((BitValue & 0xAA) >> 1);
		BitValue = ((BitValue & 0x33) << 2) | ((BitValue & 0xCC) >> 2);

		return ((BitValue & 0x0F) << 4) | ((BitValue & 0xF0) >> 4);
	};

	uint16_t BitSwapFor16bit(uint16_t BitValue)
	{
		BitValue = ((BitValue & 0x5555) << 1) | ((BitValue & 0xAAAA) >> 1);
		BitValue = ((BitValue & 0x3333) << 2) | ((BitValue & 0xCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F) << 4) | ((BitValue & 0xF0F0) >> 4);

		return ((BitValue & 0x00FF) << 8) | ((BitValue & 0xFF00) >> 8);
	};


	uint32_t BitSwapFor32bit(uint32_t BitValue)
	{
		BitValue = ((BitValue & 0x55555555) << 1) | ((BitValue & 0xAAAAAAAA) >> 1);
		BitValue = ((BitValue & 0x33333333) << 2) | ((BitValue & 0xCCCCCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F0F0F) << 4) | ((BitValue & 0xF0F0F0F0) >> 4);
		BitValue = ((BitValue & 0x00FF00FF) << 8) | ((BitValue & 0xFF00FF00) >> 8);

		return ((BitValue & 0x0000FFFF) << 16) | ((BitValue & 0xFFFF0000) >> 16);
	};

	uint64_t BitSwapFor64bit(uint64_t BitValue)
	{
		BitValue = ((BitValue & 0x5555555555555555) << 1) | ((BitValue & 0xAAAAAAAAAAAAAAAA) >> 1);
		BitValue = ((BitValue & 0x3333333333333333) << 2) | ((BitValue & 0xCCCCCCCCCCCCCCCC) >> 2);
		BitValue = ((BitValue & 0x0F0F0F0F0F0F0F0F) << 4) | ((BitValue & 0xF0F0F0F0F0F0F0F0) >> 4);
		BitValue = ((BitValue & 0x00FF00FF00FF00FF) << 8) | ((BitValue & 0xFF00FF00FF00FF00) >> 8);
		BitValue = ((BitValue & 0x0000FFFF0000FFFF) << 16) | ((BitValue & 0xFFFF0000FFFF0000) >> 16);

		return ((BitValue & 0x00000000FFFFFFFF) << 32) | ((BitValue & 0xFFFFFFFF00000000) >> 32);

	};


    void EndianConvertFor2Byte(char* _data_, uint64_t _datasize_)
    {
        uint64_t l_loop = _datasize_ * 0.5; //_datasize_ / sizeof(int16_t)
        uint16_t* lp_data = reinterpret_cast<uint16_t*>(_data_);

        for(uint64_t i = 0; i < l_loop; ++i)
        {
            lp_data[i] = (lp_data[i] << 8) | ((lp_data[i] >>8) & 0xFF);
        };    
    };
    
    void EndianConvertFor4Byte(char* _data_, uint64_t _datasize_)
    {
        uint64_t l_loop = _datasize_ * 0.25; //_datasize_ / sizeof(int32_t)
        uint32_t* lp_data = reinterpret_cast<uint32_t*>(_data_);

        for(uint64_t i = 0; i < l_loop; ++i)
        {
            lp_data[i] = (lp_data[i] << 24)
                         |((lp_data[i] & 0x0000FF00) << 8)
                         |((lp_data[i] & 0x00FF0000) >> 8)
                         |((lp_data[i] & 0xFF000000) >> 24);
        };
    };

    void EndianConvertFor8Byte(char* _data_, uint64_t _datasize_)
    {
        uint64_t l_loop = _datasize_ * 0.125; //_datasize_ / sizeof(int64_t)
        uint64_t* lp_data = reinterpret_cast<uint64_t*>(_data_);

        for(uint64_t i = 0; i < l_loop; ++i)
        {
            lp_data[i] = (lp_data[i] << 56)
                         |((lp_data[i] & 0x000000000000FF00ULL) << 40)
                         |((lp_data[i] & 0x0000000000FF0000ULL) << 24)
                         |((lp_data[i] & 0x00000000FF000000ULL) << 8)
                         |((lp_data[i] & 0x000000FF00000000ULL) >> 8)
                         |((lp_data[i] & 0x0000FF0000000000ULL) >> 24)
                         |((lp_data[i] & 0x00FF000000000000ULL) >> 40)
                         |((lp_data[i] & 0xFF00000000000000ULL) >> 56);
        };
    };
 
};

