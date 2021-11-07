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
add_executable(trick1 trick_test_1.cpp)
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
        src/aosp_libutils/include/Errors.h
        src/aosp_libutils/include/macros.h
        src/aosp_libutils/include/Log.h
        src/aosp_libutils/include/VectorImpl.h
        src/aosp_libutils/include/KeyedVector.h
        src/aosp_libutils/include/Vector.h
        src/aosp_libutils/include/AndroidThreads.h
        src/aosp_libutils/include/Thread.h
        src/aosp_libutils/include/RefBase.h
        src/aosp_libutils/include/StrongPointer.h
        src/aosp_libutils/StrongPointer.cpp
        src/aosp_libutils/SharedBuffer.h
        src/aosp_libutils/SharedBuffer.cpp
        src/aosp_libutils/include/
        src/aosp_libutils/Timers.cpp
        src/aosp_libutils/Looper.cpp
        src/aosp_libutils/RefBase.cpp
        src/aosp_libutils/Threads.cpp
        src/aosp_libutils/VectorImpl.cpp
        src/aosp_libutils_test/LooperTest.cpp)

add_executable(simple_looper_test
        src/simple_looper/Epoll.h
        src/simple_looper/Epoll.cpp
        src/simple_looper/SimpleLooper.cpp)

add_executable(timer_example
        src/timers/Timers.h
        src/timers/Timers.cpp
        src/timers/TimerExample.cpp)

add_executable(std_func_test
        src/cpp_functional/StdFunctionalTest.cpp)

add_executable(sys_time
        src/system_misc/DateNTime.cpp)

add_executable(char_encode_test src/simple_char_encode/ChineseCharEncode.cpp)

add_executable(binary_file_op src/io_operation/BinaryFileOp.cpp)

add_executable(nest_cls src/devil_detect/NestCls.cpp)

# the AOSP SharedPointer test
add_executable(shared_ptr_test
        src/test_sp/log.h
        src/test_sp/StrongPointer.h
        src/test_sp/Atomic-x86.h
        src/test_sp/RefBase.h
        src/test_sp/RefBase.cpp
        src/test_sp/test/apple.h
        src/test_sp/test/main.cpp
        )

add_executable(check_even_or_odd src/competive_tricks/CheckEvenOrOdd.cpp)

#include_directories(src/boost_dev)
#add_subdirectory(src/boost_dev)

add_executable(class_test src/class_internal/ClassInternalFeature.cpp)

add_executable(simple_cal src/SimpleCal.cpp)

add_subdirectory(src/json_test)

add_executable(map_op src/stl/map_op.cpp)


add_executable(variable_arg src/VariableArguments.cpp)

add_executable(simple_arr src/detail_devil/SimpleArrTest.cpp)

add_executable(vector_op src/detail_devil/ListOp.cpp)

#add_executable(timeout_handler src/TimeoutHandler.cpp)

add_executable(signal_timeout_handler src/TimeoutHandlerBySignal.cpp)
target_link_libraries(signal_timeout_handler -lrt)

#add_executable(terminal_db
#        src/ky_store/util/byte_array.h
#        src/ky_store/util/config_parser.h
#
#        src/kv_store/algo/coding.h
#        src/kv_store/algo/coding.cpp
#        src/kv_store/TerminalDB.cpp
#        src/kv_store/TerminalDB.h)

add_executable(simple_kv src/simple_kv/SimpleKVTest.cpp)

add_executable(gbk_encoder_test src/GBKEncoder2.cpp)
add_executable(int2str src/Int2Str.cpp)

#add_executable(fileobserver_test
#        src/fileobserver/FileObserverUser.cpp
#        src/fileobserver/TerminalFileObserver.h
#        src/fileobserver/TerminalFileObserver.cpp)

#include_directories(/home/guoshichao/work_profile/ky_haisi_base_libs/build/include)
#target_link_libraries(fileobserver_test /home/guoshichao/work_profile/ky_haisi_base_libs/build/lib/libkyruntime.so)

add_executable(list_op_1 src/ListOp.cpp)

add_executable(time_range src/detail_devil/TimeRange.cpp)

add_executable(simple_tcp_server src/SimpleTcpServer.c)

add_executable(queue_test
        src/c_queue/list.h
        src/c_queue/Queue.h
        src/c_queue/Queue.cpp
        src/c_queue/queue_test.cpp)

add_executable(time_stamp_op src/time_stamp_op.cpp)

add_executable(list_op_test list_op.cpp)

add_executable(dir_op src/dir_op.cpp)

#add_executable(circle_buf
#        src/CircleBufTest.cpp
#        src/CircleBuf.cpp)

#add_executable(simple_binder_test
#        binder_adventure/client/SimpleBinderClient.cpp
#        binder_adventure/server/SimpleServer.cpp
#        binder_adventure/server/DeathNotifier.cpp
#        binder_adventure/server/BnSimpleFunc.cpp
#        binder_adventure/client/BpSimpleFunc.cpp
#        )
#
#set(BUILD_DIRS /media/guoshichao/04167E5E167E50A2/a_work_profile/build)
#
#set(LINK_PATH ${BUILD_DIRS}/lib)
#
#include_directories(${BUILD_DIRS}/include
#        ${BUILD_DIRS}/include/systemserver
#        ${BUILD_DIRS}/include/settingd)
#
#link_directories(${LINK_PATH})


add_executable(struct_cpp_op src/stl/struct_list.cpp)

add_executable(list_op_2 src/ListOp2.cpp)

include_directories(native_looper/include)

#add_library(native_looper native_looper/src/AMessage.cpp
#        native_looper/src/ALooper.cpp
#        native_looper/src/Timers.cpp
#        native_looper/src/SharedBuffer.cpp
#        native_looper/src/String8.cpp
#        native_looper/src/String16.cpp
#        native_looper/src/Unicode.cpp
#        native_looper/src/Thread.cpp
#        native_looper/src/sched_policy.c
#        native_looper/src/AStringUtils.cpp)
#
#add_executable(handler_test native_looper/test/NativeLooperTest.cpp)
#
#link_libraries(handle_test native_looper)

add_executable(ref_test src/RefTest.cpp)

add_executable(len_test src/detail_devil/LenTest.cpp)

add_executable(vector_test src/detail_devil/VectorTest.cpp)

add_executable(parse_test src/DataParser.cpp)

add_executable(dive_overriding src/DiveOverriding.cpp)

#add_executable(static_trick src/StaticMemberFuncOp.cpp)

add_executable(hex_convert src/hex_convert.cpp)

add_executable(format_ip_address src/FormatIPAddress.cpp)

add_executable(split_arr src/SplitArr.cpp)

add_executable(dev_op src/DevOp.cpp)

add_executable(loc_ref src/LocRef.cpp)

add_executable(file_read_test src/ReadFileTest.cpp)


add_executable(state_manage_test
        src/callback_del/ManageTest.cpp
        src/callback_del/Manager.h
        src/callback_del/Manager.cpp
        src/callback_del/Child.h
        src/callback_del/Child.cpp)


add_executable(virtual_test src/VirtualDestructor.cpp)

add_executable(timeout_handler src/QueueWaitTimeoutHandler.cpp)

add_executable(circle_buf_test src/JT1078CircleBuffer.cpp)

add_executable(test_size src/test_size.cpp)

add_executable(list_op3 src/ListOp3.cpp)

add_executable(size_test src/size_test.cpp)

add_executable(realloc_test src/ReallocTest.cpp)

add_executable(cls_template_test src/ClsTemplateTest.cpp)

add_executable(stest src/SimpleTest.cpp)

add_executable(io_multiplex_test src/IOMultiplex.cpp)

add_executable(dump_u_char_arr src/DumpUCharArr.cpp)

add_executable(scanf_test src/ScanfTest.cpp)

add_executable(rtp_send_test src/rtp_send_test.cpp src/RtpSend.cpp)

add_executable(split_str src/split_str.cpp)

add_executable(std_str_op src/std_str_op.cpp)

add_executable(process_manage src/linux_process/process_manage.cpp)

add_executable(fork_buf_test src/linux_process/fork_and_buffer.cpp)

add_executable(sizeof_impl src/linux_process/size_of_impl.cpp)

add_executable(func_test src/cpp_functional/function.cpp)

add_executable(bind_test src/cpp_functional/bind_func.cpp)










