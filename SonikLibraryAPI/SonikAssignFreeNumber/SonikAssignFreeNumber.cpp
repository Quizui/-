#include <new>
#include "SonikAssignFreeNumber.h"
#include "../Container/RangedForContainer.hpp"
#include "../MathBit/MathBit.h"

namespace SonikLib
{
    SonikAssignFreeNumber::SonikAssignFreeNumber(void)
    :m_NowMaxNumber(0)
    {
        //initialize membar variable only
    };

    SonikAssignFreeNumber::~SonikAssignFreeNumber(void)
    {
        //noprocess
    };

    //Create
    bool SonikAssignFreeNumber::CreateObject(SonikLib::SharedSmtPtr<SonikAssignFreeNumber>& _get_)
    {
        SonikAssignFreeNumber* l_object = new(std::nothrow) SonikAssignFreeNumber;
        if(l_object == nullptr)
        {
            return false;
        };

        //Create bitheader
        if( !SonikLib::Container::SonikVariableArrayContainer<uint64_t>::CreateContainer(l_object->m_bitheader, 1) )
        {
            delete l_object;
            return false;
        };

        if( !SonikLib::Container::SonikVariableArrayContainer<uint64_t>::CreateContainer(l_object->m_bitvalue, 1) )
        {
            delete l_object;
            return false;
        };

        uint64_t l_bitvalue = 0;
        l_object->m_bitheader->PushBack(l_bitvalue);
        l_object->m_bitvalue->PushBack(l_bitvalue);

        _get_.ResetPointer(l_object);
        return true;
    };

    //空き番号の貸出
    //最大値はint64_t型で0x7FFFFFFFFFFFFFFF(実値:9223372036854775807)
    //異常値は負の値
    int64_t SonikAssignFreeNumber::LendNumber(void)
    {
        uint64_t l_header_index = 1; //ヘッダ何周目か？
        int64_t l_header_lsb = 0; //LSB位置

        m_lock.lock();

        SonikLib::Container::SonikVariableArrayContainer<uint64_t>::VACIterator l_itr(m_bitheader->begin());

        while(l_itr != m_bitheader->end())
        {
            l_header_lsb = SonikMathBit::GetZEROLSBFor64bit((*l_itr));
            if(l_header_lsb != -1) //ビット列に0があれば利用可能
            {
                break;
            };

            ++l_header_index;
            ++l_itr;
        };

        //空き番号があればそれを利用
        uint64_t bitvalueindex = (64 * (l_header_index -1)) + l_header_lsb;
        uint64_t ret = SonikMathBit::GetZEROLSBFor64bit((*m_bitvalue)[bitvalueindex]) + (64 * bitvalueindex);

        if(0x7FFFFFFFFFFFFFFF < ret)
        {
            return -1;
        };

        //ビット操作
        (*m_bitvalue)[bitvalueindex] |= static_cast<int64_t>(0b0000000000000000000000000000000000000000000000000000000000000001) << ret;

        //操作の結果ビットがすべて1になったらヘッダのビットを1(配下が満タン)状態にする。
        if( (*m_bitvalue)[bitvalueindex] == 0xFFFFFFFFFFFFFFFF)
        {
            //列のビットをON(1)にしてそこのビット列はすべてONであることを示す。
            (*l_itr) |= static_cast<int64_t>(0b0000000000000000000000000000000000000000000000000000000000000001) << l_header_lsb;
            
            if(m_NowMaxNumber < ret)
            {
                uint64_t l_newvalue =0;
                
                if( (*l_itr) == 0xFFFFFFFFFFFFFFFF)
                {
                    //ヘッダがMAXなら、ヘッダをPushBack
                    m_bitheader->PushBack(l_newvalue);
                };

                //新しいビット列用オブジェクトをPushBack
                m_bitvalue->PushBack(l_newvalue);
            };

        };

        if(m_NowMaxNumber < ret)
        {
            //空き番号最大値更新
            m_NowMaxNumber = ret;
        };

        m_lock.unlock();
        return ret;
    };

    //空き番号の返還
    void SonikAssignFreeNumber::ReturnNumber(int64_t _lendnumber_)
    {
        if(0x7FFFFFFFFFFFFFFF < _lendnumber_)
        {
            return; // 0x7FFFFFFFFFFFFFFF以上の番号は取得させないので何もしない。
        };

        m_lock.lock();

        //返却された番号のフラグ位置を検索
        uint64_t l_bitvalueindex = _lendnumber_ >> 6;
        uint64_t l_headerindex = l_bitvalueindex >> 6;
        uint64_t l_headerbitpoint = (_lendnumber_ - (64 * 64 * l_headerindex)) >> 6;
        
        (*m_bitheader)[l_headerindex] &= ~( static_cast<int64_t>(0b0000000000000000000000000000000000000000000000000000000000000001) << l_headerbitpoint);
        (*m_bitvalue)[l_bitvalueindex] &= ~( static_cast<int64_t>(0b0000000000000000000000000000000000000000000000000000000000000001) << (_lendnumber_ % 64));

        m_lock.unlock();
    };


};