cmake_minimum_required(VERSION 3.16)

project(flight-rising-breeding-tracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

    qt_add_executable(flight-rising-breeding-tracker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        information.h information.cpp
        rarity.h
        allele.h allele.cpp
        colour.h colour.cpp
        eyeallele.h eyeallele.cpp
        clickableqgraphicsview.h clickableqgraphicsview.cpp
        urlopener.h urlopener.cpp
        dragon.h dragon.cpp
        searchbuilder.h searchbuilder.cpp
        gender.h
        currency.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET flight-rising-breeding-tracker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(flight-rising-breeding-tracker SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(flight-rising-breeding-tracker
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(flight-rising-breeding-tracker PRIVATE .)
configure_file(images/dragon-image-select.jpg images/dragon-image-select.jpg COPYONLY)

target_link_libraries(flight-rising-breeding-tracker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(flight-rising-breeding-tracker PRIVATE Qt6::Widgets)
target_link_libraries(flight-rising-breeding-tracker PRIVATE Qt6::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.flight-rising-breeding-tracker)
endif()
set_target_properties(flight-rising-breeding-tracker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS flight-rising-breeding-tracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(flight-rising-breeding-tracker)
endif()
