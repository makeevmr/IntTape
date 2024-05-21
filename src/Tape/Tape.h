#ifndef INT_TAPE_TAPE
#define INT_TAPE_TAPE

#include "../TapeDelays/TapeDelays.h"
#include <algorithm>
#include <iostream>

// for mmap:
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <thread>

// contains unsigned int numbers where each number is a sequence of 4 unsigned char
class Tape {
public:
    // If the new_file_size is 0 then create a tape of size corresponding to the input file,
    // otherwise clear the contents of the file and create tape of size corresponding new_file_size
    Tape(const char *file_name, const TapeDelays &delays, std::size_t new_file_size = 0);

    ~Tape();

    void shiftLeft();

    // return true if the tape is successfully shifted
    bool shiftRight();

    void rewindLeft(unsigned int rewind_length);

    void rewindRight(unsigned int rewind_length);

    [[nodiscard]] unsigned int read() const noexcept;

    void write(unsigned int new_number) noexcept;

    [[nodiscard]] std::size_t getSize() const noexcept;

    [[nodiscard]] bool isEnd() const noexcept;

    [[nodiscard]] static std::size_t getPageFileSize() noexcept;

private:
    int fd;
    unsigned char *buffer;
    std::size_t buffer_ind;
    std::size_t file_ind;
    std::size_t file_size;
    std::size_t curr_buffer_size;
    std::size_t max_buffer_size;
    TapeDelays delays;
    static std::size_t page_size;

    static void handle_error(const char *msg);
};

#endif // INT_TAPE_TAPE
