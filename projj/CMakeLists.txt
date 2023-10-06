cmake_minimum_required(VERSION 3.5)

project(main
        VERSION 1.0)

set(CMAKE_CXX_STANDARD 11 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS  "-fpermissive")
set(SOURCES
    src/SerialComm.cpp
    app/main.cpp)

include_directories(lib/)

add_executable(main ${SOURCES})

set_target_properties(main PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    #OUTPUT_NAME "my_program_name" # Çıktı dosyasının adını değiştirebilirsiniz
)