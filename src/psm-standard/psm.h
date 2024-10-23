#ifndef PSM_H

#define PSM_H

#define PSM_PORT 2025
#define PSM_MAX_MESSAGE_SIZE 1024 * 64

#define CURRENT_VERSION 0x01
#define PSM_MAX_VERSION 0x01

#define PSM_MAGIC 0x43

struct PSM_Header {
    unsigned short magic;
    unsigned char version;
    unsigned long message_length;
    unsigned char checksum;
};

#endif