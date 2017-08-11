add_library(inst_lib SHARED "inst.cpp")
add_dependencies(inst_lib dyninst)
target_link_libraries(inst_lib ${DYNINST_LIBRARIES})
install(TARGETS inst_lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)