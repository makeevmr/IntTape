#ifndef INT_TAPE_SRC_TAPE
#define INT_TAPE_SRC_TAPE

#include "tape_delays/tape_delays.hpp"

#include <cstddef>
#include <optional>

// contains uint32_t numbers where each number is a sequence of 4 uint8_t
// symbols
class Tape {
public:
    // Creates a tape associated with file_name file.
    // Changes file size to contain new_file_size elements if new_file_size was
    // provided
    Tape(const char* file_name, const TapeDelays& tape_delays,
         const std::optional<std::size_t> new_file_size = std::nullopt);

    ~Tape();

    void shiftLeft();

    void shiftRight();

    void rewindLeft(std::size_t rewind_length);

    void rewindRight(std::size_t rewind_length);

    [[nodiscard]] uint32_t read() const;

    void write(const uint32_t new_num);

    [[nodiscard]] std::size_t getSize() const noexcept;

private:
    const int fd_;
    std::size_t tape_ind_;
    std::size_t tape_size_;
    const TapeDelays tape_delays_;

    static constexpr int kShiftSize = 4;
};

#endif  // INT_TAPE_SRC_TAPE
