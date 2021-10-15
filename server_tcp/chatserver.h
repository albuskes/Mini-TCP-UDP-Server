/**
 * Author: Arthur Buskes
 * GTID: 903492010
 * GT Email: abuskes3@gatech.edu
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#pragma once

// The options for the getopt_long_only
static struct option long_options[] = {
        {"server_start", no_argument,      0,  's' },
        {"port", required_argument,       0, 'o' },
        {"passcode", required_argument, 0,  'p' },
};

void *connection_handler(void *);
