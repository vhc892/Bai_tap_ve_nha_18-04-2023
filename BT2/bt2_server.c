#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



int main() {
    //tạo socket
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    //thiết lập địa chỉ máy chủ 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9000);

    //gán socket với địa chỉ và cổng 
    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    //lắng nghe kết nối từ client
    if (listen(listen_sock, 3) == -1) {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connections...\n");
    //chấp nhận kết nối từ client 
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_sock == -1) {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    //đọc nội dung vb từ client
    char buffer[1024];
    memset(buffer, 0, 1024);

    if (recv(client_sock, buffer, 1024, 0) == -1) {
        perror("recv() failed");
        exit(EXIT_FAILURE);
    }
    //đếm xâu 0123456789
    int count = 0;
    char *p = buffer;
    while ((p = strstr(p, "0123456789")) != NULL) {
        count++;
        p += strlen("0123456789");
    }

    printf("Number of occurrences of '0123456789': %d\n", count);

    close(client_sock);
    close(listen_sock);

    return 0;
}
