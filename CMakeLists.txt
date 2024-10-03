cmake_minimum_required(VERSION 3.30.3)

project(Automotive-Invoicing-Application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "${CMAKE_CRR_FLAGS} -Werror -Wall -Wextra -Wpedantic -fsanitize=address -g3")
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package (mysql-concpp REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Automotive-Invoicing-Application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Automotive-Invoicing-Application APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Automotive-Invoicing-Application SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Automotive-Invoicing-Application
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(Automotive-Invoicing-Application PRIVATE src/sql)

target_link_libraries(Automotive-Invoicing-Application PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Automotive-Invoicing-Application PRIVATE mysqlcppconnx)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Automotive-Invoicing-Application)
endif()
set_target_properties(Automotive-Invoicing-Application PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Automotive-Invoicing-Application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Automotive-Invoicing-Application)
endif()




# UNIT TESTS
#Include(FetchContent)
#
#FetchContent_Declare(
#  Catch2
#  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#  GIT_TAG        v3.4.0 # or a later release
#)
#
#FetchContent_MakeAvailable(Catch2)
#
#add_executable(UnitTests ${CMAKE_SOURCE_DIR}/tests/databaseTests.cpp)
#target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(UnitTests PRIVATE mysqlcppconnx)

