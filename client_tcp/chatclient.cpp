/**
 * Author: Arthur Buskes
 * GTID: 903492010
 * GT Email: abuskes3@gatech.edu
 */
#include "chatclient.h"

int main(int argc, char *argv[]) {

    struct hostent *host_info;
    /**
     * Command line arguments
     */
    const char * host; // host is SERVER's IP address
    uint16_t port = 8888; // port is SERVER's listening
    char * username;
    char * passcode;
    int opt = 0;

    /**
     * Socket values
     */
    int socket_desc;
    struct sockaddr_in server;
    struct in_addr **addr_list;
    char host_ip[100];
    int i;

    /**
     * Code to process command line arguments
     */
    int long_index = 0;
    while ((opt = getopt_long_only(argc, argv, "", long_options, &long_index)) != -1) {
        switch (opt) {
            case 'j':
                break;
            case 'h':
                host = optarg;
                break;
            case 'o':
                port = atoi(optarg);
                break;
            case 'u':
                username = optarg;
                break;
            case 'p':
                passcode = optarg;
                break;
        }
    }

    /**
     * Get information about host
     */
    if ((host_info = gethostbyname(host)) == NULL) {
        herror("gethostbyname");
        printf("Host argument fail");
        return -1;
    }

    /**
     * Bringing out the IP address
     */
    //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr **) host_info->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(host_ip , inet_ntoa(*addr_list[i]) );
    }

    /**
     * Creating the socket
     */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Couldn't create socket");
    }
    server.sin_addr.s_addr = inet_addr(host_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    /**
     * Connection to server made
     */
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connect error");
        return -1;
    }
    write(socket_desc, passcode, strlen(passcode));

    char pass_response[2];
    memset(pass_response, 0, 2);
    read(socket_desc, pass_response, 100);

    if(strcmp(pass_response, "y") == 0) {
        printf("Connected to %s on port %d \n", host, port);
    } else {
        close(socket_desc);
        printf("Incorrect Passcode.");
    }

    return 0;
}
