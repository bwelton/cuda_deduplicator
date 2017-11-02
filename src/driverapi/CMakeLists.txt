add_library(DriverAPIWrapper SHARED "DriverWrapperBase.cpp" "DriverWrapperFactory.cpp" "DriverAPIWrappers.cpp")
target_link_libraries(DriverAPIWrapper ${Boost_LIBRARIES})
target_link_libraries(DriverAPIWrapper ${DYNINST_LIBRARIES})
target_link_libraries(DriverAPIWrapper "-lpthread")
INCLUDE_DIRECTORIES(DriverAPIWrapper ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(DriverAPIWrapper ${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/include)
INCLUDE_DIRECTORIES(DriverAPIWrapper ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
target_link_libraries(DriverAPIWrapper "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart -L${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/lib64 -lcupti")
add_dependencies(DriverAPIWrapper dyninst)
install(TARGETS DriverAPIWrapper
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
