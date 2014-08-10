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

const char* PIN_THERM_1 = "A10"; //thermistor 1
const char* PIN_THERM_2 = "A11"; //thermistor 2

//For LCD, these were the defaults
//LiquidCrystal(rs, enable, d4, d5, d6, d7) 
const uint8_t PIN_LCD_RS = 12; 
const uint8_t PIN_LCD_ENABLE = 11;
const uint8_t PIN__LCD_D4 = 5;
const uint8_t PIN__LCD_D5 = 4;
const uint8_t PIN__LCD_D6 = 3;
const uint8_t PIN__LCD_D7 = 2;