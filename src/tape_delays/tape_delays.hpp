#ifndef INT_TAPE_SRC_TAPE_DELAYS_TAPE_DELAYS_HPP_
#define INT_TAPE_SRC_TAPE_DELAYS_TAPE_DELAYS_HPP_

#include <cstdint>

namespace int_tape {

struct TapeDelays {
  uint32_t read_;
  uint32_t write_;
  uint32_t shift_;
};

}  // namespace int_tape

#endif  // INT_TAPE_SRC_TAPE_DELAYS_TAPE_DELAYS_HPP_
