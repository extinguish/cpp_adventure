## 实现`C++`层的`handler-looper`

主要实现理念是基于`frameworks/av/media/libstagefright/foundation`当中包含的`AHandler`来实现的。
但是考虑到`AHandler`本身和`AOSP`绑定的比较紧密，例如用到了`RefBase`,`StrongPointer`,以及`Vector`,`List`等`AOSP`内部的基础实现。
将这些`基础类型`移植出来，需要点时间，而且会分散我们分析`AHandler`的实现过程。

因此我们只是借鉴`AHandler`的实现思路，来单独实现我们这里自己版本的`AHandler`.

> 在实现过程当中，我们会尽量使用`STL`当中提供的标准组件.