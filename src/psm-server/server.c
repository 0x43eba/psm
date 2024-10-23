#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../psm-standard/psm.h"

int socket_listener() {
    int success = socket(AF_INET, SOCK_DGRAM, 0);
    if (success < 0) {
        perror("failed to create a socket");
        return -1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PSM_PORT);

    int bind_success = bind(success, (struct sockaddr *)&address, sizeof(address));

    if (bind_success < 0) {
        perror("failed to bind the socket");
        return -1;
    }

    while (1) {
        printf("Waiting for a message...\n");
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof(client_address);

        char buffer[PSM_MAX_MESSAGE_SIZE];
        ssize_t message_length = recvfrom(success, buffer, PSM_MAX_MESSAGE_SIZE, 0, (struct sockaddr *)&client_address, &client_address_length);

        if (message_length < 0) {
            perror("failed to receive a message");
            return -1;
        }

        struct PSM_Header *header = (struct PSM_Header *)buffer;

        if (header->magic != PSM_MAGIC) {
            fprintf(stderr, "received a message with an invalid magic number\n");
            continue;
        }

        if (header->version > PSM_MAX_VERSION) {
            fprintf(stderr, "received a message with an invalid version number\n");
            continue;
        }

        if (header->message_length != message_length - sizeof(struct PSM_Header)) {
            fprintf(stderr, "received a message with an invalid message length\n");
            continue;
        }

        unsigned char checksum = 0;

        for (size_t i = 0; i < message_length; i++) {
            checksum ^= buffer[i];
        }

        if (header->checksum != checksum) {
            fprintf(stderr, "received a message with an invalid checksum\n");
            continue;
        }

        printf("received a message: %s\n", buffer + sizeof(struct PSM_Header));
    }
    return 0;
}