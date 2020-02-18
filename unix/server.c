#include "common.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define backlog 32
#define max_buf_size 512

int main()
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    die_if(fd == -1, "failed to create socket");

    struct sockaddr_un *addr = build_address(path);

    int err = bind(fd, (struct sockaddr*)addr, sizeof(*addr));
    die_if(err == -1, "failed to assign name to socket");

    err = listen(fd, backlog);
    die_if(err == -1, "failed to mark socket as passive");

    while (1) {
        puts("listening for connections...");

        struct sockaddr_un client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int client_fd = accept(fd, (struct sockaddr*)&client_addr,
                &client_addr_len);
        die_if(client_fd == -1, "failed to accept connection");

        while (1) {
            char buf[max_buf_size];
            int bytes = read(client_fd, buf, sizeof(buf));
            die_if(bytes == -1, "failed to read");

            if (bytes == 0)
                break;

            printf("received message: '%s'\n", buf);
        }

        close(client_fd);
    }

    /* this isn't reached, but left for reference for good programs */
    free(addr);
    close(fd);
    unlink(path);
}

