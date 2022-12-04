#ifndef _CHECKER_H_
#define _CHECKER_H_

#include <iostream>

extern const float minTemperature;
extern const float maxTemperature;
extern const float maxChargeRate;
extern const float minSOC;
extern const float maxSOC;
extern const float tempTolerancePercent;
extern const float socTolerancePercent;
extern const float cRateTolerancePercent;

namespace BMSVariables{
  enum class variableStatus : char{
    Normal = 0,
    LowWarn,
    Low,
    HighWarn,
    High
  };

  enum class languageIDs : char{
    English = 0,
    German,
    Spanish
  };

  class variable{
    public:

    variable();
    variable(const std::string id = "Unknown",
             float lowThreshhold  = 0.0,
             float highThreshhold = 0.0,
             float warnThreshPercent = 0.0):
      m_ID{id},
      m_lowThreshhold{lowThreshhold},
      m_highThreshhold{highThreshhold},
      m_warnThreshholdRatio{warnThreshPercent}
      {
        m_warnThreshholdRatio = m_warnThreshholdRatio/100;
      };

    ~variable(){};

    bool setLanguage(languageIDs targetlang);

    std::string m_ID;
    languageIDs m_LanguageID = languageIDs::English;
    variableStatus status = variableStatus::Normal;
    float m_presentValue;
    float m_lowThreshhold;
    float m_highThreshhold;
    float m_warnThreshholdRatio;
  };

  class Temperature : public virtual variable{
    public:
    Temperature():variable("Temperature", minTemperature,
                           maxTemperature, tempTolerancePercent){};
  };

  class StateOfCharge : public virtual variable{
    public:
    StateOfCharge():variable("State of Charge"){};
  };

  class ChargeRate : public virtual variable{
    public:
    ChargeRate():variable("Charge Rate"){};
  };
}

bool IsTemperatureOk(BMSVariables::Temperature&);
bool IsStateOfChargeOk(BMSVariables::StateOfCharge&);
bool IsChargeRateOk(BMSVariables::ChargeRate&);
bool IsBatteryOk(BMSVariables::Temperature&,
                 BMSVariables::StateOfCharge&,
                 BMSVariables::ChargeRate&);

#endif  //_CHECKER_H_