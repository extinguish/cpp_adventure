#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int fd = open("/home/guoshichao/scguo_cache/tmp", O_RDWR | O_CREAT, 0664);
    if (fd == -1) {
        printf("fail to open the tmp file for mmap\n caused by %s\n", strerror(errno));
        return -1;
    }

    // 关于ftruncate的作用:
    // The  truncate()  and  ftruncate()  functions  cause the regular file named by path or
    // referenced by fd to be truncated to a size of precisely length bytes.
    //
    // If the file previously was larger than this size, the extra data is lost.  If the
    // file previously was shorter, it is extended, and the extended part reads as null
    // bytes ('\0').
    //
    // The file offset is not changed.
    //
    // If the size changed, then the st_ctime and st_mtime fields (respectively, time of last
    // status change and time of last modification; see stat(2)) for the file are updated,
    // and the set-user-ID and set-group-ID mode bits may be cleared.
    //
    // With ftruncate(), the file must be open for writing; with truncate(), the file must
    // be writable.
    ftruncate(fd, 4096);
    int len = lseek(fd, 0, SEEK_END);
    // 关于mmap在man page上的解释:
    // mmap()  creates  a  new mapping in the virtual address space of the calling process.
    // The starting address for the new mapping is specified in addr.
    // The length argument specifies the length of the mapping.
    //
    // If addr is NULL, then the kernel chooses the address at which to create the mapping;
    // this is the most portable method of creating a new mapping.
    // If addr is not NULL, then the kernel takes it as a hint about where to place the
    // mapping; on Linux, the mapping will be created at a nearby page boundary.  The address
    // of the new mapping is returned as the result of the call.
    //
    // The contents of a file mapping (as opposed to an anonymous mapping; see MAP_ANONYMOUS
    // below), are initialized using length bytes starting at  offset offset  in  the  file
    // (or  other  object)  referred  to  by  the  file  descriptor  fd.   offset must be
    // a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE).
    // 关于PROT参数(protect)的含义的解释:
    //  The prot argument describes the desired memory protection of the mapping (and must
    // not conflict with the open mode  of  the  file).   It  is  either
    // PROT_NONE or the bitwise OR of one or more of the following flags:
    // PROT_EXEC  Pages may be executed.
    // PROT_READ  Pages may be read.
    // PROT_WRITE Pages may be written.
    // PROT_NONE  Pages may not be accessed.
    // 关于MAP_标记的含义的解释:
    // MAP_SHARED
    // Share this mapping.  Updates to the mapping are visible to other processes that map
    // this file, and are  carried  through  to  the  underlying file.  (To precisely
    // control when updates are carried through to the underlying file requires the use of
    // msync(2).)
//    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        printf("fail to mmap to %d\n caused by %s \n", fd, strerror(errno));
        return -1;
    }

    int i = 0;
    char *tmp = (char *) ptr;
    for (;;) {
        // write data to the share memory field
        char str[1024] = {0};
        sprintf(str, "This the line of %d", i);
        strcpy(tmp, str);
        printf("write data of %s \n", tmp);
        // 关于sleep的作用
        // Make the process sleep for SECONDS seconds, or until a signal arrives
        //   and is not ignored.  The function returns the number of seconds less
        //   than SECONDS which it actually slept (thus zero if it slept the full time).
        //   If a signal handler does a `longjmp' or modifies the handling of the
        //   SIGALRM signal while inside `sleep' call, the handling of the SIGALRM
        //   signal afterwards is undefined.  There is no return value to indicate
        //   error, but if `sleep' returns SECONDS, it probably didn't work.
        sleep(1);
        if (++i >= 100) {
            printf("we have reach the largest value we need to write data in %d \n", i);
            // 停止写入
            break;
        }
    }
    // 释放mmap
    int ret = munmap(ptr, len);
    if (ret == -1) {
        printf("fail to unmap the shared memory caused by %s\n", strerror(errno));
        return -1;
    }

    close(fd);
    return 0;
}