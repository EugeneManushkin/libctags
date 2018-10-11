#include "include_internal_api.h"

#include <libctags/indexer.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>


#ifdef __cplusplus
extern "C" {
#endif

extern char *CurrentDirectory;

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
    IndexerImpl::IndexerImpl()
      : Executable("CtagsTestProgram")
    {
      initDefaultTrashBox();
      DEBUG_INIT();
      setErrorPrinter(stderrDefaultErrorPrinter, NULL);
      setTagWriter(WRITER_U_CTAGS);
//TODO: remove
      setCurrentDirectory();

      setExecutableName(Executable.c_str());
      checkRegex ();
      initFieldObjects();
      initXtagObjects();
      initializeParsing();
      initOptions();
    }

    virtual void Index(char const* file) override
    {
      openTagFile();
      auto resize = createTagsForEntry(file);
      closeTagFile(resize);
    }

  private:
    std::string Executable;
  };

  std::unique_ptr<LibCtags::Indexer> IndexerInstance;
}

namespace LibCtags
{
  LibCtags::Indexer& GetIndexer()
  {
    if (!IndexerInstance)
      IndexerInstance.reset(new IndexerImpl);

    return *IndexerInstance;
  }
}
