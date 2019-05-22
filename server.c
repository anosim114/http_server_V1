#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

/* some configurations */
const char *byeMsg = "> bye\n";


int main(int argc, char *argv[]) {

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = "";


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

    printf("Accepting new connections\n");

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        fprintf(stderr, "accepting failed\n");
        return 1;
    }

    printf("New connection accepted\n");

    while (1) {

        strncpy(buffer, " ", 1024);
        valread = read(new_socket, buffer, 1024);
        printf("%s", buffer);

        
    }

    send(new_socket, byeMsg, strlen(byeMsg), 0);

    return 0;
}
