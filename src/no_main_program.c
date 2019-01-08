// 如何执行没有main()函数的程序
#include <stdio.h>
#include <stdlib.h>

// the entry point of the whole program
int nomain_entry();

void _start() {
    // calling entry point
    nomain_entry();
    exit(0);
}

int nomain_entry() {
    puts("we are executed inside nomain_entry()");
    return 0;
}
// 对于本程序，如果我们直接使用gcc -o nomain_entry no_main_program.c
// 进行编译的话，会报错:
// /tmp/cc3VxqFx.o: In function `_start':
// no_main_program.c:(.text+0x0): multiple definition of `_start'
// /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o:(.text+0x0): first defined here
// /usr/lib/gcc/x86_64-linux-gnu/5/../../../x86_64-linux-gnu/crt1.o: In function `_start':
// (.text+0x20): undefined reference to `main'
// collect2: error: ld returned 1 exit status
// (严格意义上来说，不是编译错误，而是链接错误,因为程序本身并没有错误)
// 所以我们需要修改编译选项:
// gcc no_main_program.c -nostartfiles
// 然后输出为a.out
// 然后执行./a.out就可以了
// 或者也可以：gcc -nostartfiles -o no_main no_main_program.c
// 然后执行./no_main就可以