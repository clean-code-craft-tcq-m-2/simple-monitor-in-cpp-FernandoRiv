#include "checker.h"
#ifdef UTEST
#include "checker_test.h"
#endif //UTEST

using namespace std;
using namespace BMSVariables;

bool InMaxRange(float max, variable &value){
  if(max<value.presentValue){
    value.status = variableStatus::High;
  }
  else{
    value.status = variableStatus::Normal;
  }
  return value.status == variableStatus::Normal;;
}

bool InRange(float min, float max, variable &value){
  if(InMaxRange(max, value)){
    if(min>value.presentValue){
      value.status = variableStatus::Low;
    }
  }
  return value.status == variableStatus::Normal;
}

void promptFaultStatus(const variable &value){
  if(value.status != variableStatus::Normal){
    printf("%s %s (%f)\n", value.ID.c_str(), 
      (value.status==variableStatus::High)?"High":"Low", 
       value.presentValue);
  }
}

bool IsTemperatureOk(Temperature &temp){
  bool inRange = InRange(minTemperature, maxTemperature, temp);
  if(!inRange) {
    promptFaultStatus(temp);
  }
  return inRange;
}

bool IsStateOfChargeOk(StateOfCharge &soc){
  bool inRange = InRange(minSOC, maxSOC, soc);
  if(!inRange) {
    promptFaultStatus(soc);
  }
  return inRange;
}

bool IsChargeRateOk(ChargeRate &cRate){
  bool inRange = InMaxRange(maxChargeRate, cRate);
  if(!inRange) {
    promptFaultStatus(cRate);
  }
  return inRange;
}

bool IsBatteryOk(Temperature &temp, StateOfCharge &soc, ChargeRate &cRate) {
  return IsTemperatureOk(temp)&&
         IsStateOfChargeOk(soc)&&
         IsChargeRateOk(cRate);
}

int main() {
  #ifdef UTEST
  runCheckerTests();
  #endif //UTEST
}
