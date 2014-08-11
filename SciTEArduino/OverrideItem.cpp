#include "OverrideItem.h"
#include "irrigation_types.h"
#include "Time.h"

OverrideItem::OverrideItem(uint8_t j, uint8_t d, time_t t) {
    _job = j;
    _day = d;
    _time = t;
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
    void setTime(time_t t);