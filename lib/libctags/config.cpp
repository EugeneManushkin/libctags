#include "include_internal_api.h"

#include <libctags/config.h>

namespace
{
  class ConfigImpl : public LibCtags::Config
  {
  public:
    virtual std::vector<std::string> GetLanguages() const override
    {
      std::vector<std::string> result;
      for (auto count = countParsers(); count > 0; --count)
        result.push_back(getLanguageName(static_cast<langType>(count - 1)));
      
      return result;
    }
  };

}

namespace LibCtags
{
  std::unique_ptr<Config> GetConfig()
  {
    return std::unique_ptr<Config>(new ConfigImpl());
  }
}
