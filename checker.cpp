#include <iostream>
#include "checker.h"
#ifdef UTEST
#include "checker_test.h"
#endif //UTEST

using namespace std;

bool InRange(float min, float max, float value){
  if(value < min || value > max){
    return false;
  }
  return true;
}

bool InRange(float max, float value){
  if(value > max){
    return false;
  }
  return true;
}

bool temperatureCheck(float temperature){
  bool inRange = InRange(minTemperature, maxTemperature, temperature);
  if(!inRange) {
    cout << "Temperature out of range!\n";
  }
  return inRange;
}

bool stateOfChargeCheck(float SOC){
  bool inRange = InRange(minSOC, maxSOC, SOC);
  if(!inRange) {
    cout << "State of Charge out of range!\n";
  }
  return inRange;
}

bool chargeRateCheck(float chargeRate){
  bool inRange = InRange(maxChargeRate, chargeRate);
  if(!inRange) {
    cout << "Charge Rate out of range!\n";
  }
  return inRange;
}

bool batteryOk(float temperature, float soc, float chargeRate) {
  return temperatureCheck(temperature)&&
         stateOfChargeCheck(soc)&&
         chargeRateCheck(chargeRate);
}

int main() {
  runCheckerTests();
}
