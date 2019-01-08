## 关于`unique_ptr`的一些介绍

`unique_ptr`的原型

```cpp
template< class T, class Deleter = std::default_delete<T>> 
class unique_ptr;
```

```cpp
template <class T,class Deleter> 
class unique_ptr<T[], Deleter>;
```

`std::unique_ptr` 是通过指针占有并管理另一对象，并在 `unique_ptr` 离开作用域时释放该对象的智能指针。

在下列两者之一发生时用关联的删除器释放对象：

- 销毁了管理的 `unique_ptr` 对象
- 通过 `operator=` 或 `reset()` 赋值另一指针给管理的 unique_ptr 对象。 

通过调用 `get_deleter()(ptr)` ，用潜在为用户提供的删除器释放对象。默认删除器用 delete 运算符，它销毁对象并解分配内存。

`unique_ptr` 亦可以不占有对象，该情况下称它为空 (empty)。

`std::unique_ptr` 有两个版本：

- 1) 管理个对象（例如以 new 分配）
- 2) 管理动态分配的对象数组（例如以 new[] 分配）

类满足可移动构造 (MoveConstructible) 和可移动赋值 (MoveAssignable) 的要求，
但不满足可复制构造 (CopyConstructible) 或可复制赋值 (CopyAssignable) 的要求。

 