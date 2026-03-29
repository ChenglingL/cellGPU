if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DDEBUGFLAGUP)
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")
include_directories(/opt/nvidia/hpc_sdk/Linux_x86_64/25.3/math_libs/12.8/targets/x86_64-linux/include)
include_directories(${CUDAToolkit_INCLUDE_DIRS} ${CUDA_INCLUDE_DIRS})
include_directories(
            ${EIGEN3_INCLUDE_DIR}
            ${CUDA_INCLUDE_DIRS}
            ${CMAKE_SOURCE_DIR}/inc 
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/utility
            ${CMAKE_SOURCE_DIR}/src/analysis
            ${CMAKE_SOURCE_DIR}/src/models
            ${CMAKE_SOURCE_DIR}/src/forces
            ${CMAKE_SOURCE_DIR}/src/updaters
            ${CMAKE_SOURCE_DIR}/src/simulation
        )

add_library(utility
    cellListGPU.cpp
    eigenMatrixInterface.cpp
    hilbert_curve.cpp
    noiseSource.cpp
    )
cuda_add_library(utilityGPU
    cellListGPU.cu
    noiseSource.cu
    utilities.cu
    )
target_include_directories(utilityGPU
    PUBLIC
    ${CUDAToolkit_INCLUDE_DIRS}
    ${CUDA_INCLUDE_DIRS}
)

target_link_libraries(utilityGPU
    CUDA::curand
    CUDA::cudart
)
