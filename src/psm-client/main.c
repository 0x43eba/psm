#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../psm-standard/psm_header.h"
#include "../psm-standard/psm.h"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    unsigned char message[] = "Hello from client!";
    size_t message_len = strlen((char *)message) + 1;


    struct PSM_Header header;
    header.magic = PSM_MAGIC;
    header.version = CURRENT_VERSION;
    header.message_length = message_len;

    unsigned char *csum_message = malloc(message_len);
    memcopy(csum_message, message, message_len);

    unsigned char checksum = compute_checksum(csum_message, message_len);
    header.checksum = checksum;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PSM_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    size_t total_size = sizeof(struct PSM_Header) + message_len;
    unsigned char *final_message = malloc(total_size);
    if (final_message == NULL) {
        perror("Memory allocation failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    memcpy(final_message, &header, sizeof(struct PSM_Header));
    memcpy(final_message + sizeof(struct PSM_Header), message, message_len);

    if (sendto(sockfd, final_message, total_size, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("sendto failed");
        free(final_message);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to server: %s\n", message);

    free(final_message);
    close(sockfd);

    return 0;
}
