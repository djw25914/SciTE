#include "irrigation_types.h"
#include "Time.h"

#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H
class ScheduleItem
{
private:
    bool _oneShot;
    uint8_t _hour;
    uint8_t _minutes;
    bool _days[7]; // Sunday is zero!
    mode dispenseMode;
    uint16_t _amount;  // Minutes for time based, gallons for amount based
    uint16_t _itemNumber;
    static uint16_t _nextItemNumber;

public:
    ScheduleItem(bool oneShot, uint8_t hour, uint8_t minutes, bool &days, mode dispenseMode, uint16_t amount);

    bool oneShot();
    void setOneShot(bool b);

    uint8_t hour();
    void setHour(uint8_t i);

    uint8_t minutes();
    void setMinutes(uint8_t i);

    bool * days();
    void setDays(bool b[7]);

    uint16_t itemNumber();
    void setItemNumber(uint16_t n);

    mode dispenseMode();
    void setDispenseMode(mode m);

    uint16_t amount();
    void setAmount(uint16_t i);

    bool operator== ( ScheduleItem s );
    bool operator!= ( ScheduleItem s );

    static void _setNextItemNumber(uint16_t n);
};

#endif SCHEDULEITEM_H