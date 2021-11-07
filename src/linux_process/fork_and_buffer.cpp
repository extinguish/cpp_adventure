#include<unistd.h>
#include<stdio.h>

// the following program demonstrate the buffer between linux process
// which need to be caution!!!

int global_val = 6;
char buf[] = "a write to stdout\n"; // 需要注意的是这里的字符串 --> 结尾有一个换行符 --> 有没有这个换行符很重要 -->


int main(int argc, char **argv) {
    int val;
    pid_t pid;

    val = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        printf("fatal state error!!! fail to write the buf to the STDOUT\n");
        return -1;
    }
    printf("before fork --> \n"); // we do not flush stdout --> 
    if ((pid = fork()) < 0) {
        printf("fatal state error!!! fail to fork a new process --> \n");
        return -1;
    } else if (pid == 0) {
        // we are in child process now --> 
        global_val++;
        val++;
    } else {
        // we are in parent process
        sleep(2);
    }

    printf("pid = %ld, global_val = %d, val = %d\n", (long) getpid(), global_val, val);

    return 0;
}

// 关于上面程序的解释
// 如果我们是直接在终端上运行上面的程序的话，输出的内容是：
// a write to stdout
// before fork --> 
// pid = 17187, global_val = 7, val = 89
// pid = 17186, global_val = 6, val = 88
// 如果我们是把输出重定向到一个文件当中的话,即./fork_buf_test > test.out
// 然后我们此时去查看test.out文件的内容的话，会看到:
// a write to stdout
// before fork --> 
// pid = 17218, global_val = 7, val = 89
// before fork --> 
// pid = 17217, global_val = 6, val = 88

// 相对于直接在终端上输出的方式有了变化 --> 即before fork --> 打印了两次 -->
// 第一个例子之所以只打印了一次，是因为当我们在终端上运行的时候，终端上对缓冲的管理是"行缓冲" --> 
// 所以运行一次，就直接把标准IO库的缓冲区刷新了 --> 
// 但是当我们把结果重定向到文件当中的时候，就不是这样了 --> 这个缓冲区会保留着 --> 直接复制给子进程了 
// 这个例子就完美的说明了标准IO库的缓冲管理和进程管理的区别方式 -->