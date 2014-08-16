
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

public:
    OverrideItem(uint8_t job, uint8_t day);
    uint8_t job();
    void setJob(uint8_t i);

    uint8_t day();
    void setDay(uint8_t);

    uint8_t id();
    time_t time();
    void setTime(time_t t);
    bool operator== ( OverrideItem o );
    bool operator!= ( OverrideItem o );
};

#endif