#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("Server listening...\n");

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    char buffer[1024], reply[1024];

    while (1) {
        // Receive from client
        memset(buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0)
            break;

        printf("Client: %s", buffer);

        // Send reply to client
        printf("Server: ");
        fgets(reply, sizeof(reply), stdin);
        send(client_socket, reply, strlen(reply), 0);

        if (strcmp(reply, "exit\n") == 0)
            break;
    }

    close(client_socket);
    close(server_socket);
    return 0;
}

