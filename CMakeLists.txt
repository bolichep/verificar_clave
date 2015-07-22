
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(verificar_clave)

SET(APP verificar_clave)

FILE(GLOB SOURCES "*.c" "*.h" )

set( CMAKE_C_FLAGS_RELEASE "-DNDEBUG -std=c99 -Ofast -Wl,-s")

set( CMAKE_C_FLAGS_DEBUG "-DDEBUG -std=c99 -O0 -ggdb")

set( CMAKE_INSTALL_PREFIX "/usr")

include (FindPkgConfig)
pkg_search_module(GTK REQUIRE gtk+-2.0)
pkg_search_module(NOTIFY REQUIRED libnotify)

link_directories(
    ${GTK_LIBRARY_DIRS}
    ${NOTIFY_LIBRARY_DIRS}
)

include_directories(
    ${GTK_INCLUDE_DIRS}
    ${NOTIFY_INCLUDE_DIRS}
)

ADD_DEFINITIONS(${GTK_CFLAGS_OTHER})

ADD_EXECUTABLE(${APP} ${SOURCES})

TARGET_LINK_LIBRARIES(${APP} ${GTK_LIBRARIES} ${PAM_LIBRARIES} ${NOTIFY_LIBRARIES} -lpam)

INSTALL ( TARGETS "${APP}" 
    DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

INSTALL ( FILES "${CMAKE_SOURCE_DIR}/verificar_clave.desktop" 
    DESTINATION "/etc/xdg/autostart/" )
