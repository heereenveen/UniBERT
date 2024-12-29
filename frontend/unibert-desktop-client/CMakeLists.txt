cmake_minimum_required(VERSION 3.16)

project(unibert-desktop-client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp

        view/mainwindow.cpp
        view/mainwindow.h
        view/mainwindow.ui
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/view)

qt_add_executable(unibert-desktop-client
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
        view/chatwindow.h view/chatwindow.cpp view/chatwindow.ui
        view/chatmessage.h view/chatmessage.cpp
        view/chatwidget.h view/chatwidget.cpp
        model/basic_http_client.cpp model/basic_http_client.h
)

#set(SOURCES
#        main.cpp
#        mainwindow.cpp
#        chatwidget.cpp
#        chatmessage.cpp
#        chatwindow.cpp
#)
#
#set(HEADERS
#        chatmessage.h
#        chatwidget.h
#        chatwindow.h
#        mainwindow.h
#)
#set(UI_FILES
#        mainwindow.ui
#        chatwindow.ui
#)
#
#add_executable(unibert-desktop-client ${SOURCES} ${HEADERS} ${UI_FILES})

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

target_link_libraries(unibert-desktop-client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${CURLPP_LDFLAGS})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.unibert-desktop-client)
endif()
set_target_properties(unibert-desktop-client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS unibert-desktop-client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(unibert-desktop-client)
endif()

set(GTESTLIBS GTest::gtest_main GTest::GTest GTest::Main GTest::gmock_main)
find_package(GTest REQUIRED)

enable_testing()

set(TESTS
        model/http_client_unittest.cpp
)

add_executable(tests-all ${TESTS})
target_link_libraries(tests-all ${GTESTLIBS})

include(GoogleTest)
gtest_discover_tests(tests-all)
