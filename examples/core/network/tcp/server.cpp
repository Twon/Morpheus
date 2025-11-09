#include <iostream>
#include <cstring>
#include <unistd.h>         // for close()
#include <arpa/inet.h>      // for sockaddr_in, inet_addr()

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket (IPv4, TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    // Allow reuse of the address/port
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    address.sin_port = htons(8080);

    // Bind socket to port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Listen for connections (max backlog 3)
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return 1;
    }

    std::cout << "Server listening on port 8080...\n";

    // Accept a client connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        return 1;
    }

    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer));
    std::cout << "Received: " << buffer << std::endl;

    const char *reply = "Hello from server!";
    send(client_fd, reply, strlen(reply), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}