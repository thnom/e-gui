project(e-gui)

# C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.21)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

include_directories(include/rapidjson)

# Multiple Files Example
add_executable(e-gui
               main.cpp
               GUI.cpp GUI.hpp
               Menu.cpp Menu.hpp
               Component.cpp Component.hpp
               Parser.cpp Parser.hpp
               EumStruct.hpp)

# Link executable to required SFML modules
target_link_libraries(e-gui
		     sfml-graphics sfml-audio sfml-system)

# Set executable install location
install(TARGETS e-gui DESTINATION bin)
