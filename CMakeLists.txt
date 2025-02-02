cmake_minimum_required(VERSION 3.30)
project(encryption C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/SDL/sdl2/SDL2-2.30.10/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/SDL/sdl-ttf/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
set(SDL2_TTF_INCLUDE_DIR "C:/SDL/sdl-ttf/SDL2_ttf-2.22.0/x86_64-w64-mingw32/include")
set(SDL2_IMAGE_PATH "C:/SDL/sdl-image/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_IMAGE_INCLUDE_DIR "C:/SDL/sdl-image/SDL2_image-2.8.2/x86_64-w64-mingw32/include")

find_package(SDL2 REQUIRED)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image PATHS ${SDL2_IMAGE_PATH}/lib)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf PATHS ${SDL2_TTF_PATH}/lib)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(encryption main.c)

target_link_libraries(SMS ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})