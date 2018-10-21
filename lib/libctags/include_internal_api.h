#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define bool int
#define false 0
#define true 1
#define private private_

#include <error.h>
#include <field.h>
#include <gcc-attr.h>
#include <routines.h>
#include <trashbox.h>
#include <writer.h>
// workaround undefined langType in xtag.h
#include <types.h>
#include <xtag.h>

#ifdef DEBUG
  #define DEBUG_INIT() debugInit()
#else
  #define DEBUG_INIT()
#endif

void debugInit(void);
bool checkRegex(void);
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
#undef private

#ifdef __cplusplus
}
#endif
