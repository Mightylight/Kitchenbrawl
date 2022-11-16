cmake_minimum_required(VERSION 3.17)
project(KitchenBrawl)

set(CMAKE_CXX_STANDARD 23)

add_executable(KitchenBrawl main.cpp src/button.cpp
        src/scene.cpp
        src/scene.hpp
        src/character.cpp
        src/sceneHandler.hpp
        src/spriteObject.cpp
        src/button.hpp
        src/gameObject.hpp
        src/character.hpp
        src/textObject.cpp
        src/sceneHandler.cpp
        src/quitButton.cpp
        src/spriteObject.hpp
        src/quitButton.hpp
        src/gameObject.cpp
        src/textObject.hpp
        src/GameManager.cpp
        src/GameManager.hpp)

include_directories(c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(KitchenBrawl ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/Users/bejme/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.4167.35/bin/mingw/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
