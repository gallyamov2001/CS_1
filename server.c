#include "head.h"



void my_remove(){
    if (remove (ServerFIFO) == -1){
        printf("Remove error");
        exit(-1);
    }
    else{
    	printf("Done");
    }
    exit(0);
}

int main() {
    int server_fd, client_fd;

    umask(0);
    if (mkfifo(ServerFIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(-1);
    }

    server_fd = Open_fd(ServerFIFO, O_RDWR);

    signal(SIGINT, my_remove);

    while (1) {

        char client_fifo[64];
        struct MY_REQUEST req;

        if (read(server_fd, &req, sizeof(struct MY_REQUEST)) < 0) {
            perror("Incorrect request");
            continue;
        }

        sprintf(client_fifo, "%d.fifo", req.pid);

        if ((client_fd = open(client_fifo, O_WRONLY)) < 0) {
            perror("Couldn't contact with some of the clients");
            continue;
        }


        int file_in;

        if ((file_in = open(req.filename, O_RDONLY)) < 0) {
            perror("Couldn't open the file for client.");
            continue;
        }

        char buf[PAGE_SIZE] = "";
        int RD;

        while (1) {

            if((RD = read(file_in, buf, PAGE_SIZE)) < 0) {
                perror("Couln't read the file.");
            }

            if(!RD) break;

            if (write(client_fd, buf, RD) < 0) {
                perror("Couldn't send to the client content of the file.");
                break;
            }

        }

        Close_fd(client_fd);
        Close_fd(file_in);

    }
    Close_fd(server_fd);
}
