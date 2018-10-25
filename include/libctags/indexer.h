#pragma once

namespace LibCtags
{
  class Indexer
  {
  public:
    virtual ~Indexer() = default;
    virtual void Index(char const* file) = 0;
  };
}
