#include <iostream>
#include <assert.h>
#include "checker_test.h"

using namespace std;

void temperatureCheck_test(){
  cout<< "Temperature Check tests: START" <<endl;
  assert(temperatureCheck(minTemperature) == true);
  assert(temperatureCheck(maxTemperature) == true);
  assert(temperatureCheck(minTemperature - 0.1) == false);
  assert(temperatureCheck(maxTemperature + 0.1) == false);
  cout<< "Temperature Check tests: END, success!" <<endl;
}

void stateOfChargeCheck_test(){
  cout<< "State of charge Check tests: START" <<endl;
  assert(stateOfChargeCheck(minSOC) == true);
  assert(stateOfChargeCheck(maxSOC) == true);
  assert(stateOfChargeCheck(minSOC - 0.1) == false);
  assert(stateOfChargeCheck(maxSOC + 0.1) == false);
  cout<< "State of charge Check tests: END, success!" <<endl;
}

void chargeRateCheck_test(){
  cout<< "Charge Rate Check tests: START" <<endl;
  assert(chargeRateCheck(maxChargeRate) == true);
  assert(chargeRateCheck(maxChargeRate - 0.1) == true);
  assert(chargeRateCheck(maxChargeRate + 0.1) == false);
  cout<< "Charge Rate Check tests: END, success!" <<endl;
}

void batteryOk_test(){
  assert(batteryOk(25, 70, 0.7) == true);
  assert(batteryOk(50, 85, 0) == false);
}

void runCheckerTests(){
  temperatureCheck_test();
  stateOfChargeCheck_test();
  chargeRateCheck_test();
  batteryOk_test();
}