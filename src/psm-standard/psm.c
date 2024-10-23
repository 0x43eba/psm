#include <stdio.h>

#include <sys/_types/_ssize_t.h>
#include <sys/_types/_size_t.h>
#include "psm_header.h"

int message_checksum(struct PSM_Header *header, char *buffer, ssize_t message_length) {
    unsigned char checksum = 0;

    for (size_t i = 0; i < message_length; i++) {
        checksum ^= buffer[i];
    }

    if (header->checksum != checksum) {
        fprintf(stderr, "received a message with an invalid checksum\n");
        return -1;
    }

    return 0;
}