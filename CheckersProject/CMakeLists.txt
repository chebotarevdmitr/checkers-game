# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(CheckersGame LANGUAGES CXX)

# Установка стандарта C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Если вы используете vcpkg, добавьте путь к инструментам vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# Поиск и подключение библиотеки SFML версии 2.6
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Добавление исполняемого файла
add_executable(CheckersProject src/main.cpp src/GameBoard.cpp)

# Указание директории для заголовочных файлов
target_include_directories(CheckersProject PRIVATE include)

# Связывание библиотек SFML
target_link_libraries(CheckersProject sfml-graphics sfml-window sfml-system)