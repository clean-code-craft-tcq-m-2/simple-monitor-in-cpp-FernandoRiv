#include <iostream>
#include <assert.h>
#include "checker_test.h"

using namespace std;
using namespace BMSVariables;

void temperatureCheck_test(){
  cout<< "Temperature tests: START" <<endl;

  // Minimum normal temperature allowed
  Temperature temp;
  temp.m_presentValue = minTemperature + temp.m_warnThreshholdTolerance + 0.1;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.m_status == variableStatus::Normal);

  // Maximum normal temperature allowed
  temp.m_presentValue = maxTemperature - temp.m_warnThreshholdTolerance - 0.1;
  assert(IsTemperatureOk(temp) == true);
  assert(temp.m_status == variableStatus::Normal);

  // Low temperature error
  temp.m_presentValue = minTemperature - 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.m_status == variableStatus::Low);

  // High temperature error
  temp.m_presentValue = maxTemperature + 0.1;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.m_status == variableStatus::High);

  // Low temperature warning
  temp.m_presentValue = minTemperature + temp.m_warnThreshholdTolerance;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.m_status == variableStatus::LowWarn);

  // High temperature warning
  temp.m_presentValue = maxTemperature - temp.m_warnThreshholdTolerance;
  assert(IsTemperatureOk(temp) == false);
  assert(temp.m_status == variableStatus::HighWarn);

  cout<< "Temperature Check tests: END, success!" <<endl<<endl;
}

void stateOfChargeCheck_test(){
  cout<< "State of Charge tests: START" <<endl;

  // Minimum normal soc allowed
  StateOfCharge soc;
  soc.m_presentValue = minSOC + soc.m_warnThreshholdTolerance + 0.1;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.m_status == variableStatus::Normal);

  // Maximum normal soc allowed
  soc.m_presentValue = maxSOC - soc.m_warnThreshholdTolerance - 0.1;
  assert(IsStateOfChargeOk(soc) == true);
  assert(soc.m_status == variableStatus::Normal);

  // Low soc error
  soc.m_presentValue = minSOC - 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.m_status == variableStatus::Low);

  // High soc error
  soc.m_presentValue = maxSOC + 0.1;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.m_status == variableStatus::High);

  // Low soc warning
  soc.m_presentValue = minSOC + soc.m_warnThreshholdTolerance;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.m_status == variableStatus::LowWarn);

  // High soc warning
  soc.m_presentValue = maxSOC - soc.m_warnThreshholdTolerance;
  assert(IsStateOfChargeOk(soc) == false);
  assert(soc.m_status == variableStatus::HighWarn);

  cout<< "State of Charge tests: END, success!" <<endl<<endl;
}

void chargeRateCheck_test(){
  cout<< "Charge Rate Check tests: START" <<endl;

  // Normal charge rate
  ChargeRate cRate;
  cRate.m_presentValue = maxChargeRate - cRate.m_warnThreshholdTolerance - 0.1;
  assert(IsChargeRateOk(cRate) == true);
  assert(cRate.m_status == variableStatus::Normal);

  // High charge rate error
  cRate.m_presentValue = maxChargeRate + maxChargeRate/100;
  assert(IsChargeRateOk(cRate) == false);
  assert(cRate.m_status == variableStatus::High);

  // High charge rate warning
  cRate.m_presentValue = maxChargeRate - cRate.m_warnThreshholdTolerance\
                         + maxChargeRate/100;
  assert(IsChargeRateOk(cRate) == false);
  assert(cRate.m_status == variableStatus::HighWarn);

  cout<< "Charge Rate Check tests: END, success!" <<endl<<endl;
}

void prompt_test(){
  cout<< "Prompt tests: START" <<endl;

  char buffer[100];
  Temperature temp;
  temp.m_status = variableStatus::High;
  faultStatusFormat(buffer, temp);
  string evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::TEMPERATURE))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::ERROR))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::HIGH))!=string::npos);

  temp.m_status = variableStatus::Low;
  faultStatusFormat(buffer, temp);
  evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::TEMPERATURE))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::ERROR))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::LOW))!=string::npos);

  temp.m_status = variableStatus::HighWarn;
  faultStatusFormat(buffer, temp);
  evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::TEMPERATURE))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::WARNING))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::HIGH))!=string::npos);

  temp.m_status = variableStatus::LowWarn;
  faultStatusFormat(buffer, temp);
  evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::TEMPERATURE))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::WARNING))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::LOW))!=string::npos);

  StateOfCharge soc;
  soc.m_status = variableStatus::LowWarn;
  faultStatusFormat(buffer, soc);
  evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::SOC))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::WARNING))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::LOW))!=string::npos);

  ChargeRate cRate;
  cRate.m_status = variableStatus::High;
  faultStatusFormat(buffer, cRate);
  evaluatedPrompt = string(buffer);
  assert(evaluatedPrompt.find(getString(stringID::CHARGERATE))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::ERROR))!=string::npos);
  assert(evaluatedPrompt.find(getString(stringID::HIGH))!=string::npos);

  cout<< "Prompt tests: END, success!" <<endl<<endl;
}

void batteryOk_test(){
  cout<< "Battery tests: START" <<endl;

  // Battery OK scenario
  Temperature temp;
  temp.m_presentValue = minTemperature + temp.m_warnThreshholdTolerance + 0.1;
  StateOfCharge soc;
  soc.m_presentValue = minSOC + soc.m_warnThreshholdTolerance + 0.1;
  ChargeRate cRate;
  cRate.m_presentValue = maxChargeRate - 0.1;
  assert(IsBatteryOk(temp, soc, cRate) == true);

  // Wrong Temperature scenario
  temp.m_presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong SOC scenario
  temp.m_presentValue++;
  soc.m_presentValue--;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  // Wrong Charge Rate scenario
  soc.m_presentValue++;
  cRate.m_presentValue++;
  assert(IsBatteryOk(temp, soc, cRate) == false);

  cout<< "Battery tests: END, success!" <<endl<<endl;
}

void runCheckerTests(){
  temperatureCheck_test();
  stateOfChargeCheck_test();
  chargeRateCheck_test();
  batteryOk_test();
  prompt_test();
}