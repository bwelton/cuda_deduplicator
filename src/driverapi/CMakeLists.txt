add_library(DriverAPIWrapper SHARED "Parameters.cpp" "DriverWrapperBase.cpp" "DriverWrapperFactory.cpp" "DriverAPIWrappers.cpp")
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

configure_file (
    "${PROJECT_SOURCE_DIR}/src/driverapi/defs/DriverAPIWrapper.def.in"
	"${CMAKE_INSTALL_PREFIX}/defs/DriverAPIWrapper.def"
)

add_library(InterpositionDriverAPI SHARED "Parameters.cpp" "InterpositionWrappers.cpp" "DriverWrapperFactory.cpp" "DriverWrapperBase.cpp")
target_compile_definitions(InterpositionDriverAPI PRIVATE INTERPOSITION_BUILD=1)
target_link_libraries(InterpositionDriverAPI ${Boost_LIBRARIES})
target_link_libraries(InterpositionDriverAPI ${DYNINST_LIBRARIES})
target_link_libraries(InterpositionDriverAPI "-lpthread")
INCLUDE_DIRECTORIES(InterpositionDriverAPI ${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
add_dependencies(InterpositionDriverAPI dyninst)
install(TARGETS InterpositionDriverAPI
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)


add_library(dlsymwrap SHARED "dlsym_wrapper.cpp")
target_link_libraries(dlsymwrap ${Boost_LIBRARIES})
target_link_libraries(dlsymwrap ${DYNINST_LIBRARIES})
target_link_libraries(dlsymwrap "-lpthread")
INCLUDE_DIRECTORIES(dlsymwrap ${Boost_INCLUDE_DIRS})
SET_TARGET_PROPERTIES(dlsymwrap PROPERTIES LINK_FLAGS "-ldl")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
install(TARGETS dlsymwrap
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
