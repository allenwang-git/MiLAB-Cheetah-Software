cmake_minimum_required(VERSION 3.5)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(CMAKE_COLOR_MAKEFILE   ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#set(CMAKE_VERBOSE_MAKEFILE ON)

option(UP_BOARD "use compiler flags for milab up-board" OFF)
set(BUILD_TYPE_RELEASE TRUE)

option(NO_SIM "Do not build simulator" OFF)

if(UP_BOARD)
  SET (THIS_COM "../" )
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
          ${CMAKE_BINARY_DIR}/Configuration.h)
  set(CMAKE_CXX_FLAGS "-O3 -no-pie -ggdb -Wall \
  -Wextra -Wcast-align -Wdisabled-optimization -Wformat=2 \
  -Winit-self -Wmissing-include-dirs -Woverloaded-virtual \
  -Wshadow -Wsign-promo -Werror")
  set(CMAKE_C_FLAGS "-O3  -ggdb -std=gnu99 -I.")
  message("**** UP-board build enabled ****")
else(UP_BOARD)
  SET (THIS_COM "${PROJECT_SOURCE_DIR}/" )
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
          ${CMAKE_BINARY_DIR}/Configuration.h)

  if(CMAKE_SYSTEM_NAME MATCHES Linux)
    set(CMAKE_CXX_FLAGS "-O3 -no-pie -march=native -ggdb -Wall \
    -Wextra -Wcast-align -Wdisabled-optimization -Wformat=2 \
    -Winit-self -Wmissing-include-dirs -Woverloaded-virtual \
    -Wshadow -Wsign-promo -Werror")
  elseif(APPLE)
    set(CMAKE_CXX_FLAGS "-O3 -march=native -ggdb -Wall \
    -Wextra -Wcast-align -Wdisabled-optimization -Wformat=2 \
    -Winit-self -Wmissing-include-dirs -Woverloaded-virtual \
    -Wshadow -Wsign-promo")
    include_directories("/usr/local/include/")   # lcm includes
  endif()

  set(CMAKE_C_FLAGS "-O3  -ggdb  -march=native -std=gnu99 -I.")
  message("**** UP-board build disabled ****")
endif(UP_BOARD)

# Copy googletest form local dir rather than download from github
if (UP_BOARD)
  set(MY_GOOGLE_PATH ${PROJECT_SOURCE_DIR}/googletest/googletest-mc)
  set(MY_BUILD_PATH ${PROJECT_SOURCE_DIR}/mc-build)
else()
  set(MY_GOOGLE_PATH ${PROJECT_SOURCE_DIR}/googletest)
  set(MY_BUILD_PATH ${PROJECT_SOURCE_DIR}/build)
endif ()
execute_process(COMMAND cp -r ${PROJECT_SOURCE_DIR}/googletest/googletest-src ${MY_BUILD_PATH}
                COMMAND cp -r ${MY_GOOGLE_PATH}/googletest-download ${MY_BUILD_PATH}
                COMMAND cp -r ${MY_GOOGLE_PATH}/googletest-build ${MY_BUILD_PATH}
                )
message("-- Googletest is ready")

set(CMAKE_CXX_STANDARD 14)

#find_package(lcm)

add_subdirectory(robot)
add_subdirectory(third-party)
add_subdirectory(common)

if(NO_SIM)

else(NO_SIM)
  add_subdirectory(sim)
endif()

add_subdirectory(user)
add_subdirectory(rc_test)