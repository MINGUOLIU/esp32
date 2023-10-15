#ifndef PUMP_H
#define PUMP_H

#include "config.h"

class Pump
{
public:
    Pump();
    void begin();
    void on();
    void off();

    bool _isOn;
};

#endif
