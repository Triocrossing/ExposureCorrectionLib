cmake_minimum_required(VERSION 3.5)
project(AutoExposure)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp include/AutoExposure.h include/AutoExposure_impl.hxx include/exposureCoreFunc.h include/exposureCoreFunc_impl.hxx)
add_executable(AutoExposure ${SOURCE_FILES})

find_package(OpenCV REQUIRED)

target_link_libraries(AutoExposure 
${OpenCV_LIBS}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
