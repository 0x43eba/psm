#ifndef PSM_H

#define PSM_H

#define PSM_PORT 2025
#define PSM_MAX_MESSAGE_SIZE 1024 * 64

#define CURRENT_VERSION 0x01
#define PSM_MAX_VERSION 0x01

#define PSM_MAGIC 0x43

int message_checksum(struct PSM_Header *header, char *buffer, ssize_t message_length);

#endif