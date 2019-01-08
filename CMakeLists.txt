cmake_minimum_required(VERSION 3.12)
project(AndroidInternalTools C)

set(CMAKE_C_STANDARD 99)

add_executable(AndroidInternalTools main.c
        src/fake_ls.c src/fake_id.c src/uptime.c
        src/simple_writer.c src/simple_reader.c
        src/copy_constructor.cpp
        src/rtti_test.cpp
        src/private_virtual_func.cpp
        src/private_virtual_fun_2.cpp
        src/no_main_program.c
        src/private_virtual_inline_func.cpp
        src/static_field_evaluate.cpp
        src/virtual_constructor.cpp
        src/virtual_copy_constructor.cpp
        src/algo/dynamic_programming.cpp src/stl/list_operation.cpp
        src/stl/nested_list_operation.cpp
        src/stl/array_algorithm.cpp
        src/io_operation/basic_file_op.cpp
        src/stl/copy_vector.cpp
        src/memory_manage/unique_ptr_adventure.cpp
        trick_test.cpp
        src/cpp_17/string_view_adventure.cpp
        src/StrVec.cpp src/static_field_test.cpp)