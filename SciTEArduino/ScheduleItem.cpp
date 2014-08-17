#include "ScheduleItem.h"
#include "irrigation_types.h"
#include "Time.h"

ScheduleItem::ScheduleItem(bool oneShot, uint8_t hour, uint8_t minutes, bool &days, mode dispenseMode, uint16_t amount) {
    _oneShot = oneShot;
    _hours = hours;
    _minutes = minutes;
    for (int i = 0; i < 7; ++i)
        _days[i] = days[i]; // Sunday is zero thru Saturday is 6
    mode dispenseMode;
    _amount = amount;  // Minutes for time based, gallons for amount based
    _itemNumber = _nextItemNumber++;
}

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
bool ScheduleItem::dispenseMode()
{ //If we're going by time, then yes, else no
    return _dispenseMode;
}
void ScheduleItem::setDispenseMode(mode m) {
    _dispenseMode = m;
}
uint16_t ScheduleItem::amount() {
    return _amount;
}
void ScheduleItem::setAmount(uint16_t i) {
    _amount = i;
}

uint16_t ScheduleItem::itemNumber()
{
    return _itemNumber;
}

void ScheduleItem::_setNextItemNumber(uint16_t n)
{
    _nextItemNumber = n;
}

bool ScheduleItem::operator== ( ScheduleItem s )
{
    if ( s->itemNumber() == _itemNumber)
        return true;
    return false;
}

bool ScheduleItem::operator!= ( ScheduleItem s )
{
    if ( s->itemNumber() == _itemNumber )
        return true;
    return false;
}