include_directories(StandordCPPLib/)
include_directories(StandordCPPLib/collections)
include_directories(StandordCPPLib/graphics)
include_directories(StandordCPPLib/io)
include_directories(StandordCPPLib/private)
include_directories(StandordCPPLib/system)
include_directories(StandordCPPLib/util)


link_directories(StandordCPPLib/)
link_directories(StandordCPPLib/collections)
link_directories(StandordCPPLib/graphics)
link_directories(StandordCPPLib/io)
link_directories(StandordCPPLib/private)
link_directories(StandordCPPLib/system)
link_directories(StandordCPPLib/util)

file(GLOB_RECURSE stanford_src
        "*.h"
        "*.cpp"
        )
# set up configuration flags used internally by the Stanford C++ libraries
# These flags are all optional but can simplify project configuration.
# (setting x/y to 999999 centers the window)
# (see platform.cpp/h for descriptions of some of these flags)

# what version of the Stanford .pro is this? (kludgy integer YYYYMMDD format)
add_definitions(-DSPL_PROJECT_VERSION=20161201)

# x/y location and w/h of the graphical console window; set to -1 to center
add_definitions(-DSPL_CONSOLE_X=-1)
add_definitions(-DSPL_CONSOLE_Y=-1)
add_definitions(-DSPL_CONSOLE_WIDTH=800)
add_definitions(-DSPL_CONSOLE_HEIGHT=500)

# font size of the font in the graphical console window; can also be set via window menu
#add_definitions(-DSPL_CONSOLE_FONTSIZE=18)

# echo graphical console onto the plain text console as well?
add_definitions(-DSPL_CONSOLE_ECHO)

# quit the C++ program when the graphical console is closed?
add_definitions(-DSPL_CONSOLE_EXIT_ON_CLOSE)

# crash if the Java back-end version is older than that specified in version.h?
add_definitions(-DSPL_VERIFY_JAVA_BACKEND_VERSION)

# crash if the .pro is older than the minimum specified in version.h? (SPL_PROJECT_VERSION)
add_definitions(-DSPL_VERIFY_PROJECT_VERSION)

# allow clients to access the internal data inside the heap of PriorityQueue?
# (used for some practice exam exercises/demos)
add_definitions(-DPQUEUE_ALLOW_HEAP_ACCESS)

# should toString / << of a PriorityQueue display the elements in sorted order,
# or in heap internal order? the former is more expected by client; the latter
# is faster and avoids a deep-copy
add_definitions(-DPQUEUE_PRINT_IN_HEAP_ORDER)

add_library(stanford ${stanford_src})
target_include_directories(stanford PUBLIC StanfordCPPLib/ StanfordCPPLib/collections StanfordCPPLib/graphics StanfordCPPLib/io StanfordCPPLib/system StanfordCPPLib/util StanfordCPPLib/private)
target_link_libraries(stanford ${LIBS})