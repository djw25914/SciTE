// Globals.ino
// Global constants and such are all defined in this file.
// Enumerated types are not defined here because they may be needed in classes as well.
// Pin Assignments

const uint8_t PIN_GPS_RX = 19; //Set the receive port of the gps
const uint8_t PIN_GPS_TX = 18; //Set the transmit port of the gps
const uint8_t PIN_GPS_FIX = 26;
const uint8_t PIN_GPS_EN = 24;

const uint8_t PIN_FLOW_TRIG = 34; // something to do with the flowrate sensor
const uint8_t PIN_FLOW_OUT = 22; // something to do with the flowrate sensor

const uint8_t PIN_SOL1 = 28; //First solenoid - irrigation
const uint8_t PIN_SOL2 = 30; //Second solenoid - dump

const uint8_t PIN_DISPLAY_TX = 14; //transmit to display

const String PIN_THERM_1 = "A10"; //thermistor 1
const String PIN_THERM_2 = "A11"; //thermistor 2

//For LCD, these were the defaults
//LiquidCrystal(rs, enable, d4, d5, d6, d7)
const uint8_t PIN_LCD_RS = 12;
const uint8_t PIN_LCD_ENABLE = 11;
const uint8_t PIN__LCD_D4 = 5;
const uint8_t PIN__LCD_D5 = 4;
const uint8_t PIN__LCD_D6 = 3;
const uint8_t PIN__LCD_D7 = 2;






/* Granularity for the schedules */
uint8_t TIME_OFFSET = 5; // (minutes)
const bool WATERING_SOLENOID=0;
const bool DUMPING_SOLENOID=1;






TinyGPS gps; // setup GPS from TinyGPS library
#define SerialGPS Serial1
time_t prevDisplay = 0;

LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_ENABLE, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7);







//Schedule and Overrides
DynamicArray<ScheduleItem> schedule = new DynamicArray<ScheduleItem>();
DynamicArray<OverrideItem> overrides = new DynamicArray<OverrideItem>();






//Action related variables
action currentAction = none;  // Tracks which menu or action is active
mode currentMode = none;      // When watering/dumping, this tells whether it's by time or by volume
time_t endTime;               // When watering/dumping, this is the end time
double volumeRemaining = 0;   // When watering by volume, this is the amount of water yet to be dispensed (mL)

//Menu related temporaries
double waterByVolumeMenuAmount = 0;

typedef struct {
    uint8_t hour = 0;
    uint8_t minute = 0;
} xByTimeMenu;

// Struct containing data pertaining to mainMenu
typedef struct {
    const uint8_t MENU_WATER_NOW = 1;
        const uint8_t MENU_WATER_UNTIL_BACK = 10;
        const uint8_t MENU_WATER_FIXED_TIME = 11;
        const uint8_t MENU_WATER_FIXED_AMOUNT = 12;
    const uint8_t MENU_DUMP_NOW = 2;
        const uint8_t MENU_DUMP_UNTIL_BACK = 20;
        const uint8_t MENU_DUMP_FIXED_TIME = 21;
    const uint8_t MENU_SYSTEM_STATUS=3;
        const uint8_t MENU_NEXT_DATE_TIME=30;
        const uint8_t MENU_NEXT_TIME_AMOUNT=31;
    const uint8_t MENU_SCHEDULE=4;
        const uint8_t MENU_VIEW_SCHEDULE=40;
        const uint8_t MENU_EDIT_SCHEDULE=41;
        const uint8_t MENU_ADD_SCHEDULE=42;
        const uint8_t MENU_REMOVE_SCHEDULE=43;
        const uint8_t MENU_OVERRIDE_SCHEDULE=44;
    const uint8_t MENU_SCREEN_SETTINGS=5;
        const uint8_t MENU_SCREEN_BRIGHTNESS=50;
        const uint8_t MENU_SCREEN_CONTRAST=51;

    //Should be equal to the number of constants declared immediately above
    const uint8_t MENU_LENGTH=19;

    //An array of menu options, handy for use with the "in" function
    const uint8_t MENU_OPTIONS[MENU_LENGTH]
    {
        MENU_WATER_NOW ,
            MENU_WATER_UNTIL_BACK ,
            MENU_WATER_FIXED_TIME ,
            MENU_WATER_FIXED_AMOUNT ,
        MENU_DUMP_NOW,
            MENU_DUMP_UNTIL_BACK,
            MENU_DUMP_FIXED_TIME,
        MENU_SYSTEM_STATUS,
            MENU_NEXT_DATE_TIME,
            MENU_NEXT_TIME_AMOUNT,
        MENU_SCHEDULE,
            MENU_VIEW_SCHEDULE,
            MENU_EDIT_SCHEDULE,
            MENU_ADD_SCHEDULE,
            MENU_REMOVE_SCHEDULE,
            MENU_OVERRIDE_SCHEDULE,
        MENU_SCREEN_SETTINGS,
            MENU_SCREEN_BRIGHTNESS,
            MENU_SCREEN_CONTRAST
    }

    //Text of each menu option
    const String MENU_TEXTS[MENU_LENGTH] = {
        "Water Now",
            "Manual Operation",
            "Fixed Time",
            "Fixed Volume",
        "Dump Now",
            "Manual Dump"
            "Dump Time"
        "System Status",
            "Next Date/Time",
            "Next Amount/Time",
        "Schedule",
            "View Schedule",
            "Edit Schedule",
            "Add Item",
            "Remove Item",
            "Temp Override",
        "Screen Settings",
            "Screen Brightness",
            "Screen Contrast"
    }
    
    uint8_t currentSelection = 1; // Current selection in main menu

} mainMenu;


// Struct containing data pertaining to waterByVolumeMenu
typedef struct {
    uint16_t amount = 0;
} waterByVolumeMenu;


/* Struct containing data pertaining to addSchedule */
typedef struct
{
    uint8_t currentSelection = 0;
    
    uint8_t hour = 0;               // 0-23
    uint8_t minute;                 // 0-60
    bool days[7] = {1,1,1,1,1,1,1}; // 7 days a week
    uint16_t amount;                // Amount, gallons..
    mode dispenseMode = timeMode;           // timeMode or amountMode 
    bool oneshot = 0;                    // Runs once (true) or many (false)

    uint8_t MENU_HOUR = 1;
    uint8_t MENU_MINUTE = 2;
    uint8_t MENU_SUNDAY = 3;
    uint8_t MENU_MONDAY = 4;
    uint8_t MENU_TUESDAY = 5;
    uint8_t MENU_WEDNESDAY = 6;
    uint8_t MENU_THURSDAY = 7;
    uint8_t MENU_FRIDAY = 8;
    uint8_t MENU_SATURDAY = 9;
    uint8_t MENU_AMOUNT = 10;
    uint8_t MENU_MODE = 11;
    uint8_t MENU_ONESHOT = 12;

    uint8_t MENU_LENGTH = 12;
    const uint8_t MENU_OPTIONS[MENU_LENGTH] = {
        MENU_HOUR,
        MENU_MINUTE,
        MENU_SUNDAY,
        MENU_MONDAY,
        MENU_TUESDAY,
        MENU_WEDNESDAY,
        MENU_THURSDAY,
        MENU_FRIDAY,
        MENU_SATURDAY,
        MENU_AMOUNT,
        MENU_MODE,
        MENU_ONESHOT
    };
    
    const String MENU_TEXTS[MENU_LENGTH] = {
        "Hour",
        "Minute",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Amount",
        "Mode",
        "OneShot",
    };
    
    void reset()
    {
        currentSelection = 0;
        hour = 0;
        minute = 0;
        for (uint8_t i = 0; i < 7; ++i)
            days[i] = 0;
        amount = 0;
        dispenseMode = timeMode;
        oneShot = 0;
    }
    
} addScheduleMenu;
/* Struct containing data pertaining to editScheduule */
typedef struct
{
    uint8_t currentSelection = 0;
} editScheduleMenu;