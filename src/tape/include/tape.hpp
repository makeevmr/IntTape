#ifndef INT_TAPE_SRC_TAPE
#define INT_TAPE_SRC_TAPE

#include "../../tape_delays/include/tape_delays.hpp"

#include <cstddef>

// contains unsigned int numbers where each number is a sequence of 4 unsigned
// char
class Tape {
public:
    // If the new_file_size is 0 then create a tape of size corresponding to the
    // input file, otherwise clear the contents of the file and create tape of
    // size corresponding new_file_size
    Tape(const char* file_name, const TapeDelays& delays,
         std::size_t new_file_size = 0);

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
    int fd_;
    unsigned char* buffer_;
    std::size_t buffer_ind_;
    std::size_t file_ind_;
    std::size_t file_size_;
    std::size_t curr_buffer_size_;
    std::size_t max_buffer_size_;
    TapeDelays delays_;
    static std::size_t page_size;

    static void handleError(const char* msg);
};

#endif  // INT_TAPE_SRC_TAPE
