#include <libctags/config.h>
#include <libctags/indexer.h>

#include <stdio.h>

int main(int argc, char **argv)
{
  LibCtags::GetIndexer();
  for (auto const& lang : LibCtags::GetConfig()->GetLanguages())
    printf("%s\n", lang.c_str());

  if (argc < 2)
  {
    return 1;
  }
  
  char const* file = argv[1];
  printf("Indexing file: %s\n", file);
  LibCtags::GetIndexer().Index(file);
  printf("Done\n");
}
