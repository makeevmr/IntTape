#ifndef INT_TAPE_TAPE
#define INT_TAPE_TAPE

#include <algorithm>
#include <iostream>

// for mmap:
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// TODO add delays
class Tape {
public:
    Tape(const char *file_name);

    ~Tape();

    void moveLeft();

    void moveRight();

    [[nodiscard]] unsigned int read() const noexcept;

    void write(unsigned int new_number) noexcept;

private:
    int fd;
    unsigned char *buffer;
    std::size_t buffer_ind;
    std::size_t file_ind;
    std::size_t file_size;
    std::size_t curr_buffer_size;
    std::size_t max_buffer_size;
    static std::size_t page_size;

    static void handle_error(const char *msg);
};

#endif // INT_TAPE_TAPE
