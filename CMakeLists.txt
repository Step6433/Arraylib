cmake_minimum_required(VERSION 3.16)
project(arraylib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Динамическая библиотека ----
add_library(arraylib SHARED src/arraylib.cpp)

target_include_directories(arraylib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(arraylib PRIVATE ARRAYLIB_BUILD)

if (MSVC)
    target_compile_options(arraylib PRIVATE /W4)
else()
    target_compile_options(arraylib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- Демонстрационная программа ----
add_executable(app main.cpp)
target_link_libraries(app PRIVATE arraylib)

# Кроссплатформенная настройка RPATH (для macOS и Linux)
if(APPLE)
    set_target_properties(app PROPERTIES BUILD_RPATH "@executable_path")
else()
    set_target_properties(app PROPERTIES BUILD_RPATH "$ORIGIN")
endif()

# Все артефакты — в каталог сборки
set_target_properties(arraylib app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# ---- Настройка тестирования через CTest ----
include(CTest)

if (BUILD_TESTING)
    # 1. Сборка Unit-теста
    add_executable(test_unit tests/test_unit.cpp)
    target_link_libraries(test_unit PRIVATE arraylib)
    target_compile_options(test_unit PRIVATE -UNDEBUG)
    add_test(NAME unit COMMAND test_unit)

    # 2. Сборка Интеграционного теста
    add_executable(test_integration tests/test_integration.cpp)
    target_link_libraries(test_integration PRIVATE arraylib)
    target_compile_options(test_integration PRIVATE -UNDEBUG)
    add_test(NAME integration COMMAND test_integration)

    # 3. Кроссплатформенная привязка RPATH (чтобы тесты находили .dylib на Mac / .so на Linux)
    if(APPLE)
        set_target_properties(test_unit test_integration PROPERTIES BUILD_RPATH "@executable_path")
    else()
        set_target_properties(test_unit test_integration PROPERTIES BUILD_RPATH "$ORIGIN")
    endif()

    # 4. Помещаем исполняемые файлы тестов в общую папку сборки
    set_target_properties(test_unit test_integration PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()

# Демонстрационная программа (Этап 8)
add_executable(variant_01 examples/variant_01.cpp)
target_link_libraries(variant_01 PRIVATE arraylib)