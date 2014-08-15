
#include "irrigation_types.h"
#include "Time.h"

#ifndef OVERRIDEITEM_H
#define OVERRIDEITEM_H
class OverrideItem
{
private:
    uint8_t _job;
    uint8_t _day;
    uint8_t _id;
    uint16_t _itemNumber;
    static  uint16_t _nextItemNumber;

public:
    OverrideItem(uint8_t job, uint8_t day);
    uint8_t job();
    void setJob(uint8_t i);

    uint8_t day();
    void setDay(uint8_t);

    uint16_t itemNumber();
    void setItemNumber(uint16_t n);

    static void _setNextItemNumber(uint16t n);

    uint8_t id();
    time_t time();
    void setTime(time_t t);
    bool operator== ( OverrideItem o );
    bool operator!= ( OverrideItem o );
};

#endif