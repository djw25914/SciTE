#include <TinyGPS.h>
#include <Time.h>
#include <TimeAlarms.h>
#include <LiquidCrystal.h>

int currentSubMenuItem = 10; // Set initial startup menu
char* currentMode[] = {"STANDBY", "SCHEDULE", "MANUAL", "ERROR"}; //define Status messages

int holdStatus, startHour1, startMin1, startHour2, startMin2, waterLength1, waterLength2; //setup global variables for watering
int offset = 5;

TinyGPS gps; // setup GPS from TinyGPS library
#define SerialGPS Serial1
time_t prevDisplay = 0;

//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {   // put your setup code here, to run once:
  Serial.begin(9600);
  SerialGPS.begin(4800);
  Serial.println("Waiting for GPS time ... ");
  
  lcd.begin(16, 2);
  holdStatus = 0;
  startHour1 = 7;
  startMin1 = 0;
  waterLength1 = 0;
  startHour1 = 19;
  startMin1 = 0;
  waterLength2 = 0;
}

void loop() { // put your main code here, to run repeatedly:
  Alarm.timerRepeat(3600, getGPSTime);
  //as things are currently, there are only 2 jobs - a morning job and an evening job, these jobs are run every day.
  //they run at times defined by the variables listed.
  Alarm.alarmRepeat(startHour1,startMin1,0,water1);
  Alarm.alarmRepeat(startHour2,startMin2,0,water2);
  displayMenu();
}



/*
 * On View/Edit/Override Schedule, a format similar to this to discern scheudles:
  SM-W--F- 10:00AM
  Note: Th for Thursday, others are single char
*/ 

/* 
  *********************************************
  * 
  * 
  * Proposed menu structure
  * 
  * 1) Water Now (manual mode)
  *    10) Water until stop is pressed
  *    11) Water for set amount of time
  *    12) Water with set amount of water 
  * 2) System Status 
  *    20) When is next Watering?
  *    21) How long will next Watering run?
  * 3) Menu
  *    30) View Schedule
  *    31) Edit Schedule
  *        //A list of schedules in the format depicted above, each selectable by pressing enter, else back button to go back
  *        Enable/Disable Option 
  *    32) One Time Item (volatile)
  *       // Time 
  *       // - Hour (1-12) byte
  *       // - Minute (00,15,30,45) (byte)
  *       // - AM / PM (enum)
  *       // One of Sunday-Saturday 
  *       // Amount or Duration (enum)
  *       // - Amount (Add 5 gallons to the amount to compensate for volume of hose/pipe)
  *       // - - tens place (byte)
  *       // - - ones place (byte)
  *       // - Duration
  *       // - - Hours (byte)
  *       // - - Minutes (00,15,30,45) (or maybe 5 minute intervals?)
  *       // Confirm (not available till prior are set
  *       // Cancel 
  *    33) Add Schedule
  *       // Time
  *       // - Hour (1-12) (byte)
  *       // - Minute (00,15,30,45) (byte)
  *       // - AM / PM (enum)
  *       // Sunday Monday Tuesday Wednesday Thursday Friday Saturday (boolean)
  *       // Amount or Duration (enum)
  *       // - Amount (Add 5 gallons to the amount to compensate for volume of hose/pipe)
  *       // - - tens place (byte)
  *       // - - ones place (byte)
  *       // - Duration
  *       // - - Hours (byte)
  *       // - - Minutes (00,15,30,45) (or maybe 5 minute intervals?)
  *       // Confirm (not available till prior are set
  *       // Cancel
  *    34) Remove Schedule
  *       // List of items in previously mentioned format, selectable by enter button
  *       //  - Confirmation nag popup
  *       // Cancel 
  *    35) Override (don't run a particular item on a particular day)
  *       // Select schedule similar to Remove Schedule
  *       // Select Day(s)
  * 4) Screen Settings
  *    40) Screen Brightness (Byte)
  *    41) Screen Contrast (Byte)
  * 
  * ****************************************/



void displayMenu() {
   
/* 
 * Base items are 1,2,..,n 
 * children of 1 are 10,11...,19
 * children of 11 would be 110,111...119 
 * etc
 * 
 * This is a two line display, on the first line the current menu item will be displayed
 * The second line are the sub-menu options (if applicable)
 */

  lcd.setCursor(0, 0);
  
  /* Let say you were on item 110, and you hit the back button, divide by ten to get out a level so you would be back to 11
   * you would multiply by ten to go in a menu level. */
  switch (currentSubMenuItem / 10) {
    /* Do we really want people roaming the menus freely?? */
    case 1: // System Menu
      lcd.print("System Menu");
      displaySubMenu();
    case 10:
      lcd.print("System Status");
      displaySubMenu();
      break;
    case 11:
      lcd.print("Schedule");
      displaySubMenu();
      break;
    default:
      break;
  }

}


void displaySubMenu() {
  lcd.setCursor(0, 1); //First spot on the second line
  switch (currentSubMenuItem) {
    case 10:
      lcd.print("System Status");
      break;
    case 11:
      lcd.print("Schedule");
      break;
    case 12:
      lcd.print("Manual Mode");
      break;
    case 100:
      lcd.print("Mode: " + currentMode[3]);
      break;
    case 101:
      lcd.print("Date/Time");
      break;
    case 110:
      lcd.print("Add Schedule");
      break;
    case 111:
      lcd.print("View Schedule");
      break;
    case 112:
      lcd.print("Edit Schedule");
      break;
    case 113:
      lcd.print("Remove Schedule");
      break;
    case 114:
      lcd.print("Hold: " + holdStatus);
      break;
    default:
      break;
  }
}

/*
 * Button handling vs selectables (
 
 */
