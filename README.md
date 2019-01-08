## The Android toolbox source code

this directory mainly contains the source code of the `AOSP/system/core/toolbox`,
for example the android version of `ls.c`, `ps.c` program.

And here we trying to re-implement these program, and we need to compile these program
using `NDK`, not `gcc`, cause the `Android-ABI` is not compatible with `Linux-ABI`.

So we need to caution with the compile tool-chain.


----------------------------------------------------------

## 关于c++当中为什么不允许`static const double`的存在的讨论:

In C++03 we were only allowed to provide an in class initializer for `static member variables`
of `const integral` of `enumeration types`, in `C++11` we could initialize a static member 
of literal type in class using `constexpr`. This restriction was kept in C++11 for const 
variables mainly for compatibility will C++03 we can see this from closed issue 1826: 
`const floating-point` in constant expressions which says:

> A const integer initialized with a constant can be used in constant expressions, but a 
const floating point variable initialized with a constant cannot. This was intentional, 
to be compatible with C++03 while encouraging the consistent use of constexpr. Some people 
have found this distinction to be surprising, however.

CWG ended up closing this request as not a defect(NAD), basically saying:

> that programmers desiring floating point values to participate in constant expressions 
should use constexpr instead of const.

For reference N1804 the closest draft standard to C++03 publicly available in section 
9.4.2 [class.static.data] says:

> If a static data member is of const integral or const enumeration type, its 
declaration in the class definition can specify a constant-initializer which shall be an 
integral constant expression (5.19). In that case, the member can appear in integral constant expressions. The member shall still be defined in a namespace scope if it is used in the program and the namespace scope definition shall not contain an initializer.

and the draft C++11 standard section 9.4.2 [class.static.data] says:

> If a `non-volatile` const static data member is of integral or enumeration type, its 
declaration in the class definition can specify a `brace-or-equal-initializer` in which 
every initializer-clause that is an assignment expression is a constant expression 
(5.19). A static data member of literal type can be declared in the class definition 
with the constexpr specifier; if so, its declaration shall specify a 
brace-or-equal-initializer in which every initializer-clause that is an assignment-expression 
is a constant expression. [...]

this is pretty much the same in the draft C++14 standard.

 
-----------------------------------------------------------------