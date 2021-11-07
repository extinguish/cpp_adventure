#include <sys/types.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char **argv) {
    pid_t first_pid;
    pid_t second_pid;
    first_pid = fork();

    second_pid = fork();

    std::cout << "current process id :" << getpid() << " first_pid ==> " << first_pid << " second_pid ==> " << second_pid << std::endl;

    return 0;
}


