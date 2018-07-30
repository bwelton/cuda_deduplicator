add_library(SynchTool SHARED "SynchTool.cpp" "CheckAccesses.cpp" "OutputWriter.cpp" "LoadStoreDriver.cpp")
add_compile_options(-O3 -g -mno-vsx)
target_link_libraries(SynchTool ${Boost_LIBRARIES})
target_link_libraries(SynchTool ${DYNINST_LIBRARIES})
target_link_libraries(SynchTool "-lpthread")
target_link_libraries(SynchTool DriverAPIWrapper)
INCLUDE_DIRECTORIES(SynchTool ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(SynchTool ${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/include)
INCLUDE_DIRECTORIES(SynchTool ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/driverapi")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/deduplicate")
target_link_libraries(SynchTool "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart -L${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/lib64 -lcupti -lboost_timer")
install(TARGETS SynchTool
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib/plugins
        ARCHIVE DESTINATION lib/static)
