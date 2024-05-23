set(target walker)

add_src_libs_ (src the_SRC)
add_executable(walker ${the_SRC})
target_link_libraries(walker PRIVATE raylib)

