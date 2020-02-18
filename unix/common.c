#include "common.h"
#include <sys/socket.h>

struct sockaddr_un* build_address(const char *path)
{
    struct sockaddr_un *addr = malloc(sizeof(struct sockaddr_un));
    die_if(addr == NULL, "failed to alloc addr");

    memset(addr, 0, sizeof(*addr));

    addr->sun_family = AF_UNIX;

    die_if(strlen(path) > sizeof(addr->sun_path), "domain name too long");

    strncpy(addr->sun_path, path, sizeof(addr->sun_path) - 1);

    return addr;
}

