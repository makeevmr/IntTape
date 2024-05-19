#include <algorithm>
#include <fstream>
#include <iostream>

// for mmap:
#include <cstring>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void handle_error(const char *msg) {
    perror(msg);
    exit(255);
}

int main() {
    int fd = open("data_mmap.txt", O_RDWR);
    if (fd == -1) {
        handle_error("Couldn't open file");
    }
    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        handle_error("Error during mmap() call occurred");
    }
    const std::size_t file_size = sb.st_size;
    const std::size_t page_size = sysconf(_SC_PAGE_SIZE) << '\n';
    const std::size_t max_buffer_size = 2 * page_size;
    std::size_t curr_buffer_size = std::min(file_size, max_buffer_size);
    char *buffer = static_cast<char *>(
        mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0U));
    std::ifstream operations_file("operations.txt", std::ios::binary);
    std::ofstream result_file("result_mmap.txt", std::ios::binary);
    std::size_t file_ind = 0;
    std::size_t buffer_ind = 0;
    char operation = 0;
    if (operations_file.is_open() && result_file.is_open()) {
        while (operations_file.peek() != EOF) {
            operations_file.get(operation);
            switch (operation) {
            case '-':
                if (buffer_ind > 0) {
                    --buffer_ind;
                    --file_ind;
                } else if (file_ind > 0) {
                    msync((void *)buffer, curr_buffer_size, MS_SYNC);
                    curr_buffer_size = max_buffer_size;
                    buffer = static_cast<char *>(
                        mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0U));
                    if (buffer == MAP_FAILED) {
                        handle_error("Error during mmap() call occurred");
                    }
                    --file_ind;
                    buffer_ind = page_size - 1;
                }
                break;
            case '+':
                if (buffer_ind < curr_buffer_size - 1) {
                    ++buffer_ind;
                    ++file_ind;
                } else if (file_ind < file_size - 1) {
                    msync((void *)buffer, curr_buffer_size, MS_SYNC);
                    ++file_ind;
                    curr_buffer_size =
                        std::min((max_buffer_size / 2) + file_size - file_ind, max_buffer_size);
                    buffer = static_cast<char *>(
                        mmap(NULL, curr_buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0U));
                    if (buffer == MAP_FAILED) {
                        handle_error("Error during mmap() call occurred");
                    }
                    buffer_ind = page_size;
                }
                break;
            case 'r':
                result_file << buffer[buffer_ind];
                break;
            case 'w':
                operations_file.get(buffer[buffer_ind]);
                break;
            }
        }
    }
    msync((void *)buffer, curr_buffer_size, MS_SYNC);
    munmap((void *)buffer, curr_buffer_size);
    close(fd);
    result_file.close();
    operations_file.close();
}