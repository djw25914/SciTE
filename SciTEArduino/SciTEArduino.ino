/* The Arduino software recognizes multiple *.ino files as all belonging to one file, so no need to write includes for them. */

#include <TinyGPS.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ScheduleItem.cpp"
#include "OverrideItem.cpp"
#include "irrigation_types.h"

/* Keep track of where we are */
uint8_t currentSelection = 1;
action currentAction = none;

/* Granularity for the schedules */
uint8_t timeOffset = 5;

TinyGPS gps; // setup GPS from TinyGPS library
#define SerialGPS Serial1
time_t prevDisplay = 0;

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);

ScheduleItem schedule[];
OverrideItem overrides[];

void setup() {
    Serial.begin(9600);
    SerialGPS.begin(4800);
    Serial.println("Wating for GPS time ...");
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

bool isOverridden(uint8_t job, uint8_t day)
{
    // Check for overrides
    for (uint8_t ocnt = 0; ocnt < overrideCount; ++ocnt) {
        if (overrides[ocnt]->job() == job) { // There is an override on this job
            if (overrides[ocnt]->day() == day) { //... on this day
                return true;
            }
        }
    }

    return false;
}

bool nextJob(int & itemNumber, int & dayNumber) //Should be sufficient to find out everything about the job in question
{
    //snapshot of current time
    uint8_t today = today();
    uint8_t hour = hour();
    uint8_t minute = minute();
    time_t now = now();

    time_t lowestTime = now + 691200; //Now + 8 days, can't happen ever.
    uint8_t lowestDay = 255;  //255 > 7 as well.
    uint8_t lowestItem = 255; //Possible, but very unlikely

    for (cnt = 0; cnt < scheduleCount; ++cnt) {
        ScheduleItem item = schedule[cnt];
        bool * days = item->days();
        uint8_t daycnt = today;
        time_t t; //A temporary for keeping track of the lowest time
        uint8_t h; //A temporary for hours
        uint16_t m; // A temporary for minutes

        for (uint8_t daycnt = 0; daycnt < 7; ++daycnt) {
            if (days[daycnt] && isOverridden == 0) {//This schedule runs on day [daycnt]
                if (daycnt == today) {//If it runs today ... could be nearly a week away or later on today
                    if (item->hour() > hour) {//Later on today
                        t = now + item->hour() * 3600 + (item->minute() - minute) * 60;
                    } else if (item->hour() < hour { //nearly a week away
                        t = now + 86400 + (24-(hour-item->hour())) * 3600 + (item->minute() - minute) * 60;
                    } else { //same hour, need to check minutes
                        if (item->minute() > minute) {//Runs in a few minutes
                            t = now + item->minute() * 60;
                        } else {
                            t = now + 601200 + (minute - item->minute()) * 60;
                        }
                    }
                } else if (daycnt > today) {
                    t = ((daycnt - today) * 1440 - (hour*60)+minute + (item->hour()*60)+item->minute()) * 60;
                } else {
                    t = ((daycnt - today + 7) * 1440 - (hour*60)+minute + (item->hour()*60)+item->minute()) * 60;
                }
                if (t < lowestTime) {
                    lowestTime = t;
                    lowestDay = daycnt;
                    lowestItem = cnt;
                }
            } // End of if days[daycnt]
        } //End of inner for
    } //End of outer for
    if (lowestTime < now() + 691200) { //If there was a job
        itemNumber = lowestItem;
        dayNumber = lowestDay;
        return 1
    } else {
        itemNumber = 255;
        dayNumber=255;
        return 0;
    }
}

// // // short currentSubMenuItem = 10; // Set initial startup menu
// // // char* currentMode[] = {"STANDBY", "SCHEDULE", "MANUAL", "ERROR"}; //define Status messages

// // // byte holdStatus, startHour1, startMin1, startHour2, startMin2, waterLength1, waterLength2; //setup global variables for watering

// // // int menuOptions()
// // // {
// // // }

// // // void displayMenu() {
// // //
// // // /*
// // //  * Base items are 1,2,..,n
// // //  * children of 1 are 10,11...,19
// // //  * children of 11 would be 110,111...119
// // //  * etc
// // //  *
// // //  * This is a two line display, on the first line the current menu item will be displayed
// // //  * The second line are the sub-menu options (if applicable)
// // //  */
// // //
// // //   lcd.setCursor(0, 0);
// // //
// // //   /* Let say you were on item 110, and you hit the back button, divide by ten to get out a level so you would be back to 11
// // //    * you would multiply by ten to go in a menu level. */
// // //   switch (currentSubMenuItem / 10) {
// // //     /* Do we really want people roaming the menus freely??
// // //        Roaming menus doesn't bother me, but changing schedule, putting it on hold or using manual mode should probably have some security, sure. -Tim
// // //     */
// // //     case 1: // System Menu
// // //       lcd.print("System Menu");
// // //       displaySubMenu();
// // //     case 10:
// // //       lcd.print("System Status");
// // //       displaySubMenu();
// // //       break;
// // //     case 11:
// // //       lcd.print("Schedule");
// // //       displaySubMenu();
// // //       break;
// // //     default:
// // //       break;
// // //   }
// // //
// // // }

// // // void setup() {   // put your setup code here, to run once:
// // //   Serial.begin(9600);
// // //   SerialGPS.begin(4800);
// // //   Serial.println("Waiting for GPS time ... ");
// // //
// // //   lcd.begin(16, 2);
// // //   holdStatus = 0;
// // //   startHour1 = 7;
// // //   startMin1 = 0;
// // //   waterLength1 = 0;
// // //   startHour1 = 19;
// // //   startMin1 = 0;
// // //   waterLength2 = 0;
// // // }

// // // void displaySubMenu() {
// // //   lcd.setCursor(0, 1); //First spot on the second line
// // //   switch (currentSubMenuItem) {
// // //     case 10:
// // //       lcd.print("System Status");
// // //       break;
// // //     case 11:
// // //       lcd.print("Schedule");
// // //       break;
// // //     case 12:
// // //       lcd.print("Manual Mode");
// // //       break;
// // //     case 100:
// // //       lcd.print("Mode: " + currentMode[3]);
// // //       break;
// // //     case 101:
// // //       lcd.print("Date/Time");
// // //       break;
// // //     case 110:
// // //       lcd.print("Add Schedule");
// // //       break;
// // //     case 111:
// // //       lcd.print("View Schedule");
// // //       break;
// // //     case 112:
// // //       lcd.print("Edit Schedule");
// // //       break;
// // //     case 113:
// // //       lcd.print("Remove Schedule");
// // //       break;
// // //     case 114:
// // //       lcd.print("Hold: " + holdStatus);
// // //       break;
// // //     default:
// // //       break;
// // //   }
// // // }