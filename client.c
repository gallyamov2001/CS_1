#include "head.h"



int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Incorrect arguments!\n");
        exit(-1);
    }

    struct MY_REQUEST req;

    req.pid = getpid();
    strcpy(req.filename, argv[1]);


    umask(0);
    char client_fifo[64];
    sprintf(client_fifo, "%d.fifo", getpid());


    if (mkfifo(client_fifo, 0666) == -1 && errno != EEXIST) {
        perror("Server couldn't make FIFO");
        exit(-1);
    }


    int server_fd = Open_fd(ServerFIFO, O_WRONLY);


    write(server_fd, &req, sizeof(struct MY_REQUEST));


    int client_fd = Open_fd(client_fifo, O_RDONLY);


    char buf[PAGE_SIZE] = "";
    int RD = PAGE_SIZE;


    while (1) {

        if ((RD = read(client_fd, buf, PAGE_SIZE)) < 0) {
            perror("Client couldn't read from FIFO");
            exit(-1);
        }
        if (!RD) break;
        if ((write(1, buf, RD)) < 0) {
            perror("Client couldn't write correctly");
            exit(-1);
        }

    }

    Close_fd(client_fd);
    Close_fd(server_fd);
}