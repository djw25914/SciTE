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
  Alarm.alarmRepeat(startHour1,startMin1,0,water1);
  Alarm.alarmRepeat(startHour2,startMin2,0,water2);
  displayMenu();
}

void displayMenu() {
  lcd.setCursor(0, 0);
  switch (currentSubMenuItem / 10) {
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
  lcd.setCursor(0, 1);
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

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}



