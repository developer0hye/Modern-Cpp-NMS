cmake_minimum_required(VERSION 3.24)
project(example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(example example.cpp nms.cpp)

# In VS, this cmake script will copy input.txt to the same file as your final exe, no matter it's debug or release.
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/boxes.txt 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
