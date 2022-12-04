#include <iostream>
#include <assert.h>
#include "checker_test.h"

using namespace std;
using namespace BMSVariables;

void temperatureCheck_test(){
  cout<< "Temperature Check tests: START" <<endl;

  // Minimum temperature allowed
  Temperature temp;
  temp.m_presentValue = minTemperature;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::Normal);

  // Maximum temperature allowed
  temp.m_presentValue = maxTemperature;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::Normal);

  // Low temperature error
  temp.m_presentValue = minTemperature - 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.status == variableStatus::Low);

  // High temperature error
  temp.m_presentValue = maxTemperature + 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.status == variableStatus::High);

  // Low temperature warning
  temp.m_presentValue = minTemperature + maxTemperature*\
                        temp.m_warnThreshholdRatio;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::LowWarn);

  // High temperature warning
  temp.m_presentValue = maxTemperature - maxTemperature*\
                        temp.m_warnThreshholdRatio;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::HighWarn);

  cout<< "Temperature Check tests: END, success!" <<endl;
}

void stateOfChargeCheck_test(){
  cout<< "State of charge Check tests: START" <<endl;

  // Minimum soc allowed
  StateOfCharge soc;
  soc.m_presentValue = minSOC;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::Normal);

  // Maximum soc allowed
  soc.m_presentValue = maxSOC;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::Normal);

  // Low soc error
  soc.m_presentValue = minSOC - 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.status == variableStatus::Low);

  // High soc error
  soc.m_presentValue = maxSOC + 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.status == variableStatus::High);

  // Low soc warning
  soc.m_presentValue = minSOC + maxSOC*soc.m_warnThreshholdRatio;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::LowWarn);

  // High soc warning
  soc.m_presentValue = maxSOC - maxSOC*soc.m_warnThreshholdRatio;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::HighWarn);

  cout<< "State of charge Check tests: END, success!" <<endl;
}

void chargeRateCheck_test(){
  cout<< "Charge Rate Check tests: START" <<endl;

  // Normal charge rate
  ChargeRate cRate;
  cRate.m_presentValue = maxChargeRate;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.status == variableStatus::Normal);

  // Low charge rate error
  cRate.m_presentValue = maxChargeRate - 0.1;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.status == variableStatus::Normal);

  // High charge rate error
  cRate.m_presentValue = maxChargeRate + 0.1;
  assert(IsChargeRateOk(cRate) == false);
  assert(cRate.status == variableStatus::High);

  // High charge rate warning
  cRate.m_presentValue = maxChargeRate - maxChargeRate*\
                         cRate.m_warnThreshholdRatio;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.status == variableStatus::HighWarn);

  cout<< "Charge Rate Check tests: END, success!" <<endl;
}

void batteryOk_test(){
  cout<< "Battery tests: START" <<endl;

  // Battery OK scenario
  Temperature temp;
  temp.m_presentValue = minTemperature;
  StateOfCharge soc;
  soc.m_presentValue = minSOC;
  ChargeRate cRate;
  cRate.m_presentValue = maxChargeRate;
  assert(IsBatteryOk(temp, soc, cRate) == true);

  // Wrong Temperature scenario
  temp.m_presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong SOC scenario
  temp.m_presentValue++;
  soc.m_presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong Charte Rate scenario
  soc.m_presentValue++;
  cRate.m_presentValue++;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  cout<< "Battery tests: END, success!" <<endl;
}

void runCheckerTests(){
  temperatureCheck_test();
  stateOfChargeCheck_test();
  chargeRateCheck_test();
  batteryOk_test();
}