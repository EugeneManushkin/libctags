// This is include workaround file to avoid including <writer.h> which could not be compiled in C++ because of invalid "sTagWriter::private" member variable name

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define false 0
#define true 1

#include <error.h>
#include <gcc-attr.h>
#include <routines.h>
#include <trashbox.h>
// workaround undefined langType in xtag.h
#include <types.h>
#include <xtag.h>

#ifdef DEBUG
  #define DEBUG_INIT() debugInit()
#else
  #define DEBUG_INIT()
#endif

typedef enum eWriterType {
	WRITER_DEFAULT,
	WRITER_U_CTAGS = WRITER_DEFAULT,
	WRITER_E_CTAGS,
	WRITER_ETAGS,
	WRITER_XREF,
	WRITER_JSON,
	WRITER_COUNT,
} writerType;

void setTagWriter(writerType otype);
void debugInit(void);
bool checkRegex(void);
void initFieldObjects(void);
void initOptions(void);
void initializeParsing(void);
bool isExcludedFile(const char* const name);
bool parseFile(const char *const fileName);
void openTagFile(void);
void closeTagFile(const int resize);
void verbose(const char *const format, ...) CTAGS_ATTR_PRINTF (1, 2);

#undef bool
#undef false
#undef true

#ifdef __cplusplus
}
#endif
