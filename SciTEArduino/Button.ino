/*
 * Button handling vs selectables (

 */
void handleButtonPress(button pressed)
{
    if (currentAction == none)                              // We're in a menu, behave normally.
    {
        if (pressed == upButton){                           //Move cursor up one position
            if (minor(currentSelection) > 0){               //If minor digit is > 0, decrement it
                --currentSelection;
                updateDisplay();
            }}
        if (pressed == downButton){                         //Move cursor down one position
            if (inMenu(currentSelection+1)){                //make sure +1 is an option
                ++currentSelection;
                updateDisplay();
            }}
        //ignore left and right presses
        if (pressed == backButton){                         // Move up a level
            if (currentSelection > 10){                     // If <10, already the top level menu, do nothing
                currentSelection %= 10;
                updateDisplay();
            }}

        //Enter handling is more delicate ...
        if (pressed == enterButton){
            switch (currentSelection)
            {
                case MENU_WATER_NOW:                        // Enter into the Watering submenu
                    currentSelection = MENU_WATER_NOW * 10;
                    updateDisplay();
                    break;
                case MENU_WATER_UNTIL_BACK:                 // Bring up the screen for watering until back is pressed
                    currentAction = waterUntilBackMenu;
                    updateDisplay();
                    break;
                case MENU_WATER_FIXED_TIME:                 // Bring up the special menu for a waterering by time
                    currentAction = waterSetTimeMenu;
                    updateDisplay();
                    break;
                case MENU_WATER_FIXED_AMOUNT:               // Bring up the special menu for watering by volume
                    currentAction = waterSetAmount;
                    updateDisplay();
                    break;
                case MENU_DUMP_NOW:                         // Enter into the Dumping submenu
                    currentSelection = MENU_DUMP_NOW * 10;
                    break;
                case MENU_DUMP_UNTIL_BACK:                  // Bring up the screen for dumping until back is pressed
                    currentAction = dumpUntilBack;
                    updateDisplay();
                    break;
                case MENU_DUMP_FIXED_TIME:                  // Bring up the special menu for dumping by time
                    currentAction = dumpFixedTime;
                    updateDisplay();
                    break;
                case MENU_SYSTEM_STATUS:                    // Enter into the System Status submenu
                    currentSelection = MENU_SYSTEM_STATUS * 10;
                    break;
                case MENU_NEXT_DATE_TIME:                   // Display screen that shows date/time of next watering
                    menuNextDateTime();
                    break;
                case MENU_NEXT_TIME_AMOUNT:                 // Display screen that shows volume/timelimit of next watering
                    menuNextTimeAmount();
                    break;
                case MENU_SCHEDULE:                         // Enter into the Schedule submenu
                    currentSelection = MENU_SCHEDULE*10;
                    break;
                case MENU_VIEW_SCHEDULE:                    // Bring up the view schedule screen
                    menuViewSchedule();
                    break;
                case MENU_EDIT_SCHEDULE:                    // Bring up the edit schedule screen
                    menuEditSchedule();
                    break;
                case MENU_ADD_SCHEDULE:                     // Bring up the add schedule screen
                    menuAddSchedule();
                    break;
                case MENU_REMOVE_SCHEDULE:                  // Bring up the remove schedule screen
                    menuRemoveSchedule();
                    break;
                case MENU_OVERRIDE_SCHEDULE:                // Bring up the override schedule screen
                    menuOverrideSchedule();
                    break;
                case MENU_SCREEN_SETTINGS:                  // Enter into the Screen Settings submenu
                    currentSelection = MENU_SCREEN_SETTINGS * 10;
                    break;
                case MENU_SCREEN_BRIGHTNESS:                // Bring up the Alter Screen Brightness screen
                    menuScreenBrightness();
                    break;
                case MENU_SCREEN_CONTRAST:                  // Bring up the Alter Screen Contrast Screen
                    menuScreenContrast();
                    break;
            }
        }
    }
}

menuNextDateTime() {
    uint8_t itemNumber;
    uint8_t dayNumber;

    if (nextJob(itemNumber, dayNumber))
    {
        lcd.setCursor(0,0);
        lcd.print(dayStrings[dayNumber]);
        lcd.setCursor(0,1);
        lcd.print(
    }
}

