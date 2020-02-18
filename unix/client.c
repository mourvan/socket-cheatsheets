#include "common.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    die_if(fd == -1, "failed to create socket");

    struct sockaddr_un *addr = build_address(path);

    int err = connect(fd, (struct sockaddr*)addr, sizeof(*addr));
    die_if(err == -1, "failed to connect");

    char buf[] = "hello!";
    int bytes = write(fd, buf, sizeof(buf));
    die_if(bytes == -1, "failed to write");

    printf("wrote %d bytes\n", bytes);

    close(fd);
    free(addr);
}

