// Pin Assignments

const byte PIN_GPS_RX = 19; //Set the receive port of the gps
const byte PIN_GPS_TX = 18; //Set the transmit port of the gps
const byte PIN_GPS_FIX = 26;
const byte PIN_GPS_EN = 24;

const byte PIN_FLOW_TRIG = 34; // something to do with the flowrate sensor
const byte PIN_FLOW_OUT = 22; // something to do with the flowrate sensor

const byte PIN_SOL1 = 28; //First solenoid - irrigation
const byte PIN_SOL2 = 30; //Second solenoid - dump

const byte PIN_DISPLAY_TX = 14; //transmit to display

const char* PIN_THERM_1 = "A10"; //thermistor 1
const char* PIN_THERM_2 = "A11"; //thermistor 2

//For LCD, these were the defaults
//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
const byte PIN_LCD_RS = 12; 
const byte PIN_LCD_ENABLE = 11;
const byte PIN__LCD_D4 = 5;
const byte PIN__LCD_D5 = 4;
const byte PIN__LCD_D6 = 3;
const byte PIN__LCD_D7 = 2;