#include <fstream>
#include <random>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "USAGE: <EXECUTABLE> <TOTAL_NUMBERS> <MIN_NUMBER> "
                     "<MAX_NUMBER> <FILE_NAME>\n";
        return EXIT_FAILURE;
    }
    const int total_numbers = std::atoi(argv[argc - 4]);
    const int min_number = std::atoi(argv[argc - 3]);
    const int max_number = std::atoi(argv[argc - 2]);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(
        static_cast<uint64_t>(min_number), static_cast<uint64_t>(max_number));
    std::ofstream generated_file(argv[argc - 1], std::ios::binary);
    for (int _ = 0; _ < total_numbers; ++_) {
        generated_file << dist(rng) << '\n';
    }
    return 0;
}