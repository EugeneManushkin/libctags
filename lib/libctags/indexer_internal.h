#pragma once

#include <memory>

namespace LibCtags
{
  class Indexer;
  class Config;

  namespace Internal
  {
    std::unique_ptr<Indexer> CreateIndexer(Config const& config);
  }
}
