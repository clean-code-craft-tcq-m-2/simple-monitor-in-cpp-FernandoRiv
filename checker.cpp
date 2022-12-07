#include "checker.h"
#ifdef UTEST
#include "checker_test.h"
#endif //UTEST

using namespace std;
using namespace BMSVariables;

// Language environment variable
languageID currentLanguage = languageID::English;

bool variable::InMaxRange(){
  if(m_highThreshhold<m_presentValue){
    m_status = variableStatus::High;
  }
  else if((m_highThreshhold-m_warnThreshholdTolerance)<=\
            m_presentValue){
    m_status = variableStatus::HighWarn;
  }
  else{
    m_status = variableStatus::Normal;
  }
  return m_status == variableStatus::Normal;
}

bool variable::InMinRange(){
  if(m_lowThreshhold>m_presentValue){
    m_status = variableStatus::Low;
  }
  else if((m_lowThreshhold + m_warnThreshholdTolerance)>=\
            m_presentValue){
    m_status = variableStatus::LowWarn;
  }
  else{
    // Normal assignment handled in Max range evalation
    // hence, do nothing
  }
  return m_status == variableStatus::Normal;
}

bool variable::InRange(){
  return (InMaxRange() && InMinRange());
}

void setStringIfNormal(stringID &retVal, variableStatus status){
  if(variableStatus::Normal == status)
    retVal = stringID::NORMAL;
}

void setStringIfHigh(stringID &retVal, variableStatus status){
  if(variableStatus::High     == status ||
     variableStatus::HighWarn == status)
    retVal = stringID::HIGH;
}

void setStringIfLow(stringID &retVal, variableStatus status){
  if(variableStatus::Low     == status ||
     variableStatus::LowWarn == status)
    retVal = stringID::LOW;
}

void setStringIfError(stringID &retVal, variableStatus status){
  if(variableStatus::High == status ||
     variableStatus::Low  == status)
    retVal = stringID::ERROR;
}

void setStringIfWarning(stringID &retVal, variableStatus status){
  if(variableStatus::HighWarn == status ||
     variableStatus::LowWarn  == status)
    retVal = stringID::WARNING;
}

stringID getStatusHighLowString(variableStatus status){
  stringID retVal = stringID::UNKNOWN;
  setStringIfNormal(retVal, status);
  setStringIfHigh(retVal, status);
  setStringIfLow(retVal, status);
  return retVal;
}

stringID getStatusNotificationString(variableStatus status){
  stringID retVal = stringID::UNKNOWN;
  setStringIfNormal(retVal, status);
  setStringIfError(retVal, status);
  setStringIfWarning(retVal, status);
  return retVal;
}

std::string getString(stringID str){
  return strIndexer.at(str).at(currentLanguage);
}

void faultStatusFormat(char* buffer, const variable &value){
  if(value.m_status != variableStatus::Normal){
    // e.g. Breach, Temperature: High (something)
    sprintf(buffer, "%s, %s: %s (%f)\n",
            getString(getStatusNotificationString(value.m_status)).c_str(),
            getString(value.m_ID).c_str(),
            getString(getStatusHighLowString(value.m_status)).c_str(),
            value.m_presentValue);
  }
}

void promptFaultStatus(const variable &value){
  char buffer[100];
  faultStatusFormat(buffer, value);
  printf("%s", buffer);
}

bool IsTemperatureOk(Temperature &temp){
  bool inRange = temp.InRange();
  if(!inRange) {
    promptFaultStatus(temp);
  }
  return inRange;
}

bool IsStateOfChargeOk(StateOfCharge &soc){
  bool inRange = soc.InRange();
  if(!inRange) {
    promptFaultStatus(soc);
  }
  return inRange;
}

bool IsChargeRateOk(ChargeRate &cRate){
  bool inRange = cRate.InMaxRange();
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
