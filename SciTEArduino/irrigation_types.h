#ifndef IRRIGATION_TYPES_H
#define IRRIGATION_TYPES_H

/* Enumerated type for buttons and actions for convenience */
enum button{up,down,left,right,enter,back};
enum action{none, gettingTime, watering, waterSetTimeMenu, waterSetAmountMenu, waterSetAmount, dumping, dumpSetTimeMenu, editSchedule, addSchedule, overrideSchedule, removeSchedule, adjustBrightness, adjustContrast};
enum mode{none,manual,time,amount};
char* dayStrings[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#endif