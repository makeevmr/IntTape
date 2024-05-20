#include "DelayParse.h"

TapeDelays delayParse(const char *file_name) {
    TapeDelays delays;
    std::ifstream config_file(file_name, std::ios::binary);
    std::string line;
    if (config_file.is_open()) {
        while (std::getline(config_file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{}};
            unsigned int delay_number = std::stoul(tokens[1]);
            if (tokens[0] == "read:") {
                delays.read = delay_number;
            } else if (tokens[0] == "write:") {
                delays.write = delay_number;
            } else if (tokens[0] == "shift:") {
                delays.shift = delay_number;
            } else if (tokens[0] == "rewind:") {
                delays.rewind = delay_number;
            }
        }
    }
    config_file.close();
    return delays;
}
