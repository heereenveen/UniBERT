cmake_minimum_required(VERSION 3.16)

project(unibert-desktop-client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# including directory so Qt can see it
# if Qt can see our view folder, we can promote classes in Qt Designer
# if we can promote classes in Qt Designer, we can make profit.
include_directories(src/view/chat)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl
)

# Collect all source files
file(GLOB_RECURSE COMPILATION_UNITS_TMP CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

# Filter out the test files
set(COMPILATION_UNITS "")
foreach(file ${COMPILATION_UNITS_TMP})
    if (NOT file MATCHES "(test|main)\\.(cpp|c\\+\\+|cc)$")
        list(APPEND COMPILATION_UNITS ${file})
    endif()
endforeach()

file(GLOB_RECURSE UI CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/view/*.ui
)

qt_add_executable(unibert-desktop-client
        MANUAL_FINALIZATION
        ${HEADERS}
        ${UI}
        ${COMPILATION_UNITS}
        src/main.cpp
)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

target_link_libraries(unibert-desktop-client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${CURLPP_LDFLAGS})

include(GNUInstallDirs)
install(TARGETS unibert-desktop-client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(unibert-desktop-client)

file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.c++
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*test.cс
)

set(GTESTLIBS GTest::gtest_main GTest::GTest GTest::Main GTest::gmock_main)
find_package(GTest REQUIRED)

enable_testing()

add_executable(tests-all ${TESTS})
target_link_libraries(tests-all ${GTESTLIBS})

include(GoogleTest)
gtest_discover_tests(tests-all)


