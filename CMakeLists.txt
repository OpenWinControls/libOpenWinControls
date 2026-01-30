cmake_minimum_required(VERSION 3.23)

project(libOpenWinControls VERSION 1.0 DESCRIPTION "Multiplatform GPD WinControls library" LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(PROJECT_AUTHOR "kylon")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(O_BUILD_SHARED ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(src/extern/hidapi)
set(BUILD_SHARED_LIBS ${O_BUILD_SHARED})

set(PROJECT_SRC
    src/include/export.h
    src/include/HIDUsageIDMap.h
    src/include/ControllerFeature.h

    src/controller/Controller.h
    src/controller/Controller.cpp
    src/controller/ControllerV1.h
    src/controller/ControllerV1.cpp

    src/Utils.h
    src/Utils.cpp
)

if (WIN32)
  configure_file(src/resources/win.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/win.rc)

  list(APPEND PROJECT_SRC
      win.rc
  )
endif ()

add_library(${PROJECT_NAME} ${PROJECT_SRC})
add_library(lowc::owc ALIAS ${PROJECT_NAME})

if (WIN32)
  target_compile_definitions(${PROJECT_NAME} PUBLIC OWC_LIBRARY)
else ()
  target_compile_definitions(${PROJECT_NAME} PRIVATE OWC_LIBRARY)
endif ()

include(CheckIPOSupported)
check_ipo_supported(RESULT has_ipo OUTPUT ipo_error)
if (has_ipo)
  message(STATUS "${PROJECT_NAME}: IPO/LTO enabled")
  set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE hidapi::hidapi)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
