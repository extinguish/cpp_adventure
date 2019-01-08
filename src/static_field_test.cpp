/// investigate the static field inside cpp environment
#include <iostream>

/// 主要用于分析为什么C++的class当中不允许出现static const non-integral value
/// 即我们在class当中不能定义static const double,但是可以定义static const int
class IntegralStaticField {
public:
    IntegralStaticField();

    ~IntegralStaticField();

    // the following is OK
    static const int val_int = 100;

    /// the following will not compile
    /// 但是我们可以通过constexpr来进行修复
    static const double val_double = 2300.0;

    /// 此时就可以编译通过了
    /// 但是constexpr是c++11引入的特性
    /// 如果我们在c++03当中的话，想要在IntegralStaticField当中
    /// 使用static const double的话，就需要通过修改编译优化选项来实现了
    static constexpr double val_double1 = 2330.0;

    // 以下是具体的原因分析:
    /// The problem is that with an integer, the compiler usually doesn't
    /// have to ever create a memory address for the constant. It doesn't
    /// exist at runtime, and every use of it gets inlined into the
    /// surrounding code. It can still decide to give it a memory
    /// location - if its address is ever taken (or if it's passed by const
    /// reference to a function), that it must. In order to give it an
    /// address, it needs to be defined in some translation unit. And in
    /// that case, you need to separate the declaration from the definition, since
    /// otherwise it would get defined in multiple translation units.
    ////////////////////////////////////////////////////////////
    /// Using g++ with no optimization (-O0), it automatically inlines constant
    /// integer variables but not constant double values. At higher optimization
    /// levels (e.g. -O1), it inlines constant doubles. Thus, the following code
    /// compiles at -O1 but NOT at -O0:

    /// 如果我们使用以下的方式进行编译的话
    /// g++  static_field_test.cpp -O1 -o static_test
    /// 那么static const double val_double = 2300.0就是可编译通过的
    /// 但是我们添加上c++11的话，就不行了，即:
    /// g++  static_field_test.cpp -std=c++11 -O1  -o static_test
    /// 是无法编译通过的
    /// 即static const double val_double = 2300.0;
    /// 和static constexpr double val_double1 = 2330.0;
    /// 是无法共存的

    /// For maximal portability, you should declare your constants in header files and
    /// define them once in some source file. With no optimization, this will not hurt
    /// performance, since you're not optimizing anyways, but with optimizations enabled,
    /// this can hurt performance, since the compiler can no longer inline those constants
    /// into other source files, unless you enable "whole program optimization".
};


int main() {

}