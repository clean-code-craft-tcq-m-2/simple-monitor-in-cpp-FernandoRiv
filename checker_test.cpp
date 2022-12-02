#include <iostream>
#include <assert.h>
#include "checker_test.h"

using namespace std;
using namespace BMSVariables;

void temperatureCheck_test(){
  cout<< "Temperature Check tests: START" <<endl;
  
  // Minimum temperature check
  Temperature temp;
  temp.presentValue = minTemperature;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::Normal);

  // Maximum temperature check
  temp.presentValue = maxTemperature;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.status == variableStatus::Normal);

  // Low temperature check
  temp.presentValue = minTemperature - 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.status == variableStatus::Low);

  // High temperature check
  temp.presentValue = maxTemperature + 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.status == variableStatus::High);

  cout<< "Temperature Check tests: END, success!" <<endl;
}

void stateOfChargeCheck_test(){
  cout<< "State of charge Check tests: START" <<endl;
  
  // Minimum soc check
  StateOfCharge soc;
  soc.presentValue = minSOC;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::Normal);

  // Maximum soc check
  soc.presentValue = maxSOC;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.status == variableStatus::Normal);

  // Low soc check
  soc.presentValue = minSOC - 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.status == variableStatus::Low);
  
  // High soc check
  soc.presentValue = maxSOC + 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.status == variableStatus::High);

  cout<< "State of charge Check tests: END, success!" <<endl;
}

void chargeRateCheck_test(){
  cout<< "Charge Rate Check tests: START" <<endl;

  // Normal charge rate
  ChargeRate cRate;
  cRate.presentValue = maxChargeRate;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.status == variableStatus::Normal);

  // Low charge rate
  cRate.presentValue = maxChargeRate - 0.1;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.status == variableStatus::Normal);

  // High charge rate
  cRate.presentValue = maxChargeRate + 0.1;
  assert(IsChargeRateOk(cRate) == false);
  assert(cRate.status == variableStatus::High);

  cout<< "Charge Rate Check tests: END, success!" <<endl;
}

void batteryOk_test(){
  cout<< "Battery tests: START" <<endl;

  // Battery OK scenario
  Temperature temp;
  temp.presentValue = minTemperature;
  StateOfCharge soc;
  soc.presentValue = minSOC;
  ChargeRate cRate;
  cRate.presentValue = maxChargeRate;
  assert(IsBatteryOk(temp, soc, cRate) == true);

  // Wrong Temperature scenario
  temp.presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong SOC scenario
  temp.presentValue++;
  soc.presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong Charte Rate scenario
  soc.presentValue++;
  cRate.presentValue++;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  cout<< "Battery tests: END, success!" <<endl;
}

void runCheckerTests(){
  temperatureCheck_test();
  stateOfChargeCheck_test();
  chargeRateCheck_test();
  batteryOk_test();
}