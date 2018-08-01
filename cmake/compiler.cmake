set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

##! Global Configuration
set(COMMON_CXX_FLAGS "-Wall -Wextra -Wfatal-errors -Wno-unknown-pragmas")

##! Configuration for debug builds

macro(__internal_debug_cxx_flags)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 ${COMMON_CXX_FLAGS}")
endmacro()

##! Configuration for release builds
macro(__internal_release_cxx_flags)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native ${COMMON_CXX_FLAGS}")
endmacro()

##! Compiler Configuration
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
    __internal_debug_cxx_flags()
    MSG_YELLOW_BOLD(STATUS "CMAKE_CXX_FLAGS_DEBUG:" "${CMAKE_CXX_FLAGS_DEBUG}" "")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DRELEASE)
    add_definitions(-DNDEBUG)
    __internal_release_cxx_flags()
    MSG_YELLOW_BOLD(STATUS "CMAKE_CXX_FLAGS_RELEASE:" "${CMAKE_CXX_FLAGS_RELEASE}" "")
endif ()
