#pragma once

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define die_if(Condition, Message...) \
    if (Condition) { \
        printf(Message); \
        printf(": errno = %d\n", errno); \
        exit(1); \
    }

