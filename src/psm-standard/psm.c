#include <stdio.h>

#include <sys/_types/_ssize_t.h>
#include <sys/_types/_size_t.h>
#include "psm_header.h"

unsigned char compute_checksum(unsigned char *buffer, ssize_t message_length) {
    unsigned char checksum = 0;

    for (size_t i = 0; i < message_length; i++) {
        checksum ^= buffer[i];
    }

    return checksum;
}


int message_checksum_validate(struct PSM_Header *header, unsigned char *buffer, ssize_t message_length) {

    unsigned char checksum = compute_checksum(buffer, message_length);

    if (header->checksum != checksum) {
        fprintf(stderr, "received a message with an invalid checksum\n");
        return -1;
    }

    return 0;
}