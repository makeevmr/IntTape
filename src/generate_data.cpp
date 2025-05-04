#include <fstream>
#include <random>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "USAGE: <EXECUTABLE> <TOTAL_NUMBERS> <MIN_NUMBER> "
                     "<MAX_NUMBER> <FILE_NAME>\n";
        return EXIT_FAILURE;
    }
    const uint32_t total_numbers =
        static_cast<uint32_t>(std::stoull(argv[argc - 4]));
    const uint32_t min_number =
        static_cast<uint32_t>(std::stoull(argv[argc - 3]));
    const uint32_t max_number =
        static_cast<uint32_t>(std::stoull(argv[argc - 2]));
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min_number,
                                                                  max_number);
    std::ofstream generated_file(argv[argc - 1], std::ios::binary);
    if (!generated_file.is_open()) {
        throw std::runtime_error("Couldn't open file");
    }
    for (uint32_t _ = 0; _ < total_numbers; ++_) {
        generated_file << dist(rng) << '\n';
    }
    generated_file.close();
    return 0;
}