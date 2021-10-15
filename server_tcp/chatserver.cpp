/**
 * Author: Arthur Buskes
 * GTID: 903492010
 * GT Email: abuskes3@gatech.edu
 */

#include "chatserver.h"

int main(int argc, char *argv[]) {
    /**
     * Socket values
     */
    int conn_socket; // Listening socket
    int client_socket; // currently, the ONLY new socket created for ONE connection
    int c;
    int * new_socket;
    struct sockaddr_in server;
    struct sockaddr_in client; // still need IP addr, port #
    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);

    /**
     * Command line args
     */
    uint16_t port = 0;
    char * passcode;
    int opt = 0;

    char * clientpass;

    /**
     * Code to process command line arguments
     */
    int long_index = 0;
    while ((opt = getopt_long_only(argc, argv, "s:o::p:", long_options, &long_index)) != -1) {
        switch (opt) {
            case 's':
                break;
            case 'o':
                port = atoi(optarg);
                break;
            case 'p':
                passcode = optarg;
                break;
        }
    }

    // Create the socket
    conn_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_socket == -1) {
        printf("Couldn't create socket");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // We bind our connection socket, conn_socket, to our server address, held in server
    if (bind(conn_socket,(struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed \n");
        return -1;
    }

    // This tells our connection socket to passively 'listen' for incoming connections
    listen(conn_socket, 3);
    printf("Server started on port %d. Accepting connections \n", port );

    // Accept incoming connections
    char cpass[20];
    memset(cpass, 0, 20);
    c = sizeof(struct sockaddr_in);
    while((client_socket = accept(conn_socket, (struct sockaddr *)&client, (socklen_t*)&c))){
        /**
         * Collect the password input by the client
         */
        recv(client_socket, cpass, 2000, 0);
        printf("Passcode: %s \n", cpass);

        printf("Connection accepted \n");

        /**
         * Handle the password
         */
        const char *pass_correct = "y";
        const char *pass_wrong = "n";

        if(strcmp(passcode, cpass) != 0) {
            write(client_socket, pass_wrong, strlen(pass_wrong));
            printf("Wrong pass \n");
        } else {
            write(client_socket, pass_correct, strlen(pass_correct));
            printf("Right pass \n");
        }


        /**
        pthread_t sniffer_thread;
        new_socket = malloc(1);
        *new_socket = client_socket;

        if( pthread_create(&sniffer_thread, NULL, connection_handler, (void*)new_sock) < 0){
            perror("Couldn't create thread");
            return -1;
        }
        pthread_join(sniffer_thread, NULL);
        */
    }

    if (client_socket<0) {
        perror("accept failed");
        return -1;
    }
    return 0;
}


void *connection_handler(void *socket_desc) {
    int sock = *(int*)socket_desc;
    int read_size;
    char *message;
    char client_message[2000];

    free(socket_desc);
    return 0;
}
