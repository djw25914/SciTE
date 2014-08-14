
//Menu option constants, because using the numbers directly could be a headache later ...
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
const char* MENU_TEXTS[MENU_LENGTH] = {
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


/*
 * On View/Edit/Override Schedule, a format similar to this to discern scheudles:
 S M-W--F- 10:00AM                           *
 Note: Th for Thursday, others are single char
 */ 

/* 
 * ********************************************
 * 
 * 
 * Proposed menu structure
 * 
 * 1) Water Now (manual mode)
 *    10) Water until back is pressed
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
 *       // - - Minutes (00,15,30,45) (or maybe 5 minute uint16_tervals?)
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
 *       // - - Minutes (00,15,30,45) (or maybe 5 minute uint16_tervals?)
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