#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Echo server listening on port 12345...\n");

    client_fd = accept(server_fd, NULL, NULL);

    while (1) {
        int n = read(client_fd, buffer, sizeof(buffer) - 1);

        if (n <= 0) {
            break;
        }

        printf("Received: %s\n", buffer);

	if (strcmp(buffer, "exit") == 0) {
            break;
        }

        write(client_fd, buffer, strlen(buffer));
        write(client_fd, "\n", 1);
    }

    close(client_fd);
    close(server_fd);

    return 0;
}


