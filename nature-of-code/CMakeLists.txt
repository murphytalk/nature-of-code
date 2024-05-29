set(target nc)

add_src_libs_ (src the_SRC)
add_executable(nc ${the_SRC})
target_link_libraries(nc PRIVATE raylib)

