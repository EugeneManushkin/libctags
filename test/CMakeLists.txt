include_directories (
    ../include
)

add_executable(ctags_test main.cpp)
target_link_libraries(ctags_test libctags_static)
