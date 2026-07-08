#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int read_line(int fd, char *buf, size_t size)
{
	int i = 0;
	char c;

	while (i < size - 1) {
		int n = read(fd, &c, 1);

		if (n <= 0) {
			break;
		}

		if (c == '\r') {
			continue;
		}

		if (c == '\n') {
			break;
		}

		buf[i] = c;
		i++;
	}

	buf[i] = '\0';

	return i;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[1024];
    char filename[256];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("HTTP server listening on port 12345...\n");

    
    while (1) {
    	client_fd = accept(server_fd, NULL, NULL);

    
    	while (1) {
        	int n = read_line(client_fd, buffer, sizeof(buffer));

        	if (n <= 0) {
            		break;
        	}

		if (buffer[0] == '\0') {
	    		break;
		}

        	printf("Line: %s\n", buffer);

		if (strncmp(buffer, "GET ", 4) == 0) {
            		sscanf(buffer, "GET %255s", filename);
	    		printf("File name: %s\n", filename);
       		}
    	}

	const char *response =
    		"HTTP/1.1 404 Not Found\r\n"
    		"Content-Type: text/plain\r\n"
    		"Content-Length: 13\r\n"
    		"\r\n"
    		"404 Not Found";

	write(client_fd, response, strlen(response));       	
    	close(client_fd);
    }

    return 0;
}


