include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(pybind11)
pybind11_add_module(pyrelays src/pyrelays.cpp)
target_link_libraries(pyrelays PRIVATE relays-${API_VERSION})

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
    OUTPUT_VARIABLE PYTHON_DIST_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
install(TARGETS pyrelays LIBRARY DESTINATION ${PYTHON_DIST_PACKAGES})
