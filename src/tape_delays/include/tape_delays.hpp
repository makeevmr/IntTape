#ifndef INT_TAPE_SRC_TAPE_DELAYS
#define INT_TAPE_SRC_TAPE_DELAYS

#include <cstdint>

struct TapeDelays {
    uint32_t read_;
    uint32_t write_;
    uint32_t shift_;
    uint32_t rewind_;
};

#endif  // INT_TAPE_SRC_TAPE_DELAYS
