set(target walker)

add_src_libs_ (src the_SRC)
add_executable(walker ${the_SRC})
target_link_libraries(walker PRIVATE sfml-graphics)
target_compile_features(walker PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET walker 
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:walker>
        VERBATIM)
endif()
