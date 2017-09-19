file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/defs)
configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/defs/DetectDuplicates.def.in"
	"${CMAKE_INSTALL_PREFIX}/defs/DetectDuplicates.def"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/defs/Deduplicate.def.in"
	"${CMAKE_INSTALL_PREFIX}/defs/Deduplicate.def"
)
add_library(dedup SHARED "deduplicator.cpp" "CudaDeviceWrappers.cpp" "TransferTimeline.cpp")
if (DEFINED ENABLE_STRACE AND "${ENABLE_STRACE}" MATCHES "yes")
	target_sources(dedup PUBLIC "strace.cpp")
	target_link_libraries(dedup ${DYNINST_LIBRARIES})
	add_definitions("-DENABLE_STACKTRACING")
	# add_library(dedup SHARED "deduplicator.cpp" "CudaDeviceWrappers.cpp")
endif(DEFINED ENABLE_STRACE AND "${ENABLE_STRACE}" MATCHES "yes")

# if (DEFINED ENABLE_TIMELINE AND "${ENABLE_TIMELINE}" MATCHES "yes") 
# 	target_sources(dedup PRIVATE "TransferTimeline.cpp")
# 	add_definitions("-DTRANSFER_TIMELINE")
# endif (DEFINED ENABLE_TIMELINE AND "${ENABLE_TIMELINE}" MATCHES "yes")

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
