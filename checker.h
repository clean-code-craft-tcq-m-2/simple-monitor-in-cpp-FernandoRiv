#ifndef _CHECKER_H_
#define _CHECKER_H_

#include <iostream>

static const float minTemperature = 0.0;
static const float maxTemperature = 45.0;
static const float maxChargeRate  = 0.8;
static const float minSOC = 20.0;
static const float maxSOC = 80.0;

namespace BMSVariables{
  enum class variableStatus : char{
    Normal = 0,
    Low,
    High
  };

  class variable{
    public:

    variable();
    variable(const std::string id):
      ID{id}{};

    ~variable(){};

    std::string ID = "Undefined";
    float presentValue = 0.0;
    variableStatus status = variableStatus::Normal;
  };

  class Temperature : public virtual variable{
    public:
    Temperature():variable("Temperature"){};
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