cmake_minimum_required(VERSION 3.10)

set(lf "frame")
project(lib${lf}
  DESCRIPTION "LibFrame provides the frame for your project"
  VERSION 0.1.0
  LANGUAGES C
)

option(LF_PANIC "whether panic should be defined" ON)
set(LF_PANIC_SYM "panic_impl" CACHE STRING "name of the panic method")

set(lf_topdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(lf_incdir "${lf_topdir}/include")
set(lf_srcdir "${lf_topdir}/src")

set(lf_sources
  "${lf_srcdir}/bit.c"
  "${lf_srcdir}/assert.c"
  "${lf_srcdir}/allocator.c"
  "${lf_srcdir}/array.c"
)

add_library(${lf} STATIC ${lf_sources})
target_include_directories(${lf} PUBLIC ${lf_incdir})

target_compile_definitions(${lf}
  PUBLIC
    LF_PANIC_SYM=${LF_PANIC_SYM}
  PRIVATE
    $<$<BOOL:${LF_PANIC}>:LF_PANIC>
)

set_target_properties(${lf} PROPERTIES
  C_STANDARD 11
  C_STANDARD_REQUIRED ON
  C_EXTENSIONS OFF
)
