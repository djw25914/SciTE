#include "OverrideItem.h"
#include "irrigation_types.h"
#include "Time.h"

OverrideItem::OverrideItem(uint8_t j, uint8_t d, time_t t) {
    _job = j; // Corresponds to ScheduleItem itemNumber
    _day = d; // Day that override takes place
    _time = t; // Absolute Start time of the job (relative to epoch)
}

uint8_t OverrideItem::job() {
    return _job;
}
void OverrideItem::setJob(uint8_t j) {
    _job = j;
}

uint8_t OverrideItem::day() {
    return _day;
}
void OverrideItem::setDay(uint8_t d) {
    _day = d;
}


time_t OverrideItem::time() {
    return _time;
}
void OverrideItem::setTime(time_t t)
{
    _time = t;
}

bool OverrideItem::operator== ( OverrideItem o )
{
    if (o->time() == _time)
    )
        return  true;
    return false;
}

bool OverrideItem::operator!= ( OverrideItem o )
{
    if ( o->time != _time )
        return true;
    return false;
}