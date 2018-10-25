#include "config_internal.h"
#include "include_internal_api.h"
#include "indexer_internal.h"

#include <libctags/config.h>
#include <libctags/indexer.h>
#include <libctags/interface.h>

namespace
{
  class InterfaceImpl : public LibCtags::Interface
  {
  public:
    InterfaceImpl(std::string const& executable)
      : Executable(executable)
    {
      initDefaultTrashBox();
      DEBUG_INIT();
      setErrorPrinter(stderrDefaultErrorPrinter, NULL);
      setTagWriter(WRITER_U_CTAGS);
      setCurrentDirectory();
      setExecutableName(Executable.c_str());
      checkRegex();
      initFieldObjects();
      initXtagObjects();
      initializeParsing();
      initOptions();
      DefaultConfig = LibCtags::Internal::CreateConfig();
    }

    virtual ~InterfaceImpl()
    {
//TODO: implement
    }

    virtual std::unique_ptr<LibCtags::Config> GetDefaultConfig() const override
    {
      return DefaultConfig->Clone();
    }

    virtual std::unique_ptr<LibCtags::Indexer> GetIndexer(LibCtags::Config const& config) const override
    {
      return LibCtags::Internal::CreateIndexer(config);
    }

  private:
    std::string Executable;
    std::unique_ptr<LibCtags::Config> DefaultConfig;
  };

  std::unique_ptr<LibCtags::Interface> InterfaceInstance;
}

namespace LibCtags
{
  void Initialize(std::string const& executable)
  {
    if (InterfaceInstance)
      throw std::runtime_error("Already initialized");

    InterfaceInstance.reset(new InterfaceImpl(executable));
  }

  Interface const& GetInterface()
  {
    if (!InterfaceInstance)
      throw std::runtime_error("Not initialized");

    return *InterfaceInstance;
  }
}
