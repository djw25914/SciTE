#include "ScheduleItem.h"

bool ScheduleItem::oneShot() {
    return _oneShot;
}

void ScheduleItem::setOneShot(bool b) {
    _oneShot = b;
}
uint8_t ScheduleItem::hour() {
    //If we correct in the clock, we won't have to correct *everywhere* else. Expect the system clock is set to *local time*
    return _hour;
}
void ScheduleItem::setHour(uint8_t i) {
    _hour = i;
}
uint8_t ScheduleItem::minutes() {
    return _minutes;
}
void ScheduleItem::setMinutes(uint8_t i) {
    _minutes = i;
}
bool * ScheduleItem::days() { //Expects to be assigned to a bool *!!
    return _days;
}
void ScheduleItem::setDays(bool b[7]) { //Expects a bool * passed in!!
    for (int cnt = 0; cnt < 7; ++cnt) {
        _days[cnt] = b[cnt];
    }
}
bool ScheduleItem::timeMode()
{ //If we're going by time, then yes, else no
    return _timeMode;
}
void ScheduleItem::setTimeMode(bool b) {
    _timeMode = b;
}
uint16_t ScheduleItem::amount() {
    return _amount;
}
void ScheduleItem::setAmount(uint16_t i) {
    _amount = i;
}