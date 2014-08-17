/*
 * Button handling vs selectables (

 */
void handleButtonPress(button pressed)
{
    switch (currentAction)
    {
        // Handling the button pressed is dependent on which action is currently being performed, so
        // Call the appropriate function.
        case none:                                          // We're in the main menu
            handleButtonPressedNoneAction(pressed);
            break;
        case gettingTime:                                   // Ignore button presses when getting time
            break;
        case watering:                                      // We're currently watering
            handleButtonPressedWatering(pressed);
            break;
        case waterSetTimeMenu:                              // We're currently in the Water-By-Time special menu
            handleButtonPressedXByTimeMenu(pressed, false);
            break;
        case waterSetAmountMenu:                            // We're currently in the Water-By-Volume special menu
            handleButtonPressedWaterByVolumeMenu(pressed);
            break;
        case dumping:                                       // We're currently dumping
            handleButtonPressedDumping(pressed);
            break;
        case dumpSetTimeMenu:                               // We're currently in the Dump-By-time special menu
            handleButtonPressedXByTimeMenu(pressed, true);
            break;
        case editSchedule:                                  // We're currently in the Edit Schedule special menu
            handleButtonPressedEditScheduleMenu(pressed);
            break;
        case addSchedule:                                   // We're currently in the Add Schedule special menu
            handleButtonPressedAddScheduleMenu(pressed);
            break;
        case removeSchedule:                                // We're currently in the Remove Schedule special menu
            handleButtonPressedRemoveScheduleMenu(pressed);
            break;
        case overrideSchedule:                              // We're currently in the Override Schedule special menu
            handleButtonPressedOverrideScheduleMenu(pressed);
            break;
        case adjustBrightness:                              // We're currently in the Adjust Brightness special menu
            handleButtonPressedAdjustBrightness(pressed);
            break;
        case adjustContrast:                                // We're currently in the Adjust Contrast special menu
            handleButtonPressedAdjustContrast(pressed);
            break;
    }
    updateDisplay();
}

void handleButtonPressNoneAction(button pressed)
{
    //We're in the main menu
    if (pressed == upButton){                               //Move cursor up one position
        if (minor(mainMenu.currentSelection) > 0){               //If minor digit is > 0, decrement it
            --mainMenu.currentSelection;
          }}
    if (pressed == downButton){                         //Move cursor down one position
        if (inMenu(mainMenu.currentSelection+1)){                //make sure +1 is an option
            ++mainMenu.currentSelection;
          }}
    //ignore left and right presses
    if (pressed == backButton){                         // Move up a level
        if (mainMenu.currentSelection > 10){                     // If <10, already the top level menu, do nothing
            mainMenu.currentSelection %= 10;
          }}

    //Enter handling is more delicate ...
    if (pressed == enterButton){
        switch (mainMenu.currentSelection)
        {
            case MENU_WATER_NOW:                        // Enter into the Watering submenu
                mainMenu.currentSelection = mainMenu.MENU_WATER_NOW * 10;
                break;
            case MENU_WATER_UNTIL_BACK:                 // Bring up the screen for watering until back is pressed
                currentAction = watering;
                currentMode = manualMode;
                endTime = now() + 60*60*3;              // End after 3 hours regardless whether back has been pressed..., in case somebody forgets. to stop it.
                break;
            case MENU_WATER_FIXED_TIME:                 // Bring up the special menu for a waterering by time
                currentAction = waterSetTimeMenu;
                break;
            case MENU_WATER_FIXED_AMOUNT:               // Bring up the special menu for watering by volume
                currentAction = waterSetAmountMenu;
                break;
            case MENU_DUMP_NOW:                         // Enter into the Dumping submenu
                mainMenu.currentSelection = mainMenu.MENU_DUMP_NOW * 10;
                break;
            case MENU_DUMP_UNTIL_BACK:                  // Bring up the screen for dumping until back is pressed
                currentAction = dumping;
                currentMode = manualMode;
                break;
            case MENU_DUMP_FIXED_TIME:                  // Bring up the special menu for dumping by time
                currentAction = dumpFixedTimeMenu;
                break;
            case MENU_SYSTEM_STATUS:                    // Enter into the System Status submenu
                mainMenu.currentSelection = mainMenu.MENU_SYSTEM_STATUS * 10;
                break;
            case MENU_NEXT_DATE_TIME:                   // Display screen that shows date/time of next watering
                menuNextDateTime();
                break;
            case MENU_NEXT_TIME_AMOUNT:                 // Display screen that shows volume/timelimit of next watering
                menuNextTimeAmount();
                break;
            case MENU_SCHEDULE:                         // Enter into the Schedule submenu
                mainMenu.currentSelection = mainMenu.MENU_SCHEDULE*10;
                break;
            case MENU_VIEW_SCHEDULE:                    // Bring up the view schedule screen
                menuViewSchedule();
                break;
            case MENU_EDIT_SCHEDULE:                    // Bring up the edit schedule screen
                menuEditSchedule();
                break;
            case MENU_ADD_SCHEDULE:                     // Bring up the add schedule screen
                addScheduleMenu.currentSelection = 1;
                menuAddSchedule();
                break;
            case MENU_REMOVE_SCHEDULE:                  // Bring up the remove schedule screen
                generateRemoveScheduleOptions();
                if 
                menuRemoveSchedule();
                break;
            case MENU_OVERRIDE_SCHEDULE:                // Bring up the override schedule screen
                menuOverrideSchedule();
                break;
            case MENU_SCREEN_SETTINGS:                  // Enter into the Screen Settings submenu
                mainMenu.currentSelection = MENU_SCREEN_SETTINGS * 10;
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

void menuNextDateTime() {
    uint8_t itemIndex;
    uint8_t dayNumber;

    if ( nextJob(itemIndex, dayNumber))
    {
        item = schedule.at(itemIndex);
        uint8_t h = item->hour();
        uint8_t m = item->minute();

        lcd.setCursor(0,0);
        lcd.print(dayStrings[dayNumber]);
        lcd.setCursor(0,1);
        lcd.print(h + ":" + m);
    }
}

void handleButtonPressedWatering(pressed) {
    // Handles button presses that occur while the system is irrigating
    if (pressed == backButton) {
        //Abort watering
        closeSolenoid(WATERING_SOLENOID);
    }
    currentAction = none;
    currentMode = none;
    endTime = 0;
    volumeRemaining = 0;
}

void handleButtonPressedXByTimeMenu(button pressed, bool dumping) {
    if ( pressed == upButton )
    {
        xByTimeMenu.hour++;
    }
    else if ( pressed == rightButton )
    {
        xByTimeMenu.minute += TIME_OFFSET;
    }
    else if ( pressed == downButton)
    {
        xByTimeMenu.hour -= 1;
    }
    else if ( pressed == leftButton )
    {
        xByTimeMenu.minute -= TIME_OFFSET;
    }
    else if ( pressed == backButton )
    {
        currentAction = none;
    }
    else if ( pressed == enterButton )
    {
        if ( xByTimeMenu.hour > 0 || xByTimeMenu.minute > 0 )
        {
            if (dumping)
                currentAction = dumping;
            else
                currentAction = watering;
            currentMode = timeMode;
            endTime = now() + xByTimeMenu.hour * 60*60 + xByTimeMenu.minute * 60;
        }
    }
}

void handleButtonPressedWaterByVolumeMenu(button pressed) {
    if (pressed == leftButton )
    {
        if ( waterByVolumeMenu.amount > 0 )
        {
            waterByVolumeMenu.amount -= 5;
        }
    }
    else if ( pressed == rightButton )
    {
        if ( waterByVolumeMenu.amount < 999 )
        {
            waterByVolumeMenu.amount += 5;
        }
    }
    else if ( pressed == backButton )
    {
        currentAction = noneAction;
    }
    else if ( pressed == enterbutton )
    {
        volumeRemaining = 3785.41 * waterByVolumeMenuAmount; //Convert to milliliters
        currentAction = watering;
        currentMode = amountMode;
    }
}

void handleButtonPressedDumping(button pressed) {

    //Handles button presses that occur while the system is dumping
    if (pressed == backButton)
    {
        closeSolenoid(DUMPING_SOLENOID);
        currentAction = none;
        currentMode = none;
        endTime = 0;
    }
}

void handleButtonPressedEditScheduleMenu(button pressed) {
    /*Edit schedule menu has a list of current schedule items, this:
    * ---- moves up and down within that list
    * ---- selects an item for editing
    * ---- or cancels/goes back
    */
    
    if ( pressed == backButton )
    {
        currentAction = none;
        editScheduleMenu.currentSelection = 0;
    }
    else if ( pressed == upButton && editScheduleMenu.currentSelection > 1)
    {
        --editScheduleMenu.currentSelection;
    }
    else if ( pressed == downButton && (editScheduleMenu.currentSelection < editScheduleMenu.count)
    {
        ++currentSelectionEditScheduleMenu;
    }
    else if ( pressed = enterButton && editScheduleMenu.currentSelection > 0 )
    {
        /// /// /// Implement me later. Needs to remove the current schedule item, and then bring up the Add Schedule menu with the same settings as before
        // Gather current settings
        bool oneShot = schedule.at(editScheduleMenu.currentSelection)->oneShot();
        uint8_t hour = schedule.at(editScheduleMenu.currentSelection)->hour();
        uint8_t minutes = schedule.at(editScheduleMenu.currentSelection)->minutes();
        bool * days = schedule.at(editScheduleMenu.currentSelection)->days(); 
        mode dispenseMode = schedule.at(editScheduleMenu.currentSelection)->dispenseMode();
        uint16_t amount = schedule.at(editScheduleMenu.currentSelection)->amount();
        // Remove this item
        schedule.remove(currentSelectionEditScheduleMenu)  
        // Enter the add menu with current settings
        addScheduleMenu.oneShot = oneShot;
        addScheduleMenu.hour = hour;
        addScheduleMenu.minutes = minutes;
        for (int i = 0; i <  7; ++i)
            addScheduleMenu.days[i] = days[i];
        addScheduleMenu.dispenseMode = dispenseMode;
        addScheduleMenu.amount = amount;
        addScheduleMenu.currentSelection = 1;
        currentAction = addSchedule;
    }
}

void handleButtonPressedAddScheduleMenu(button pressed) {
    if ( pressed == backButton )
    {
        addScheduleMenu.reset();
        currentAction = none;
    }
    else if ( pressed == upButton )
    {
        if ( addScheduleMenu.currentSelection > 1 )
        {
            --addScheduleMenu.currentSelection;
        }
    }
    else if ( pressed == downButton )
    {
        if ( addScheduleMenu.currentSelection < addScheduleMenu.MENU_LENGTH)
            ++addScheduleMenu.currentSelection;
    }
    else if ( pressed == leftButton )
    {
        switch (addScheduleMenu.currentSelection)
        {
            case addScheduleMenu.MENU_HOUR:
                addScheduleMenu.hour = (24 + addScheduleMenu.hour - 1) % 24;
                break;
            case addScheduleMenu.MENU_MINUTE:
                addScheduleMenu.minute = (60 + addScheduleMenu.minute - TIME_OFFSET) % 60;
                break;
            case addScheduleMenu.MENU_SUNDAY:
                addScheduleMenu.days[0] = (2 + addScheduleMenu.days[0] - 1) % 2;
                break;
            case addScheduleMenu.MENU_MONDAY:
                addScheduleMenu.days[1] = (2 + addScheduleMenu.days[1] - 1) % 2;
                break;
            case addScheduleMenu.MENU_TUESDAY:
                addScheduleMenu.days[2] = (2 + addScheduleMenu.days[2] - 1) % 2;
                break;
            case addScheduleMenu.MENU_WEDNESDAY:
                addScheduleMenu.days[3] = (2 + addScheduleMenu.days[3] - 1) % 2;
                break;
            case addScheduleMenu.MENU_THURSDAY:
                addScheduleMenu.days[4] = (2 + addScheduleMenu.days[4] - 1) % 2;
                break;
            case addScheduleMenu.MENU_FRIDAY:
                addScheduleMenu.days[5] = (2 + addScheduleMenu.days[5] - 1) % 2;
                break;
            case addScheduleMenu.MENU_SATURDAY:
                addScheduleMenu.days[6] = (2 + addScheduleMenu.days[6] - 1) % 2;
                break;
            case addScheduleMenu.MENU_AMOUNT:
                if (addScheduleMenu.amount > 0)
                    addScheduleMenu.amount = addScheduleMenu.amount - TIME_OFFSET;
            case addScheduleMenu.MENU_MODE:=
                if (addScheduleMenu.mode == timeMode)
                    addScheduleMenu.mode = amountMode;
                else
                    addScheduleMenu.mode = timeMode;
            case addScheduleMenu.ONE_SHOT:
                addScheduleMenu.oneShot = (2 + addScheduleMenu.oneShot - 1) % 2;
        }
    }
    else if ( pressed == rightButton )
    {
        switch (addScheduleMenu.currentSelection)
        {
            case addScheduleMenu.MENU_HOUR:
                addScheduleMenu.hour = (addScheduleMenu.hour + 1) % 24;
                break;
            case addScheduleMenu.MENU_MINUTE:
                addScheduleMenu.minute = (addScheduleMenu.minute + TIME_OFFSET) % 60;
                break;
            case addScheduleMenu.MENU_SUNDAY:
                addScheduleMenu.days[0] = (addScheduleMenu.days[0] + 1) % 2;
                break;
            case addScheduleMenu.MENU_MONDAY:
                addScheduleMenu.days[1] = (addScheduleMenu.days[1] + 1) % 2;
                break;
            case addScheduleMenu.MENU_TUESDAY:
                addScheduleMenu.days[2] = (addScheduleMenu.days[2] + 1) % 2;
                break;
            case addScheduleMenu.MENU_WEDNESDAY:
                addScheduleMenu.days[3] = (addScheduleMenu.days[3] + 1) % 2;
                break;
            case addScheduleMenu.MENU_THURSDAY:
                addScheduleMenu.days[4] = (addScheduleMenu.days[4] + 1) % 2;
                break;
            case addScheduleMenu.MENU_FRIDAY:
                addScheduleMenu.days[5] = (addScheduleMenu.days[5] + 1) % 2;
                break;
            case addScheduleMenu.MENU_SATURDAY:
                addScheduleMenu.days[6] = (addScheduleMenu.days[6] + 1) % 2;
                break;
            case addScheduleMenu.MENU_AMOUNT:
                if (addScheduleMenu.amount > 0)
                    addScheduleMenu.amount = addScheduleMenu.amount - TIME_OFFSET;
            case addScheduleMenu.MENU_MODE:=
                if (addScheduleMenu.dispenseMode == timeMode)
                    addScheduleMenu.dispenseMode = amountMode;
                else
                    addScheduleMenu.mode = timeMode;
            case addScheduleMenu.ONE_SHOT:
                addScheduleMenu.oneShot = (addScheduleMenu.oneShot + 1) % 2;
        }
    }
    else if ( pressed == enterButton )
    {
        if (addScheduleMenu.amount > 0 && 
            (addScheduleMenu.days[0] ||
             addScheduleMenu.days[1] ||
             addScheduleMenu.days[2] ||
             addScheduleMenu.days[3] ||
             addScheduleMenu.days[4] ||
             addScheduleMenu.days[5] ||
             addScheduleMenu.days[6]))
        {
            // Everything seems okay, add a schedule item

            ScheduleItem::ScheduleItem(bool oneShot, uint8_t hour, uint8_t minutes, bool &days, mode dispenseMode, uint16_t amount) {
          
            ScheduleItem t = new ScheduleItem(addScheduleMenu.oneShot, addScheduleMenu.hour, addScheduleMenu.minutes, addScheduleMenu.days, addScheduleMenu.dispenseMode, addScheduleMenu.amount);
            schedule.add(t);
            addScheduleMenu.reset();
            currentAction=none;
        }
    }
}

void handleButtonPressedRemoveScheduleMenu(button pressed) {

}

void handleButtonPressedOverrideScheduleMenu(button pressed) {

}

void generateScheduleOptions()
{
    for (int i = 0; i < schedule->count(); ++i )
    {
        String schedule = 
    }
}