// Get the time from the GPS device

void getGPSTime(){
  while (SerialGPS.available()) {
    if (gps.encode(SerialGPS.read())) { // process gps messages
      // when TinyGPS reports new data...
      uint32_t long age;
      uint16_t int Year;
      uint8_t Month, Day, Hour, Minute, Second;
      gps.crack_datetime(&Year, &Month, &Day, &Hour, &Minute, &Second, NULL, &age);
      if (age < 500) { // 500 milliseconds, presumably
        // set the Time to the latest GPS reading
        setTime(Hour, Minute, Second, Day, Month, Year);
        adjustTime(offset * SECS_PER_HOUR); // where is SECS_PER_HOUR ... probably a library, perhaps timegps library
      }
    }
  }
  if (timeStatus()!= timeNotSet) {
    if (now() != prevDisplay) { //update the display only if the time has changed
      prevDisplay = now();
      //digitalClockDisplay();  
    }
  }
}
