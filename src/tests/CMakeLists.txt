if ("${BUILD_HOST}" MATCHES "(titan-ext)[1-7]")
	set(PROJ_ID "$ENV{PROJ_ID}")
	set(LAUNCHER "aprun -n 1 -N 1")
endif("${BUILD_HOST}" MATCHES "(titan-ext)[1-7]")

if (NOT DEFINED ENV{PROJ_ID})
	set(PROJ_ID "0")
endif (NOT DEFINED ENV{PROJ_ID})

if (NOT DEFINED LAUNCHER)
	set(LAUNCHER "")
endif (NOT DEFINED LAUNCHER)

if (NOT DEFINED SPACK_ROOT)
	MESSAGE(INFO "No spack directory set, cannot create titan test launch file")
	set(SPACK_MOD_DIR "")
else()
	message(INFO "Spack root set to ${SPACK_ROOT}share/spack/modules/cray-CNL-interlagos")
	set(SPACK_MOD_DIR "${SPACK_ROOT}share/spack/modules/cray-CNL-interlagos")
endif (NOT DEFINED SPACK_ROOT)

add_executable(basic_checker_test "basic_checker_test.cpp")

target_link_libraries(basic_checker_test ${Boost_LIBRARIES})
target_link_libraries(basic_checker_test "-lpthread")
target_link_libraries(basic_checker_test "-L${CUDA_TOOLKIT_ROOT_DIR}/lib64 -lcudart")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/common")
INCLUDE_DIRECTORIES(basic_checker_test ${CUDA_TOOLKIT_ROOT_DIR}/include)
INCLUDE_DIRECTORIES(basic_checker_test ${Boost_INCLUDE_DIRS})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

install(TARGETS basic_checker_test
        RUNTIME DESTINATION tests)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/scripts)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/tests/LoadSpackModules.py.in"
  "${PROJECT_BINARY_DIR}/scripts/LoadSpackModules.py"
  @ONLY
  )
configure_file (
  "${PROJECT_SOURCE_DIR}/src/tests/RunTests.sh.in"
  "${PROJECT_BINARY_DIR}/scripts/RunTests.sh"
  @ONLY
  )
configure_file (
  "${PROJECT_SOURCE_DIR}/src/tests/TitanTestScript.ksh.in"
  "${PROJECT_BINARY_DIR}/scripts/TitanTestScript.ksh"
  @ONLY
  )

install(FILES ${PROJECT_BINARY_DIR}/scripts/TitanTestScript.ksh ${PROJECT_BINARY_DIR}/scripts/RunTests.sh  ${PROJECT_BINARY_DIR}/scripts/LoadSpackModules.py
		DESTINATION tests)

