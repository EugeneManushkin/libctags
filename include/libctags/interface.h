#pragma once

#include <memory>
#include <string>

namespace LibCtags
{
  class Indexer;
  class Config;

  class Interface
  {
  public:
    virtual ~Interface() = default;
    virtual std::unique_ptr<Config> GetDefaultConfig() const = 0;
    virtual std::unique_ptr<Indexer> GetIndexer(Config const&) const = 0;
  };

  void Initialize(std::string const& executable);
  Interface const& GetInterface();
}
