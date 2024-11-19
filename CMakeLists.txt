# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(StepwiseRegression)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Проверка доступности wx-config
find_program(WX_CONFIG wx-config)

# Проверка, если wx-config найден
if(NOT WX_CONFIG)
    message(FATAL_ERROR "wx-config not found. Please install wxWidgets.")
endif()

# Получаем флаги для компиляции и линковки через wx-config
execute_process(COMMAND ${WX_CONFIG} --cxxflags
                OUTPUT_VARIABLE WX_CXXFLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${WX_CONFIG} --libs
                OUTPUT_VARIABLE WX_LIBS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# Указываем флаги для компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WX_CXXFLAGS}")

# Указываем исходные файлы проекта
include_directories(src)

set(SOURCES
    src/main.cpp
    src/matrix.cpp
    src/regression.cpp
)

# Создаем исполнимый файл "StepwiseRegression"
add_executable(StepwiseRegression ${SOURCES})

# Линкуем библиотеки wxWidgets с исполнимым файлом
target_link_libraries(StepwiseRegression ${WX_LIBS})
