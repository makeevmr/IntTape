#include "src/ConvertFile/ConvertFile.h"
#include "src/DelayParse/DelayParse.h"
#include "src/SortTape/SortTape.h"

#define INPUT_TAPE "tmp/input_tape.txt"
#define OUTPUT_TAPE "tmp/output_tape.txt"

int main(int argc, char *argv[]) {
    // const char *input_tape_file = INPUT_TAPE;
    // const char *output_tape_file = OUTPUT_TAPE;
    // TapeDelays delays = delayParse("config/delay.txt");
    // const char *output_file = "output/output5.txt";
    // const char *input_file = "input/input5.txt";
    TapeDelays delays = delayParse(argv[argc - 1]);
    const char *output_file = argv[argc - 2];
    const char *input_file = argv[argc - 3];
    encode(input_file, INPUT_TAPE);
    SortTape::sort(INPUT_TAPE, OUTPUT_TAPE, delays);
    decode(OUTPUT_TAPE, output_file);
    return 0;
}
