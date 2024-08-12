//0～連番で番号を排出し、管理します。
//返却された番号が最大値より前にあればそれを返却します。

#ifndef __SONIK_ASSIGN_FEEE_NUMBER_CLASS_HEADER__
#define __SONIK_ASSIGN_FEEE_NUMBER_CLASS_HEADER__

#include <stdint.h>
#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../SonikCAS/SonikAtomicLock.h"

//前方宣言
namespace SonikLib
{
	namespace Container
	{
		template <class T>
		class SonikVariableArrayContainer;
    };
};


namespace SonikLib
{
    class SonikAssignFreeNumber
    {
    private:
        uint64_t m_NowMaxNumber;
        SonikLib::S_CAS::SonikAtomicLock m_lock;
        SonikLib::SharedSmtPtr<SonikLib::Container::SonikVariableArrayContainer<uint64_t>> m_bitheader;
        SonikLib::SharedSmtPtr<SonikLib::Container::SonikVariableArrayContainer<uint64_t>> m_bitvalue;

    private:
        SonikAssignFreeNumber(const SonikAssignFreeNumber& _copy_) = delete;
        SonikAssignFreeNumber(SonikAssignFreeNumber&& _copy_) = delete;
        SonikAssignFreeNumber& operator =(const SonikAssignFreeNumber& _copy_) = delete;
        SonikAssignFreeNumber& operator =(SonikAssignFreeNumber&& _copy_) = delete;

        SonikAssignFreeNumber(void);

    public:
        ~SonikAssignFreeNumber(void);
        static bool CreateObject(SonikLib::SharedSmtPtr<SonikAssignFreeNumber>& _get_);

        //空き番号の貸出
        //最大値はint64_t型で0x7FFFFFFFFFFFFFFF(実値:9223372036854775807)
        //異常値は負の値
        int64_t LendNumber(void);

        //空き番号の返還
        void ReturnNumber(int64_t _lendnumber_);

    };


};



#endif //__SONIK_ASSIGN_FEEE_NUMBER_CLASS_HEADER__