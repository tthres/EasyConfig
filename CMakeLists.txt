cmake_minimum_required(VERSION 3.10)

project(EasyConfig VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE -DEASY_CONFIG_EXPORTS)

# 安装规则
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES 
    ${PROJECT_SOURCE_DIR}/src/easy_config.h
    ${PROJECT_SOURCE_DIR}/src/easy_config_define.h
    DESTINATION include
)

# 设置编译选项
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

add_executable(test_ini ${PROJECT_SOURCE_DIR}/examples/ts_ini.cpp)
target_link_libraries(test_ini PRIVATE ${PROJECT_NAME})