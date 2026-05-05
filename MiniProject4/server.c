#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// --- دالة معالجة الطلب ---
void* handle_request(void* arg) {
    int client_fd = *((int*)arg);
    free(arg);

    char buffer[2048] = {0};
    read(client_fd, buffer, 2048);

    char method[10], path[100], protocol[10];
    if (sscanf(buffer, "%s %s %s", method, path, protocol) < 3) {
        close(client_fd);
        return NULL;
    }

    // [Extension: Security]
    if (strstr(path, "..")) {
        char *error = "HTTP/1.0 403 Forbidden\r\n\r\nAccess Denied!";
        write(client_fd, error, strlen(error));
        close(client_fd);
        return NULL;
    }

    char *file_name = path + 1;
    if (strlen(file_name) == 0) file_name = "index.html";

    // [Extension: Logging]
    FILE *log_file = fopen("server.log", "a");
    if (log_file) {
        fprintf(log_file, "[LOG] Method: %s, Requested: %s\n", method, path);
        fclose(log_file);
    }

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        char *not_found = "HTTP/1.0 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
        write(client_fd, not_found, strlen(not_found));
        printf("[-] Not Found: %s\n", file_name);
    } else {
        char *header = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n";
        write(client_fd, header, strlen(header));

        char file_buffer[1024];
        int bytes_read;
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), file)) > 0) {
            write(client_fd, file_buffer, bytes_read);
        }
        fclose(file);
        printf("[+] Served: %s\n", file_name);
    }

    close(client_fd);
    return NULL;
}

// --- الدالة الرئيسية ---
int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    listen(server_fd, 10);
    printf("Project 4: Server is running on port 8080...\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addrlen = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
        
        if (client_fd < 0) continue;

        pthread_t thread_id;
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_fd;

        if (pthread_create(&thread_id, NULL, handle_request, (void*)new_sock) != 0) {
            perror("Thread failed");
            free(new_sock);
            close(client_fd);
        }
        pthread_detach(thread_id);
    }
    return 0;
}