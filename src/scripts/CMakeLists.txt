file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/scripts)
configure_file (
  "${PROJECT_SOURCE_DIR}/src/scripts/inst_app.sh.in"
  "${PROJECT_BINARY_DIR}/scripts/inst_app.sh"
  @ONLY
  )

install(FILES ${PROJECT_BINARY_DIR}/scripts/inst_app.sh 
		DESTINATION bin)

