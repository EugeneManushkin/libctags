#pragma once

#include <memory>

namespace LibCtags
{
  class Config;

  namespace Internal
  {
    std::unique_ptr<Config> CreateConfig();
  }
}
