file(GLOB LIBCTAGS_SOURCES
    "libctags/*"
)

include_directories (
    ../include
    ctags_internal/ctags/main
)

add_library(libctags_static ${LIBCTAGS_SOURCES} $<TARGET_OBJECTS:ctags_internal>)
add_subdirectory(ctags_internal)
