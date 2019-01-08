// corresponding to the simple_writer.c
// this program will be using to read data from the /home/guoshichao/scguo_cache/tmp
// memory map file
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void) {

    int fd = open("/home/guoshichao/scguo_cache/tmp", O_RDWR | O_CREAT, 0664);
    if (fd == -1) {
        printf("fail to open the shared memory file %s \n", strerror(errno));
        return -1;
    }

    ftruncate(fd, 4096);
    int len = lseek(fd, 0, SEEK_END);
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        printf("fail to map the file to the shared memory : %s", strerror(errno));
        return -1;
    }
    char *tmp = (char *) ptr;
    int i = 1;
    for (;;) {
        // read data from the tmp memory file
        char str[1024] = {0};
        strcpy(str, tmp);
        printf("the data we read out are %s \n", str);
        tmp += strlen(str);
        sleep(1);
        if (++i >= 100) {
            break;
        }
    }

    int ret = munmap(ptr, len);
    if (ret == -1) {
        printf("fail to unmap the memory %s", strerror(errno));
        return -1;
    }

    close(fd);
    return 0;
}