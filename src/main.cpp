#include "convert_file/include/convert_file.hpp"
#include "delay_parse/include/delay_parse.hpp"
#include "sort_tape/include/sort_tape.hpp"

#include <iostream>
#include <exception>

static constexpr const char* kTmpInputTape = "../tmp/input_tape.txt";
static constexpr const char* kTmpOutputTape = "../tmp/output_tape.txt";

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr
            << "USAGE: <EXECUTABLE> <INPUT_FILE> <OUTPUT_FILE> <CONFIG_FILE>\n";
        return EXIT_FAILURE;
    }
    TapeDelays delays = delayParse(argv[argc - 1]);
    const char* output_file_name = argv[argc - 2];
    const char* input_file_name = argv[argc - 3];
    try {
        encode(input_file_name, kTmpInputTape);
        SortTape::sort(kTmpInputTape, kTmpOutputTape, delays);
        decode(kTmpOutputTape, output_file_name);
    } catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }
    return 0;
}
