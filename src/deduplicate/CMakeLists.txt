add_library(dedup SHARED "deduplicator.cpp" "CudaDeviceWrappers.cpp")
target_link_libraries(dedup ${Boost_LIBRARIES})
target_link_libraries(dedup "-lpthread")
INCLUDE_DIRECTORIES(dedup ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(dedup ${Boost_INCLUDE_DIRS})
target_link_libraries(dedup "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
add_dependencies(dedup dyninst)
install(TARGETS dedup
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
