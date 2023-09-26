cmake_minimum_required(VERSION 3.1)

project(OpenCVTemplate LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 11)  # Adjust C++ Standard Version here

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(OPENCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/OpenCV)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

# Build Options
if(NOT DEFINED COMPILE_LIBS)
    set(COMPILE_LIBS True)
endif()
if(NOT DEFINED CV_ENABLED_MODULES)
    set(CV_ENABLED_MODULES core calib3d features2d dnn flann highgui imgcodecs imgproc ml objdetect photo stitching video videoio)
endif()

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

if(COMPILE_LIBS)
    add_subdirectory(${OPENCV_DIR})

    target_include_directories(${PROJECT_NAME} PUBLIC
            ${CMAKE_BINARY_DIR}
    )
    foreach(cvmodule ${CV_ENABLED_MODULES})
        target_link_libraries(${PROJECT_NAME} PUBLIC
            opencv_${cvmodule}
        )
        target_include_directories(${PROJECT_NAME} PUBLIC
            ${OPENCV_DIR}/modules/${cvmodule}/include
        )
    endforeach()
else ()
    # Using System Installed Library (Dependencies: hdf5, vtk and glew <-- Need to be installed)
    find_package(OpenCV REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
endif()

# Copy Resources into output folder of the executable after successful build
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        VERBATIM
)
