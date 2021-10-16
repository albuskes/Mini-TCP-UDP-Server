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

#define BUFFER_SIZE 2048
#define MAX_CLIENTS 20

/**
 * Struct to hold options for getopt_long_only
 */
static struct option long_options[] = {
        {"server_start", no_argument,      0,  's' },
        {"port", required_argument,       0, 'o' },
        {"passcode", required_argument, 0,  'p' },
};

/**
 * Client structure; used to hold info about client that successfully connects
 */
typedef struct {
    struct sockaddr_in address; // transport address: port, sin_addr.s_addr gives IP addr as long
    char user[20]; // user name
    int socket; // the socket connecting to client
    int uid; // assigned user id
} client_t;


/////// THREADS
void *client_handler(void *);

////// CLIENT QUEUE/TRACKING
int add_client(client_t **new_client);

///// COMMUNICATION W/CLIENT(S)
int check_pass(int *client_socket, char **passcode);
void send_message_all(char *message);
void send_message_others(char *message, int uid);