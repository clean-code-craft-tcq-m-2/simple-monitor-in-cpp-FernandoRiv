// Constant declarations
#include "checkerTypes.h"

namespace BMSVariables{
  // Float values
  float minTemperature = 0.0;
  float maxTemperature = 45.0;
  float maxChargeRate  = 0.8;
  float minSOC = 20.0;
  float maxSOC = 80.0;
  float tempTolerancePercent   = 5.0;
  float socTolerancePercent    = 5.0;
  float cRateTolerancePercent  = 5.0;

  // Variable Strings
  languageIndexer temperatureStrings{
    {languageID::English, "Temperature"},
    {languageID::German,  "Temperatur"}
  };
  languageIndexer stateOfChargeStrings{
    {languageID::English, "State of Charge"},
    {languageID::German,  "Ladezustand"}
  };
  languageIndexer chargeRateStrings{
    {languageID::English, "Charge Rate"},
    {languageID::German,  "Ladestrom"}
  };

  // Status Strings
  languageIndexer normalStrings{
    {languageID::English, "normal"},
    {languageID::German,  "normal"}
  };
  languageIndexer lowStrings{
    {languageID::English, "low"},
    {languageID::German,  "niedrig"}
  };
  languageIndexer highStrings{
    {languageID::English, "high"},
    {languageID::German,  "hoch"}
  };
  languageIndexer errorStrings{
    {languageID::English, "Breach"},
    {languageID::German,  "Bruch"}
  };
  languageIndexer warningStrings{
    {languageID::English, "Warning"},
    {languageID::German,  "Warnung"}
  };

  stringIndexer strIndexer{
    {stringID::TEMPERATURE, temperatureStrings},
    {stringID::SOC,         stateOfChargeStrings},
    {stringID::CHARGERATE,  chargeRateStrings},
    {stringID::LOW,         lowStrings},
    {stringID::HIGH,        highStrings},
    {stringID::WARNING,     warningStrings},
    {stringID::ERROR,       errorStrings}
  };
}

