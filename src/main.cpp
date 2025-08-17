#include <iostream>
#include <exception>

#include "convert_file/convert_file.hpp"
#include "delay_parse/delay_parse.hpp"
#include "sort_tape/sort_tape.hpp"

static constexpr const char* kTmpInputTape = "../tmp/input_tape.txt";
static constexpr const char* kTmpOutputTape = "../tmp/output_tape.txt";

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "USAGE: <EXECUTABLE> <INPUT_FILE> <OUTPUT_FILE> "
                 "<MAX_RAM_USED> <CONFIG_FILE>\n";
    return EXIT_FAILURE;
  }
  int_tape::TapeDelays tape_delays = int_tape::delayParse(argv[argc - 1]);
  const char* output_file_name = argv[argc - 3];
  const char* input_file_name = argv[argc - 4];
  std::size_t max_ram_used = std::stoull(argv[argc - 2]);
  try {
    int_tape::encode(input_file_name, kTmpInputTape);
    int_tape::SortTape::sortTape(kTmpInputTape, kTmpOutputTape, max_ram_used,
                                 tape_delays);
    int_tape::decode(kTmpOutputTape, output_file_name);
  } catch (const std::exception& err) {
    std::cerr << err.what() << '\n';
    return EXIT_FAILURE;
  }
  return 0;
}
