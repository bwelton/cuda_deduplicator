file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/defs)

set(CUPTI_DRIVER_CIBHEADER "${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/include/cupti_driver_cbid.h")
set(CUPTI_RUNTIME_CIBHEADER "${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/include/cupti_runtime_cbid.h")
configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/defs/DetectDuplicates.def.in"
	"${CMAKE_INSTALL_PREFIX}/defs/DetectDuplicates.def"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/defs/Deduplicate.def.in"
	"${CMAKE_INSTALL_PREFIX}/defs/Deduplicate.def"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenDriverCIBs.py.in"
	"${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenDriverCIBs.py"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenDriverCIBs.py.in"
	"${CMAKE_INSTALL_PREFIX}/defs/GenDriverCIBs.py"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenRuntimeCIBs.py.in"
	"${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenRuntimeCIBs.py"
)

configure_file (
    "${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenRuntimeCIBs.py.in"
	"${CMAKE_INSTALL_PREFIX}/defs/GenRuntimeCIBs.py"
)
add_custom_target(GEN_CIB_DRIVER_TRANSLATORS
		COMMAND python ${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenDriverCIBs.py)
add_custom_target(GEN_CIB_RUNTIME_TRANSLATORS
		COMMAND python ${PROJECT_SOURCE_DIR}/src/deduplicate/support/GenRuntimeCIBs.py)

add_library(dedup SHARED "CUPTIEventHandler.cpp" "CudaDeviceWrappers.cpp" "DestinationHash.cpp" "HashData.cpp" "InstrumentBase.cpp" "TransferBase.cpp" "TransferTimeline.cpp" "InstrumentFactory.cpp" "DuplicateTracker.cpp")
add_definitions("-DTRANSFER_TIMELINE")
target_link_libraries(dedup ${Boost_LIBRARIES})
target_link_libraries(dedup "-lpthread")
INCLUDE_DIRECTORIES(dedup ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(dedup ${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/include)
INCLUDE_DIRECTORIES(dedup ${Boost_INCLUDE_DIRS})
target_link_libraries(dedup "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart -L${CUDA_TOOLKIT_ROOT_DIR}/extras/CUPTI/lib64 -lcupti")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
add_dependencies(dedup GEN_CIB_DRIVER_TRANSLATORS)
add_dependencies(dedup GEN_CIB_RUNTIME_TRANSLATORS)
add_dependencies(dedup dyninst)
install(TARGETS dedup
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
