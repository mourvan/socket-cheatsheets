#include "common.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    die_if(fd == -1, "failed to create socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    int err = inet_aton("127.0.0.1", &addr.sin_addr);
    die_if(err == 0, "failed to convert address");

    err = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    die_if(err == -1, "failed to connect");

    char buf[] = "hello!";
    int bytes = write(fd, buf, sizeof(buf));
    die_if(bytes == -1, "failed to write");

    printf("wrote %d bytes\n", bytes);

    close(fd);
}

