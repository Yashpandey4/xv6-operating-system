cmake_minimum_required(VERSION 3.14)

project(xv6-public
    VERSION
        1.0
    DESCRIPTION
        "xv6 OS"
    LANGUAGES
        C
)

file(GLOB allFiles_SRC CONFIGURE_DEPENDS "*.c" "*.h")

add_executable(xv6-public ${allFiles_SRC} print_count.c)