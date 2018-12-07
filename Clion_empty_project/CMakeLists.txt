cmake_minimum_required(VERSION 3.6)
set (CMAKE_CXX_STANDARD 11)

# ucm_add_linker_flags
# Adds linker flags to CMAKE_<TYPE>_LINKER_FLAGS or to a specific config
macro(add_linker_flags)
    cmake_parse_arguments(ARG "CLEAR_OLD;EXE;MODULE;SHARED;STATIC" "" "CONFIG" ${ARGN})

    if(NOT ARG_CONFIG)
        set(ARG_CONFIG " ")
    endif()

    foreach(CONFIG ${ARG_CONFIG})
        string(TOUPPER "${ARG_CONFIG}" ARG_CONFIG)

        if(NOT ${ARG_EXE} AND NOT ${ARG_MODULE} AND NOT ${ARG_SHARED} AND NOT ${ARG_STATIC})
            set(ARG_EXE 1)
            set(ARG_MODULE 1)
            set(ARG_SHARED 1)
            set(ARG_STATIC 1)
        endif()

        set(flags_configs "")
        if(${ARG_EXE})
            if(NOT "${CONFIG}" STREQUAL " ")
                list(APPEND flags_configs CMAKE_EXE_LINKER_FLAGS_${CONFIG})
            else()
                list(APPEND flags_configs CMAKE_EXE_LINKER_FLAGS)
            endif()
        endif()
        if(${ARG_MODULE})
            if(NOT "${CONFIG}" STREQUAL " ")
                list(APPEND flags_configs CMAKE_MODULE_LINKER_FLAGS_${CONFIG})
            else()
                list(APPEND flags_configs CMAKE_MODULE_LINKER_FLAGS)
            endif()
        endif()
        if(${ARG_SHARED})
            if(NOT "${CONFIG}" STREQUAL " ")
                list(APPEND flags_configs CMAKE_SHARED_LINKER_FLAGS_${CONFIG})
            else()
                list(APPEND flags_configs CMAKE_SHARED_LINKER_FLAGS)
            endif()
        endif()
        if(${ARG_STATIC})
            if(NOT "${CONFIG}" STREQUAL " ")
                list(APPEND flags_configs CMAKE_STATIC_LINKER_FLAGS_${CONFIG})
            else()
                list(APPEND flags_configs CMAKE_STATIC_LINKER_FLAGS)
            endif()
        endif()

        # clear the old flags
        if(${ARG_CLEAR_OLD})
            foreach(flags ${flags_configs})
                set(${flags} "")
            endforeach()
        endif()

        # add all the passed flags
        foreach(flag ${ARG_UNPARSED_ARGUMENTS})
            foreach(flags ${flags_configs})
                set(${flags} "${${flags}} ${flag}")
            endforeach()
        endforeach()
    endforeach()
endmacro()

# ucm_set_linker_flags
# Sets the CMAKE_<TYPE>_LINKER_FLAGS linker flags or for a specific config
macro(set_linker_flags)
    add_linker_flags(CLEAR_OLD ${ARGN})
endmacro()

# checks to ensure that the Stanford C++ library and its associated
# Java back-end are both present in this project
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/StanfordCPPLib/private/version.h)
    message("*** Stanford C++ library not found!")
    message("*** This project cannot run without the folder lib/StanfordCPPLib/.")
    message("*** Place that folder into your project and try again.")
    message(FATAL_ERROR "Exiting.")
endif()

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/spl.jar)
    message(FATAL_ERROR "*** Stanford Java back-end library 'spl.jar' not found!")
    message("*** This project cannot run without spl.jar present.")
    message("*** Place that file into your lib/ folder and try again.")
    message(FATAL_ERROR "Exiting.")
endif()

if (WIN32)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/addr2line.exe)
        message("*** Stanford C++ library support file 'addr2line.exe' not found!")
        message("*** Our library needs this file present to produce stack traces.")
        message("*** Place that file into your lib/ folder and try again.")
        message(FATAL_ERROR "Exiting.")
    endif()
endif()


include_directories(${PROJECT_SRC_DIR}/src/)
include_directories(${PROJECT_SRC_DIR}/lib/)


file(GLOB_RECURSE resources ${PROJECT_SRC_DIR}/res/)

file(COPY ${resources} DESTINATION ${PROJECT_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/lib/spl.jar DESTINATION ${PROJECT_BINARY_DIR}/)

if(WIN32)
    file(COPY ${CMAKE_SOURCE_DIR}/lib/addr2line.exe DESTINATION ${PROJECT_BINARY_DIR}/)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wcast-align -Wfloat-equal -Wlong-long \
 -Wreturn-type -Wunreachable-code -Werror=return-type -Werror=uninitialized \
  -Wno-missing-field-initializers -Wno-sign-compare -Wno-sign-conversion -Wno-write-strings \
   -Wint-to-void-pointer-cast")


if (WIN32)
    add_linker_flags(-Wl,--stack,268435456)
    set(LIBS ${LIBS} bfd imagehlp Dbgheklp)
endif()

if (APPLE)

endif()

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic -Wl,--export-dynamic")
    add_linker_flags(-rdynamic)
    add_linker_flags(-Wl,--export-dynamic)
endif()

if(NOT WIN32)
    find_library(dl REQUIRED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-const-variable")
    set(LIBS ${LIBS} dl)
endif()

# include various source .cpp files and header .h files in the build process
# (student's source code can be put into project root, or src/ subfolder)
if (EXISTS ${CMAKE_SOURCE_DIR}/lib/StanfordCPPLib/)
    add_subdirectory(lib/)
endif()

add_executable(main src/hello.cpp P1.cpp P1.h P2.h P3.h graphtypes.h buffer.cpp buffer.h employee.cpp employee.h P4.h P5.h P5.cpp pqueue_heap.h pqueue_list.h)
target_link_libraries(main stanford ${LIBS})