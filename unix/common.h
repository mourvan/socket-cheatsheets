#pragma once

#include "../util.h"
#include <sys/un.h>

static const char path[] = "/tmp/fgsfds";

struct sockaddr_un* build_address(const char *path);

