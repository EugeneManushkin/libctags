#include <libctags/config.h>
#include <libctags/indexer.h>
#include <libctags/interface.h>

#include <stdio.h>

namespace
{
  void PrintConfig(LibCtags::Config const& config)
  {
    for (auto const& lang : config.GetLanguages())
    {
      printf("%s\n", lang.c_str());
      for (auto const& kind : config.GetKinds(lang))
        printf("  %15s, %s (enabled==%d): %s\n", kind.FullName.c_str(), kind.ShortName.c_str(), kind.Enabled, kind.Description.c_str());
    }
  }
}

int main(int argc, char **argv)
{
  LibCtags::Initialize(argv[0]);
  auto config = LibCtags::GetInterface().GetDefaultConfig();
  PrintConfig(*config);
  if (argc < 2)
  {
    return 1;
  }
  
  char const* file = argv[1];
  printf("Indexing file: %s\n", file);
  LibCtags::GetInterface().GetIndexer(*config)->Index(file);
  printf("Done\n");
}
