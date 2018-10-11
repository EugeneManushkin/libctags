#pragma once

namespace LibCtags
{
  class Indexer
  {
    public:
      virtual void Index(char const* file) = 0;
  };

  Indexer& GetIndexer();
}
