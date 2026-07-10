#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>


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

char* load_file(const char *path, size_t *size)
{
	FILE *fp = fopen(path, "rb");

	if (fp == NULL) {
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	*size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *data = malloc(*size);

	if (data == NULL) {
		fclose(fp);
		return NULL;
	}

	fread(data, 1, *size, fp);
	fclose(fp);

	return data;
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
	
	char path[512];
	size_t file_size;

	snprintf(path, sizeof(path), "html%s", filename);

	char *content = load_file(path, &file_size);

	if (content == NULL) {
		const char *response =
    			"HTTP/1.1 404 Not Found\r\n"
    			"Content-Type: text/plain\r\n"
    			"Content-Length: 13\r\n"
    			"\r\n"
    			"404 Not Found";
	
			write(client_fd, response, strlen(response));
	} else {
		char header[256];

		snprintf(header, sizeof(header),
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: text/html\r\n"
				"Content-Length: %zu\r\n"
				"\r\n",
				file_size);

		write(client_fd, header, strlen(header));
		write(client_fd, content, file_size);	


		free(content);
	}

    	close(client_fd);
    
    }

    return 0;
}


