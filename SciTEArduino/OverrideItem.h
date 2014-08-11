
#include "irrigation_types.h" 
#include "Time.h"

#ifndef OVERRIDEITEM_H
#define OVERRIDEITEM_H
class OverrideItem
{
private:
    uint8_t _job;
    uint8_t _day;
public:
    OverrideItem(uint8_t job, uint8_t day);
    uint8_t job();
    void setJob(uint8_t i);

    uint8_t day();
    void setDay(uint8_t);
    
    time_t time();
    void setTime(time_t t);
};

#endif