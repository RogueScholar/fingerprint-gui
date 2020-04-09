cmake_minimum_required(VERSION 3.2)
project(fingerprint-gui)

include(FindPkgConfig)
macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} ${sympath})")
    install(CODE "message(\"-- Install: ${sympath} -> ${filepath}\")")
endmacro(install_symlink)

set (QT_MIN_VERSION "5.5.0")

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Widgets Xml X11Extras)
find_package(Qca-qt5 REQUIRED)
find_package(PolkitQt5-1 REQUIRED)
find_package(Threads REQUIRED)
find_package(Qt5LinguistTools)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
pkg_check_modules(LIBFPRINT REQUIRED libfprint)
pkg_check_modules(FAKEKEY REQUIRED libfakekey)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
include_directories(${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${Qt5X11Extras_INCLUDE_DIRS}
    ${Qca-qt5_INCLUDE_DIRS}

    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/upek/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
        "${CMAKE_BINARY_DIR}/src"
        "${CMAKE_BINARY_DIR}/include"
)
set(QT_LIBRARIES
                Qt5::Core
                Qt5::Gui
                Qt5::Widgets
                Qt5::Xml
    ${CMAKE_THREAD_LIBS_INIT}
        )
set(LIBEXECDIR "${CMAKE_INSTALL_PREFIX}/lib/fingerprint-gui")
add_subdirectory(src)
add_subdirectory(upek)
add_subdirectory(bin)
add_subdirectory(locales)

install(FILES COPYING DESTINATION "share/doc/fingerprint-gui/")
install(DIRECTORY DESTINATION "/var/lib/fingerprint-gui")
install(DIRECTORY DESTINATION "/var/upek_data")
