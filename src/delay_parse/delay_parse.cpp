#include "include/delay_parse.hpp"

#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
#include <cassert>

#define assertm(exp, msg) assert((void(msg), exp))

[[nodiscard]] TapeDelays delayParse(const char* file_name) {
    TapeDelays delays;
    std::ifstream config_file(file_name, std::ios::binary);
    std::string line;
    assertm(config_file.is_open(), "Couldn't open config file");
    while (std::getline(config_file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
        uint32_t delay_number = static_cast<uint32_t>(std::stoul(tokens[1]));
        if (tokens[0] == "read:") {
            delays.read_ = delay_number;
        } else if (tokens[0] == "write:") {
            delays.write_ = delay_number;
        } else if (tokens[0] == "shift:") {
            delays.shift_ = delay_number;
        } else if (tokens[0] == "rewind:") {
            delays.rewind_ = delay_number;
        }
    }
    config_file.close();
    return delays;
}
