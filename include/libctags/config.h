#pragma once

#include <memory>
#include <string>
#include <vector>

namespace LibCtags
{
  struct Kind
  {
    std::string FullName;
    std::string ShortName;
    std::string Description;
    bool Enabled;
  };

  class Config
  {
  public:
    virtual ~Config() = default;
    virtual std::vector<std::string> GetLanguages() const = 0;
    virtual std::vector<Kind> GetKinds(std::string const& language) const = 0;
  };

  std::unique_ptr<Config> GetConfig();
}
