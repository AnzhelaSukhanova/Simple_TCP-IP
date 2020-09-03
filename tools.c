#include "tools.h"

extern int tap_fd;

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

void tap_write(struct frame *frame, unsigned int len) {
    write(tap_fd, frame, len);
}