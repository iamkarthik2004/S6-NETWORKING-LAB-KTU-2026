#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char message[1024], buffer[1024];

    while (1) {
        // Send message to server
        printf("Client: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        if (strcmp(message, "exit\n") == 0)
            break;

        // Receive reply from server
        memset(buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "exit\n") == 0)
            break;

        printf("Server: %s", buffer);
    }

    close(client_socket);
    return 0;
}
