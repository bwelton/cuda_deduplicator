configure_file (
    "${PROJECT_SOURCE_DIR}/src/driverapi/launcher/main.cpp.in"
	"${PROJECT_SOURCE_DIR}/src/driverapi/launcher/main.cpp"
)
add_executable(LaunchCUInstriment "main.cpp")
target_link_libraries(LaunchCUInstriment ${Boost_LIBRARIES})
target_link_libraries(LaunchCUInstriment "-lpthread")
target_link_libraries(LaunchCUInstriment "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/driverapi")
INCLUDE_DIRECTORIES(LaunchCUInstriment ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(LaunchCUInstriment ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(LaunchCUInstriment "${CMAKE_SOURCE_DIR}/src/common")

install(TARGETS LaunchCUInstriment
        RUNTIME DESTINATION bin)
