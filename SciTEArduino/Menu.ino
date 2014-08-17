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
 * 
addScheduleHour
addScheduleMinute
addScheduleSunday
addScheduleMonday
addScheduleTuesday
addScheduleWednesday
addScheduleThursday
addScheduleFriday
addScheduleSaturday
addScheduleAmount
addScheduleDurationHours
addScheduleDurationMinutes
addScheduleMode
addScheduleOneshot
addScheduleConfirm


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