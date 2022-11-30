#ifndef _CHECKER_H_
#define _CHECKER_H_

static const float minTemperature = 0.0;
static const float maxTemperature = 45.0;
static const float maxChargeRate  = 0.8;
static const float minSOC = 20.0;
static const float maxSOC = 80.0;

bool temperatureCheck(float temperature);
bool stateOfChargeCheck(float SOC);
bool chargeRateCheck(float chargeRate);
bool batteryOk(float temperature, float soc, float chargeRate);

#endif  //_CHECKER_H_