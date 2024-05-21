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
    // int fd = open("test.txt", O_WRONLY);
    std::size_t page_size = sysconf(_SC_PAGE_SIZE);
    std::size_t file_size = 11;
    std::size_t size = 11;
    // std::size_t size = page_size;
    // ftruncate(fd, file_size);
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        std::cout << "ERROR\n fstat()";
    }
    file_size = sb.st_size;
    char *map = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0u);
    // char *map = (char *)mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0u);
    if (map == MAP_FAILED) {
        std::cout << "ERROR\n";
    }
    // std::cout << "complete1\n";
    strcpy(map, "HELLO THERE");
    // strcpy(map, "hello there");
    // std::cout << "complete2\n";
    msync(map, size, MS_SYNC);
    // std::cout << "complete3\n";
    // munmap(map, size);
    // std::cout << sysconf(_SC_PAGE_SIZE) << '\n';
    // map = (char *)mmap(NULL, size + 3, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_size);
    // // map = (char *)mmap(NULL, size + 3, PROT_WRITE, MAP_SHARED, fd, 0u);
    // strcpy(map, "hello there");
    // msync(map, size, MS_SYNC);
    // std::cout << "complete4\n";
    // msync(map, size, MS_SYNC);
    munmap(map, size);
    close(fd);
}