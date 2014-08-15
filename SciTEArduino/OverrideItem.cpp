#include "OverrideItem.h"
#include "irrigation_types.h"
#include "Time.h"

OverrideItem::OverrideItem(uint8_t j, uint8_t d, time_t t) {
    _job = j;
    _day = d;
    _time = t;
    _itemNumber = _nextItemNumber++;
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

uint16_t OverrideItem::itemNumber()
{
    return _itemNumber;
}

void OverrideItem::setItemNumber(uint16_t n)
{
    _itemNumber = n;
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
    if ( o->itemNumber == _itemNumber )
        return  true;
    return false;
}

bool OverrideItem::operator!= ( OverrideItem o )
{
    if ( o->itemNumber != _itemNumber )
        return true;
    return false;
}

void OverrideItem::_setNextItemNumber(uint16_t n)
{
    _nextItemNumber = n;
}