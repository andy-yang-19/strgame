#pragma once

#include <stdio.h>
#include <stdlib.h>

#define handle_err(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

