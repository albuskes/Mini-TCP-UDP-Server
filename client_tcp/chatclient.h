/**
 * Author: Arthur Buskes
 * GTID: 903492010
 * GT Email: abuskes3@gatech.edu
 */

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include <ctype.h>
#include<string.h>	//strlen
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <netdb.h>

#pragma once

// The options for the getopt_long_only
static struct option long_options[] = {
        {"join", no_argument,      0,  'j' },
        {"host", required_argument,       0, 'h' },
        {"port", required_argument, 0,  'o' },
        {"username", required_argument, 0,  'u' },
        {"passcode", required_argument, 0,  'p' }
};