/*
 * Button handling vs selectables (
 
 */
void handleButtonPress(button pressed)
{
    if (currentAction == none) // We're in a menu, behave normally.
    {
        if (pressed == up){ //Move cursor up one position
            if (minor(currentSelection) >= 0){//If minor digit is >= 0, decrement it
                currentSelection--;
                updateDisplay();
            }}
        if (pressed = down){ //Move cursor down one position
            if (inMenu(currentSelection+1)){
                currentSelection++;
                updateDisplay();
            }}
        //ignore left and right presses
        if (pressed = back){ //Move up a level
            if (currentSelection > 10){
                currentSelection %= 10;
                updateDisplay();
            }}
        //Enter handling is more delicate ...
        if (pressed = enter){
            switch (currentSelection)
            {
                case MENU_WATER_NOW:
                    currentSelection = MENU_WATER_NOW * 10;
                    updateDisplay();
                    break;
                case MENU_WATER_UNTIL_BACK:
                    currentAction = waterUntilBack;
                    updateDisplay();
                    break;
                case MENU_WATER_FIXED_TIME:
                    currentAction = waterSetTime;
                    updateDisplay();
                    break;
                case MENU_WATER_FIXED_AMOUNT:
                    currentAction = waterSetAmount;
                    updateDisplay();
                    break;
                case MENU_DUMP_NOW:
                    currentSelection = MENU_DUMP_NOW * 10;
                    break;
                case MENU_DUMP_UNTIL_BACK:
                    currentAction = dumpUntilBack;
                    updateDisplay();
                    break;
                case MENU_DUMP_FIXED_TIME:
                    currentAction = dumpFixedTime;
                    updateDisplay();
                    break;
                case MENU_SYSTEM_STATUS:
                    currentSelection = MENU_SYSTEM_STATUS * 10;
                    break;
                case MENU_NEXT_DATE_TIME:
                    menuNextDateTime();
                    break;
                case MENU_NEXT_TIME_AMOUNT:
                    menuNextTimeAmount();
                    break;
                case MENU_SCHEDULE:
                    currentSelection = MENU_SCHEDULE*10;
                    break;
                case MENU_VIEW_SCHEDULE:
                    menuViewSchedule();
                    break;
                case MENU_EDIT_SCHEDULE:
                    menuEditSchedule();
                    break;
                case MENU_ADD_SCHEDULE:
                    menuAddSchedule();
                    break;
                case MENU_REMOVE_SCHEDULE:
                    menuRemoveSchedule();
                    break;
                case MENU_OVERRIDE_SCHEDULE:
                    menuOverrideSchedule();
                    break;
                case MENU_SCREEN_SETTINGS:
                    currentSelection = MENU_SCREEN_SETTINGS * 10;
                    break;
                case MENU_SCREEN_BRIGHTNESS:
                    menuScreenBrightness();
                    break;
                case MENU_SCREEN_CONTRAST:
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

