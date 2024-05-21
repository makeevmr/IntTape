#include "src/ConvertFile/ConvertFile.h"
#include "src/DelayParse/DelayParse.h"
#include "src/SortTape/SortTape.h"

#define INPUT_TAPE "tmp/input_tape.txt"
#define OUTPUT_TAPE "tmp/output_tape.txt"

int main(int argc, char *argv[]) {
    TapeDelays delays = delayParse(argv[argc - 1]);
    const char *output_file = argv[argc - 2];
    const char *input_file = argv[argc - 3];
    encode(input_file, INPUT_TAPE);
    SortTape::sort(INPUT_TAPE, OUTPUT_TAPE, delays);
    decode(OUTPUT_TAPE, output_file);
    return 0;
}
