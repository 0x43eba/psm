struct PSM_Header {
    unsigned short magic;
    unsigned char version;
    unsigned long message_length;
    unsigned char checksum;  
}