#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "header/http-headers.h"
#include "header/type-header.h"

#define PORT 8080

/* some configurations */
const char *byeMsg = "HTTP/1.1 200 OK\r\nContent-Length: 5\r\n\r\n> bye";

int main(int argc, char *argv[]) {

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        fprintf(stderr, "socket failed\n");
        return 1;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        fprintf(stderr, "setsockopt failed\n");
        return 1;
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT); 

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        fprintf(stderr, "binding failed\n");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        fprintf(stderr, "listening failed\n");
        return 1;
    }


    /* Main Playground */
    while (1) {
        char buffer[1024] = "";
        char content[10240];

        printf("Accepting new connections\n");
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        /* if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            fprintf(stderr, "accepting failed\n");
            return 1;
        } */

        printf("New connection accepted\n");

        while (1) {
            char exit = 0;
            strncpy(buffer, " ", 1024);
            valread = read(new_socket, buffer, 1024);

            strcat(content, buffer);
            
            int bufferLen = strlen(buffer);
            
            // super duper test for "\r\n\r\n": end of http request
            for (int i = 0; i < bufferLen; i++) {
                if (buffer[i] == '\r') {
                    if (buffer[i + 1] == '\n') {
                        if (buffer[i + 2] == '\r') {
                            if (buffer[i + 3] == '\n') {
                                exit = 1;
                            }
                        }
                    }
                }
            }
            if (exit) {
                break;
            }
        }

        struct Request_HTTP_Header req;
        parse_http_req_header(content, &req);

        printf("url: %s\n", req.url);

        send(new_socket, byeMsg, strlen(byeMsg), 0);

        close(new_socket);
    }

    return 0;
}
