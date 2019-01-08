//
// Created by guoshichao on 18-10-11.
//
/// about the std::unique_ptr usage
/// std::unique_ptr的原型:
/// template< class T, class Deleter = std::default_delete<T>>
/// class unique_ptr;
/// 以上是第一种原型定义，我们可以看到我们使用unique_ptr时，除了基本的指定
/// 我们要引用的类型外，还可以指定我们释放内存的具体实现方式(当然了，基本上90%的
/// 使用场合当中只是指定了unique_ptr引用的类型)
/// std::unique_ptr的第二种原型:
/// template <class T, class Deleter>
/// class unique_ptr<T[], Deleter>;

