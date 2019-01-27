cmake_minimum_required(VERSION 3.12)
project(CppAdventure)

# set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(CppAdventure main.c)


add_executable(fake_ls src/fake_ls.c)
add_executable(fake_id src/fake_id.c)
# add_executable(uptime src/uptime.c)
add_executable(simple_write src/simple_writer.c)
add_executable(simple_read src/simple_reader.c)
add_executable(copy_constructor src/copy_constructor.cpp)
add_executable(rtti_test src/rtti_test.cpp)
add_executable(private_virtual_fun_1 src/private_virtual_func.cpp)
add_executable(private_virtual_fun_2 src/private_virtual_fun_2.cpp)
# the no_main_program need to use the gcc tool to compile
# add_executable(no_main_program src/no_main_program.c)
add_executable(virtual_inline_func src/private_virtual_inline_func.cpp)
add_executable(static_field_eval src/static_field_evaluate.cpp)
add_executable(virtual_constructor src/virtual_constructor.cpp)
add_executable(virtual_copy_constructor src/virtual_copy_constructor.cpp)
add_executable(dynamic_programming src/algo/dynamic_programming.cpp)
add_executable(list_op src/stl/list_operation.cpp)
add_executable(nest_list_op src/stl/nested_list_operation.cpp)
add_executable(arr_algo_test src/stl/array_algorithm.cpp)
add_executable(file_io_test src/io_operation/basic_file_op.cpp)
add_executable(copy_vec_test src/stl/copy_vector.cpp)
add_executable(uniq_pointer_test src/memory_manage/unique_ptr/unique_ptr_adventure.cpp)
add_executable(trick trick_test.cpp)
add_executable(str_view_test src/cpp_17/string_view_adventure.cpp)
add_executable(str_vec_test src/StrVec.cpp)
add_executable(static_field_test src/static_field_test.cpp)
add_executable(polyphism_test src/oop_design/PolyphismTricks.cpp)

add_executable(interface_test
        src/oop_design/interface/InterfaceTest.cpp
        src/oop_design/interface/IClientDataListener.h
        src/oop_design/interface/ResponseHandler.cpp
        src/oop_design/interface/ResponseHandler.h
        src/Log.h)


add_executable(type_convert src/detail_devil/TypeConversion.cpp
        src/Log.h)

add_executable(bcd_convertor src/BCDConverter.cpp)

add_executable(concurrent_test
        src/concurrent/adasplus_concurrent_util/log.h
        src/concurrent/adasplus_concurrent_util/list.h
        src/concurrent/adasplus_concurrent_util/CmdThread.cpp
        src/concurrent/adasplus_concurrent_util/CmdThread.h
        src/concurrent/adasplus_concurrent_util/Mutex.h
        src/concurrent/adasplus_concurrent_util/Queue.h
        src/concurrent/adasplus_concurrent_util/Queue.cpp
        src/concurrent/adasplus_concurrent_util/Thread.cpp
        src/concurrent/adasplus_concurrent_util/Thread.h
        src/concurrent/adasplus_concurrent_util/sem.h
        src/concurrent/adasplus_concurrent_util/ConcurrentTest.cpp)


add_executable(looper_test
        src/aosp_libutils_test/TestHelper.h
        src/aosp_libutils/include/macros.h
        src/aosp_libutils/include/Log.h
        src/aosp_libutils/include/VectorImpl.h
        src/aosp_libutils/include/KeyedVector.h
        src/aosp_libutils/include/Vector.h
        src/aosp_libutils/include/AndroidThreads.h
        src/aosp_libutils/include/Thread.h
        src/aosp_libutils/include/RefBase.h
        src/aosp_libutils/include/Looper.h
        src/aosp_libutils/Looper.cpp
        src/aosp_libutils/RefBase.cpp
        src/aosp_libutils/Threads.cpp
        src/aosp_libutils/VectorImpl.cpp
        src/aosp_libutils_test/LooperTest.cpp)

add_executable(simple_looper_test
        src/simple_looper/Epoll.h
        src/simple_looper/Epoll.cpp
        src/simple_looper/SimpleLooper.cpp)

#add_executable(beta_looper_test
#        src/beta_looper/Timers.h
#        src/beta_looper/Timers.cpp
#        src/beta_looper/Looper.h)

