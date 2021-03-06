#include "tools.h"

int tap_fd;

void print_hex(char *str, int len)
{
    for (int i = 0; i < len; i ++) {
        if (i % 8 == 0) printf("\n");
        printf("%02x ", (unsigned char)str[i]);
    }
    printf("\n");
}

uint16_t check_sum(void *addr, int count)
{
    uint32_t sum = 0;
    uint16_t *ptr = (uint16_t *)addr;

    while (count > 1) {
        sum += htons(*ptr);
        ++ptr;
        count -= 2;
    }
    if (count > 0)
        sum += htons(*(uint8_t *) ptr);
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);

    return ~sum;
}

void set_tap_fd(int fd) {
    tap_fd = fd;
}

int tap_write(struct frame *frame, unsigned int len) {
    return write(tap_fd, frame, len);
}

int tap_read(struct frame *frame, unsigned int len) {
    return read(tap_fd, frame, len);
}

int broadcast(uint8_t *mac)
{
    for (int i = 0; i < 6; i++){
        if (mac[i] != 0xff) return 0;
    }
    return 1;
}

int multicast(uint8_t *mac) //not completed
{
    if (mac[0] != 0x01 || mac[1] != 0x00 || mac[2] != 0x5e) return 0;
    return 1;
}