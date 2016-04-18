INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MINMAX minmax)

FIND_PATH(
    MINMAX_INCLUDE_DIRS
    NAMES minmax/api.h
    HINTS $ENV{MINMAX_DIR}/include
        ${PC_MINMAX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MINMAX_LIBRARIES
    NAMES gnuradio-minmax
    HINTS $ENV{MINMAX_DIR}/lib
        ${PC_MINMAX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MINMAX DEFAULT_MSG MINMAX_LIBRARIES MINMAX_INCLUDE_DIRS)
MARK_AS_ADVANCED(MINMAX_LIBRARIES MINMAX_INCLUDE_DIRS)

