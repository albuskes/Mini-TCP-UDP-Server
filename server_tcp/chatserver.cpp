/**
 * Author: Arthur Buskes
 * GTID: 903492010
 * GT Email: abuskes3@gatech.edu
 */

#include "chatserver.h"

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int active_clients = 0;
int id_gen = 0;

int main(int argc, char *argv[]) {
    /**
     * Socket values
     */
    int conn_socket; // Listening socket
    int client_socket; // Most recently created client socket identifier
    struct sockaddr_in server;
    struct sockaddr_in client; // still need IP addr, port #
    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);
    char cuser[20];
    memset(cuser, 0, 20);
    pthread_t sniffer_thread;

    /**
     * Command line args
     */
    uint16_t port = 0;
    char * passcode;
    int opt = 0;

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

    /**
     * Set up listening socket
     */
    conn_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_socket == -1) {
        printf("Couldn't create socket");
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // We bind our connection socket, conn_socket, to our server address, held in server
    if (bind(conn_socket,(struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Bind failed \n");
        return -1;
    }
    listen(conn_socket, 3);
    printf("Server started on port %d. Accepting connections \n", port );


    while(1){
        socklen_t client_length = sizeof(client);
        if((client_socket = accept(conn_socket, (struct sockaddr *)&client, &client_length)) > 0 ) {
            printf("Client accept \n");

            if (active_clients + 1 > MAX_CLIENTS) {
                printf("Max clients reached. Could not connect \n");
                close(client_socket);
                continue;
            }

            if (check_pass(&client_socket, &passcode) == 1) {
                //printf("Right pass... creating client \n");
            } else {
                //printf("Wrong pass... disconnecting client \n");
                close(client_socket);
                continue;
            }
            printf("Checked passes\n");

            // if here, password was right. Create a client version
            client_t * new_client = (client_t *) malloc(sizeof(client));
            printf(" client malloced\n");
            recv(client_socket, cuser,20, 0);
            printf(" username recieved, %s\n", cuser);
            new_client->socket = client_socket;
            printf(" socket\n");
            new_client->address = client;
            printf(" address\n");
            new_client->uid = id_gen++;
            printf("uid \n");
            strcpy(new_client->user, cuser);
            printf(" user\n");
            add_client(&new_client);

            printf("Added client \n");

            if( pthread_create(&sniffer_thread, NULL, &client_handler, (void *)new_client) != 0) {
                perror("Couldn't create thread");
                return -1;
            }
            pthread_join(sniffer_thread, NULL);
            printf("threads joined \n");

            // every time a recieve is called, it reads through the buffer UP TO the amount specified. If you have
            // multiple amounts of tdata in that buffer, it will read thorugh all of them, even if written via diff
            // write calls
        } else{
            perror("accept failed");
            break;
        }
    }
    return 0;
}

/**
 * Sends a message to ALL clients
 * @param message the message to send
 */
void send_message_all(char* message) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++ ) {
        if(clients[i]){
            if(write(clients[i]->socket, message, strlen(message)) < 0) {
                perror("Failed to send message");
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Sends a message to everyone EXCEPT the client with the chosen id
 * @param message message to send
 * @param uid uid of client not to send message to
 */
void send_message_others(char* message, int uid) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < MAX_CLIENTS; i++ ) {
        if(clients[i] && clients[i]->uid != uid){
            if(write(clients[i]->socket, message, strlen(message)) < 0) {
                perror("Failed to send message");
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Checks if client sent correct password
 * @param client_socket The socket connecting to client
 * @param passcode The passcode client entered
 * @return 0 if wrong, 1 if right
 */
int check_pass(int *client_socket, char **passcode) {
    char cpass[20];
    memset(cpass, 0, 20);
    recv(*client_socket, cpass, 20, 0);

    /**
     * Handle the password
     */
    const char *pass_correct = "y";
    const char *pass_wrong = "n";

    if (strcmp(*passcode, cpass) != 0) {
        write(*client_socket, pass_wrong, strlen(pass_wrong));
        return 0;
    } else {
        write(*client_socket, pass_correct, strlen(pass_correct));
        return 1;
    }
}

/**
 *
 * @param new_client
 * @return
 */
int add_client(client_t **new_client) {
    pthread_mutex_lock(&clients_mutex);
    for(int i = 0; i < MAX_CLIENTS; i++) {
        if(!clients[i]) {
            clients[i] = *new_client;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

/**
 *
 * @param socket_desc
 * @return
 */
void *client_handler(void *arg) {
    printf("Got into client handler! \n");
    char buff[1000];
    memset(buff, 0, 1000);
    char join_message[40];
    memset(join_message, 0, 40);
    char standard[] = " joined the chatroom";
    client_t *new_client = (client_t *)arg;
    active_clients++;

    /**
     * Handle sending intro message
     */
    strcpy(join_message, new_client->user);
    strcat(join_message, standard);
    printf("%s \n", join_message);
    send_message_others(join_message, new_client->uid);
    printf("Send message to others \n");
    return 0;
}
