set(lf_testdir "${CMAKE_CURRENT_SOURCE_DIR}")

set(lf_test_sources
  "${lf_testdir}/test_bit.c"
  "${lf_testdir}/test_array.c"
)

add_subdirectory(unity)

foreach(lf_test_source IN LISTS lf_test_sources)
  get_filename_component(lf_test_name "${lf_test_source}" NAME_WE)

  add_executable(${lf_test_name} "${lf_test_source}")
  target_link_libraries(${lf_test_name} PRIVATE ${lf} unity)

  add_test(NAME ${lf_test_name} COMMAND ${lf_test_name})
endforeach()
