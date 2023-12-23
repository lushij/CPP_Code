#include "lab.h"

void printServerInfo(unsigned short port) {
    printf("═══════ Server ═══════\n");
    printf("Server IP is 127.0.0.1\n");
    printf("Listening on port %hu\n", port);
    printf("══════════════════════\n");
}

void sendMessage(char *message) {
    Packet packet;
    memset(&packet, 0, sizeof(packet));

    packet.header.size = strlen(message);
    packet.header.isLast = true;
    strcpy((char *)packet.data, message);

    if (sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&clientInfo, sizeof(struct sockaddr_in)) == -1) {
        perror("sendto()");
        exit(EXIT_FAILURE);
    }
}

void recvCommand(char *command) {
    Packet packet;
    memset(&packet, 0, sizeof(packet));

    if (recvfrom(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&clientInfo, (socklen_t *)&addrlen) == -1) {
        perror("recvfrom()");
        exit(EXIT_FAILURE);
    }

    strncpy(command, (char *)packet.data, packet.header.size);
}

FILE *getFile(char *filename) {
    FILE *fd = fopen(filename, "rb");
    return fd;
}

size_t getFileSize(FILE *fd) {
    fseek(fd, 0, SEEK_END);
    size_t size = ftell(fd);
    return size;
}

void sendFile(FILE *fd) {
    Packet send, recv;
    memset(&send, 0, sizeof(send));
    memset(&recv, 0, sizeof(recv));
    //获取文件大小
    size_t filesize = getFileSize(fd);
    size_t current = 0;//当前已经发送的大小

    while (current < filesize) {
        fseek(fd, current, SEEK_SET);  // 设置文件位置
        //读取信息存到数据包里
        size_t bytesRead = fread(send.data, 1, sizeof(send.data), fd);
        send.header.size = bytesRead;
        //printf("%s\n",send.data);
        if (current + bytesRead >= filesize) {
            send.header.isLast = true;
        }

         //发送EQ值 
        printf("Send SEQ = %u\n", send.header.seq);
        if (sendto(sockfd, &send, sizeof(send), 0, (struct sockaddr *)&clientInfo, addrlen) == -1) {
            perror("sendto()");
            exit(EXIT_FAILURE);
        }
        // 递增序列号
        ++send.header.seq;
        struct pollfd poll_fd;
        poll_fd.fd = sockfd;
        poll_fd.events = POLLIN;

        if (poll(&poll_fd, 1, TIMEOUT) == 0) {
            printf("Timeout! Resend!\n");
            --send.header.seq;
            continue;
        }

        if (recvfrom(sockfd, &recv, sizeof(recv), 0, (struct sockaddr *)&clientInfo, &addrlen) == -1) {
            perror("recvfrom()");
            exit(EXIT_FAILURE);
        }
        printf("Received ACK = %u\n", recv.header.ack);
        current += bytesRead;
    }
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    unsigned short port = atoi(argv[1]);

    setServerInfo(INADDR_ANY, port);
    printServerInfo(port);
    setClientInfo();
    createSocket();
    bindSocket();

    FILE *fd;
    char command[96];
    char message[64];

    while (true) {
        memset(command, '\0', sizeof(command));
        memset(message, '\0', sizeof(message));

        printf("Server is waiting...\n");
        recvCommand(command);

        printf("Processing command...\n");
        char *str = strtok(command, " ");

        if (strcmp(str, "download") == 0) {
            str = strtok(NULL, "");
            printf("Filename is %s\n", str);

            if ((fd = getFile(str))) {
                snprintf(message, sizeof(message) - 1, "FILE_SIZE=%zu", getFileSize(fd));
                sendMessage(message);

                printf("══════ Sending ═══════\n");
                sendFile(fd);
                printf("══════════════════════\n");

                fclose(fd);
                fd = NULL;
            } else {
                printf("File does not exist\n");
                sendMessage("NOT_FOUND");
            }
            continue;
        }
        printf("Invalid command\n");
    }
    return 0;
}
