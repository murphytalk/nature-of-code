set(target play)

add_src_libs_ (src the_SRC)
add_executable(play ${the_SRC})
target_link_libraries(play PRIVATE raylib)

