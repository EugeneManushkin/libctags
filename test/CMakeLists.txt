include_directories (
    ../lib/ctags_internal/ctags/main
)

add_definitions (
    -Dbool=int
    -Dtrue=1
    -Dfalse=0
)

add_executable(ctags_test ../lib/ctags_internal/ctags/main/main.c)
target_link_libraries(ctags_test ctags_internal)
