class ScheduleItem
{
private:
    bool _oneShot;
    uint8_t _hour;
    uint8_t _minutes;
    bool _days[7]; // Sunday is zero!
    bool _timeMode;    // 1 for time based, 0 for amount based
    uint16_t _amount;  // Minutes for time based, gallons for amount based
public:
    bool oneShot();
    void setOneShot(bool b);

    uint8_t hour();
    void setHour(uint8_t i);

    uint8_t minutes();
    void setMinutes(uint8_t i);
    
    bool * days();
    void setDays(bool b[7]);
    
    bool timeMode();
    void setTimeMode(bool b);

    uint16_t amount();
    void setAmount(uint16_t i);
};