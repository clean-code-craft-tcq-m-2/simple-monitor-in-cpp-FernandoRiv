#ifndef _CHECKER_CONSTANTS_H_
#define _CHECKER_CONSTANTS_H_

#include <string>
#include <unordered_map>

namespace BMSVariables{
  //===== Types =====
  enum class variableStatus : char{
    Normal = 0,
    LowWarn,
    Low,
    HighWarn,
    High,
    Unknown
  };

  enum class languageID : char{
    English = 0,
    German,
    Unknown
  };

  enum class stringID : char{
    TEMPERATURE = 0,
    SOC,
    CHARGERATE,
    NORMAL,
    LOW,
    HIGH,
    WARNING,
    ERROR,
    UNKNOWN
  };

  typedef std::unordered_map<languageID, std::string> languageIndexer;
  typedef std::unordered_map<stringID, languageIndexer> stringIndexer;
}

#endif // _CHECKER_CONSTANTS_H_