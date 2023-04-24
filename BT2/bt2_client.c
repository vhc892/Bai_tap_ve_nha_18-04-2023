#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }
    //thiết lập địa chỉ máy chủ 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(9000);

    //kết nối đến server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }

    //nhập nội dung văn bản
    char buffer[1024];
    printf("Enter text: ");
    fgets(buffer, 1024, stdin);

    //gửi đến server
    if (send(sock, buffer, strlen(buffer), 0) == -1) {
        perror("send() failed");
        exit(EXIT_FAILURE);
    }

    close(sock);

    return 0;
}
