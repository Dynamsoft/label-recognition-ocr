cmake_minimum_required (VERSION 2.6)
project (DLR)
MESSAGE( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

option(ENABLE_OPENCV "Build with OpenCV" OFF)
MESSAGE(STATUS "Build with OpenCV: ${ENABLE_OPENCV}")

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Set RPATH
if(WINDOWS)
else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()


# Add search path for include and lib files
if(WINDOWS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/win/lib/") 
elseif(LINUX)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/linux/") 
elseif(MACOS)
    link_directories("${PROJECT_SOURCE_DIR}/platforms/macos/") 
endif()
include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/include/")

# Add the executable
if (ENABLE_OPENCV)
    find_package(OpenCV REQUIRED)
    add_executable(LabelRecognition LabelRecognitionDemoOpenCV.cpp)
    if(WINDOWS)
        target_link_libraries (LabelRecognition "DynamsoftLabelRecognitionx64" ${OpenCV_LIBS})
    else()
        target_link_libraries (LabelRecognition "DynamsoftLabelRecognition" ${OpenCV_LIBS})
    endif()
else()
    add_executable(LabelRecognition LabelRecognitionDemo.cpp)
    if(WINDOWS)
        target_link_libraries (LabelRecognition "DynamsoftLabelRecognitionx64")
    else()
        target_link_libraries (LabelRecognition "DynamsoftLabelRecognition")
    endif()
endif()



if(WINDOWS)
    add_custom_command(TARGET LabelRecognition POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/platforms/win/bin/"      
        $<TARGET_FILE_DIR:LabelRecognition>)
endif()

