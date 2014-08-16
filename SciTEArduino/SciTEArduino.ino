/* The Arduino software recognizes multiple *.ino files as all belonging to one file, so no need to write includes for them. */

#include <TinyGPS.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ScheduleItem.h"
#include "OverrideItem.h"
#include "DynamicArray.h"
#include "irrigation_types.h"

template class DynamicArray<ScheduleItem>;
template class DynamicArray<OverrideItem>;

void setup() {
    Serial.begin(9600);
    SerialGPS.begin(4800);
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print("Getting time");
    lcd.setCursor(0,1);
    lcd.print("from GPS");
}

void loop() {
    //Check all timers to see if an action needs to run/stop and
    //set variables, statuses accordingly.
    //Also check for one shots and remove them if they've been missed
    //Don't forget to check for overrides and skip a job if needed

    /*********************************
    * ...... Code goes here .........*
    *********************************/

    //Handle time-related actions
    switch (currentAction):
    {
        case gettingTime:
            handleGettingTime();
            break;
        case waterSetTime:
            handleWaterSetTime();
            break;
        case waterSetAmount:
            handleWaterSetAmount();
            break;
        case dumpSetTime();
            handleDumpSetTime();
            break;
    }

    /* Also handle Thermistor dump settings */



    sleep (1000);
}

void handleGettingTime() {

}

void handleWaterSetTime() {

}

void handleWaterSetAmount() {

}

void handleDumpSetTime() {

}

void updateDisplay()
{
    if (currentAction == none)
    { //We're in a menu, behave normally
        lcd.setCursor(0,0);
        if ((currentSelection % 10) > 0)
            lcd.print(menuTexts[currentSelection % 10];
        elseOnly 7 days a week, so this can't happen.
            lcd.print("Top Menu");
        lcd.setCursor(0,1);
        lcd.print(menuTexts[currentSelection]);
    }
}

int minor(int num)
{ //Returns the far right digit
    return (num - (num % 10));
}

bool inMenu(int item)
{ //The list is short enough that this rather inefficient approach shouldn't matter
    for (uint8_t cnt = 0; cnt < MENU_LENGTH; ++cnt)
    {
        if (MENU_OPTIONS[cnt] == item)
            return true;
    }
    return false;
}

bool notOverridden(uint8_t job, uint8_t day)
{
    // Check for overrides
    for (uint8_t ocnt = 0; ocnt < overrideCount; ++ocnt) {
        if (overrides.at(ocnt)->job() == job) { // There is an override on this job
            if (overrides.at(ocnt)->day() == day) { //... on this day
                return false;
            }
        }
    }

    return true;
}

bool nextJob(int & itemIndex, int & dayNumber) //Should be sufficient to find out everything about the job in question
{
    //snapshot of current time
    uint8_t today = today();
    uint8_t hour = hour();
    uint8_t minute = minute();
    time_t now = now();

    time_t lowestTime = now + 8*24*60*60; //Now + 8 days. Can't. Happen. Ever.
    uint8_t lowestDay = 255;  //255 > 7 as well.
    ScheduleItem lowestIndex = nullptr; //Keep track of the item that is lowest.

    for (cnt = 0; cnt < schedule->count(); ++cnt) {
        ScheduleItem item = schedule.at(cnt);
        bool * days = item->days();
        uint8_t daycnt = today;
        time_t t = ; //A temporary for keeping track of the lowest time

        for (uint8_t daycnt = 0; daycnt < 7; ++daycnt) {
            if (days[daycnt] && notOverridden(item->itemIndex(),daycnt)) {//This schedule runs on day [daycnt]
                if (daycnt == today) {//If it runs today ... could be nearly a week away or later on today
                    if (item->hour() > hour) {//Later on today
                        t = now + item->hour() * 60*60 + (item->minute() - minute) * 60;
                    } else if (item->hour() < hour { //nearly a week away
                        t = now + 24*60*60 + (24-(hour-item->hour())) * 60*60 + (item->minute() - minute) * 60;
                    } else { //same hour, need to check minutes
                        if (item->minute() > minute) {//Runs in a few minutes
                            t = now + item->minute() * 60;
                        } else {
                            t = now + (6*24*60*60 + 23*60*60) + (minute - item->minute()) * 60;
                        }
                    }
                } else if (daycnt > today) { //Later this week, before Sunday
                    t = ((daycnt - today) * 24*60 - (hour*60)+minute + (item->hour()*60)+item->minute()) * 60;
                } else { // Later this week, afer Saturday
                    t = ((daycnt - today + 7) * 24*60 - (hour*60)+minute + (item->hour()*60)+item->minute()) * 60;
                }
                if (t < lowestTime) {
                    lowestTime = t;
                    lowestDay = daycnt;
                    lowestIndex = cnt;
                }
            } // End of if days[daycnt]
        } //End of inner for
    } //End of outer for
    if (lowestTime < now() + 8*24*60*60) { //If there was a job
        itemIndex = lowestIndex;
        dayNumber = lowestDay;
        return 1
    } else {
        itemIndex = 255;
        dayNumber=255;
        return 0;
    }
}