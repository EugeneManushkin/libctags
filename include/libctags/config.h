#pragma once

#include <memory>
#include <string>
#include <vector>

namespace LibCtags
{
  class Config
  {
  public:
    virtual ~Config() = default;
    virtual std::vector<std::string> GetLanguages() const = 0;
  };

  std::unique_ptr<Config> GetConfig();
}
