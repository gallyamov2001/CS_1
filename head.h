
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>

#define ServerFIFO "file.fifo"

#define PAGE_SIZE 4096


struct MY_REQUEST {
    pid_t pid;
    char filename[256];

};

void Close_fd(int fd) {
    if (close(fd) == -1) {
        perror("Client couldn't close the file");
        exit(-1);
    }
}

int Open_fd(const char *name, int flags) {

    int fd;
    if ((fd = open(name, flags)) < 0) {
        printf("Client couldn't open %s \n", name);
        exit(-1);
    }
    return fd;
}
#define ServerFIFO "file.fifo"

#define PAGE_SIZE 4096
