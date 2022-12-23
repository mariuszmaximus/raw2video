cmake_minimum_required(VERSION 3.0.0)
project(raw2video VERSION 0.1.0)

add_library(raw2video raw2video.cpp)
add_library(raw2video::raw2video ALIAS raw2video)
target_link_libraries(raw2video avcodec  avdevice avfilter avformat avutil postproc swresample swscale)
target_include_directories(raw2video PUBLIC ./)

add_subdirectory(example)