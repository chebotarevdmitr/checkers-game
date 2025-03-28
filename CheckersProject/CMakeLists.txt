cmake_minimum_required(VERSION 3.10)

project(CheckersGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Добавление всех исходных файлов
add_executable(CheckersProject src/main.cpp src/GameBoard.cpp)

# Указание директории для заголовочных файлов
target_include_directories(CheckersProject PRIVATE include)

# Связывание библиотек SFML
target_link_libraries(CheckersProject sfml-graphics sfml-window sfml-system)