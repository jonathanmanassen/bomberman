cmake_minimum_required(VERSION 3.6)

project(Bomberman)

include_directories(include ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4/include ${CMAKE_CURRENT_BINARY_DIR}/fmod/inc)

set (SRC src/Game.cpp src/main.cpp src/Display.cpp src/Core.cpp src/Map.cpp src/Score.cpp src/Settings.cpp src/Player.cpp src/Human.cpp src/Ia.cpp src/Command.cpp src/Menu.cpp src/Bomb.cpp src/Bonus.cpp src/Sound.cpp src/SaveGame.cpp)

add_executable(bomberman
	${SRC}
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

link_directories(./lib)

if (UNIX)
set(LIBRARIES
  X11
  Xxf86vm
  GL
  pthread
  ${CMAKE_CURRENT_BINARY_DIR}/lib/libIrrlicht.a
  ${CMAKE_CURRENT_BINARY_DIR}/fmod/lib/x86_64/libfmod.so
)
endif (UNIX)

if (WIN32)
set(LIBRARIES
${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4/lib/Win32-visualStudio/Irrlicht.lib
${CMAKE_CURRENT_BINARY_DIR}/fmod/lib/x86_64/fmod_vc.lib
)
endif (WIN32)

target_link_libraries(
  bomberman
  ${LIBRARIES}
)

if (UNIX)

add_custom_command(
OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/lib/libIrrlicht.a
COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4 ${CMAKE_CURRENT_BINARY_DIR}/lib/libIrrlicht.a
COMMAND unzip ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4.zip
COMMAND mv irrlicht-1.8.4 ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4
COMMAND make -C ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4/source/Irrlicht/
COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/lib/irrlicht-1.8.4/lib/Linux/libIrrlicht.a ${CMAKE_CURRENT_BINARY_DIR}/lib
)

add_custom_target(
irrlicht
DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/lib/libIrrlicht.a
)

install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build \"${CMAKE_CURRENT_BINARY_DIR}\" --target irrlicht)")

add_dependencies(bomberman irrlicht)

add_custom_target(
fclean
COMMAND rm -rf CMakeFiles/ CMakeCache.txt cmake_install.cmake install_manifest.txt Makefile bomberman
)

endif (UNIX)
