# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(CheckersGame)

# Установка стандарта C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Поиск и подключение библиотеки SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Если вы используете Boost, добавьте поиск и подключение Boost
# find_package(Boost 1.87 REQUIRED COMPONENTS system filesystem)

# Добавление исполняемого файла
add_executable(CheckersProject src/main.cpp src/GameBoard.cpp)

# Указание директории для заголовочных файлов
target_include_directories(CheckersProject PRIVATE include)

# Связывание библиотек SFML
target_link_libraries(CheckersProject sfml-graphics sfml-window sfml-system)

# Если вы используете Boost, добавьте связывание компонентов Boost
# target_link_libraries(CheckersProject Boost::system Boost::filesystem)