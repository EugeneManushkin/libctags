#include "include_internal_api.h"

#include <libctags/config.h>
#include <libctags/indexer.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>


#ifdef __cplusplus
extern "C" {
#endif

int isDestinationStdout(void)
{
  return 0;
}

void addTotals(const unsigned int files, const long unsigned int lines, const long unsigned int bytes)
{
}

#ifdef __cplusplus
}
#endif

namespace
{
  int createTagsForEntry(const char *const entryName)
  {
    int resize = false;
    fileStatus *status = eStat (entryName);

    if (isExcludedFile(entryName))
        verbose("excluding \"%s\"\n", entryName);
//TODO: make Option available and handle symlinks
//    else if (status->isSymbolicLink && !Option.followLinks)
//        verbose("ignoring \"%s\" (symbolic link)\n", entryName);
    else if (!status->exists)
        error(WARNING | PERROR, "cannot open input file \"%s\"", entryName);
    else if (status->isDirectory)
        error(WARNING | PERROR, "invalid usage: specified file \"%s\" is directory", entryName);
    else if (!status->isNormalFile)
        verbose("ignoring \"%s\" (special file)\n", entryName);
    else
        resize = parseFile(entryName);

    eStatFree (status);
    return resize;
  }


  class IndexerImpl : public LibCtags::Indexer
  {
  public:
    IndexerImpl(LibCtags::Config const& config)
      : Config(config.Clone())
    {
    }

    virtual void Index(char const* file) override
    {
      openTagFile();
      auto resize = createTagsForEntry(file);
      closeTagFile(resize);
    }

  private:
    std::unique_ptr<LibCtags::Config> Config;
  };
}

namespace LibCtags
{
  namespace Internal
  {
    std::unique_ptr<Indexer> CreateIndexer(Config const& config)
    {
      return std::unique_ptr<Indexer>(new IndexerImpl(config));
    }
  }
}
