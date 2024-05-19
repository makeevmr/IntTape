#include <algorithm>
#include <fstream>
#include <iostream>

// for mmap:
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
    unsigned frontier_size = 2;
    const unsigned URL_MAX_SIZE = 100;

    int fd = open("test.txt", O_RDWR);
    loff_t size = frontier_size * URL_MAX_SIZE;
    ftruncate(fd, size);
    char *map = (char *)mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(map, "hello there");
    msync(map, size, MS_SYNC);
    munmap(map, size);
    close(fd);
}