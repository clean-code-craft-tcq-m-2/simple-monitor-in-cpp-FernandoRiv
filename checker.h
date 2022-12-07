#ifndef _CHECKER_H_
#define _CHECKER_H_

#include <iostream>
#include "checkerTypes.h"

namespace BMSVariables{
  extern const float minTemperature;
  extern const float maxTemperature;
  extern const float maxChargeRate;
  extern const float minSOC;
  extern const float maxSOC;
  extern const float tempTolerancePercent;
  extern const float socTolerancePercent;
  extern const float cRateTolerancePercent;
  extern const stringIndexer strIndexer;

  class variable{
    public:

    variable();
    variable(const stringID id = stringID::UNKNOWN,
             float lowThreshhold  = 0.0,
             float highThreshhold = 0.0,
             float warnThreshPercent = 0.0):
      m_ID{id},
      m_lowThreshhold{lowThreshhold},
      m_highThreshhold{highThreshhold},
      m_warnThreshholdTolerance{warnThreshPercent}
      {
        m_warnThreshholdTolerance = m_highThreshhold*\
                                    m_warnThreshholdTolerance/100;
      };

    ~variable(){};

    bool InMaxRange();
    bool InMinRange();
    bool InRange();

    stringID m_ID;
    variableStatus m_status = variableStatus::Normal;
    float m_presentValue = 0.0;
    float m_lowThreshhold;
    float m_highThreshhold;
    float m_warnThreshholdTolerance;
  };

  class Temperature : public virtual variable{
    public:
    Temperature():variable(stringID::TEMPERATURE, minTemperature,
                           maxTemperature, tempTolerancePercent){};
  };

  class StateOfCharge : public virtual variable{
    public:
    StateOfCharge():variable(stringID::SOC, minSOC, maxSOC,
                             socTolerancePercent){};
  };

  class ChargeRate : public virtual variable{
    public:
    ChargeRate():variable(stringID::CHARGERATE, 0.0, maxChargeRate,
                          cRateTolerancePercent){};
  };
}

bool IsTemperatureOk(BMSVariables::Temperature&);
bool IsStateOfChargeOk(BMSVariables::StateOfCharge&);
bool IsChargeRateOk(BMSVariables::ChargeRate&);
bool IsBatteryOk(BMSVariables::Temperature&,
                 BMSVariables::StateOfCharge&,
                 BMSVariables::ChargeRate&);

#ifdef UTEST
void faultStatusFormat(char* buffer, const BMSVariables::variable &value);
std::string getString(BMSVariables::stringID str);
#endif

#endif  //_CHECKER_H_